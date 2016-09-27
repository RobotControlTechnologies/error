#include "error.h"

#include <algorithm>
#include <cstdio>
#include <iterator>
#include <sstream>

BaseError::BaseError(): m_isEmpty{true}, m_child(nullptr) {}
BaseError::~BaseError() {}

static std::string generateMessage(std::string mask, va_list args) {
  std::string result;
  int sizeNeed = vsnprintf(nullptr, 0, mask.c_str(), args);
  if (sizeNeed >= 0) {
    result.resize(sizeNeed);
    vsnprintf(&result[0], sizeNeed + 1, mask.c_str(), args);
  } else {
    result.clear();
  }
  return result;
}

BaseError::BaseError(BaseError* child, std::string mask, va_list args):
    m_isEmpty{false}, m_child(child),
    m_message(generateMessage(mask, args)) {}

BaseError::BaseError(std::string mask, va_list args):
    BaseError(nullptr, mask, args) {}

bool BaseError::isEmpty() const {
  return !(m_neighbours.size() || m_child || !m_isEmpty);
}

const std::string& BaseError::getMessage() const {
  return m_message;
}

void BaseError::checkSelf() {
  checkSelfThrow();
  delete this;
}

void BaseError::checkSelfThrow() {
  if (!isEmpty()) {
    throwThis();
  }
}

void BaseError::append(BaseError *neighbour) {
  m_neighbours.emplace_back(neighbour);
}

void BaseError::forEach(Action action, unsigned level) const {
  if (!m_isEmpty) {
    action(this, level);
  }

  if (m_child) {
    m_child->forEach(action, level + 1);
  }

  for (const auto& e : m_neighbours) {
    if (e) {
      e->forEach(action, level);
    }
  }
}

std::string BaseError::emit(unsigned level) const {
  std::stringstream ss;
  forEach([&ss] (const BaseError* feError, unsigned feLevel) {
    std::fill_n(std::ostream_iterator<char>(ss), feLevel * 2, ' ');
    ss << feError->m_message << std::endl;
  }, level);
  return ss.str();
}

Error::Error(BaseError* child, std::string mask, ...):
    BaseError(child, mask, (va_start(m_va, mask), m_va))
{
  va_end(m_va);
}

Error::Error(std::string mask, ...):
    BaseError(mask, (va_start(m_va, mask), m_va))
{
  va_end(m_va);
}

void Error::throwThis() {
  throw this;
}