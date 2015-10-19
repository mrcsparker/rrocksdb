#ifndef __DB_H__
#define __DB_H__

#include <unordered_map>
#include <utility>
#include <Rcpp.h>

#include "rocksdb/db.h"
#include "OptionsWrapper.h"
#include "IteratorWrapper.h"
#include "WriteBatchWrapper.h"

using namespace rocksdb;

class DBWrapper {
public:

  // open
  DBWrapper(std::string dbName, OptionsWrapper& options);

  DBWrapper(std::string dbName);

  Status open(std::string name, OptionsWrapper& options);

  Status createColumnFamily(std::string name);

  std::string put(std::string key, std::string value);

  std::string putWithColumnFamily(std::string columnFamilyName, std::string key, std::string value);

  Status remove(std::string key);

  Status removeWithColumnFamily(std::string columnFamilyName, std::string key);

  Status write(WriteBatchWrapper& batch);

  std::string get(std::string key);

  std::string getWithColumnFamily(std::string columnFamilyName, std::string key);

  IteratorWrapper* newIterator();

  IteratorWrapper* newIteratorWithColumnFamily(const std::string& columnFamilyName);

  std::string getName();

  ~DBWrapper();

private:

  rocksdb::ColumnFamilyHandle* getColumnFamilyHandle_(const std::string& columnFamilyName);

  rocksdb::DB* db_;
  std::unordered_map<std::string, rocksdb::ColumnFamilyHandle*> columnFamilies_;
};


#endif /* __DB_H__ */
