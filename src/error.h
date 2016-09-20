/*
 * File:   error.h
 * Author: Tulkin
 *
 * Created on 17 апреля 2015 г., 19:37
 */

#ifndef RCT_ERROR_H
#define RCT_ERROR_H

#include "current/module.h"

#include <cstdarg>
#include <list>
#include <string>

class Error {
private:
  bool is_empty;
  ConsoleColor color;
  std::string message;
  Error *child;
  std::list<Error *> neighbours;
  void init(std::string mask, va_list *args);
public:
  Error();
  Error(std::string mask, ...);
  Error(ConsoleColor color, std::string mask, ...);
  Error(Error *child, std::string mask, ...);
  Error(Error *child, ConsoleColor color, std::string mask, ...);

  // va_list
  Error(ConsoleColor color, std::string mask, va_list _list);

  bool isEmpty();
  void checkSelf();
  void checkSelfThrow();
  void append(Error *neighbour);
  std::string emit(unsigned int level = 0);
  ~Error();
};

#endif /* RCT_ERROR_H */
