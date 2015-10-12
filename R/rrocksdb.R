# Some useful keyboard shortcuts for package authoring:
#
#   Build and Reload Package:  'Cmd + Shift + B'
#   Check Package:             'Cmd + Shift + E'
#   Test Package:              'Cmd + Shift + T'

library(R6)

DB = R6Class("DB",
  public = list(

    db_name = NA,
    db = NA,

    initialize = function(name) {
      self$db_name <- name
      self$db <- rrocksdb_new(name)
    },

    put = function(key, value) {
      rrocksdb_put(self$db, key, value)
    },

    get = function(key) {
      rrocksdb_get(self$db, key)
    },

    delete = function(key) {
      rrocksdb_delete(self$db, key)
    }
  )
)
