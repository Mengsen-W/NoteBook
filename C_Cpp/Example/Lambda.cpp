/*
 * @Author: Mengsen.Wang
 * @Date: 2020-03-21 11:21:12
 * @Last Modified by: Mengsen.Wang
 * @Last Modified time: 2020-03-21 11:44:06
 */

#include <functional>
#include <iostream>

void printInfo(const int a, const int b, const int c) {
  std::cout << "a = " << a << " b = " << b << " c = " << c << std::endl;
}

struct Print {
  void operator()(const int a, const int b, const int c) const {
    std::cout << "a = " << a << " b = " << b << " c = " << c << std::endl;
  }
};

template <typename T1, typename T2, typename T3>
void templatePrint(const T1 a, const T2 b, const T3 c) {
  std::cout << "a = " << a << " b = " << b << " c = " << c << std::endl;
}

struct TemplatePrint {
  template <typename T1, typename T2, typename T3>
  void operator()(const T1 a, const T2 b, const T3 c) const {
    std::cout << "a = " << a << " b = " << b << " c = " << c << std::endl;
  }
};

template <typename Func>
void printUseFunc(Func func, const int a, const int b, const int c) {
  func(a, b, c);
}

int main() {
  Print printUseClass;
  TemplatePrint printUseTemplate;

  printInfo(1, 2, 3);
  printUseClass(1, 2, 3);
  templatePrint(1, 2, 3);
  printUseTemplate(1, 2, 3);

  // lambad
  // local
  auto local = [](const int a, const int b, const int c) {
    std::cout << "a = " << a << " b = " << b << " c = " << c << std::endl;
  };

  printUseFunc(
      [](const int a, const int b, const int c) {
        std::cout << "a = " << a << " b = " << b << " c = " << c << std::endl;
      },
      1, 2, 3);

  return 0;
}