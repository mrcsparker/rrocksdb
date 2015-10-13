#include <Rcpp.h>
#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include "rocksdb/options.h"

using namespace Rcpp;

// [[Rcpp::plugins(cpp11)]]

class WriteBatch {
public:
  WriteBatch() {
    _batch = new rocksdb::WriteBatch();
  }

  void put(std::string& key, std::string& value) {
    _batch->Put(key, value);
  }

  void remove(std::string& key) {
    _batch->Delete(key);
  }

  rocksdb::WriteBatch* getBatch() {
    return _batch;
  }

  ~WriteBatch() {
    delete _batch;
  }

private:
  rocksdb::WriteBatch* _batch;
};

RCPP_EXPOSED_CLASS(WriteBatch)

class DB {
public:
  DB(const std::string& dbName) {
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

  std::string put(const std::string& key, const std::string& value) {
    rocksdb::Status s = _db->Put(rocksdb::WriteOptions(), key, value);
    assert(s.ok());
    return value;
  }

  std::string get(const std::string& key) {
    std::string value;
    rocksdb::Status s = _db->Get(rocksdb::ReadOptions(), key, &value);
    assert(s.ok());
    return value;
  }

  std::string remove(const std::string& key) {
    rocksdb::Status s = _db->Delete(rocksdb::WriteOptions(), key);
    assert(s.ok());
    return key;
  }

  void write(WriteBatch& batch) {
    _db->Write(rocksdb::WriteOptions(), batch.getBatch());
  }

  ~DB() {
    delete _db;
  }

private:
  rocksdb::DB* _db;
};


RCPP_MODULE(rrocksdb) {

  using namespace Rcpp;

  Rcpp::class_<DB>("DB")
  .constructor<std::string>()
  .method("put", &DB::put, "Put data into RocksDB")
  .method("get", &DB::get, "Get data from RocksDB")
  .method("remove", &DB::remove, "Remove data from RocksDB")
  .method("rm", &DB::remove, "Remove data from RocksDB")
  .method("write", &DB::write, "Write batch data")
  ;

  Rcpp::class_<WriteBatch>("WriteBatch")
  .constructor()
  .method("put", &WriteBatch::put, "Put onto batch")
  .method("rm", &WriteBatch::remove, "Remove from batch")
  .method("remove", &WriteBatch::remove, "Remove from batch")
  ;
}
