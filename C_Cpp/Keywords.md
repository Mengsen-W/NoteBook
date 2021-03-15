<!--
 * @Date: 2021-03-11 15:22:20
 * @Author: Mengsen Wang
 * @LastEditors: Mengsen Wang
 * @LastEditTime: 2021-03-15 11:14:47
 * @FilePath: \NoteBook\C_Cpp\Keywords.md
 * @Description: file content
-->
# C/C++ Keywords

1. alignas 定义类成员变量的**对齐字节数**，使用**0定义**会被忽略，使用**默认**实现。
```c++
struct alignas(8) S {}; // 以8字节方式对齐
struct alignas(1) U { S s;} //错误 U 以 1 字节方式对齐，与 S 对其方式不同
```
2. alignof 查询对齐的字节数，默认为类成员变量**最大字节数**作为对齐默认值，若声明了**alignas**，则为声明大小，若**空类**则为1，若定义与成员变量**冲突**，以内部**成员变量为准**。对于**基础类型**和**sizeof()**是一致的。
3. and 和 && 等价
4. and_eq 和 &= 等价
5. asm 内嵌汇编语言，用于提高效率
6. **auto** 自动类型推断
7. bitand / bitor 等价于 & 和 |
8. bool 基础类型 1字节 由于全平台的通用
9. break 推出循环的方法，只退一层
10. case 和 switch 一起用
11. catch 捕获异常
12. char 基础类型 1字节，在Linux中没有正负，Windows有正负
13. char16_t Unicode utf-8
14. char32_t Unicode
15. class 类
16. compl 等价与 ~
17. concept 概念TS
18. **const** 只读属性
19. **constexpr** 在编译期能确定的值进行优化，可以直接在运行期用。拓展了编译期的执行效率
20. **const_cast** 改变const，可能导致未定义行为
21. continue 结束本次循环跳入下一次循环
22. **decltype** 类似于**auto**，用于在函数体后置指示返回值，不能写在前面的原因是因为编译器在前面还不知道返回类型，decltype() **带括号**是**引用**返回
23. default 在类中参数
24. delete 在类中参数
25. do
26. double **8字节**
27. dynamic_cast 把**父类指针尝试转化成子类指针**，对于指针类型不能转换会返回空指针，引用类型不能转换返回异常，会在运行期进行检查，可能会慢一些。
28. else 和 if 搭配
29. **enum / enum class A : char**是**强类型**，使用时必须 **Class::enum**，而且**不能直接赋值**给int，要用 **static_cast 转换**，而且确定了enum的类型，若**不写类型默认为int**
30. **explicit** 防止**构造函数的隐式类型转换**，可以用**static_cast**可以强转，可以减小默认的bug，也就是说你必须**明确告知类型**
31. export 废弃
32. extern extern"c" 表示以C语言形式编译，单纯的extern表示其函数或者变量表示声明，但是没有初始化，既没有分配内存空间
33. false
34. float **4字节**
35. for
36. friend 一般只在**重载 <<** 才能用到，friend是单一的关系，而且不会被继承
37. goto 可能导致可读性下降，是从汇报遗留下的产物，太强了
38. if 条件
39. inline 将代码从函数中展开，编译器是否展开其实不确定
40. int 一般**4字节**
41. long 一般**不会小于int**
42. mutable 在**类中突破const**
43. namespace 防止名字冲突，全局量直接写::，类似与import...as...
44. new 创建内存
45. noexcept 保证**限定的函数不会抛出异常**，否则出现异常直接就终止
46. not 等价与 !
47. not_eq 等价与 !=
48. nullptr 空指针，实际上是一个类型
47. operator 重载运算符
48. or ||
49. or_eq |=
50. private 私有
51. protected 保护
52. public 公有
53. register 废弃不用，放入寄存器内，加快速度
54. reinterpret_cast 用来处理**无关类型之间的转换**
55. requires 概念
56. return 终结和返回
57. short 整形 **大于char 小于int**
58. sizeof 在**编译期**就完成替换，void，无具体类型，占用不到1字节会报错
59. static 定义一个**静态的有作用范围**的量，在全局区
60. static_assert 在**编译期**若**条件不满足**，就退出编译，保证信息在编译期就满足或者不满足
61. static_cast **同种类型转化**
62. struct 全部是公有
63. switch 选择
64. template 模板
65. this 指向自己
66. thread_local 多线程
67. throw 抛出异常
68. true 真
69. try 尝试异常
70. typedef 把一个名字换成另一个名字
71. typeid 在运行期的定义
72. typename 在运行期的定义
73. union 共和体
74. unsigned / signed 是否带有符号
75. using 和typedef相似**建议使用using**
76. virtual 虚函数标志
77. void 空类型
78. volatile 通知**编译器不做优化**
79. wchar_t 多字节的char
80. while 循环
80. xor 等价于^
81. xor_eq 等价于 ^=
