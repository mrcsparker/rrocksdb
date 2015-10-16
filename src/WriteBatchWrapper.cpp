#include "WriteBatchWrapper.h"

WriteBatchWrapper::WriteBatchWrapper() {
  batch_ = new rocksdb::WriteBatch();
}

void WriteBatchWrapper::put(std::string& key, std::string& value) {
  batch_->Put(key, value);
}

void WriteBatchWrapper::remove(std::string& key) {
  batch_->Delete(key);
}

void WriteBatchWrapper::merge(std::string& key, std::string& value) {
  batch_->Merge(key, value);
}

void WriteBatchWrapper::clear() {
  batch_->Clear();
}

void WriteBatchWrapper::setSavePoint() {
  batch_->SetSavePoint();
}

rocksdb::WriteBatch* WriteBatchWrapper::getBatch() {
  return batch_;
}

WriteBatchWrapper::~WriteBatchWrapper() {
  delete batch_;
}

