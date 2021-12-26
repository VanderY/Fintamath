#ifndef NUMBERSPARSER_HPP
#define NUMBERSPARSER_HPP

class NumbersParser final {
public:
  NumbersParser() = delete;
  NumbersParser(NumbersParser &&) = delete;
  NumbersParser(const NumbersParser &) = delete;
  NumbersParser &operator=(NumbersParser &&) = delete;
  NumbersParser &operator=(const NumbersParser &) = delete;
  ~NumbersParser() = delete;
};

#endif // NUMBERSPARSER_HPP
