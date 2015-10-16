#include <Rcpp.h>
#include "OptionsWrapper.h"
#include "DBWrapper.h"

DBWrapper::DBWrapper(const std::string& dbName, OptionsWrapper& options) {
  std::vector<std::string> tmpCf;
  auto s = rocksdb::DB::ListColumnFamilies(options.getOptions(), dbName, &tmpCf);

  if (!s.ok()) {
    open(dbName, options);
    return;
  }

  std::vector<rocksdb::ColumnFamilyDescriptor> columnFamilyDescriptors;

  for (auto const& cf : tmpCf) {
    columnFamilyDescriptors.push_back(ColumnFamilyDescriptor(cf, rocksdb::ColumnFamilyOptions()));
  }

  std::vector<rocksdb::ColumnFamilyHandle *> columnFamilyHandles;
  s = rocksdb::DB::Open(options.getOptions(), dbName, columnFamilyDescriptors, &columnFamilyHandles, &db_);

  for (auto const& cfh : columnFamilyHandles) {
    columnFamilies_.emplace(cfh->GetName(), cfh);
  }

  if (!s.ok()) {
    throw std::runtime_error(s.ToString());
  }
}

DBWrapper::DBWrapper(const std::string& dbName) {
  auto options = OptionsWrapper::defaultOptions();
  open(dbName, options);
}

Status DBWrapper::createColumnFamily(std::string& name) {

  if (columnFamilies_[name] != nullptr) {
    return rocksdb::Status();
  }

  rocksdb::ColumnFamilyHandle* cf;
  auto s = db_->CreateColumnFamily(rocksdb::ColumnFamilyOptions(), name, &cf);

  columnFamilies_.emplace(cf->GetName(), cf);

  return s;
}

Status DBWrapper::open(const std::string& dbName, OptionsWrapper& options) {
  auto s = rocksdb::DB::Open(options.getOptions(), dbName, &db_);
  if (!s.ok()) {
    throw std::runtime_error(s.ToString());
  }
  return s;
}

std::string DBWrapper::put(const std::string& key, const std::string& value) {
  auto s = db_->Put(rocksdb::WriteOptions(), key, value);
  assert(s.ok());
  return value;
}

std::string DBWrapper::putWithColumnFamily(const std::string& columnFamilyName, const std::string& key, const std::string& value) {
  auto cfh = getColumnFamilyHandle_(columnFamilyName);
  if (cfh == nullptr) {
    throw std::runtime_error("Can not find ColumnFamily: " + columnFamilyName);
  }

  auto s = db_->Put(rocksdb::WriteOptions(), cfh, key, value);
  assert(s.ok());
  return value;
}

Status DBWrapper::remove(const std::string& key) {
  return db_->Delete(rocksdb::WriteOptions(), key);
}

Status DBWrapper::removeWithColumnFamily(const std::string& columnFamilyName, const std::string& key) {
  auto cfh = getColumnFamilyHandle_(columnFamilyName);
  if (cfh == nullptr) {
    throw std::runtime_error("Can not find ColumnFamily: " + columnFamilyName);
  }

  return db_->Delete(rocksdb::WriteOptions(), cfh, key);
}

Status DBWrapper::write(WriteBatchWrapper& batch) {
  return db_->Write(rocksdb::WriteOptions(), batch.getBatch());
}

std::string DBWrapper::get(const std::string& key) {
  std::string value;
  auto s = db_->Get(rocksdb::ReadOptions(), key, &value);
  assert(s.ok());
  return value;
}

std::string DBWrapper::getWithColumnFamily(const std::string& columnFamilyName, const std::string& key) {
  auto cfh = getColumnFamilyHandle_(columnFamilyName);
  if (cfh == nullptr) {
    throw std::runtime_error("Can not find ColumnFamily: " + columnFamilyName);
  }

  std::string value;
  auto s = db_->Get(rocksdb::ReadOptions(), cfh, key, &value);
  assert(s.ok());
  return value;
}

IteratorWrapper* DBWrapper::newIterator() {
  return new IteratorWrapper(db_->NewIterator(rocksdb::ReadOptions()));
}

IteratorWrapper* DBWrapper::newIteratorWithColumnFamily(const std::string& columnFamilyName) {
  auto cfh = getColumnFamilyHandle_(columnFamilyName);
  if (cfh == nullptr) {
    throw std::runtime_error("Can not find ColumnFamily: " + columnFamilyName);
  }

  return new IteratorWrapper(db_->NewIterator(rocksdb::ReadOptions(), cfh));
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

rocksdb::ColumnFamilyHandle* DBWrapper::getColumnFamilyHandle_(const std::string& columnFamilyName) {
  return columnFamilies_[columnFamilyName];
}

