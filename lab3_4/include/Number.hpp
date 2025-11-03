#include <stdint.h>
#include <string>

class Number {
  private:
  uint8_t *_table;
  int _length;
  bool _isNegative;
  bool _isTemporary;
  int _firstNonZeroDigitId;

  void _changeTabLen(int newLength);
  void _normalize();
  Number& _addAbsoluteValue(const Number &value) const;
  Number& _subtractAbsoluteValue(const Number &value) const;
  int _compareAbsoluteValues(const Number &value) const;  // 1 - this is greater, 0 - equal, -1 - this is smaller

  public:
  static const int defaultLength = 10;
  static const int systemBase = 10;

  Number();
  Number(int length);
  Number(const Number &other);
  ~Number();

  void operator=(int value);

  void operator=(const Number &value);
  Number& operator+(const Number &value);
  void operator++(int);
  Number& operator-(const Number &value);
  Number& operator*(const Number &value);
  Number& operator/(const Number &value);
  Number& operator%(Number &value);

  std::string toStr() const;
  void set0();
};  // class Number
