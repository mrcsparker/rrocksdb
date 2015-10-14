#include <Rcpp.h>
#include "OptionsWrapper.h"
#include "DBWrapper.h"

DBWrapper::DBWrapper(const std::string& dbName, OptionsWrapper& options) {
  std::vector<std::string> tmpCf;
  rocksdb::Status s = rocksdb::DB::ListColumnFamilies(options.getOptions(), dbName, &tmpCf);

  if (!s.ok()) {
    open(dbName, options);
    return;
  }

  std::vector<rocksdb::ColumnFamilyDescriptor> columnFamilyDescriptors;

  for (auto const& cf : tmpCf) {
    columnFamilyDescriptors.push_back(rocksdb::ColumnFamilyDescriptor(cf, rocksdb::ColumnFamilyOptions()));
  }

  std::vector<rocksdb::ColumnFamilyHandle *> columnFamilyHandles;
  s = rocksdb::DB::Open(options.getOptions(), dbName, columnFamilyDescriptors, &columnFamilyHandles, &_db);

  if (!s.ok()) {
    throw std::runtime_error(s.ToString());
  }
}

DBWrapper::DBWrapper(const std::string& dbName) {
  OptionsWrapper options = OptionsWrapper::defaultOptions();
  open(dbName, options);
}

Status DBWrapper::createColumnFamily(std::string& name) {
  rocksdb::ColumnFamilyHandle* cf;
  rocksdb::Status s = _db->CreateColumnFamily(rocksdb::ColumnFamilyOptions(), name, &cf);
  delete cf;
  return s;
}

Status DBWrapper::open(const std::string& dbName, OptionsWrapper& options) {
  rocksdb::Status s = rocksdb::DB::Open(options.getOptions(), dbName, &_db);
  if (!s.ok()) {
    throw std::runtime_error(s.ToString());
  }
  return s;
}

std::string DBWrapper::put(const std::string& key, const std::string& value) {
  rocksdb::Status s = _db->Put(rocksdb::WriteOptions(), key, value);
  assert(s.ok());
  return value;
}

Status DBWrapper::remove(const std::string& key) {
  rocksdb::Status s = _db->Delete(rocksdb::WriteOptions(), key);
  return s;
}

void DBWrapper::write(WriteBatchWrapper& batch) {
  _db->Write(rocksdb::WriteOptions(), batch.getBatch());
}

std::string DBWrapper::get(const std::string& key) {
  std::string value;
  rocksdb::Status s = _db->Get(rocksdb::ReadOptions(), key, &value);
  assert(s.ok());
  return value;
}

IteratorWrapper* DBWrapper::newIterator() {
  return new IteratorWrapper(_db->NewIterator(rocksdb::ReadOptions()));
}

std::string DBWrapper::getName() {
  return _db->GetName();
}

DBWrapper::~DBWrapper() {
  delete _db;
}

