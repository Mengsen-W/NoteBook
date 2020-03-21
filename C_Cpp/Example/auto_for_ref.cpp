#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>

static void autoValue();
static void autoPointer();
static void newVersionFor();
static void newVersionConstruct();
static void leftRefAndRightRef();

int main() {
  // autoValue();
  // autoPointer();
  // newVersionFor();
  // newVersionConstruct();
  // leftRefAndRightRef();
  return 0;
}

static void autoValue() {
  auto age = 10;
  auto name = std::string("AUTO");
  auto height = 160.1f;
  auto weight = 55.2;

  std::cout << "age is type = " << typeid(age).name() << std::endl;
  std::cout << "name is type = " << typeid(name).name() << std::endl;
  std::cout << "height is type = " << typeid(height).name() << std::endl;
  std::cout << "weight is type = " << typeid(weight).name() << std::endl;
  /**
   * age is type = i
   * name is type = NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
   * height is type = f
   * weight is type = d
   */
}

static void autoPointer() {
  auto age = new int(10);
  auto name = "AUTO";
  // const char* name = "AUTO";
  auto height = new float(160.1f);
  auto weight = new double(55.2);

  std::cout << "age is type = " << typeid(age).name() << std::endl;
  std::cout << "name is type = " << typeid(name).name() << std::endl;
  std::cout << "height is type = " << typeid(height).name() << std::endl;
  std::cout << "weight is type = " << typeid(weight).name() << std::endl;
  /**
   * age is type = Pi
   * name is type = PKc
   * height is type = Pf
   * weight is type = Pd
   */
}

static void newVersionFor() {
  int ids[] = {1, 2, 3, 4, 5};
  std::cout << "new version";
  for (auto v : ids) {
    std::cout << "v is type = " << typeid(v).name();
    // 不能得到位置，简洁 v 是一个值
    std::cout << v << " ";
  }
  std::cout << std::endl;

  std::cout << "old version";
  for (int i = 0; i < sizeof(ids) / sizeof(ids[0]); ++i) {
    // 能得到位置，灵活性高 i 是一个地址
    std::cout << "i is type = " << typeid(i).name();
    std::cout << ids[i] << " ";
  }
  std::cout << std::endl;

  std::vector<int> group;
  for (int i = 0; i < 4; ++i) {
    group.push_back(i);
  }

  // auto version
  std::cout << "vercor group =";
  // 类中定义 begin() 和 end() 就可以使用 范围for
  for (auto v : group) {
    std::cout << "v is type = " << typeid(v).name();
  }
  for (auto& v : group) {
    std::cout << "v is type = " << typeid(v).name();
  }
  for (const auto& v : group) {
    std::cout << "v is type = " << typeid(v).name();
  }
  // 全部类型都是int 没有& 会产生副本
  //但是引用可以减少拷贝构造，类似于 iterator
  //而 const& 可以防止修改类似于 const_iterator
}

class A {
 public:
  A() {}
  explicit A(int value) : m_value(value) {}

 private:
  int m_value;
};

static void newVersionConstruct() {
  A a(10);
  A b{3};

  A c(true);
  A d{false};

  A e(1.0);
  // 没有精度损失，有损失不能用花括号
  // A f{1.0};
  // explicit 相当于 f = A temp(10)
  // A f;
  // f = 10;
}

static void leftRefAndRightRef() {
  int a = 10;
  int& refA = a;
  const int& constRefA = a;
  // const& 可以传右值
  const int& constRefB = 20;

  int&& rrA = 10;
  // 此时已经不算一个右值了，但仍是一个引用
  const int&& crrB = 20;
  rrA = 15;

  // 右值转换不改变地址，但是操作类型可能是不一样的
  int b = 20;
  int&& newRRB = std::move(b);
  const int&& cNewRRB = std::move(b);
  // 隐式的转换不支持
  // int&& rrB = b;
}