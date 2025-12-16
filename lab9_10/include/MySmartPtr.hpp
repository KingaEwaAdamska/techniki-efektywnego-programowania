template<typename T>
class MySmartPtr {
  public:
    MySmartPtr(T *ptr);
    MySmartPtr(const MySmartPtr<T> &other);
    ~MySmartPtr();

    T& operator*();
    T* operator->();
    MySmartPtr& operator=(const MySmartPtr<T> &other);
  private:
    Counter *counter;
    T *ptr;
};

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
    counter->add();
}

template<typename T>
MySmartPtr<T>::~MySmartPtr() {
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
MySmartPtr& MySmartPtr<T>::operator=(const MySmartPtr<T> &other) {
    counter->dec();
    if (counter->get() == 0) {
        delete counter;
        delete ptr;
    }
    ptr = other.ptr;
    counter = other.counter;
    counter->add();
}
