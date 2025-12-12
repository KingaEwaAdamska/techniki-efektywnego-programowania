#pragma once

#include <vector>
#include "Error.hpp"

class Tree;
class Node;

template <typename T, typename E>
class Result {
    friend class Result<Tree*, Error>;
public:
    Result();
    Result(const T& value);
    Result(const T& value, E* error);
    Result(E* error);
    Result(std::vector<E*>& errors);
    Result(const Result<T, E>& other);
    ~Result();

    static Result<T, E> ok(const T& value);
    static Result<T, E> warning(const T& value, E* error);
    static Result<T, E> fail(E* error);
    static Result<T, E> fail(std::vector<E*>& errors);

    Result<T, E>& operator=(const Result<T, E>& other);

    bool isSuccess();
    bool errorsExist();
    T& getValue();
    std::vector<E*>& getErrors();
    void joinErrors(const Result<T, E>& other);
    void addValue(const T& val);
    void addError(E* error);
    std::string errorsToString();

private:
    T* _value;
    std::vector<E*> _errors;
};

template<typename E>
class Result<Tree*, E>{
  public:
    Result(Tree* value);
    Result();
    Result(std::vector<E*>& errors);
    static Result<Tree*, E> fail(E* error);
    static Result<Tree*, E> fail(std::vector<E*>& errors);
    static Result<Tree*, E> ok(const Tree*& value);
    void addError(E* error);
    std::string errorsToString();
    void joinErrors(const Result<Node*, E>& other);
    bool errorsExist();
 private:
    Tree** _value;
    std::vector<E*> _errors;   
};

template<typename E>
Result<Tree*, E> Result<Tree*, E>::fail(E* error) {
  Result<Tree*, E> res;
  return res;
}

template<typename T, typename E>
Result<T, E>::Result() {
    _value = NULL;
}

template<typename E>
Result<Tree*, E>::Result() {
    _value = NULL;
}

template<typename T, typename E>
Result<T, E>::Result(const T& value) {
    this->_value = new T(value);
}

template<typename E>
Result<Tree*, E>::Result(Tree* value) {
    this->_value = &value;
}

template<typename T, typename E>
Result<T, E>::Result(const T& value, E* error) {
    this->_value = new T(value);
    _errors.push_back(error);
}

template<typename T, typename E>
Result<T, E>::Result(E* error) {
    _value = NULL;
    _errors.push_back(error);
}

template<typename T, typename E>
Result<T, E>::Result(std::vector<E*>& errors) {
    this->_value = NULL;
    int size = errors.size();

    for (int i = 0; i < size; i++) {
        this->_errors.push_back(new E(*(errors[i])));
    }
}
template<typename E>
Result<Tree*, E>::Result(std::vector<E*>& errors) {
    this->_value = NULL;
    int size = errors.size();

    for (int i = 0; i < size; i++) {
        this->_errors.push_back(new E(*(errors[i])));
    }
}

template<typename T, typename E>
Result<T, E>::Result(const Result<T, E>& other) {
    if (other._value) {
        this->_value = new T(*other._value);
    } else {
        this->_value = NULL;
    }

    int size = other._errors.size();

    for (int i = 0; i < size; i++) {
        this->_errors.push_back(new E(*(other._errors[i])));
    }
}

template<typename T, typename E>
Result<T, E>::~Result() {
    delete _value;
    int errorsSize = _errors.size();
    for (int i = 0; i < errorsSize; i++) {
        delete _errors[i];
    }
}

template<typename T, typename E>
Result<T, E> Result<T, E>::ok(const T& value) {
    return Result<T, E>(value);
}

template<typename T, typename E>
Result<T, E> Result<T, E>::warning(const T& value, E* error) {
    return Result<T, E>(value, error);
}

template<typename T, typename E>
Result<T, E> Result<T, E>::fail(E* error) {
    return Result<T, E>(error);
}

template<typename T, typename E>
Result<T, E> Result<T, E>::fail(std::vector<E*>& errors) {
    return Result<T, E>(errors);
}

template<typename E>
Result<Tree*, E> Result<Tree*, E>::fail(std::vector<E*>& errors) {
    return Result<Tree*, E>(errors);
}
template<typename T, typename E>
Result<T, E>& Result<T, E>::operator=(const Result<T, E>& other) {
    if (this != &other) {
        delete this->_value;

        if (other._value)
            this->_value = new T(*other._value);
        else
            this->_value = NULL;

        this->_errors = other._errors;
    }
    return *this;
}

template<typename T, typename E>
bool Result<T, E>::isSuccess() {
    return this->_value != NULL;
}

template<typename T, typename E>
bool Result<T, E>::errorsExist() {
    return !_errors.empty();
}


template<typename E>
bool Result<Tree*, E>::errorsExist() {
    return !_errors.empty();
}

template<typename T, typename E>
T& Result<T, E>::getValue() {
    return *this->_value;
}

template<typename T, typename E>
std::vector<E*>& Result<T, E>::getErrors() {
    return this->_errors;
}

template<typename T, typename E>
void Result<T, E>::joinErrors(const Result<T, E>& other) {
    int size = other._errors.size();
    for (int i = 0; i < size; i++) {
        E* copied_error = new E(*(other._errors[i]));
        this->_errors.push_back(copied_error);
    }
}

template<typename E>
void Result<Tree*, E>::joinErrors(const Result<Node*, E>& other) {
    int size = other._errors.size();
    for (int i = 0; i < size; i++) {
        E* copied_error = new E(*(other._errors[i]));
        this->_errors.push_back(copied_error);
    }
}

template<typename T, typename E>
void Result<T, E>::addValue(const T& val) {
    _value = new T(val);
}

template<typename T, typename E>
void Result<T, E>::addError(E* error) {
    _errors.push_back(error);
}

template<typename E>
void Result<Tree*, E>::addError(E* error) {
    _errors.push_back(error);
}
template<typename E>
std::string Result<Tree*, E>::errorsToString() {
  std::string result = "";
  int size = _errors.size();
  for (int i = 0; i < size; i++) {
    if (!result.empty()) {
      result += "\n";
    }
    result += _errors[i]->toString();
  }
  return result;
}

template<typename E>
class Result<void, E> {
public:
    Result() {}

    Result<void, E>(E* error){
      _errors.push_back(error);
    }

    Result<void, E>(std::vector<E*>& errors){
      this->_errors = errors;
    }

    Result<void, E>(const Result<void, E>& other){
      int size = other._errors.size();

      for (int i = 0; i < size; i++) {
        this->_errors.push_back(new E(*(other._errors[i])));
      }
    }

    static Result<void, E> ok(){
      Result<void, E> res;
      res._success = true;
      return res;
    }

    static Result<void, E> warning(E* error) {
      Result<void, E> res(error);
      res._success = true;
      return res;
    }

    static Result<void, E> fail(E* error) {
      Result<void, E> res(error);
      res._success = false;
      return res;
    }

    static Result<void, E> fail(std::vector<E*>& errors) {
      Result<void, E> res(errors);
      res._success = false;
      return res;
    }

    std::string errorsToString() {
      std::string result = "";
      int size = _errors.size();
      for (int i = 0; i < size; i++) {
        if (!result.empty()) {
          result += "\n";
        }
        result += _errors[i]->toString();
      }
      return result;
    }

    void addError(E* error) {
        _errors.push_back(error);
    }

    bool isSuccess() const {
        return _success;
    }

    bool errorsExist() {
      return !_errors.is_empty();
    }

    void joinErrors(const Result<void, E>& other) {
      int size = other._errors.size();
      for (int i = 0; i < size; i++) {
        E* copied_error = new E(*(other._errors[i]));
        this->_errors.push_back(copied_error);
      }
    }
    
private:
    std::vector<E*> _errors;
    bool _success;
};

