#include "Counter.hpp"
#include <bits/stdc++.h>
#include <vector>
#include <string>

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
    void getAll();
  private:
    std::vector<T **> *adresses;
    Counter *counter;
    T *ptr;
};

template<typename T>
MySmartPtr<T>::MySmartPtr() : ptr(nullptr), counter(nullptr), adresses(nullptr) {}

template<typename T>
MySmartPtr<T>::MySmartPtr(T *ptr) {
  this->ptr = ptr;
  counter = new Counter();
  counter->add();
  adresses = new std::vector<T **>;
  adresses->push_back(&ptr);
}

template<typename T>
MySmartPtr<T>::MySmartPtr(const MySmartPtr<T> &other) {
  ptr = other.ptr;
  counter = other.counter;
  adresses = other.adresses;
  if (counter != nullptr) counter->add();
  if (adresses != nullptr) adresses->push_back(&ptr);
}

template<typename T>
MySmartPtr<T>::~MySmartPtr() {
  if (counter == nullptr) return;
  counter->dec();

  if (adresses == nullptr) return;
  adresses->erase(std::find(adresses->begin(), adresses->end(),  &ptr));

  if (counter->get() == 0) {
    delete counter;
    delete ptr;
    delete adresses;
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

template<typename T>
void MySmartPtr<T>::getAll(){
  for (int i = 0; i < adresses->size(); i++){
    std::cout << (*adresses)[i] << std::endl;
  }
}
