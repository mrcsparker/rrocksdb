# Some useful keyboard shortcuts for package authoring:
#
#   Build and Reload Package:  'Cmd + Shift + B'
#   Check Package:             'Cmd + Shift + E'
#   Test Package:              'Cmd + Shift + T'

loadModule("rrocksdb", TRUE)

require(randomNames)

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
  db$createColumnFamily("csv")
  db$createColumnFamily("csv_metadata")

  print("loaded")

  for (i in 1:100) {
    name = unlist(strsplit(randomNames::randomNames(), ","))
    db$putCF("csv", paste(toString(i), ":", "1", ":", "id", sep = ""), toString(i))
    db$putCF("csv", paste(toString(i), ":", "2", ":","first_name", sep = ""), name[2])
    db$putCF("csv", paste(toString(i), ":", "3", ":", "last_name", sep = ""), name[1])
  }

  iterator <- db$iterator()
  iterator$seek("1:")
  while (iterator$valid()) {
    if (match(iterator$key, "(.*):(.*):last_name") && match(iterator$value, "Lee")) {
      print(paste(iterator$key, ":", iterator$value))
    }
    iterator$moveNext()
  }
}

sampleLoad <- function() {
  fakeCSV()
  #runRRocksDB()
  invisible(gc())
}
