#include <Rcpp.h>
#include "rrocksdb_types.h"

using namespace Rcpp;

// This is a simple function using Rcpp that creates an R list
// containing a character vector and a numeric vector.
//
// Learn more about how to use Rcpp at:
//
//   http://www.rcpp.org/
//   http://adv-r.had.co.nz/Rcpp.html
//
// and browse examples of code using Rcpp at:
//
//   http://gallery.rcpp.org/
//

// [[Rcpp::plugins(cpp11)]]

// [[Rcpp::export]]
XPtr<RocksdbWrapper> rrocksdb_new(std::string name) {
  return XPtr<RocksdbWrapper>(
    new RocksdbWrapper(name)
  );
}

// [[Rcpp::export]]
std::string rrocksdb_put(XPtr<RocksdbWrapper> r,
                         std::string key,
                         std::string value) {
  return r->putVal(key, value);
}

// [[Rcpp::export]]
std::string rrocksdb_get(XPtr<RocksdbWrapper> r,
                         std::string key) {
  return r->getVal(key);
}

// [[Rcpp::export]]
std::string rrocksdb_delete(XPtr<RocksdbWrapper> r,
                         std::string key) {
  return r->deleteVal(key);
}
