#ifndef __WRITE_BATCH_H__
#define __WRITE_BATCH_H__

#include <Rcpp.h>
#include "rocksdb/db.h"

class WriteBatch {
public:
  WriteBatch();

  void put(std::string& key, std::string& value);

  void remove(std::string& key);

  void merge(std::string& key, std::string& value);

  void clear();

  void setSavePoint();

  rocksdb::WriteBatch* getBatch();

  ~WriteBatch();

private:
  rocksdb::WriteBatch* _batch;
};

RCPP_EXPOSED_CLASS(WriteBatch)

#endif /* __WRITE_BATCH_H__ */
