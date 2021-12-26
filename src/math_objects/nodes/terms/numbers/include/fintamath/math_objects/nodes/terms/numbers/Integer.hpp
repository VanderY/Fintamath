#ifndef INTEGER_HPP
#define INTEGER_HPP

#include <string>

#include "fintamath/math_objects/nodes/terms/numbers/INumber.hpp"

class Integer final : public INumber {
public:
  Integer() = default;
  [[nodiscard]] std::string toString() const override;
};

#endif // INTEGER_HPP
