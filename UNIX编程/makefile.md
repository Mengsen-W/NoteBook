# makefile 编写
---
## makefile 基础
0. makefile 第一优先级 Makefile 第二优先级 其他的都不管用
1. makefile 的编写
   1. 自定义变量 obj=xxx 直接写 以后用到需要 &(obj)
   2. 系统维护的变量
      1. CC=gcc
      2. CPPFLAGS 预处理选项 如 -I
      3. CFLAGS 编译选项 -Wall -g -c
      4. LDFLAGS 链接库选项 -L -l
      5. 还是需要写 &(CC) / &(CFLAGS)
   3. .PHONY:clean 可以防止文件夹中重名
2. makefile 的规则
   1. 规则三要素：目标、依赖、命令
      - 目标：依赖条件 (下一行tab)命令
   2. 子目标和终极目标的关系
      1. 子目标写在终极目标下面, 搜索的顺序从上到下
   3. 更新目标的原则
      1. 拆分后更改部分文件不会导致全部重编译，根据修改时间对比
3. makefile 的两个函数
   1. wildcard 查找某个指定目录下的某种文件
   2. patsubst 把所有.c替换成.o .c文件由第三个参数指定
4. makefile 的三个变量
   1. $< 规则中的第一个依赖
   2. $@  规则中的目标
   3. $^ 规则中所有的依赖 只能在命令中使用

---
```makefile
app:main.o sub.o mul.o
  gcc main.o sub.o mul.o -o app
# gcc $^ -o %@
main.o:main.c
  gcc main.c -c main.o
sub.o:sub.c
  gcc sub.o -c sub.c
mul.o:mul.c
  gcc mul.o -c mul.c
# %.o:%.c
#     gcc -c &< -o &@
```

```makefile
obj = main.o add.o sub.o mul.o
CC = gcc
target = app
CPPFLAGS = -I

$(target):$(obj)
  $(CC) $(obj) -o $(target)
%.c:%.o
  $(CC) -c $< -o $@

```

```makefile
target = app
src=$(wildcard ./*c)
obj = $(patsubst ./%.c, ./%.o, $(src))
CC = gcc
CPPFLAGS = -I

$(target):$(obj)
  $(CC $(obj) -o $(target)
%.c:%.o
  $(CC) -c $< -o $@

.PHONY:clean
clean:
  -rm $(obj) $(target) -f
# - 失则继续执行

hello:
  echo "hello, makefile"
```
