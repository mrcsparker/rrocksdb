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

  Status remove(const std::string& key);

  void write(WriteBatchWrapper& batch);

  std::string get(const std::string& key);

  IteratorWrapper* newIterator();

  std::string getName();

  ~DBWrapper();

private:
  rocksdb::DB* _db;
};


#endif /* __DB_H__ */
