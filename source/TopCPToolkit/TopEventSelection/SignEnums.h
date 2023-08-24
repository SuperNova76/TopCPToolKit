#ifndef EVENT_SELECTOR_SIGN_ENUMS_H
#define EVENT_SELECTOR_SIGN_ENUMS_H

namespace SignEnum {
  enum ComparisonOperator {
    LT,
    GT,
    EQ,
    GE,
    LE
  };
  
  static std::map<std::string, ComparisonOperator> stringToOperator = {
    {"LT", ComparisonOperator::LT}, // <
    {"GT", ComparisonOperator::GT}, // >
    {"EQ", ComparisonOperator::EQ}, // ==
    {"GE", ComparisonOperator::GE}, // >=
    {"LE", ComparisonOperator::LE}  // <=
  };

  template <typename T>
  bool checkValue(T reference, ComparisonOperator sign, T test) {
    switch (sign) {
    case ComparisonOperator::LT:
      return test < reference;
    case ComparisonOperator::GT:
      return test > reference;
    case ComparisonOperator::EQ:
      return test == reference;
    case ComparisonOperator::GE:
      return test >= reference;
    case ComparisonOperator::LE:
      return test <= reference;
    }
    throw std::runtime_error("SignEnum::checkValue did not recognise the sign argument! Make sure it is listed within SignEnum::ComparisonOperator.");
    return false;
  }

} // namespace SignEnum

#endif // EVENT_SELECTOR_SIGN_ENUMS_H
