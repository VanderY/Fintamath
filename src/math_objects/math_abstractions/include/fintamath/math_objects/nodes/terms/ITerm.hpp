#ifndef ITERM_HPP
#define ITERM_HPP

#include "fintamath/math_objects/nodes/INode.hpp"

class ITerm : public INode {
protected:
  ITerm() = default;
  ITerm(ITerm &&rhs) = default;
  ITerm(const ITerm &rhs) = default;
  ITerm &operator=(ITerm &&rhs) = default;
  ITerm &operator=(const ITerm &rhs) = default;

public:
  ~ITerm() override = 0;
};

inline ITerm::~ITerm() = default;

#endif // ITERM_HPP
