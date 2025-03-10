#include "expressions/Expression.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <ext/alloc_traits.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "single_entities/operators/Function.hpp"
#include "single_entities/operators/Operator.hpp"
#include "single_entities/terms/literals/Constant.hpp"
#include "single_entities/terms/numbers/Rational.hpp"

static std::vector<std::string> makeVectOfTokens(const std::string &strExpr);
static Expression makeExpression(const std::vector<std::string> &tokensVect);

static void cutSpaces(std::string &strExpr);

static bool isDigit(char ch);
static bool isLetter(char ch);

static void addMultiply(std::vector<std::string> &tokensVect);
static void addClosingBracket(std::vector<std::string> &tokensVect);
static void addOpenBracket(std::vector<std::string> &tokensVect);
static void addUnaryOperator(std::vector<std::string> &tokensVect);
static void addOperator(std::vector<std::string> &tokensVect, char token);
static void addRational(std::vector<std::string> &tokensVect, const std::string &token, size_t &pos);
static void addFactorial(std::vector<std::string> &tokensVect, const std::string &token, size_t &pos);
static void addConstOrFunction(std::vector<std::string> &tokensVect, const std::string &token, size_t &pos);
static void addBinaryFunctions(std::vector<std::string> &tokensVect);
static void addBinaryFunction(std::vector<std::string> &tokensVect, std::vector<size_t> &placementsVect, size_t num);
static void addValue(const std::shared_ptr<Expression::Elem> &elem, const std::string &token);

static bool descent(const std::vector<std::string> &tokensVect, const std::shared_ptr<Expression::Elem> &elem,
                    size_t begin, size_t end, const std::string &oper1, const std::string &oper2);
static bool descent(const std::vector<std::string> &tokensVect, const std::shared_ptr<Expression::Elem> &elem,
                    size_t begin, size_t end, const std::string &oper);
static bool descent(const std::vector<std::string> &tokensVect, const std::shared_ptr<Expression::Elem> &elem,
                    size_t begin, size_t end);

static void makeExpressionRec(const std::vector<std::string> &tokensVect, std::shared_ptr<Expression::Elem> &elem,
                              size_t first, size_t last);

Expression::Expression(const std::string &strExpr) {
  *this = makeExpression(makeVectOfTokens(strExpr));
}

std::shared_ptr<Expression::Elem> &Expression::getRootModifiable() {
  return root;
}

static std::vector<std::string> makeVectOfTokens(const std::string &strExpr) {
  std::string tmpStrExpr = strExpr;
  cutSpaces(tmpStrExpr);
  std::vector<std::string> tokensVect;

  size_t i = 0;
  while (i < tmpStrExpr.size()) {
    if (tmpStrExpr[i] == ')') {
      addClosingBracket(tokensVect);
    } else if (tmpStrExpr[i] == '(') {
      addOpenBracket(tokensVect);
    } else if (types::isOperator(std::string(1, tmpStrExpr[i]))) {
      addOperator(tokensVect, tmpStrExpr[i]);
    } else if (tmpStrExpr[i] == '!') {
      addFactorial(tokensVect, tmpStrExpr, i);
    } else if (isDigit(tmpStrExpr[i])) {
      addRational(tokensVect, tmpStrExpr, i);
    } else {
      addConstOrFunction(tokensVect, tmpStrExpr, i);
    }

    i++;
  }

  addBinaryFunctions(tokensVect);
  reverse(tokensVect.begin(), tokensVect.end());

  return tokensVect;
}

static Expression makeExpression(const std::vector<std::string> &tokensVect) {
  if (tokensVect.empty()) {
    throw std::invalid_argument("Expression invalid input");
  }
  Expression expr;
  expr.getRootModifiable() = std::make_shared<Expression::Elem>();
  makeExpressionRec(tokensVect, expr.getRootModifiable()->right, 0, tokensVect.size() - 1);
  return expr;
}

static void cutSpaces(std::string &strExpr) {
  while (!strExpr.empty()) {
    if (strExpr.front() != ' ') {
      break;
    }
    strExpr.erase(strExpr.begin());
  }

  int64_t i = 0;
  while (i < strExpr.size()) {
    if (strExpr[i] == ' ') {
      strExpr.erase(i, 1);
      i--;
    }
    i++;
  }
}

static bool isDigit(char ch) {
  return (ch >= '0' && ch <= '9');
}

static bool isLetter(char ch) {
  return ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'));
}

static void addMultiply(std::vector<std::string> &tokensVect) {
  if (tokensVect.empty()) {
    return;
  }
  if (tokensVect.back() != "," && tokensVect.back() != "(" && !types::isOperator(tokensVect.back()) &&
      !types::isFunction(tokensVect.back())) {
    tokensVect.emplace(tokensVect.end(), "*");
  }
}

static void addClosingBracket(std::vector<std::string> &tokensVect) {
  tokensVect.emplace_back(")");
}

static void addOpenBracket(std::vector<std::string> &tokensVect) {
  addMultiply(tokensVect);
  tokensVect.emplace_back("(");
}

static void addUnaryOperator(std::vector<std::string> &tokensVect) {
  if (tokensVect.back() == "+") {
    tokensVect.pop_back();
  } else if (tokensVect.back() == "-") {
    tokensVect.pop_back();
    tokensVect.emplace_back("-1");
    tokensVect.emplace_back("*");
  }
}

static void addOperator(std::vector<std::string> &tokensVect, char token) {
  tokensVect.emplace_back(1, token);
  if (tokensVect.size() == 1) {
    addUnaryOperator(tokensVect);
    return;
  }
  if (*(tokensVect.end() - 2) == "(") {
    addUnaryOperator(tokensVect);
  }
}

static void addRational(std::vector<std::string> &tokensVect, const std::string &token, size_t &pos) {
  addMultiply(tokensVect);

  std::string strVal;
  while (pos < token.size()) {
    strVal += token[pos];
    pos++;
    if (!isDigit(token[pos]) && !(token[pos] == '.')) {
      break;
    }
  }
  if (pos != 0) {
    pos--;
  }

  tokensVect.push_back(strVal);
}

static void addFactorial(std::vector<std::string> &tokensVect, const std::string &token, size_t &pos) {
  if (tokensVect.empty()) {
    throw std::invalid_argument("Expression invalid input");
  }

  std::string factorialFunc = "!";
  if (pos != token.size() - 1 && token[pos + 1] == '!') {
    factorialFunc += '!';
    pos++;
  }

  size_t bracketsNum = 0;

  for (size_t i = tokensVect.size() - 1; i > 0; i--) {
    if (tokensVect[i] == ")") {
      bracketsNum++;
    } else if (tokensVect[i] == "(") {
      if (bracketsNum == 0) {
        throw std::invalid_argument("Expression invalid input");
      }
      bracketsNum--;
    }
    if (bracketsNum == 0) {
      if (types::isFunction(tokensVect[i - 1])) {
        tokensVect.insert(tokensVect.begin() + (int64_t)i - 1, factorialFunc);
      }
      tokensVect.insert(tokensVect.begin() + (int64_t)i, factorialFunc);
      return;
    }
  }

  if (tokensVect.front() == "(") {
    if (bracketsNum == 0) {
      throw std::invalid_argument("Expression invalid input");
    }
    bracketsNum--;
  }
  if (bracketsNum != 0) {
    throw std::invalid_argument("Expression invalid input");
  }

  tokensVect.insert(tokensVect.begin(), factorialFunc);
}

static void addConstOrFunction(std::vector<std::string> &tokensVect, const std::string &token, size_t &pos) {
  if (token[pos] == '!') {
    addFactorial(tokensVect, token, pos);
    return;
  }
  if (token[pos] == ',') {
    tokensVect.emplace_back(",");
    return;
  }

  addMultiply(tokensVect);

  std::string literalExpr;
  while (pos < token.size()) {
    literalExpr += token[pos];
    pos++;
    if (!isLetter(token[pos])) {
      break;
    }
  }
  if (pos != 0) {
    pos--;
  }

  if (types::isConstant(literalExpr) || types::isFunction(literalExpr)) {
    tokensVect.push_back(literalExpr);
  } else {
    throw std::invalid_argument("Expression invalid input");
  }
}

static void addBinaryFunctions(std::vector<std::string> &tokensVect) {
  std::vector<size_t> placementsVect;
  size_t i = 0;
  while (i < tokensVect.size()) {
    if (types::isBinaryFunction(tokensVect[i]) &&
        find(placementsVect.begin(), placementsVect.end(), i) == placementsVect.end()) {
      addBinaryFunction(tokensVect, placementsVect, i);
    }
    i++;
  }
}

static void addBinaryFunction(std::vector<std::string> &tokensVect, std::vector<size_t> &placementsVect, size_t num) {
  std::string token = tokensVect[num];
  tokensVect.erase(tokensVect.begin() + (int64_t)num);
  size_t bracketsNum = 1;

  size_t i = num + 1;
  while (i < tokensVect.size()) {
    if (bracketsNum == 0) {
      throw std::invalid_argument("Expression invalid input");
    }

    if (tokensVect[i] == "(") {
      bracketsNum++;
    } else if (tokensVect[i] == ")") {
      bracketsNum--;
    } else if (bracketsNum == 1 && tokensVect[i] == ",") {
      tokensVect.erase(tokensVect.begin() + (int64_t)i);
      tokensVect.insert(tokensVect.begin() + (int64_t)i, {")", token, "("});

      transform(placementsVect.begin(), placementsVect.end(), placementsVect.begin(),
                [i](size_t k) { return (k > i) ? k + 1 : k; });
      placementsVect.push_back(i + 1);

      return;
    }

    i++;
  }

  throw std::invalid_argument("Expression invalid input");
}

static void addValue(const std::shared_ptr<Expression::Elem> &elem, const std::string &token) {
  if (types::isConstant(token)) {
    elem->info = std::make_shared<Constant>(token);
  } else {
    try {
      elem->info = std::make_shared<Rational>(token);
    } catch (const std::invalid_argument &) {
      throw std::invalid_argument("Expression invalid input");
    }
  }
}

static bool descent(const std::vector<std::string> &tokensVect, const std::shared_ptr<Expression::Elem> &elem,
                    size_t begin, size_t end, const std::string &oper1, const std::string &oper2) {
  size_t bracketsNum = 0;

  for (size_t i = begin; i <= end; i++) {
    if (tokensVect[i] == ")") {
      bracketsNum++;
    } else if (tokensVect[i] == "(") {
      if (bracketsNum == 0) {
        throw std::invalid_argument("Expression invalid input");
      }
      bracketsNum--;
    }

    if (bracketsNum == 0 && (tokensVect[i] == oper1 || tokensVect[i] == oper2)) {
      if (types::isBinaryFunction(oper1)) {
        elem->info = std::make_shared<Function>(tokensVect[i]);
      } else {
        elem->info = std::make_shared<Operator>(tokensVect[i]);
      }
      makeExpressionRec(tokensVect, elem->right, i + 1, end);
      makeExpressionRec(tokensVect, elem->left, begin, i - 1);
      return true;
    }
  }

  return false;
}

static bool descent(const std::vector<std::string> &tokensVect, const std::shared_ptr<Expression::Elem> &elem,
                    size_t begin, size_t end, const std::string &oper) {
  return descent(tokensVect, elem, begin, end, oper, "");
}

static bool descent(const std::vector<std::string> &tokensVect, const std::shared_ptr<Expression::Elem> &elem,
                    size_t begin, size_t end) {
  if (types::isFunction(tokensVect[end])) {
    elem->info = std::make_shared<Function>(tokensVect[end]);
    makeExpressionRec(tokensVect, elem->right, begin, end - 1);
    return true;
  }
  return false;
}

static void makeExpressionRec(const std::vector<std::string> &tokensVect, std::shared_ptr<Expression::Elem> &elem,
                              size_t first, size_t last) {
  if (first > last) {
    throw std::invalid_argument("Expression invalid input");
  }
  if (first == SIZE_MAX || last == SIZE_MAX) {
    throw std::invalid_argument("Expression invalid input");
  }

  if (elem == nullptr) {
    elem = std::make_shared<Expression::Elem>();
  }

  if (first == last) {
    addValue(elem, tokensVect[first]);
    return;
  }

  if (descent(tokensVect, elem, first, last, "+", "-")) {
    return;
  }
  if (descent(tokensVect, elem, first, last, "*", "/")) {
    return;
  }
  if (descent(tokensVect, elem, first, last, "^")) {
    return;
  }
  if (descent(tokensVect, elem, first, last, "log")) {
    return;
  }
  if (descent(tokensVect, elem, first, last)) {
    return;
  }
  if (tokensVect[first] == ")" && tokensVect[last] == "(") {
    makeExpressionRec(tokensVect, elem, first + 1, last - 1);
  }
}
