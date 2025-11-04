#include <iostream>
#include <algorithm>
#include <cmath>
#include "Number.hpp"

Number::Number(){
  _table = new uint8_t[defaultLength];
  _isTemporary = false;
  _length = defaultLength;
  _firstNonZeroDigitId = 0;
  this->set0();
}

Number::Number(int length){
  _table = new uint8_t[length];
  _isTemporary = false;
  _length = length;
  _firstNonZeroDigitId = 0;
  this->set0();
}

Number::Number(const Number &other){
  _length = other._length;
  _isTemporary = false;
  _table = new uint8_t[_length];
  _firstNonZeroDigitId = other._firstNonZeroDigitId;
  _isNegative = other._isNegative;

  for (int i = 0; i < _length; i++){
    _table[i] = other._table[i];
  }
}

Number::~Number(){
  delete [] _table;
}

void Number::_changeTabLen(int newLength) {
  delete [] _table;
  _table = new uint8_t[newLength];
  _length = newLength;
}

void Number::operator=(int value){
  _firstNonZeroDigitId = -1;
  if(value < 0){
    value = -value;
    _isNegative = true;
  }else {
    _isNegative = false;
  }

  int length = std::log(value) /std::log(systemBase) + 1;
  if (length > _length){
    _changeTabLen(length);
  }

  for (int i = 0; i < _length ; i++){
    _table[i] = value % systemBase;
    value = value / systemBase;
    if (value == 0 && _firstNonZeroDigitId == -1) {
      _firstNonZeroDigitId = i;
    } 
  }
}

void Number::operator=(const Number &value){
  if (_length < value._firstNonZeroDigitId + 1){
    _changeTabLen(value._firstNonZeroDigitId + 1);
  }
  set0();
  _isNegative = value._isNegative;
  _firstNonZeroDigitId = value._firstNonZeroDigitId;
  for (int i = 0; i <= _firstNonZeroDigitId; i++){
    _table[i] = value._table[i];
  }

  if (value._isTemporary) delete &value;
}

Number& Number::_addAbsoluteValue(const Number &value) const {
  Number *result = new Number((std::max(_firstNonZeroDigitId, value._firstNonZeroDigitId) + 2));
  int buffor = 0;
  int shortSum = 0;

  for (int i = 0; i < result->_length; i++) {
    shortSum += buffor;
    if (i <= _firstNonZeroDigitId){
      shortSum += _table[i];
    }
    if (i <= value._firstNonZeroDigitId) {
      shortSum += value._table[i];
    }
    result->_table[i] = shortSum % systemBase;
    buffor = shortSum / systemBase;
    shortSum = 0;
  }
  
  if (result->_table[result->_length - 1] != 0) {
    result->_firstNonZeroDigitId = result->_length - 1;
  } else {
    result->_firstNonZeroDigitId = result->_length - 2;
  }

  result->_isTemporary = true;
  return *result;
}

Number& Number::_subtractAbsoluteValue(const Number &value) const {
  Number *result = new Number(_firstNonZeroDigitId + 1);
  int buffor = 0;
  
  for (int i = 0; i <= _firstNonZeroDigitId; i++) {
    buffor += _table[i];
    if (i <= value._firstNonZeroDigitId) {
      buffor -= value._table[i];
    }
    if (buffor < 0) {
      result->_table[i] = buffor + systemBase;
      buffor = -1;
    } else {
      result->_table[i] = buffor;
      buffor = 0;
    }
  }

  result->_normalize();
  result->_isTemporary = true;
  return *result;
}

int Number::_compareAbsoluteValues(const Number &value) const {
  if (_firstNonZeroDigitId > value._firstNonZeroDigitId) return 1;
  if (_firstNonZeroDigitId < value._firstNonZeroDigitId) return -1;
  for (int i = _firstNonZeroDigitId; i >= 0; i--){
    if (_table[i] > value._table[i]) return 1;
    if (_table[i] < value._table[i]) return -1;
  }
  return 0;
}

Number& Number::operator+(const Number &value){
  Number *result;
  int comparison = _compareAbsoluteValues(value);

  if (_isNegative == value._isNegative){
    result = &_addAbsoluteValue(value);
  } else if(comparison == 1){
    result = &_subtractAbsoluteValue(value);
  } else {
    result = &value._subtractAbsoluteValue(*this);
  }

  if (comparison == -1) {
    result->_isNegative = value._isNegative;
  } else{
    result->_isNegative = _isNegative;
  }
  
  result->_isTemporary = true;
  return *result;
}

void Number::operator++(int) {
    Number *temp = new Number(*this);
    Number one;
    one = 1;
    *this = *this + one;
}

Number& Number::operator-(const Number &value) {
  Number *result;
  int comparison = _compareAbsoluteValues(value);

  if (_isNegative != value._isNegative){
    result = &_addAbsoluteValue(value);
  } else if(comparison == 1){
    result = &_subtractAbsoluteValue(value);
  } else {
    result = &value._subtractAbsoluteValue(*this);
  }

  if (comparison == -1) {
    result->_isNegative = !value._isNegative;
  } else{
    result->_isNegative = _isNegative;
  }

  result->_normalize();
  result->_isTemporary = true;
  return *result;
}

Number& Number::operator*(const Number &value){
  Number *result = new Number(_length + value._length);
  int buffor = 0;
  int shortMultiply = 0;
  const uint8_t *a;
  const uint8_t *b;
  int aLen;
  int bLen;

  if (_length >= value._length){
    a = _table;
    aLen = _length;
    b = value._table;
    bLen = value._length;
  } else {
    a = value._table;
    aLen = value._length;
    b = _table;
    bLen = _length;
  }

  for (int i = 0; i < bLen; i++) {
    for (int j = 0; j < aLen; j++) {
      shortMultiply = buffor + a[j] * b[i] + result->_table[i+j];
      result->_table[i+j] = shortMultiply % systemBase;
      buffor = shortMultiply / systemBase;
    }
  }

  result->_isNegative = !(_isNegative == value._isNegative);
  result->_isTemporary = true;
  result->_normalize();
  return *result;
}

Number& Number::operator/(const Number &value){
  if (value._firstNonZeroDigitId == -1 || (value._firstNonZeroDigitId == 0 && value._table[0] == 0)) {
    throw std::runtime_error("Division by zero");
  }
  
  Number *result = new Number(_firstNonZeroDigitId + 1);
  Number *tmp = new Number(value._firstNonZeroDigitId + 2);
  Number systemBaseNum;
  Number currentResult;
  
  systemBaseNum = systemBase;
  for (int i = _firstNonZeroDigitId; i >= 0; i--) {
    *tmp = *tmp * systemBaseNum;
    tmp->_table[0] = _table[i];
    *result = *result * systemBaseNum;
    currentResult = 0;
    currentResult._normalize();
    
    while (tmp->_compareAbsoluteValues(value) != -1){
      currentResult++;
      *tmp = tmp->_subtractAbsoluteValue(value);
      tmp->_normalize();
    }
    *result = currentResult + *result;
  }
  
  result->_isNegative = !(_isNegative == value._isNegative);
  result->_normalize();
  result->_isTemporary = true;
  
  if (tmp->_isTemporary) {
    delete tmp;
  }
  
  return *result;
}

std::string Number::toStr() const{
  std::string val;
  if (_isNegative){
    val+="-";
  }
  for (int i = _firstNonZeroDigitId; i >= 0; i--){
    val+= static_cast<char>(_table[i] + '0');
  }
  return val;
}

void Number::set0(){
  for (int i = 0; i < _length; i++){
    _table[i] = 0;
  }
  _isNegative = false;
  _firstNonZeroDigitId = 0;
}

void Number::_normalize(){
  int i = _length - 1;
  int nonZero = 0;

  while (i > 0 && nonZero == 0) {
    if (_table[i] != 0){
      nonZero = i;
    }
    i--;
  }

  _firstNonZeroDigitId = nonZero;
}
