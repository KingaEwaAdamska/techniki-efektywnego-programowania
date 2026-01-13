#include "MySmartPtr.hpp"
#include "Book.hpp"

#include <iostream>

int main() {
  MySmartPtr<Book> ptr1(new Book());
  MySmartPtr<Book> ptr2(ptr1);
  
  ptr1.getAll();
}
