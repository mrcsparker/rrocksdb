#include "OptionsWrapper.h"

#include "rocksdb/filter_policy.h"
#include "rocksdb/table.h"

OptionsWrapper::OptionsWrapper() {
  options_ = new rocksdb::Options();
}

OptionsWrapper OptionsWrapper::defaultOptions() {
  OptionsWrapper o;
  o.increaseParallelism();
  o.optimizeLevelStyleCompaction();
  o.createIfMissing(true);
  return o;
}

void OptionsWrapper::increaseParallelism() {
  options_->IncreaseParallelism();
}

void OptionsWrapper::optimizeLevelStyleCompaction() {
  options_->OptimizeLevelStyleCompaction();
}

void OptionsWrapper::createIfMissing(const bool& v) {
  options_->create_if_missing = v;
}

void OptionsWrapper::createMissingColumnFamilies(const bool& v) {
  options_->create_missing_column_families = v;
}

void OptionsWrapper::errorIfExists(const bool& v) {
  options_->error_if_exists = v;
}

void OptionsWrapper::paranoidChecks(const bool& v) {
  options_->paranoid_checks = v;
}

void OptionsWrapper::setFixedPrefixTransform(const size_t& length) {
  options_->prefix_extractor.reset(rocksdb::NewFixedPrefixTransform(length));
}

void OptionsWrapper::setCappedPrefixTransform(const size_t& length) {
  options_->prefix_extractor.reset(rocksdb::NewCappedPrefixTransform(length));
}

void OptionsWrapper::setNoopTransform() {
  options_->prefix_extractor.reset(rocksdb::NewNoopTransform());
}

const rocksdb::Options OptionsWrapper::getOptions() {
  return *options_;
}

OptionsWrapper::~OptionsWrapper() {
  delete options_;
}


