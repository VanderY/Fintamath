#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <string>

#include "fintamath/math_objects/nodes/terms/numbers/INumber.hpp"

class Rational final : public INumber {
public:
  Rational() = default;
  [[nodiscard]] std::string toString() const override;
};

#endif // RATIONAL_HPP
