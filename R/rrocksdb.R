# Some useful keyboard shortcuts for package authoring:
#
#   Build and Reload Package:  'Cmd + Shift + B'
#   Check Package:             'Cmd + Shift + E'
#   Test Package:              'Cmd + Shift + T'

loadModule("rrocksdb", TRUE)

runRRocksDB <- function() {

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
    iterator$moveNext()
  }

  s <- db$createColumnFamily("column_family")
  if (!s$ok()) {
    print(paste("error: " , s$toString()))
  }
}

fakeCSV <- function() {

  options <- new(Options)
  options$increaseParallelism()
  options$optimizeLevelStyleCompaction()
  options$createIfMissing(TRUE)
  options$setFixedPrefixTransform(10)

  db <- new(rrocksdb::DB, "/tmp/csv.db", options)

  print("loaded")

  db$put("1/id", "1")
  db$put("1/first_name", "Chris")
  db$put("1/last_name", "Parker")

  db$put("2/id", "2")
  db$put("2/first_name", "John")
  db$put("2/last_name", "Doe")

  db$put("3/id", "3")
  db$put("3/first_name", "Jane")
  db$put("3/last_name", "Doe")

  iterator <- db$iterator()
  iterator$seek("2/")
  while (iterator$valid()) {
    print(paste(iterator$key, " : ", iterator$value))
    iterator$moveNext()
  }
}

sampleLoad <- function() {
  fakeCSV()
  #runRRocksDB()
  invisible(gc())
}
