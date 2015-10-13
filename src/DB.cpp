#include "DB.h"

DB::DB(const std::string& dbName) {
  rocksdb::Options options;
  // Optimize RocksDB. This is the easiest way to get RocksDB to perform well
  options.IncreaseParallelism();
  options.OptimizeLevelStyleCompaction();
  // create the DB if it's not already present
  options.create_if_missing = true;
  // open DB
  rocksdb::Status s = rocksdb::DB::Open(options, dbName, &_db);

  if (!s.ok()) {
    throw std::runtime_error(s.ToString());
  }
}

std::string DB::put(const std::string& key, const std::string& value) {
  rocksdb::Status s = _db->Put(rocksdb::WriteOptions(), key, value);
  assert(s.ok());
  return value;
}

std::string DB::remove(const std::string& key) {
  rocksdb::Status s = _db->Delete(rocksdb::WriteOptions(), key);
  assert(s.ok());
  return key;
}

void DB::write(WriteBatch& batch) {
  _db->Write(rocksdb::WriteOptions(), batch.getBatch());
}

std::string DB::get(const std::string& key) {
  std::string value;
  rocksdb::Status s = _db->Get(rocksdb::ReadOptions(), key, &value);
  assert(s.ok());
  return value;
}

Iterator* DB::newIterator() {
  return new Iterator(_db->NewIterator(rocksdb::ReadOptions()));
}

std::string DB::getName() {
  return _db->GetName();
}

DB::~DB() {
  delete _db;
}

