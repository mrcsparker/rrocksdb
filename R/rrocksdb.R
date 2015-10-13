# Some useful keyboard shortcuts for package authoring:
#
#   Build and Reload Package:  'Cmd + Shift + B'
#   Check Package:             'Cmd + Shift + E'
#   Test Package:              'Cmd + Shift + T'

loadModule("rrocksdb", TRUE)

sample_load <- function() {

  db <- new(rrocksdb::DB, "/tmp/foo.db")
  db$put("name", "Bar")
  print(db$get("name"))

  batch <- new(rrocksdb::WriteBatch)
  batch$put("name", "Chris")

  db$write(batch)

}
