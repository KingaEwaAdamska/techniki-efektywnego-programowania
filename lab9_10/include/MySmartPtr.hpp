#include "Counter.hpp"

template<typename T>
class MySmartPtr {
  public:
    MySmartPtr(); 
    MySmartPtr(T *ptr);
    MySmartPtr(const MySmartPtr<T> &other);
    ~MySmartPtr();

    T& operator*();
    T* operator->();
    MySmartPtr& operator=(const MySmartPtr<T> &other);
    bool operator!();
  private:
    Counter *counter;
    T *ptr;
};

template<typename T>
MySmartPtr<T>::MySmartPtr() : ptr(nullptr), counter(nullptr) {}

template<typename T>
MySmartPtr<T>::MySmartPtr(T *ptr) {
  this->ptr = ptr;
  counter = new Counter();
  counter->add();
}

template<typename T>
MySmartPtr<T>::MySmartPtr(const MySmartPtr<T> &other) {
  ptr = other.ptr;
  counter = other.counter;
  if (counter != nullptr) counter->add();
}

template<typename T>
MySmartPtr<T>::~MySmartPtr() {
  if (counter == nullptr) return;
  counter->dec();
  if (counter->get() == 0) {
    delete counter;
    delete ptr;
  }
}

template<typename T>
T& MySmartPtr<T>::operator*() {
  return *ptr;
}

template<typename T>
T* MySmartPtr<T>::operator->() {
  return ptr;
}

template<typename T>
MySmartPtr<T>& MySmartPtr<T>::operator=(const MySmartPtr<T> &other) {
  if (this == &other) return *this;

  if (counter != nullptr) {
    counter->dec();
    if (counter->get() == 0) {
      delete counter;
      delete ptr;
    }
  }

  ptr = other.ptr;
  counter = other.counter;

  if (counter != nullptr) counter->add();
  return *this;
}

template<typename T>
bool MySmartPtr<T>::operator!() {
  return ptr == nullptr;
}
