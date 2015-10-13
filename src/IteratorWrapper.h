#ifndef __ITERATOR_H__
#define __ITERATOR_H__

#include <Rcpp.h>
#include "rocksdb/db.h"

class IteratorWrapper {
public:
  IteratorWrapper(rocksdb::Iterator *iterator);

  bool valid();

  void seekToFirst();

  void seekToLast();

  // virtual void Seek(const Slice& target) = 0;

  void next();

  void prev();

  std::string key();

  std::string value();

  // virtual Status status() const = 0;

  ~IteratorWrapper();

private:
  rocksdb::Iterator* _iterator;
};

RCPP_EXPOSED_CLASS(IteratorWrapper)

#endif /* __ITERATOR_H__ */
