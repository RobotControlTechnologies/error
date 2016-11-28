#ifndef RCT_BASE_ERROR_H
#define RCT_BASE_ERROR_H

#include <cstdarg>
#include <list>
#include <memory>
#include <string>

class BaseError {
private:
  const bool m_isEmpty;
  const std::unique_ptr<BaseError> m_child;
  const std::string m_message;

  std::list<std::unique_ptr<BaseError>> m_neighbours;
protected:
  virtual void throwThis() = 0;
public:
  BaseError();
  virtual ~BaseError();

  BaseError(BaseError* child, std::string mask, va_list args);
  BaseError(std::string mask, va_list args);

  bool isEmpty() const;
  const std::string& getMessage() const;
  void checkSelf();
  void checkSelfThrow();
  void append(BaseError *neighbour);

  using Action = std::function<void(const BaseError* /* error */, unsigned /* level */)>;
  void forEach(Action action, unsigned level = 0) const;

  std::string emit(unsigned level = 0) const;
};


#endif // RCT_BASE_ERROR_H