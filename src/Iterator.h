#ifndef __ITERATOR_H__
#define __ITERATOR_H__

#include <Rcpp.h>
#include "rocksdb/db.h"

class Iterator {
public:
  Iterator(rocksdb::Iterator *iterator);

  bool valid();

  void seekToFirst();

  void seekToLast();

  // virtual void Seek(const Slice& target) = 0;

  void next();

  void prev();

  std::string key();

  std::string value();

  // virtual Status status() const = 0;

  ~Iterator();

private:
  rocksdb::Iterator* _iterator;
};

RCPP_EXPOSED_CLASS(Iterator)

#endif /* __ITERATOR_H__ */
