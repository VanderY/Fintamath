#ifndef TERMSPARSER_HPP
#define TERMSPARSER_HPP

class TermsParser final {
public:
  TermsParser() = delete;
  TermsParser(TermsParser &&) = delete;
  TermsParser(const TermsParser &) = delete;
  TermsParser &operator=(TermsParser &&) = delete;
  TermsParser &operator=(const TermsParser &) = delete;
  ~TermsParser() = default;
};

#endif // TERMSPARSER_HPP
