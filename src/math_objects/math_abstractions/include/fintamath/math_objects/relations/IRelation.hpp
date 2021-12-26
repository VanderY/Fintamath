#ifndef IRELATION_HPP
#define IRELATION_HPP

#include <string>

#include "fintamath/math_objects/IMathObject.hpp"

class IRelation : public IMathObject {
protected:
  IRelation() = default;
  IRelation(IRelation &&rhs) = default;
  IRelation(const IRelation &rhs) = default;
  IRelation &operator=(IRelation &&rhs) = default;
  IRelation &operator=(const IRelation &rhs) = default;

public:
  ~IRelation() override = 0;

  [[nodiscard]] virtual std::string toString() const = 0;
};

inline IRelation::~IRelation() = default;

#endif // IRELATION_HPP
