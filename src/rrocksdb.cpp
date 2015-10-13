#include <Rcpp.h>
#include "rrocksdb_types.h"

using namespace Rcpp;

// [[Rcpp::plugins(cpp11)]]

RCPP_MODULE(rrocksdb) {

  using namespace Rcpp;

  Rcpp::class_<DB>("DB")
  .constructor<std::string>()
  .method("put", &DB::put, "Put data into RocksDB")
  .method("remove", &DB::remove, "Remove data from RocksDB")
  .method("rm", &DB::remove, "Remove data from RocksDB")
  .method("write", &DB::write, "Write batch data")
  .method("get", &DB::get, "Get data from RocksDB")
  .method("iterator", &DB::newIterator, "Create iterator")
  .method("get_name", &DB::getName)
  ;

  Rcpp::class_<WriteBatch>("WriteBatch")
  .constructor()
  .method("put", &WriteBatch::put, "Put onto batch")
  .method("rm", &WriteBatch::remove, "Remove from batch")
  .method("remove", &WriteBatch::remove, "Remove from batch")
  .method("merge", &WriteBatch::merge)
  .method("clear", &WriteBatch::clear)
  .method("setSavePoint", &WriteBatch::setSavePoint)
  .method("set_save_point", &WriteBatch::setSavePoint)
  ;

  Rcpp::class_<Iterator>("Iterator")
  .method("valid", &Iterator::valid)
  .method("seekToFirst", &Iterator::seekToFirst)
  .method("seek_to_first", &Iterator::seekToFirst)
  .method("seekToLast", &Iterator::seekToLast)
  .method("seek_to_last", &Iterator::seekToLast)
  .method("move_next", &Iterator::next)
  .method("move_prev", &Iterator::prev)
  .property("key", &Iterator::key)
  .property("value", &Iterator::value)
  ;
}
