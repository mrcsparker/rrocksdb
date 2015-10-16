#include <Rcpp.h>
#include <regex>
#include "rrocksdb_types.h"

using namespace Rcpp;

// [[Rcpp::plugins(cpp11)]]

//' @title C++ regex_match wrapper
//' @name regexMatch
//' @return string
//' @examples
//' regexMatch("1:2:last_name", "(.*):(.*):last_name")
// [[Rcpp::export]]
bool regexMatch(std::string s, std::string m) {
  std::regex reg(m);
  return std::regex_match(s, reg);
}

RCPP_MODULE(rrocksdb) {

  using namespace Rcpp;

  using namespace rocksdb;

  Rcpp::class_<OptionsWrapper>("Options")
    .constructor()
    .method("increaseParallelism", &OptionsWrapper::increaseParallelism)
    .method("optimizeLevelStyleCompaction", &OptionsWrapper::optimizeLevelStyleCompaction)
    .method("createIfMissing", &OptionsWrapper::createIfMissing)
    .method("createMissingColumnFamilies", &OptionsWrapper::createMissingColumnFamilies)
    .method("errorIfExists", &OptionsWrapper::errorIfExists)
    .method("paranoidChecks", &OptionsWrapper::paranoidChecks)
    .method("setFixedPrefixTransform", &OptionsWrapper::setFixedPrefixTransform)
    .method("setCappedPrefixTransform", &OptionsWrapper::setCappedPrefixTransform)
    .method("setNoopTransform", &OptionsWrapper::setNoopTransform);

  Rcpp::class_<Status>("Status")
  .method("ok", &Status::ok)
  .method("isNotFound", &Status::IsNotFound)
  .method("isCorruption", &Status::IsCorruption)
  .method("isNotSupported", &Status::IsNotSupported)
  .method("isInvalidArgument", &Status::IsInvalidArgument)
  .method("isIOError", &Status::IsIOError)
  .method("isMergeInProgress", &Status::IsMergeInProgress)
  .method("isIncomplete", &Status::IsIncomplete)
  .method("isShutdownInProgress", &Status::IsShutdownInProgress)
  .method("isTimedOut", &Status::IsTimedOut)
  .method("isAborted", &Status::IsAborted)
  .method("isBusy", &Status::IsBusy)
  .method("toString", &Status::ToString)
  ;

  Rcpp::class_<DBWrapper>("DB")
  .constructor<std::string, OptionsWrapper&>()
  .constructor<std::string>()
  .method("createColumnFamily", &DBWrapper::createColumnFamily)
  .method("put", &DBWrapper::put, "Put data into RocksDB")
  .method("putWithColumnFamily", &DBWrapper::putWithColumnFamily, "Put data into RocksDB")
  .method("putCF", &DBWrapper::putWithColumnFamily, "Put data into RocksDB")
  .method("remove", &DBWrapper::remove, "Remove data from RocksDB")
  .method("removeWithColumnFamily", &DBWrapper::removeWithColumnFamily, "Remove data from RocksDB")
  .method("removeCF", &DBWrapper::removeWithColumnFamily, "Remove data from RocksDB")
  .method("rm", &DBWrapper::remove, "Remove data from RocksDB")
  .method("rmWithColumnFamily", &DBWrapper::removeWithColumnFamily, "Remove data from RocksDB")
  .method("rmCF", &DBWrapper::removeWithColumnFamily, "Remove data from RocksDB")
  .method("write", &DBWrapper::write, "Write batch data")
  .method("get", &DBWrapper::get, "Get data from RocksDB")
  .method("getWithColumnFamily", &DBWrapper::getWithColumnFamily, "Get data from RocksDB")
  .method("getCF", &DBWrapper::getWithColumnFamily, "Get data from RocksDB")
  .method("iterator", &DBWrapper::newIterator, "Create iterator")
  .method("iteratorWithColumnFamily", &DBWrapper::newIteratorWithColumnFamily, "Create iterator")
  .method("iteratorCF", &DBWrapper::newIteratorWithColumnFamily, "Create iterator")
  .method("getName", &DBWrapper::getName)
  ;

  Rcpp::class_<WriteBatchWrapper>("WriteBatch")
  .constructor()
  .method("put", &WriteBatchWrapper::put, "Put onto batch")
  .method("rm", &WriteBatchWrapper::remove, "Remove from batch")
  .method("remove", &WriteBatchWrapper::remove, "Remove from batch")
  .method("merge", &WriteBatchWrapper::merge)
  .method("clear", &WriteBatchWrapper::clear)
  .method("setSavePoint", &WriteBatchWrapper::setSavePoint)
  ;

  Rcpp::class_<IteratorWrapper>("Iterator")
  .method("valid", &IteratorWrapper::valid)
  .method("seekToFirst", &IteratorWrapper::seekToFirst)
  .method("seekToLast", &IteratorWrapper::seekToLast)
  .method("seek", &IteratorWrapper::seek)
  .method("moveNext", &IteratorWrapper::next)
  .method("movePrev", &IteratorWrapper::prev)
  .property("key", &IteratorWrapper::key)
  .property("value", &IteratorWrapper::value)
  .property("status", &IteratorWrapper::status)
  ;

}
