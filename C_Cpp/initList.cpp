/**
 * 构造函数的执行可以分成两个阶段
 * 初始化阶段和计算阶段
 * 初始化阶段先于计算阶段
 * 初始化阶段就是对应着初始化列表那部分
 * 计算阶段就是构造函数的函数体部分
 */

/**
 * Construct Student1
 * Construct Student1
 * Equal Construct Student1
 */

/**
 * Construct Student1
 * Copy Construct Student1
 */
/**
 * 由此可见
 * 1.成员类型是没有默认构造函数的类。（列表初始化采用 Copy 函数）
 * 若没有提供显示初始化式，则编译器隐式使用成员类型的默认构造函数，
 * 若类没有默认构造函数，则编译器尝试使用默认构造函数将会失败。
 * 2.const 成员或引用类型的成员。因为 const
 * 对象或引用类型只能初始化，不能对他们赋值。 因为 const 和 引用
 * 必须在初始化的时候赋值
 */

#include <iostream>

using namespace std;

class Student1 {
 public:
  int a;

  Student1() { cout << "Construct Student1" << endl; }

  Student1(const Student1 &t1) {
    cout << "Copy Construct Student1" << endl;
    this->a = t1.a;
  }

  Student1 &operator=(const Student1 &t1) {
    cout << "Equal Construct Student1" << endl;
    this->a = t1.a;
    return *this;
  }
};
class Student2 {
 public:
  Student1 test;
  Student2(Student1 &t1) { test = t1; }
};
int main() {
  Student1 A;
  Student2 B(A);
  /**
   * 在 Student2 中要先构造自己的成员 test
   * 调用 Student1 类的构造函数
   * 调用 Student1 类中的赋值函数将 A 赋给 test
   * 完成 Student2 的构造
   */
  // }

  class Student1 {
   public:
    int a;

    Student1() { cout << "Construct Student1" << endl; }

    Student1(const Student1 &t1) {
      cout << "Copy Construct Student1" << endl;
      this->a = t1.a;
    }

    Student1 &operator=(const Student1 &t1) {
      cout << "Equal Construct Student1" << endl;
      this->a = t1.a;
      return *this;
    }
  };
  class Student2 {
   public:
    Student1 test;
    Student2(Student1 &t1) : test(t1) {}
  };
  int main() {
    Student1 A;
    Student2 B(A);
    /**
     * 由 A 对象直接拷贝生成 test 对象，而不需要先生成 test 对象再赋值
     */
  }