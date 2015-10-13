# rrocksdb

Initial checkin of a RocksDB (http://rocksdb.org) wrapper for R.

```R
loadModule("rrocksdb", TRUE)

sample_load <- function() {

  db <- new(rrocksdb::DB, "/tmp/foo.db")
  db$put("name", "Bar")
  print(db$get("name"))

  batch <- new(rrocksdb::WriteBatch)
  batch$put("name", "Chris")

  db$write(batch)

}

```
