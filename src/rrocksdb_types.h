#ifndef __RROCKSDB_TYPES_H__
#define __RROCKSDB_TYPES_H__

#include "DBWrapper.h"
#include "WriteBatchWrapper.h"
#include "IteratorWrapper.h"

#include "rocksdb/status.h"
using namespace rocksdb;
RCPP_EXPOSED_CLASS_NODECL(Status)

#endif /* __RROCKSDB_TYPES_H__ */
