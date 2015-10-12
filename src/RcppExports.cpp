// This file was generated by Rcpp::compileAttributes
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include "rrocksdb_types.h"
#include <Rcpp.h>

using namespace Rcpp;

// rrocksdb_new
XPtr<RocksdbWrapper> rrocksdb_new(std::string name);
RcppExport SEXP rrocksdb_rrocksdb_new(SEXP nameSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< std::string >::type name(nameSEXP);
    __result = Rcpp::wrap(rrocksdb_new(name));
    return __result;
END_RCPP
}
// rrocksdb_put
std::string rrocksdb_put(XPtr<RocksdbWrapper> r, std::string key, std::string value);
RcppExport SEXP rrocksdb_rrocksdb_put(SEXP rSEXP, SEXP keySEXP, SEXP valueSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< XPtr<RocksdbWrapper> >::type r(rSEXP);
    Rcpp::traits::input_parameter< std::string >::type key(keySEXP);
    Rcpp::traits::input_parameter< std::string >::type value(valueSEXP);
    __result = Rcpp::wrap(rrocksdb_put(r, key, value));
    return __result;
END_RCPP
}
// rrocksdb_get
std::string rrocksdb_get(XPtr<RocksdbWrapper> r, std::string key);
RcppExport SEXP rrocksdb_rrocksdb_get(SEXP rSEXP, SEXP keySEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< XPtr<RocksdbWrapper> >::type r(rSEXP);
    Rcpp::traits::input_parameter< std::string >::type key(keySEXP);
    __result = Rcpp::wrap(rrocksdb_get(r, key));
    return __result;
END_RCPP
}
// rrocksdb_delete
std::string rrocksdb_delete(XPtr<RocksdbWrapper> r, std::string key);
RcppExport SEXP rrocksdb_rrocksdb_delete(SEXP rSEXP, SEXP keySEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< XPtr<RocksdbWrapper> >::type r(rSEXP);
    Rcpp::traits::input_parameter< std::string >::type key(keySEXP);
    __result = Rcpp::wrap(rrocksdb_delete(r, key));
    return __result;
END_RCPP
}