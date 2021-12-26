#ifndef INODE_HPP
#define INODE_HPP

#include <string>

#include "fintamath/math_objects/IMathObject.hpp"

class INode : public IMathObject {
protected:
  INode() = default;
  INode(INode &&rhs) = default;
  INode(const INode &rhs) = default;
  INode &operator=(INode &&rhs) = default;
  INode &operator=(const INode &rhs) = default;

public:
  ~INode() override = 0;

  [[nodiscard]] virtual std::string toString() const = 0;
};

inline INode::~INode() = default;

#endif // INODE_HPP
