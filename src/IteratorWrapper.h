#ifndef __ITERATOR_H__
#define __ITERATOR_H__

#include <Rcpp.h>
#include "rocksdb/db.h"

using namespace rocksdb;

class IteratorWrapper {
public:
  IteratorWrapper(rocksdb::Iterator *iterator);

  bool valid();

  void seekToFirst();

  void seekToLast();

  void seek(std::string& query);

  void next();

  void prev();

  std::string key();

  std::string value();

  Status status();

  ~IteratorWrapper();

private:
  rocksdb::Iterator* iterator_;
};

RCPP_EXPOSED_CLASS(IteratorWrapper)

#endif /* __ITERATOR_H__ */
