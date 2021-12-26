#ifndef IMATHOBJECT_HPP
#define IMATHOBJECT_HPP

class IMathObject {
protected:
  IMathObject() = default;
  IMathObject(IMathObject &&rhs) = default;
  IMathObject(const IMathObject &rhs) = default;
  IMathObject &operator=(IMathObject &&rhs) = default;
  IMathObject &operator=(const IMathObject &rhs) = default;

public:
  virtual ~IMathObject() = 0;
};

inline IMathObject::~IMathObject() = default;

#endif // IMATHOBJECT_HPP
