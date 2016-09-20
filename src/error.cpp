#include "error.h"

#include <cstdio>

void Error::init(std::string mask, va_list *args) {
  char buffer[1024];
  vsnprintf(buffer, 1024, mask.c_str(), *args);
  message += buffer;
}

#define ERROR_CONSTRUCTOR_CODE \
  va_list args;                \
  va_start(args, mask);        \
  init(mask, &args);           \
  va_end(args);

Error::Error()
    : is_empty(true),
      color(ConsoleColor(ConsoleColor::red)),
      message(""),
      child(nullptr)
{}

Error::Error(std::string mask, ...)
    : is_empty(false),
      color(ConsoleColor::red),
      message(""),
      child(nullptr)
{
  ERROR_CONSTRUCTOR_CODE
}

Error::Error(ConsoleColor color, std::string mask, ...)
    : is_empty(false),
      color(color),
      message(""),
      child(nullptr)
{
  ERROR_CONSTRUCTOR_CODE
}

Error::Error(Error *child, std::string mask, ...)
    : is_empty(false),
      color(ConsoleColor::red),
      child(child)
{
  ERROR_CONSTRUCTOR_CODE
}

Error::Error(Error *child, ConsoleColor color, std::string mask, ...)
    : is_empty(false), color(color), child(child)
{
  ERROR_CONSTRUCTOR_CODE
}

Error::Error(ConsoleColor color, std::string mask, va_list _list)
    : is_empty(false), color(color), message(""), child(nullptr)
{
  init(mask, &_list);
}

bool Error::isEmpty() { return !(neighbours.size() || child || !is_empty); }

void Error::checkSelf() {
  checkSelfThrow();
  delete this;
}

void Error::checkSelfThrow() {
  if (!isEmpty()) {
    throw this;
  }
}

void Error::append(Error *neighbour) { neighbours.push_back(neighbour); }

std::string Error::emit(unsigned int level) {
  std::string result = "";
  if (!is_empty) {
    for (unsigned int i = 0; i < level; ++i) {
      result += "  ";
    }
    result += message;
    result += "\n";
  }

  if (child) {
    result += child->emit(level + 1);
  }
  if (!neighbours.empty()) {
    for (Error* e : neighbours) {
      result += e->emit(level);
    }
  }
  return result;
}

Error::~Error() {
  if (child) {
    delete child;
  }
  if (neighbours.size()) {
    for (Error* e : neighbours) {
      delete e;
    }
  }
}