#pragma once

#include <vector>
#include "Error.hpp"

class Node;
class Tree;

template <typename T, typename E>
class Result {
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

template<typename T, typename E>
Result<T, E>::Result() {
    _value = NULL;
}

template<typename T, typename E>
Result<T, E>::Result(const T& value) {
    this->_value = new T(value);
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
    for (E* err : _errors) {
        delete err;
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

template<typename T, typename E>
Result<T, E>& Result<T, E>::operator=(const Result<T, E>& other) {
    if (this != &other) {
        delete _value;
        _value = other._value ? new T(*other._value) : nullptr;
        _errors = other._errors; // Shallow copy, deep copy of errors handled in destructor
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

template<typename T, typename E>
T& Result<T, E>::getValue() {
    return *_value;
}

template<typename T, typename E>
std::vector<E*>& Result<T, E>::getErrors() {
    return _errors;
}

template<typename T, typename E>
void Result<T, E>::joinErrors(const Result<T, E>& other) {
    for (E* err : other._errors) {
        _errors.push_back(new E(*err));
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

template<typename T, typename E>
std::string Result<T, E>::errorsToString() {
    std::string result;
    for (size_t i = 0; i < _errors.size(); ++i) {
        if (i > 0) result += "\n";
        result += _errors[i]->toString();
    }
    return result;
}

template<typename E>
class Result<void, E> {
public:
    Result();
    Result(E* error);
    Result(std::vector<E*>& errors);
    Result(const Result<void, E>& other);
    ~Result() = default;

    static Result<void, E> ok();
    static Result<void, E> warning(E* error);
    static Result<void, E> fail(E* error);
    static Result<void, E> fail(std::vector<E*>& errors);

    std::string errorsToString();
    void addError(E* error);

    bool isSuccess() const;
    bool errorsExist();

    void joinErrors(const Result<void, E>& other);

private:
    std::vector<E*> _errors;
    bool _success;
};

template<typename E>
Result<void, E>::Result() {}

template<typename E>
Result<void, E>::Result(E* error) {
    _errors.push_back(error);
}

template<typename E>
Result<void, E>::Result(std::vector<E*>& errors) : _errors(errors) {}

template<typename E>
Result<void, E>::Result(const Result<void, E>& other) {
    for (E* err : other._errors) {
        _errors.push_back(new E(*err));
    }
}

template<typename E>
Result<void, E> Result<void, E>::ok() {
    Result<void, E> res;
    res._success = true;
    return res;
}

template<typename E>
Result<void, E> Result<void, E>::warning(E* error) {
    Result<void, E> res(error);
    res._success = true;
    return res;
}

template<typename E>
Result<void, E> Result<void, E>::fail(E* error) {
    Result<void, E> res(error);
    res._success = false;
    return res;
}

template<typename E>
Result<void, E> Result<void, E>::fail(std::vector<E*>& errors) {
    Result<void, E> res(errors);
    res._success = false;
    return res;
}

template<typename E>
std::string Result<void, E>::errorsToString() {
    std::string result;
    for (size_t i = 0; i < _errors.size(); ++i) {
        if (i > 0) result += "\n";
        result += _errors[i]->toString();
    }
    return result;
}

template<typename E>
void Result<void, E>::addError(E* error) {
    _errors.push_back(error);
}

template<typename E>
bool Result<void, E>::isSuccess() const {
    return _success;
}

template<typename E>
bool Result<void, E>::errorsExist() {
    return !_errors.empty();
}

template<typename E>
void Result<void, E>::joinErrors(const Result<void, E>& other) {
    for (E* err : other._errors) {
        _errors.push_back(new E(*err));
    }
}

