/*
 * @Author: Mengsen.Wang
 * @Date: 2020-03-21 12:00:17
 * @Last Modified by: Mengsen.Wang
 * @Last Modified time: 2020-03-21 12:20:14
 */
#include <algorithm>
#include <array>
#include <chrono>
#include <deque>
#include <forward_list>
#include <iostream>
#include <list>
#include <map>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

static void vectorPart();
static void arrayPart();
static void dequePart();
static void listPart();
static void forward_list();
static void mapPart();
static void setPart();
static void unorderedMapPart();
static void unorderedSetPart();
static void stlAlgorithm();

int main() {
  // arrayPart();
  // vectorPart();
  // dequePart();
  // listPart();
  // forward_list();
  setPart();
  mapPart();
  unorderedSetPart();
  unorderedMapPart();
  stlAlgorithm();

  return 0;
}

// interface of container
template <typename T>
void containerAllInterface(T& a, T& b) {
  T c;                      // init
  T d(a);                   // copy
  T e = a;                  // copy
  T f(std::move(a));        // move
  auto iterB = b.begin();   // iterator
  auto iterE = b.end();     // iterator
  T g(b.begin(), b.end());  // copy
  b.size();                 // std::forward_list no size() function,
                            // beacause more less space of for this
                            // even no size()
  b.empty();                // return b.size() != 0;
                            // return true of false
  b.max_size();             // max of container number
  if (b == c) {             // first compare number of all then size of element
  }
  if (b != c) {
  }
  if (b < e) {  // hash table container no this function
  }
  e = b;
  e = std::move(b);
  e.swap(g);             // std::array swap is linear another is O1
  swap(e, g);            // O1 else array
  e.cbegin();            // return const iterator &
  e.cend();              // return const iterator &
  auto ea = e.cbegin();  // depend on e if e is const return const iterator
  auto eea = e.begin();  // forver return const iterator
  e.clear();             // clear container
                         // std::array no clear() function
}

// arrayPart
void arrayPart() {
  // build
  std::array<int, 100> a;       // no init
  std::array<int, 100> b = {};  // inti to 0
  std::array<int, 5> obj = {1, 2, 3, 4, 5};
  std::array<int, 5> obj2 = {1};  // another element is 0
  std::array<int, 5> obj3{0};     // command

  // interface
  a.empty();  // never be true if size() > 0
  a.size();
  a.max_size();
  auto aa = a;  // operator == < != > <= >=

  aa.swap(a);  // one by one swap so time is linear
  std::swap(aa, a);

  // visit element
  a[1];       // no check legitimacy of index
  a.at(1);    // check up legitimacy of index
  a.front();  // return reference of head
  a.back();   // return reference of back

  // iterator
  a.begin();   // return head iterator
  a.end();     // return behind of tail
  a.cbegin();  // return head const_iterator
  a.cend();
  a.rbegin();  // return reverse of head mining tail
  a.rend();
  a.crbegin();
  a.crend();

  // with c interface
  std::array<char, 100> carr;
  strcpy(&carr[0], "helloworld\n");  // more better use carr.data();
  printf("%s", &carr[0]);            // more better use carr.data();
  // printf("%s", carr.begin());     // error

  // spacial use
  auto info = std::get<1>(carr);  // equal with carr[1]
  carr.fill(0);                   // all of element in carr assignment 0
}

// vectorPart
void vectorPart() {
  using Group = std::vector<float>;
  Group a;                       // 0 element
  Group b = a;                   // copy
  Group c(a);                    // copy
  Group d(10);                   // have 10 element of 0
  Group e(10, 1.0f);             // have 10 element of 1.0
  Group f(e.begin(), e.end());   // iterator init
  Group g({1.0f, 2.0f, 3.0f});   // list init
  Group h = {1.0f, 3.0f, 4.0f};  // initialize list
  Group i{1.0f, 3.0f, 4.0f};     // initialize list command

  d.empty();          // is empty? true : false
  d.size();           // return element size
  d.max_size();       // Maximun capacity of all of memory, may be infinite
  d.capacity();       // capacity number if no redistribution memory
  d.reserve(100);     // reserve capacity memory in advance
  d.shrink_to_fit();  // shrink_to_fit

  // operator == != < > <= >=

  // assign
  b = g;
  b.assign(3, 1.0f);  // {1.0, 1.0, 1.0}
  b.assign(g.begin(), g.end());
  b.assign({1.0f, 3.0f, 4.0f});

  // swap
  b.swap(a);   // very efficiention and don't throw exception
  swap(a, b);  // just swap pointer

  // visit element
  b[0];     // don't throw exception
  b.at(0);  // may throw out of range exception
  b.front();
  b.back();
  if (b.empty()) {
    // undefined
    b.front();
    b.back();
  }

  // iterator
  a.begin();   // return head iterator
  a.end();     // return behind of tail
  a.cbegin();  // return head const_iterator
  a.cend();
  a.rbegin();  // return reverse of head mining tail
  a.rend();
  a.crbegin();
  a.crend();

  a.pop_back();  // may be wrong
  if (b.empty())
    b.pop_back();  // undefined single thread ok and multithread maybe wrong
  auto iterAfter = d.erase(d.begin());  // low efficient
  d.erase(b.begin(), b.end());          // no check iterator

  b.push_back(10.0f);
  auto iter = b.insert(b.end(), 100.0f);
  iter = b.insert(b.end(), 10, 100.0f);
  b.insert(b.end(), h.begin(), h.end());
  b.emplace(b.end(), 10.0f);  // no temp element
  b.emplace_back(10.0f);      // && move copy&&
  b.resize(10);               // resize
  b.resize(100, 10.0f);
  b.clear();          // no memory change
  b.shrink_to_fit();  // memory change

  // with c interface
  std::array<char, 100> carr;
  strcpy(&carr[0], "helloworld\n");  // more better use carr.data();
  printf("%s", &carr[0]);            // more better use carr.data();
  // printf("%s", carr.begin());     // error no ensure begin is alive or is a
  // iterator/ pointer

  // spacial use
  auto info = std::get<1>(carr);  // equal with carr[1]
  carr.fill(0);                   // all of element in carr assignment 0
}

// dequePart()
void dequePart() {
  using Group = std::deque<float>;
  Group a;                       // 0 element
  Group b = a;                   // copy
  Group c(a);                    // copy
  Group d(10);                   // have 10 element of 0
  Group e(10, 1.0f);             // have 10 element of 1.0
  Group f(e.begin(), e.end());   // iterator init
  Group g({1.0f, 2.0f, 3.0f});   // list init
  Group h = {1.0f, 3.0f, 4.0f};  // initialize list
  Group i{1.0f, 3.0f, 4.0f};     // initialize list command

  d.empty();     // is empty? true : false
  d.size();      // return element size
  d.max_size();  // Maximun capacity of all of memory, may be infinite
  // d.capacity();  // 没有分配移动内存的过程
  // d.reserve(100);
  d.shrink_to_fit();  // shrink_to_fit 类似内存收缩

  // operator == != < > <= >=

  // assign
  b = g;
  b.assign(3, 1.0f);  // {1.0, 1.0, 1.0}
  b.assign(g.begin(), g.end());
  b.assign({1.0f, 3.0f, 4.0f});

  // swap
  b.swap(a);   // very efficiention and don't throw exception
  swap(a, b);  // just swap pointer

  // visit element
  b[0];     // don't throw exception
  b.at(0);  // may throw out of range exception
  b.front();
  b.back();
  if (b.empty()) {
    // undefined
    b.front();
    b.back();
  }

  // iterator
  a.begin();   // return head iterator
  a.end();     // return behind of tail
  a.cbegin();  // return head const_iterator
  a.cend();
  a.rbegin();  // return reverse of head mining tail
  a.rend();
  a.crbegin();
  a.crend();

  a.pop_back();  // may be wrong
  if (b.empty())
    b.pop_back();  // undefined single thread ok and multithread maybe wrong
  auto iterAfter = d.erase(d.begin());  // low efficient
  d.erase(b.begin(), b.end());          // no check iterator

  b.push_back(10.0f);
  b.push_front(10.0f);
  auto iter = b.insert(b.end(), 100.0f);
  iter = b.insert(b.end(), 10, 100.0f);
  b.insert(b.end(), h.begin(), h.end());
  b.emplace(b.end(), 10.0f);  // no temp element
  b.emplace_front(10.0f);     // && move copy&&
  b.emplace_back(10.0f);      // && move copy&&
  b.resize(10);               // resize
  b.resize(100, 10.0f);
  b.clear();          // no memory change
  b.shrink_to_fit();  // memory change
}

// listPart
void listPart() {
  using Group = std::list<float>;
  Group a;                       // 0 element
  Group b = a;                   // copy
  Group c(a);                    // copy
  Group d(10);                   // have 10 element of 0
  Group e(10, 1.0f);             // have 10 element of 1.0
  Group f(e.begin(), e.end());   // iterator init
  Group g({1.0f, 2.0f, 3.0f});   // list init
  Group h = {1.0f, 3.0f, 4.0f};  // initialize list
  Group i{1.0f, 3.0f, 4.0f};     // initialize list command

  d.empty();     // is empty? true : false
  d.size();      // return element size
  d.max_size();  // Maximun capacity of all of memory, may be infinite
  // d.capacity();  // 没有分配移动内存的过程
  // d.reserve(100);
  // d.shrink_to_fit();  // shrink_to_fit 类似内存收缩

  // operator == != < > <= >=

  // assign
  b = g;
  b.assign(3, 1.0f);  // {1.0, 1.0, 1.0}
  b.assign(g.begin(), g.end());
  b.assign({1.0f, 3.0f, 4.0f});

  // swap
  b.swap(a);   // very efficiention and don't throw exception
  swap(a, b);  // just swap pointer

  // visit element no random visit
  // b[0];     // don't throw exception
  // b.at(0);  // may throw out of range exception
  b.front();
  b.back();
  if (b.empty()) {
    // undefined
    b.front();
    b.back();
  }

  // iterator
  a.begin();   // return head iterator
  a.end();     // return behind of tail
  a.cbegin();  // return head const_iterator
  a.cend();
  a.rbegin();  // return reverse of head mining tail
  a.rend();
  a.crbegin();
  a.crend();
  // 对访问中间元素不友好
  auto iterBegin = a.begin();
  std::advance(iterBegin, 4);

  a.pop_back();  // may be wrong
  if (b.empty())
    b.pop_back();  // undefined single thread ok and multithread maybe wrong
  auto iterAfter = d.erase(d.begin());  // low efficient
  d.erase(b.begin(), b.end());          // no check iterator

  b.push_back(10.0f);
  b.push_front(10.0f);
  auto iter = b.insert(b.end(), 100.0f);
  iter = b.insert(b.end(), 10, 100.0f);
  b.insert(b.end(), h.begin(), h.end());
  b.emplace(b.end(), 10.0f);  // no temp element
  b.emplace_front(10.0f);     // && move copy&&
  b.emplace_back(10.0f);      // && move copy&&
  b.resize(10);               // resize
  b.resize(100, 10.0f);
  b.clear();  // no memory change
  // b.shrink_to_fit();  // memory change

  // algorithm
  b.remove(1.0f);
  b.remove_if([](auto v) { return v > 100.0f; });
  b.reverse();
  b.sort();
  g.sort();
  b.merge(d);
  c.unique();              // unique after sort or unique of adjacent
  c.splice(c.begin(), b);  // b join to c.begin()
}

// forward_listPart
void forward_listPart() {
  using Group = std::forward_list<float>;
  Group a;                       // 0 element
  Group b = a;                   // copy
  Group c(a);                    // copy
  Group d(10);                   // have 10 element of 0
  Group e(10, 1.0f);             // have 10 element of 1.0
  Group f(e.begin(), e.end());   // iterator init
  Group g({1.0f, 2.0f, 3.0f});   // list init
  Group h = {1.0f, 3.0f, 4.0f};  // initialize list
  Group i{1.0f, 3.0f, 4.0f};     // initialize list command

  d.empty();  // is empty? true : false
  // d.size();   // 不统计大小, 只要一个最轻量的链表
  d.max_size();  // Maximun capacity of all of memory, maybe infinite
  // d.capacity();  // 没有分配移动内存的过程
  // d.reserve(100);
  // d.shrink_to_fit();  // shrink_to_fit 类似内存收缩

  // operator == != < > <= >=

  // assign
  b = g;
  b.assign(3, 1.0f);  // {1.0, 1.0, 1.0}
  b.assign(g.begin(), g.end());
  b.assign({1.0f, 3.0f, 4.0f});

  // swap
  b.swap(a);   // very efficiention and don't throw exception
  swap(a, b);  // just swap pointer

  // visit element no random visit
  // b[0];     // don't throw exception
  // b.at(0);  // may throw out of range exception
  b.front();
  // b.back();  // 没有尾元素
  if (b.empty()) {
    // undefined
    b.front();
    // b.back();
  }

  // iterator
  a.begin();   // return head iterator
  a.end();     // return behind of tail
  a.cbegin();  // return head const_iterator
  a.cend();
  a.before_begin();   // return front of head
  a.cbefore_begin();  // iter->data undefined
  // a.rbegin();  // return reverse of head mining tail
  // a.rend();    // 不能从后向前遍历
  // a.crbegin();
  // a.crend();
  // 对访问中间元素不友好
  auto iterBegin = a.begin();
  std::advance(iterBegin, 4);

  // a.pop_back();  // 后插也没有
  if (b.empty())
    // b.pop_back();  // undefined single thread ok and multithread maybe wrong
    // auto iterAfter = d.erase(d.begin());  // low efficient
    // d.erase(b.begin(), b.end());            // no check iterator
    b.erase_after(b.before_begin(), b.end());  // return void

  // b.push_back(10.0f);
  b.push_front(10.0f);
  b.emplace_front(10.0f);  // && move copy&&
  b.insert_after(b.before_begin(), c.begin(), c.end());
  // auto iter = b.insert(b.end(), 100.0f);
  // iter = b.insert(b.end(), 10, 100.0f);
  // b.insert(b.end(), h.begin(), h.end());
  // b.emplace(b.end(), 10.0f);  // no temp element
  // b.emplace_back(10.0f);      // && move copy&&
  b.resize(10);  // resize
  b.resize(100, 10.0f);
  b.clear();  // no memory change
  // b.shrink_to_fit();  // memory change

  // algorithm
  b.remove(1.0f);
  b.remove_if([](auto v) { return v > 100.0f; });
  b.reverse();
  b.sort();
  g.sort();
  b.merge(d);
  c.unique();  // unique after sort or unique of adjacent
  // c.splice(c.begin(), b);  // b join to c.begin()
}

// setPart
void setPart() {
  using Group = std::set<float>;
  Group a;      // 0 element
  Group b = a;  // copy
  Group c(a);   // copy
  Group d(c.begin(), c.end());
  Group g({1.0f, 2.0f, 3.0f});   // list init 排序
  Group h = {1.0f, 3.0f, 4.0f};  // initialize list
  Group i{1.0f, 3.0f, 4.0f};     // initialize list command

  d.empty();  // is empty? true : false
  d.size();
  d.max_size();  // Maximun capacity of all of memory, maybe infinite

  // Compare,对于 set 下面两个是一个东西
  auto keycomp = c.key_comp();
  auto valuecomp = c.value_comp();

  // operator == != < > <= >=

  // assign
  b = g;

  // swap
  b.swap(a);   // very efficiention and don't throw exception
  swap(a, b);  // just swap pointer

  // iterator
  a.begin();   // return head iterator
  a.end();     // return behind of tail
  a.cbegin();  // return head const_iterator
  a.cend();
  a.rbegin();
  a.rend();
  a.crbegin();
  a.crend();
  auto iterBegin = a.begin();

  b.clear();  // no memory change

  // algorithm
  // set count 0 1
  // multiset count >= 0
  auto num = a.count(1.0f);
  // set 和 multiset 返回一致
  auto findIter = a.find(1.0f);
  if (findIter != a.end()) {
  }

  // 插入已经存在的一个值会导致下面几种方法返回值不一致
  // 对于一个已经存在的值
  // lower 返回相等位置
  // high 返回相等的下一个位置
  // equal 返回上面两个值的区间
  auto lower = a.lower_bound(1.0f);  // 第一个可插入点
  // 没内存可能插不进
  if (lower != a.end()) {
    if (*lower == 1.0f) {
      // has 1.0f
    }
  }
  auto high = a.upper_bound(1.0f);   // 最后一个可插入点
  auto equal = a.equal_range(1.0f);  // 返回一个pair

  auto eraseIter = b.erase(b.begin(), b.end());
  // return pair<iterator, bool>
  auto state = b.insert(100.0f);
  g.insert(c.begin(), c.end());
}