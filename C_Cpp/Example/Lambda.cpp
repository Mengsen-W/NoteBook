/*
 * @Author: Mengsen.Wang
 * @Date: 2020-03-21 11:21:12
 * @Last Modified by: Mengsen.Wang
 * @Last Modified time: 2020-03-21 11:31:18
 */

#include <functional>
#include <iostream>

const void printInfo(int a, int b, int c) {
  std::cout << "a = " << a << " b = " << b << " c = " << c << std::endl;
}

struct Print {
  void operator()(int a, int b, int c) const {
    std::cout << "a = " << a << " b = " << b << " c = " << c << std::endl;
  }
};

template <typename T1, typename T2, typename T3>
void templatePrint(T1 a, T2 b, T3 c) {
  std::cout << "a = " << a << " b = " << b << " c = " << c << std::endl;
}

struct TemplatePrint {
  template <typename T1, typename T2, typename T3>
  void operator()(T1 a, T2 b, T3 c) {
    std::cout << "a = " << a << " b = " << b << " c = " << c << std::endl;
  }
};

int main() {
  Print printUseClass;
  TemplatePrint printUseTemplate;

  printInfo(1, 2, 3);
  printUseClass(1, 2, 3);
  templatePrint(1, 2, 3);
  printUseTemplate(1, 2, 3);
  return 0;
}