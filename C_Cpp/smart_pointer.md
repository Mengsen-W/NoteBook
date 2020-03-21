# 智能指针
定义在**memory**头文件
---
---
1. ## auto_ptr 推荐**不用**，通用不强
---
2. ## shared_ptr
   1. 通过拷贝或者赋值实现**共享**
   2. 提供一个**计数器**用来计数
   3. 将智能指针值传入函数，会导致次数加一，离开函数次数减一，**引用传入**不会变化
   4. 可以由一个**前置声明**就可以创建智能指针
   5. ### enable_shared_from_this
      - 当类A被share_ptr管理，且在类A的成员函数里需要把当前类对象作为参数传给其他函数时，就需要传递一个指向自身的share_ptr。
        1. 为何不直接传递this指针
            - 使用智能指针的初衷就是为了方便资源管理，如果在某些地方使用智能指针，某些地方使用原始指针，很容易破坏智能指针的语义，从而产生各种错误。
        2. 可以直接传递share_ptr<this>么？
            - 答案是不能，因为这样会造成2个非共享的share_ptr指向同一个对象，未增加引用计数导对象被析构两次
---
3. ## weak_ptr
   1. 不增加**引用次数**的前提下，引用一个变量
   2. 能够**打破** shared_ptr **循环引用**
   3. 本身是一个**监听者**，并**不影响引用次数**
   4. 关注**资源本身**而不是智能指针，**更换智能指针不一定**会使weak_ptr.lock()**失效**
   5. 只有当指向**资源**的**智能指针数为零**时，lock() 才会返回 false
   6. 若 shared_ptr 管理资源失效，则 weak_ptr 管理资源也失效
---
4. ## unique_ptr
   1. 保证了**异常情况**下也可以**析构**
   2. 继承了一部分auto_ptr的特性在异常情况下也是安全的
   3. **优先**使用 unique_ptr
---
5. ## 智能指针总结
   1. **绝对不要**自己**手动**管理资源
   ```c++
   malloc();
   free();
   new();
   delete;
   ```
   2. 一个**裸指针**不要用**两个智能指针管理** 包括 shared_ptr unique_ptr
   ```c++
   auto pObj = new Object(1);
   ObjectPtr obj(pObj);
   ObjectPtr obj2(pObj);
   ```
   3. 用 **weak_ptr 打破循环引用**
   4. 在**类的内部接口**中，需要将**this**作为智能指针使用，需要改类派生自**enable_shared_from_this**
   5. 尽量使用 **const shared_ptr& 作为接口**，多线程例外
   6. **智能指针效率不高**，空间和时间复杂度都高很多
   ```c++
   // new 一次
   ObjectPtr obj = std::make_shared<Object>(3);
   // new 两次
   ObjectPtr obj(new Object(3));
   ```
   7. enable_shared_from_this 中 shared_from_this() 在**构造析构**函数的**某些情况**下**不能使用**
   8. 某些情况下，尤其是使用**weak_ptr处理循环引用**时，内存不会降。类似于weak_ptr**勾**住了一个已经不存在的实例，虽然**实例在栈中消失了**，但由于**weak_ptr堆中**
   9. 如果有可能**优先使用类的实例**，**其次 unique_ptr** 最后 **shared_ptr**