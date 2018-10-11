#include "IteratorWrapper.h"

IteratorWrapper::IteratorWrapper(rocksdb::Iterator *iterator) {
  iterator_ = iterator;
  iterator_->SeekToFirst();
}

bool IteratorWrapper::valid() {
  return iterator_->Valid();
}

void IteratorWrapper::seekToFirst() {
  iterator_->SeekToFirst();
}

void IteratorWrapper::seekToLast() {
  iterator_->SeekToLast();
}

void IteratorWrapper::seek(std::string& query) {
  iterator_->Seek(query);
}

void IteratorWrapper::seekForPrev(std::string& query) {
  iterator_->SeekForPrev(query);
}

void IteratorWrapper::next() {
  iterator_->Next();
}

void IteratorWrapper::prev() {
  iterator_->Prev();
}

std::string IteratorWrapper::key() {
  return iterator_->key().ToString();
}

std::string IteratorWrapper::value() {
  return iterator_->value().ToString();
}

Status IteratorWrapper::status() {
  return iterator_->status();
}

IteratorWrapper::~IteratorWrapper() {
  delete iterator_;
}

