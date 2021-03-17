/*
 * @Date: 2021-03-17 21:27:11
 * @Author: Mengsen Wang
 * @LastEditors: Mengsen Wang
 * @LastEditTime: 2021-03-17 21:37:43
 */

#include <iostream>

class Base {
 public:
  virtual void foo() { std::cout << "Base" << std::endl; }
  int a;
  int b;
};

class Derived : public Base {
 public:
  virtual void foo() final { std::cout << "Derived" << std::endl; }
  int c;
  int d;
};

int main() {
  Base* base = new Derived{};
  base->foo();
  Base base2 = *base;
  base2.foo();

  Base base3{};
  base3.foo();
  // base do not cast to derived, but derived can cast to base
  // Derived derived1 = dynamic_cast<Derived*>(base3);

  Derived derived1{};
  derived1.foo();
  Base base4 = derived1;
  base4.foo();
  return 0;
}