#ifndef __WRITE_BATCH_H__
#define __WRITE_BATCH_H__

#include <Rcpp.h>
#include "rocksdb/db.h"

class WriteBatchWrapper {
public:
  WriteBatchWrapper();

  void put(std::string& key, std::string& value);

  void remove(std::string& key);

  void merge(std::string& key, std::string& value);

  void clear();

  void setSavePoint();

  rocksdb::WriteBatch* getBatch();

  ~WriteBatchWrapper();

private:
  rocksdb::WriteBatch* batch_;
};

RCPP_EXPOSED_CLASS(WriteBatchWrapper)

#endif /* __WRITE_BATCH_H__ */
