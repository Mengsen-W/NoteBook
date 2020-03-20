#include <iostream>

class IntCell {
 private:
  int *s;

 public:
  explicit IntCell(int init = 0) {
    s = new int{init};
    std::cout << "Construct" << std::endl;
  }
  ~IntCell() {
    delete s;
    std::cout << "Disconstruct" << std::endl;
  }
  IntCell(const IntCell &rhs) : s(new int(*(rhs.s))) {
    // s = new int{*(rhs.s)};
    std::cout << "Copy Construct" << std::endl;
  }
  IntCell(IntCell &&rhs) : s(rhs.s) {
    // s = rhs.s;
    rhs.s = nullptr;
    std::cout << "Move Construct" << std::endl;
  }
  IntCell &operator=(const IntCell &rhs) {
    if (this != &rhs) *s = *(rhs.s);
    std::cout << "Copy Equal Construct" << std::endl;
    return *this;
  }
  IntCell &operator=(IntCell &&rhs) {
    std::swap(s, rhs.s);
    // 防止自我赋值，强异常安全，防止临时变量构造
    std::cout << "Move Equal Construct" << std::endl;
    return *this;
  }
};

int main() {
  //!! 默认构造
  // IntCell a1;
  // IntCell a2(5);
  // IntCell a3{5};

  //!! 拷贝构造

  //!! 拷贝赋值
  // IntCell c1;
  // IntCell c2;
  // c2 = c1;

  //!! 移动构造
  // IntCell d1;
  // IntCell d2 = std::move(d1);
  // IntCell d3{std::move(d1)};
  // IntCell d4(std::move(d1));

  //!! 移动赋值
  // IntCell e1;
  // IntCell e2;
  // e2 = std::move(e1);
  return 0;
}
