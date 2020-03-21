# 容器/迭代器/算法
---
1. ## 顺序容器--数组或指针--遍历快空间小
   1. array--对数组的封装，内存分配在栈，绝对不会重新分配，随机访问元素，不能改变大小，速度和原生速度相差不多
      - template<typename T, size_t N>
      - 异常：异常若元素本身的move copy 不会抛出异常，则 array 不抛出异常
   2. vector--dynamic array，随机访问元素，末端增删元素效率高，前端中间增删效率低
      - template<typename T, typename Allocator = allocator<T> >
      - 异常若元素本身的move copy 不会抛出异常，则不会抛异常
      - 不要使用bool
   3. deque--与 vector 不同末端头部增删改效率高，中间增改删效率低，元素访问比 vector 慢，迭代器不是普通指针，按块分配，不全连续，类似分页，局部连续，整体离散
      - 异常：copy和swap没异常，操作就没异常
   4. list--不支持随机访问，任何位置增删常数时间，插入删除不会造成迭代失败，对于异常支持好，要不成功不要没影响
      - template<typename T, typename Allocator = allocator<T> >
   5. forward_list--访问头结点快，与手写的单链表时间和空间一致，和list比几乎一样是一个单链表
      - template<typename T, typename Allocator = allocator<T> >
   6. stack
   7. queue
   8. priority_queue
   9.  string
   10. bitset
---
2. ## 关联容器--平衡二叉树--排序查找块
   1. set--红黑树单值
      - template<typename T, typename Compare = less<T>, typename Allocator = allocator<T> >
      - 元素自动排序
      - 插入删除都是O(logN)
      - 元素必须支持严格的弱顺序
      - 不能比较查找元素的值，key
      - 内存消耗高
      - 使用重载()的模板类，定义set中的查找方式（key）
      - std::find 通过传入类的 == 重载，自身find() 通过第二个模板类，注意std::find 不同
   2. multiset--红黑树多值
   3. map--特点和set基本一致但是可以自定value值
      - template<typename Key, typename T, typename Compare = less<T> ,typename Allocator = allocator<pair <const Key ,T>>
   4. multimap
---
3. ## 无序容器--hash_table--遍历快查找快
   1. unordered_set
   2. unordered_map
   3. unordered_multimap
   4. unordered_multiset
---
4. ## 基本知识
   1. 必须可以被**复制copy**或者**移动move**，隐含的条件是搬移和拷贝中应该没有副作用
   2. 元素必须可以**被赋值操作**来**复制和移动**，必须有**赋值=**重载
   3. 元素可以**被销毁**，**析构函数**不能是**private**，不能**抛出异常**
   4. **关联式容器**要提供**比较运算**
   5. **无顺序容器**必须要**提供hash函数**
   6. stl容器**存**的是**元素的值**不是引用，改变一个容器里面的值，不会对另一个容器里丽的值产生影响
   7. stl**设计效率优先安全为次**