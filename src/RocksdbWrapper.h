#ifndef __ROCKSDB_WRAPPER_H__
#define __ROCKSDB_WRAPPER_H__

#include <unordered_map>
#include <Rcpp.h>
#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include "rocksdb/options.h"

// [[Rcpp::plugins("cpp11")]]

class RocksdbWrapper {
public:
  RocksdbWrapper(const std::string& dbName);
  ~RocksdbWrapper();

  std::string putVal(const std::string& key, const std::string& value);
  std::string getVal(const std::string& key);
  std::string deleteVal(const std::string& key);
private:
  rocksdb::DB* _db;
};

#endif /* __ROCKSDB_WRAPPER_H__ */
