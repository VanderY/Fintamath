#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <cstddef>
#include <cstdint>
#include <iosfwd>
#include <string>

#include "single_entities/ISingleEntity.hpp"
#include "single_entities/terms/numbers/Integer.hpp"

class Rational : public ISingleEntity {
public:
  Rational() = default;
  explicit Rational(const std::string &strVal);
  // cppcheck-suppress noExplicitConstructor // NOLINTNEXTLINE
  Rational(Integer val);
  // cppcheck-suppress noExplicitConstructor // NOLINTNEXTLINE
  Rational(int64_t val);
  Rational(Integer numerator, Integer denominator);
  Rational(int64_t numerator, int64_t denominator);

  Rational &operator=(const Integer &rhs);
  Rational &operator=(int64_t rhs);

  Rational &operator+=(const Rational &rhs);
  Rational &operator+=(const Integer &rhs);
  Rational &operator+=(int64_t rhs);
  Rational operator+(const Rational &rhs) const;
  Rational operator+(const Integer &rhs) const;
  Rational operator+(int64_t rhs) const;
  friend Rational operator+(const Integer &lhs, const Rational &rhs);
  friend Rational operator+(int64_t lhs, const Rational &rhs);

  Rational &operator-=(const Rational &rhs);
  Rational &operator-=(const Integer &rhs);
  Rational &operator-=(int64_t rhs);
  Rational operator-(const Rational &rhs) const;
  Rational operator-(const Integer &rhs) const;
  Rational operator-(int64_t rhs) const;
  friend Rational operator-(const Integer &lhs, const Rational &rhs);
  friend Rational operator-(int64_t lhs, const Rational &rhs);

  Rational &operator*=(const Rational &rhs);
  Rational &operator*=(const Integer &rhs);
  Rational &operator*=(int64_t rhs);
  Rational operator*(const Rational &rhs) const;
  Rational operator*(const Integer &rhs) const;
  Rational operator*(int64_t rhs) const;
  friend Rational operator*(const Integer &lhs, const Rational &rhs);
  friend Rational operator*(int64_t lhs, const Rational &rhs);

  Rational &operator/=(const Rational &rhs);
  Rational &operator/=(const Integer &rhs);
  Rational &operator/=(int64_t rhs);
  Rational operator/(const Rational &rhs) const;
  Rational operator/(const Integer &rhs) const;
  Rational operator/(int64_t rhs) const;
  friend Rational operator/(const Integer &lhs, const Rational &rhs);
  friend Rational operator/(int64_t lhs, const Rational &rhs);

  Rational &operator++();
  Rational operator++(int);

  Rational &operator--();
  Rational operator--(int);

  Rational operator+() const;
  Rational operator-() const;

  bool operator==(const Rational &rhs) const;
  bool operator==(const Integer &rhs) const;
  bool operator==(int64_t rhs) const;
  friend bool operator==(const Integer &lhs, const Rational &rhs);
  friend bool operator==(int64_t lhs, const Rational &rhs);

  bool operator!=(const Rational &rhs) const;
  bool operator!=(const Integer &rhs) const;
  bool operator!=(int64_t rhs) const;
  friend bool operator!=(const Integer &lhs, const Rational &rhs);
  friend bool operator!=(int64_t lhs, const Rational &rhs);

  bool operator<(const Rational &rhs) const;
  bool operator<(const Integer &rhs) const;
  bool operator<(int64_t rhs) const;
  friend bool operator<(const Integer &lhs, const Rational &rhs);
  friend bool operator<(int64_t lhs, const Rational &rhs);

  bool operator>(const Rational &rhs) const;
  bool operator>(const Integer &rhs) const;
  bool operator>(int64_t rhs) const;
  friend bool operator>(const Integer &lhs, const Rational &rhs);
  friend bool operator>(int64_t lhs, const Rational &rhs);

  bool operator<=(const Rational &rhs) const;
  bool operator<=(const Integer &rhs) const;
  bool operator<=(int64_t rhs) const;
  friend bool operator<=(const Integer &lhs, const Rational &rhs);
  friend bool operator<=(int64_t lhs, const Rational &rhs);

  bool operator>=(const Rational &rhs) const;
  bool operator>=(const Integer &rhs) const;
  bool operator>=(int64_t rhs) const;
  friend bool operator>=(const Integer &lhs, const Rational &rhs);
  friend bool operator>=(int64_t lhs, const Rational &rhs);

  friend std::istream &operator>>(std::istream &in, Rational &rhs);
  friend std::ostream &operator<<(std::ostream &out, const Rational &rhs);

  Integer getInteger() const;
  Integer getNumerator() const;
  Integer getDenominator() const;

  Rational round(size_t precision) const;

  std::string toString() const override;
  std::string toString(size_t precision) const;
  std::string getTypeName() const override;

private:
  Integer numerator = 0;
  Integer denominator = 1;
  bool sign{};

  void fixNegative();
  void fixZero();
  void toIrreducibleRational();
  static void toCommonDenominators(Rational &lhs, Rational &rhs);
};

#endif // RATIONAL_HPP
