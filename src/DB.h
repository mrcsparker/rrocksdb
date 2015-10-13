#ifndef __DB_H__
#define __DB_H__

#include <Rcpp.h>
#include "rocksdb/db.h"
#include "Iterator.h"
#include "WriteBatch.h"

class DB {
public:

  // open
  DB(const std::string& dbName);

  std::string put(const std::string& key, const std::string& value);

  std::string remove(const std::string& key);

  void write(WriteBatch& batch);

  std::string get(const std::string& key);

  Iterator* newIterator();

  std::string getName();

  ~DB();

private:
  rocksdb::DB* _db;
};


#endif /* __DB_H__ */
