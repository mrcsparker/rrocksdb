#include <iostream>
#include <Rcpp.h>
#include <map>
#include "OptionsWrapper.h"
#include "DBWrapper.h"

DBWrapper::DBWrapper(std::string dbName, OptionsWrapper& options) {
  std::vector<std::string> tmpCf;
  auto s = DB::ListColumnFamilies(options.getOptions(), dbName, &tmpCf);

  if (!s.ok()) {
    open(dbName, options);
    return;
  }

  std::vector<ColumnFamilyDescriptor> descriptors;

  for (auto const& cf : tmpCf) {
    descriptors.push_back(ColumnFamilyDescriptor(cf, ColumnFamilyOptions()));
  }

  std::vector<ColumnFamilyHandle *> handles;
  s = DB::Open(options.getOptions(), dbName, descriptors, &handles, &db_);

  for (const auto& handle : handles) {
    columnFamilies_[handle->GetName()] = handle;
  }

  if (!s.ok()) {
    throw std::runtime_error(s.ToString());
  }
}

DBWrapper::DBWrapper(std::string dbName) {
  auto options = OptionsWrapper::defaultOptions();
  open(dbName, options);
}

Status DBWrapper::createColumnFamily(std::string name) {

  if (getColumnFamilyHandle_(name) != nullptr) {
    return Status();
  }

  ColumnFamilyHandle* cf;
  auto s = db_->CreateColumnFamily(ColumnFamilyOptions(), name, &cf);

  columnFamilies_[name] = cf;

  return s;
}

Status DBWrapper::open(std::string dbName, OptionsWrapper& options) {
  auto s = DB::Open(options.getOptions(), dbName, &db_);
  if (!s.ok()) {
    throw std::runtime_error(s.ToString());
  }
  return s;
}

std::string DBWrapper::put(std::string key, std::string value) {
  auto s = db_->Put(WriteOptions(), key, value);
  assert(s.ok());
  return value;
}

std::string DBWrapper::putWithColumnFamily(std::string columnFamilyName, std::string key, std::string value) {
  auto cfh = getColumnFamilyHandle_(columnFamilyName);
  if (cfh == nullptr) {
    throw std::runtime_error("Can not find ColumnFamily: " + columnFamilyName);
  }

  auto s = db_->Put(WriteOptions(), cfh, key, value);
  assert(s.ok());
  return value;
}

Status DBWrapper::remove(std::string key) {
  return db_->Delete(WriteOptions(), key);
}

Status DBWrapper::removeWithColumnFamily(std::string columnFamilyName, std::string key) {
  auto cfh = getColumnFamilyHandle_(columnFamilyName);
  if (cfh == nullptr) {
    throw std::runtime_error("Can not find ColumnFamily: " + columnFamilyName);
  }

  return db_->Delete(WriteOptions(), cfh, key);
}

Status DBWrapper::write(WriteBatchWrapper& batch) {
  return db_->Write(WriteOptions(), batch.getBatch());
}

std::string DBWrapper::get(std::string key) {
  std::string value;
  auto s = db_->Get(ReadOptions(), key, &value);
  assert(s.ok());
  return value;
}

std::string DBWrapper::getWithColumnFamily(std::string columnFamilyName, std::string key) {
  auto cfh = getColumnFamilyHandle_(columnFamilyName);
  if (cfh == nullptr) {
    throw std::runtime_error("Can not find ColumnFamily: " + columnFamilyName);
  }

  std::string value;
  auto s = db_->Get(ReadOptions(), cfh, key, &value);
  assert(s.ok());
  return value;
}

IteratorWrapper* DBWrapper::newIterator() {
  return new IteratorWrapper(db_->NewIterator(ReadOptions()));
}

IteratorWrapper* DBWrapper::newIteratorWithColumnFamily(const std::string& columnFamilyName) {
  auto cfh = getColumnFamilyHandle_(columnFamilyName);
  if (cfh == nullptr) {
    throw std::runtime_error("Can not find ColumnFamily: " + columnFamilyName);
  }

  return new IteratorWrapper(db_->NewIterator(ReadOptions(), cfh));
}

std::string DBWrapper::getName() {
  return db_->GetName();
}

DBWrapper::~DBWrapper() {

  for (auto& cfs : columnFamilies_) {
    delete cfs.second;
  }

  delete db_;
}

ColumnFamilyHandle* DBWrapper::getColumnFamilyHandle_(const std::string& columnFamilyName) {
  return columnFamilies_[columnFamilyName];
}

