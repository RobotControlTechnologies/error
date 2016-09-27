/*
 * File:   error.h
 * Author: Tulkin
 *
 * Created on 17 апреля 2015 г., 19:37
 */

#ifndef RCT_ERROR_H
#define RCT_ERROR_H

#include "base_error.h"

class Error final: public BaseError {
private:
  va_list m_va;
protected:
  void throwThis() override;
public:
  Error() = default;
  Error(BaseError* child, std::string mask, ...);
  Error(std::string mask, ...);
};

#endif /* RCT_ERROR_H */
