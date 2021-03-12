<!--
 * @Date: 2021-03-11 15:22:20
 * @Author: mengsen
 * @LastEditors: mengsen
 * @LastEditTime: 2021-03-11 15:37:05
 * @FilePath: \NoteBook\C_Cpp\lambdaFun.md
-->

# lambda 表达式

[捕获列表] (参数列表) {实现}

1. 本质是一个**inline函数**，加了一些语法糖，可以保存为**本地对象**，或者作为一个**参数传递**
2. 可以在中括号内写入需要**捕获**的**外部变量**

   1. " = "外部所以**值捕获**
   2. " & "外部所以**引用捕获**

3. 空lambda 和空类一样，实际上是一个语法糖，实际上是一个lambda类重载了()

```c++
//[b, &c] (int a) { std:: cout <<a << std::endl; }
class Lambda {
   public:

      Lambda(int b, int& c): m_b(b), m_c(c){}
      void operator() (int a) const {
         std::cout << a << std::endl;
      }

   private:

      int m_b;
      int& m_c;

}
```
