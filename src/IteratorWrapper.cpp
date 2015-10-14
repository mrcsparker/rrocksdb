#include "IteratorWrapper.h"

IteratorWrapper::IteratorWrapper(rocksdb::Iterator *iterator) {
  _iterator = iterator;
  _iterator->SeekToFirst();
}

bool IteratorWrapper::valid() {
  return _iterator->Valid();
}

void IteratorWrapper::seekToFirst() {
  _iterator->SeekToFirst();
}

void IteratorWrapper::seekToLast() {
  _iterator->SeekToLast();
}

void IteratorWrapper::seek(std::string& query) {
  _iterator->Seek(query);
}

void IteratorWrapper::next() {
  _iterator->Next();
}

void IteratorWrapper::prev() {
  _iterator->Prev();
}

std::string IteratorWrapper::key() {
  return _iterator->key().ToString();
}

std::string IteratorWrapper::value() {
  return _iterator->value().ToString();
}

// virtual Status status() const = 0;

IteratorWrapper::~IteratorWrapper() {
  delete _iterator;
}

