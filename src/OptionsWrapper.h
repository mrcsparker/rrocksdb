#ifndef __OPTIONS_WRAPPER_H__
#define __OPTIONS_WRAPPER_H__

#include <Rcpp.h>
#include "rocksdb/options.h"
#include "rocksdb/slice_transform.h"

// Wrapping this up so that R can free it up

class OptionsWrapper {
public:

  OptionsWrapper();

  static OptionsWrapper defaultOptions();

  void increaseParallelism();

  void optimizeLevelStyleCompaction();

  void createIfMissing(const bool& v);

  void createMissingColumnFamilies(const bool& v);

  void errorIfExists(const bool& v);

  void paranoidChecks(const bool& v);

  void setFixedPrefixTransform(const size_t& length);

  void setCappedPrefixTransform(const size_t& length);

  void setNoopTransform();

  const rocksdb::Options getOptions();

  ~OptionsWrapper();

private:
  rocksdb::Options *_options;
};

RCPP_EXPOSED_CLASS(OptionsWrapper)

#endif /* __OPTIONS_WRAPPER_H__ */
