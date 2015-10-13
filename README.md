# rrocksdb

Initial checkin of a RocksDB (http://rocksdb.org) wrapper for R.

```R
loadModule("rrocksdb", TRUE)

run_rrocksdb <- function() {

  db <- new(rrocksdb::DB, "/tmp/foo.db")
  print(db)
  db$put("name", "Bar")
  print(db$get("name"))

  batch <- new(rrocksdb::WriteBatch)

  for(i in 1:1000) {
    batch$put(paste("name", i), paste("Chris", i))
  }

  db$write(batch)

  iterator <- db$iterator()

  while (iterator$valid()) {
    print(paste(iterator$key, " : ", iterator$value))
    iterator$move_next()
  }
}

sample_load <- function() {
  run_rrocksdb()
  invisible(gc())
}

```
