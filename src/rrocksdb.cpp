#include <Rcpp.h>
#include "rrocksdb_types.h"

using namespace Rcpp;

// [[Rcpp::plugins(cpp11)]]

RCPP_MODULE(rrocksdb) {

  using namespace Rcpp;

  using namespace rocksdb;

  Rcpp::class_<Status>("Status")
  .method("ok", &Status::ok)
  .method("isNotFound", &Status::IsNotFound)
  ;

  Rcpp::class_<DBWrapper>("DB")
  .constructor<std::string>()
  .method("createColumnFamily", &DBWrapper::createColumnFamily)
  .method("create_column_family", &DBWrapper::createColumnFamily)
  .method("put", &DBWrapper::put, "Put data into RocksDB")
  .method("remove", &DBWrapper::remove, "Remove data from RocksDB")
  .method("rm", &DBWrapper::remove, "Remove data from RocksDB")
  .method("write", &DBWrapper::write, "Write batch data")
  .method("get", &DBWrapper::get, "Get data from RocksDB")
  .method("iterator", &DBWrapper::newIterator, "Create iterator")
  .method("get_name", &DBWrapper::getName)
  ;

  Rcpp::class_<WriteBatchWrapper>("WriteBatch")
  .constructor()
  .method("put", &WriteBatchWrapper::put, "Put onto batch")
  .method("rm", &WriteBatchWrapper::remove, "Remove from batch")
  .method("remove", &WriteBatchWrapper::remove, "Remove from batch")
  .method("merge", &WriteBatchWrapper::merge)
  .method("clear", &WriteBatchWrapper::clear)
  .method("setSavePoint", &WriteBatchWrapper::setSavePoint)
  .method("set_save_point", &WriteBatchWrapper::setSavePoint)
  ;

  Rcpp::class_<IteratorWrapper>("Iterator")
  .method("valid", &IteratorWrapper::valid)
  .method("seekToFirst", &IteratorWrapper::seekToFirst)
  .method("seek_to_first", &IteratorWrapper::seekToFirst)
  .method("seekToLast", &IteratorWrapper::seekToLast)
  .method("seek_to_last", &IteratorWrapper::seekToLast)
  .method("move_next", &IteratorWrapper::next)
  .method("move_prev", &IteratorWrapper::prev)
  .property("key", &IteratorWrapper::key)
  .property("value", &IteratorWrapper::value)
  ;

}
