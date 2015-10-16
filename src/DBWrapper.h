#ifndef __DB_H__
#define __DB_H__

#include <Rcpp.h>

#include "rocksdb/db.h"
#include "OptionsWrapper.h"
#include "IteratorWrapper.h"
#include "WriteBatchWrapper.h"

using namespace rocksdb;

class DBWrapper {
public:

  // open
  DBWrapper(const std::string& dbName, OptionsWrapper& options);

  DBWrapper(const std::string& dbName);

  Status open(const std::string& name, OptionsWrapper& options);

  Status createColumnFamily(std::string& name);

  std::string put(const std::string& key, const std::string& value);

  std::string putWithColumnFamily(const std::string& columnFamilyName, const std::string& key, const std::string& value);

  Status remove(const std::string& key);

  Status removeWithColumnFamily(const std::string& columnFamilyName, const std::string& key);

  Status write(WriteBatchWrapper& batch);

  std::string get(const std::string& key);

  std::string getWithColumnFamily(const std::string& columnFamilyName, const std::string& key);

  IteratorWrapper* newIterator();

  IteratorWrapper* newIteratorWithColumnFamily(const std::string& columnFamilyName);

  std::string getName();

  ~DBWrapper();

private:

  rocksdb::ColumnFamilyHandle* getColumnFamilyHandle_(const std::string& columnFamilyName);

  rocksdb::DB* db_;
  std::unordered_map<std::string, rocksdb::ColumnFamilyHandle *> columnFamilies_;
};


#endif /* __DB_H__ */
