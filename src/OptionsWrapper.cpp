#include "OptionsWrapper.h"

#include "rocksdb/filter_policy.h"
#include "rocksdb/table.h"

OptionsWrapper::OptionsWrapper() {
  _options = new rocksdb::Options();
}

OptionsWrapper OptionsWrapper::defaultOptions() {
  OptionsWrapper o;
  o.increaseParallelism();
  o.optimizeLevelStyleCompaction();
  o.createIfMissing(true);
  return o;
}

void OptionsWrapper::increaseParallelism() {
  _options->IncreaseParallelism();
}

void OptionsWrapper::optimizeLevelStyleCompaction() {
  _options->OptimizeLevelStyleCompaction();
}

void OptionsWrapper::createIfMissing(const bool& v) {
  _options->create_if_missing = v;
}

void OptionsWrapper::createMissingColumnFamilies(const bool& v) {
  _options->create_missing_column_families = v;
}

void OptionsWrapper::errorIfExists(const bool& v) {
  _options->error_if_exists = v;
}

void OptionsWrapper::paranoidChecks(const bool& v) {
  _options->paranoid_checks = v;
}

void OptionsWrapper::setFixedPrefixTransform(const size_t& length) {
  _options->prefix_extractor.reset(rocksdb::NewFixedPrefixTransform(length));
}

void OptionsWrapper::setCappedPrefixTransform(const size_t& length) {
  _options->prefix_extractor.reset(rocksdb::NewCappedPrefixTransform(length));
}

void OptionsWrapper::setNoopTransform() {
  _options->prefix_extractor.reset(rocksdb::NewNoopTransform());
}

const rocksdb::Options OptionsWrapper::getOptions() {
  return *_options;
}

OptionsWrapper::~OptionsWrapper() {
  delete _options;
}


