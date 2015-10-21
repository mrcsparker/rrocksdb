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
  db$createColumnFamily("csv")

  db$createColumnFamily("csv_index_on_id")
  db$createColumnFamily("csv_index_on_first_name")
  db$createColumnFamily("csv_index_on_last_name")

  for (i in 1:100) {
    name = unlist(strsplit(randomNames::randomNames(), ", "))

    idKey = sprintf("%d:%d:%d:id", i, 1, i)
    firstNameKey = sprintf("%d:%d:%s:first_name", i, 1, name[2])
    lastNameKey = sprintf("%d:%d:%s:last_name", i, 1, name[1])

    db$putCF("csv_index_on_id", toString(i), idKey)
    db$putCF("csv_index_on_first_name", name[2], firstNameKey)
    db$putCF("csv_index_on_last_name", name[1], lastNameKey)

    db$putCF("csv", idKey, toString(i))
    db$putCF("csv", firstNameKey, name[2])
    db$putCF("csv", lastNameKey, name[1])
  }

  iterator <- db$iteratorCF("csv")
  iterator$seek("1:")
  while (iterator$valid()) {
    #if (regexMatch(iterator$key, "(.*):(.*):last_name")) {
      print(paste(iterator$key, ":", iterator$value))
    #}
    iterator$moveNext()
  }
}

sampleLoad <- function() {
  fakeCSV()
  #runRRocksDB()
  invisible(gc())
}
