#include "WriteBatchWrapper.h"

WriteBatchWrapper::WriteBatchWrapper() {
  _batch = new rocksdb::WriteBatch();
}

void WriteBatchWrapper::put(std::string& key, std::string& value) {
  _batch->Put(key, value);
}

void WriteBatchWrapper::remove(std::string& key) {
  _batch->Delete(key);
}

void WriteBatchWrapper::merge(std::string& key, std::string& value) {
  _batch->Merge(key, value);
}

void WriteBatchWrapper::clear() {
  _batch->Clear();
}

void WriteBatchWrapper::setSavePoint() {
  _batch->SetSavePoint();
}

rocksdb::WriteBatch* WriteBatchWrapper::getBatch() {
  return _batch;
}

WriteBatchWrapper::~WriteBatchWrapper() {
  delete _batch;
}

