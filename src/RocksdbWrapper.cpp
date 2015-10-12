#include "RocksdbWrapper.h"

RocksdbWrapper::RocksdbWrapper(const std::string& dbName) {

  rocksdb::Options options;
  // Optimize RocksDB. This is the easiest way to get RocksDB to perform well
  options.IncreaseParallelism();
  options.OptimizeLevelStyleCompaction();
  // create the DB if it's not already present
  options.create_if_missing = true;
  // open DB
  rocksdb::Status s = rocksdb::DB::Open(options, dbName, &_db);

  assert(s.ok());
}

RocksdbWrapper::~RocksdbWrapper() {
  delete _db;
}

std::string RocksdbWrapper::putVal(const std::string& key, const std::string& value) {
  rocksdb::Status s = _db->Put(rocksdb::WriteOptions(), key, value);
  assert(s.ok());
  return value;
}

std::string RocksdbWrapper::getVal(const std::string& key) {
  std::string value;
  rocksdb::Status s = _db->Get(rocksdb::ReadOptions(), key, &value);
  assert(s.ok());
  return value;
}

std::string RocksdbWrapper::deleteVal(const std::string& key) {
  rocksdb::Status s = _db->Delete(rocksdb::WriteOptions(), key);
  assert(s.ok());
  return key;
}
