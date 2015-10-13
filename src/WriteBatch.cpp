#include "WriteBatch.h"

WriteBatch::WriteBatch() {
  _batch = new rocksdb::WriteBatch();
}

void WriteBatch::put(std::string& key, std::string& value) {
  _batch->Put(key, value);
}

void WriteBatch::remove(std::string& key) {
  _batch->Delete(key);
}

void WriteBatch::merge(std::string& key, std::string& value) {
  _batch->Merge(key, value);
}

void WriteBatch::clear() {
  _batch->Clear();
}

void WriteBatch::setSavePoint() {
  _batch->SetSavePoint();
}

rocksdb::WriteBatch* WriteBatch::getBatch() {
  return _batch;
}

WriteBatch::~WriteBatch() {
  delete _batch;
}

