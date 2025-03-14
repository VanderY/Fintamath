#include "calculator/Calculator.hpp"

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <string>

#include "expressions/Expression.hpp"
#include "single_entities/terms/numbers/Rational.hpp"

static void insertFloatingPoint(std::string &strVal, int64_t precision);

size_t cutZeros(std::string &strVal) {
  size_t order = 0;
  while (*strVal.begin() == '0') {
    strVal.erase(strVal.begin());
    order++;
  }
  return order;
}

void Calculator::toShortForm(std::string &strVal) const {
  bool isNegative = (*strVal.begin() == '-');
  if (isNegative) {
    strVal.erase(0, 1);
  }

  if (strVal == "0") {
    return;
  }

  if (*strVal.begin() == '0') {
    strVal.erase(strVal.begin() + 1);
    size_t order = cutZeros(strVal);
    insertFloatingPoint(strVal, solver.getPrecision());
    strVal += "*10^(-";
    strVal += std::to_string(order) + ')';
  } else {
    size_t order = distance(begin(strVal), find(begin(strVal), end(strVal), '.'));
    if (order != strVal.size()) {
      strVal.erase(order, 1);
    }
    if (strVal.size() > solver.getPrecision() + 1) {
      strVal.erase(solver.getPrecision() + 2);
    }

    insertFloatingPoint(strVal, solver.getPrecision());

    if (order > 1) {
      strVal += "*10^";
      strVal += std::to_string(order - 1);
    }
  }

  if (isNegative) {
    strVal.insert(strVal.begin(), '-');
  }
}

std::string Calculator::calculate(const std::string &strExpr) {
  Expression expr(strExpr);
  Rational val = solver.solve(expr);
  std::string valStr = val.toString(solver.getPrecision());
  toShortForm(valStr);
  return valStr;
}

int64_t Calculator::getPrecision() const {
  return solver.getPrecision();
}

void Calculator::setPrecision(int64_t precision) {
  solver.setPrecision(precision);
}

static void insertFloatingPoint(std::string &strVal, int64_t precision) {
  strVal.insert(strVal.begin() + 1, '.');
  strVal += '0';
  strVal = Rational(strVal).toString(precision);
}
