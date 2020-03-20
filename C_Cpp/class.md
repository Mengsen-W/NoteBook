# C++ 类
1. ## 前置声明
```c++
class RuleofFive;   //前置声明，
```
  - 没有给出实际定义，没有实现
  - 不完全类型类似（int a[]; void）
```c++
class Parent;
class Child {
  public:
    explicit Child(Parent* p) : m_parent(p) {}
  private:
    Parent* m_parent;
};
class Parent {
  public:
    bool addChild(Child* child) { m_children.push_back(child);}
  private:
    std::vector<Child*> m_children;
}
```
  - 对于**Child**类，初始化需要指针是因为指针是确定的字节数，而传入一个对象，由于**Parent**还未定义，故编译器还不知道需要多大空间，所以只能**传递指针**。私有成员也是如此。
  - 在**Parent**内部传指针和传值一样，因为对于编译器来说**Child**类型是完整的，编译器知道分配多少空间和地址。
  - 运用前置声明，可以解决构造**Child**需要**Parent**，构造**Parent**需要**Child**的困境。
  - 对于多文件编辑，用指针和前置声明可以不必**include头文件**，若**Parent**里面的方法用到了**Child**里面的方法，则前置声明不可以满足，必须**include <Parent.h>**，或者把**Parent**类中方法的实现放在**cpp**文件中，在**cpp**文件中**include<Parent.h>和include<Child.h>**，在头文件中尽可能少的包括其他头文件的引用
  - 若**继承**一个类，则必须在**h**文件中**include**；有类的**成员**，也必须**include**，成员函数的**返回类型不论是引用指针还是值**，可以通过**前置声明**省略**include**，作为参数的接口包括**指针和引用**都可以通过**前置声明**省略

2. ## 构造和析构
- **自己管理的内容**要自己**控制析构拷贝赋值**
    1. 当类成员中有**自己管理**的内容，析构函数必须手动释放，析构函数只能**释放内存中关于此类的空间**而不会把此类中可能有**指针指向的内存**释放。
    2. 若类中有**自己管理**的内容拷贝和赋值要自己写，因为默认的拷贝和赋值函数只会**单纯赋值**。若类中有指针，可能直接**复制指针**的内容，导致多个指针指向同一块内存，在析构的时会发生**重复析构**。

- **左值**和**右值**区分是**有没有明确地址**
    1. 左值**有名字有地址**可能有内容或没内容
    2. 右值**没名字没地址有内容**，但是可以依靠**右值引用**
    3. **引用或指针**是**左值**
    4. **std::move()**把一个**左值**转化成一个**右值**
    5. 对于一个右值可以传入**const引用**
    ```c++
    int print (const int& a) {
      std::cout << a  << std::endl;
    }
    // 以下全部正确
    int a = 10;
    const int& bc = abc;
    int& bcd = abc;
    print(10);
    print(bc);
    print(abc);
    print(bcd;
    ```

- **右值拷贝**和**右值赋值**
    1. ClassName(const ClassName& rhs){}
    2. ClassName(ClassName&& rhs){ // **注意右值销毁**，可以理解为**资源的转换**}
       1. 当调用 std::move() 中会把**参数内容**完全**复制给结果**然后把**资源变为空资源或空指针**
       2. 凡是调用了**资源转移**的类，之后就**不要使用**
    3. ClassName& operator= (const ClassName& rhs){}
    4. ClassName& operator= (ClassName&& rhs){}
       1. 注意判断**左右**两个值是否是**同一个**

- **析构函数**绝对不要**抛出异常**
    1. 编译器做出的默认析构函数是**noexcept**，除非加入**noexcept(false)**
    2. 编译器在**try...catch...**中**一次只能捕获一个异常**，若父子类都会抛出异常，可能不能处理这**两个异常**

- **构造函数鼓励抛出异常**
