#ifndef INUMBER_HPP
#define INUMBER_HPP

#include "fintamath/math_objects/nodes/terms/ITerm.hpp"

class INumber : public ITerm {
protected:
  INumber() = default;
  INumber(INumber &&rhs) = default;
  INumber(const INumber &rhs) = default;
  INumber &operator=(INumber &&rhs) = default;
  INumber &operator=(const INumber &rhs) = default;

public:
  ~INumber() override = 0;
};

inline INumber::~INumber() = default;

#endif // INUMBER_HPP
