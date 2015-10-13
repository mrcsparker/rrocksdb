#include "Iterator.h"

Iterator::Iterator(rocksdb::Iterator *iterator) {
  _iterator = iterator;
  _iterator->SeekToFirst();
}

bool Iterator::valid() {
  return _iterator->Valid();
}

void Iterator::seekToFirst() {
  _iterator->SeekToFirst();
}

void Iterator::seekToLast() {
  _iterator->SeekToLast();
}

// virtual void Seek(const Slice& target) = 0;

void Iterator::next() {
  _iterator->Next();
}

void Iterator::prev() {
  _iterator->Prev();
}

std::string Iterator::key() {
  return _iterator->key().ToString();
}

std::string Iterator::value() {
  return _iterator->value().ToString();
}

// virtual Status status() const = 0;

Iterator::~Iterator() {
  delete _iterator;
}

