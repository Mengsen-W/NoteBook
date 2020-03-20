#include <cassert>
#include <iostream>
#include <memory>
// auto_ptr
// shared_ptr
// unique_ptr
// weak_ptr
class Object {
 public:
  Object(int id) : m_id(id) {
    std::cout << "hello obj = " << m_id << std::endl;
  }
  ~Object() { std::cout << "bye bye = " << m_id << std::endl; }
  int id() const { return m_id; }

 private:
  int m_id = 0;
};
typedef std::shared_ptr<Object> ObjectPtr;

class Parent;
typedef std::shared_ptr<Parent> ParentPtr;
typedef std::weak_ptr<Parent> WeakParent;
class Child {
 public:
  WeakParent father;
  Child();
  ~Child();
};

typedef std::shared_ptr<Child> ChildPtr;
typedef std::weak_ptr<Child> WeakChild;
class Parent {
 public:
  WeakChild son;
  Parent();
  ~Parent();
};

Child::Child() { std::cout << "hi child \n"; }
Child::~Child() { std::cout << "bye child \n"; }
Parent::Parent() { std::cout << "hi parent \n"; }
Parent::~Parent() { std::cout << "bye parent \n"; }

static void testParentAndChild() {
  ParentPtr p(new Parent());
  ChildPtr c(new Child());
  p->son = c;     // c 的 use_count 为 2
  c->father = p;  // p 的 use_count 为 2
  // 析构时智能指针的use_count 确实减一，但是他们管理的资源并未被释放掉
  // 在释放类内资源前类以及析构了
  // 类似死锁
}

static void sharedPtrWithWeakPtr() {
  ObjectPtr obj(new Object(1));
  typedef std::weak_ptr<Object> WeakObjPtr;
  // 传入一个 shareded_ptr 指针
  WeakObjPtr weakObj(obj);
  std::cout << "obj use count is = " << obj.use_count() << std::endl;  // 1
  {
    // 若调用 lock() 时，引用次数不为零，就返回一个智能指针，若为零返回空指针
    auto p = weakObj.lock();  // auto == ObjectPtr
    if (p) {
      std::cout << "p.unique() = " << p.unique()
                << std::endl;  // false p.use_count() >= 2，p 管理一个
                               // 若p存在则外部一定还有一个
      std::cout << "p.use_count() = " << p.use_count() << std::endl;
      // do what you want to do
      /**
       * init obj = 1
       * obj use count is = 1
       * p.unique() = 0
       * p.use_count() = 2
       */
    } else {
    }
  }

  std::cout << "reset() ... " << std::endl;
  // 释放智能指针，此时Object(1) 引用数为零
  obj.reset();
  {
    auto p = weakObj.lock();
    if (p) {
      assert(false);
      // doing everything
    } else {
      std::cout << "p.unique() = " << p.unique() << std::endl;
      std::cout << "p.use_count() = " << p.use_count() << std::endl;
      // Empty pointers are never unique (as they do not own any pointers).
      /**
       * reset ...
       * bye bye = 1
       * p.unique() = 0
       * p.use_count() = 0
       */
    }
  }

  std::cout << "obj.reset(new Object(2))" << std::endl;
  obj.reset(new Object(2));
  {
    // weakObj 管理的资源是 new Object(1)
    // 此时已经被释放掉了
    // Object(1) 现在没有智能指针管理
    auto p = weakObj.lock();
    if (p) {
      assert(false);
      // doing everything
    } else {
      std::cout << "p.unique() = " << p.unique() << std::endl;
      std::cout << "p.use_count() = " << p.use_count() << std::endl;
      // Empty pointers are never unique (as they do not own any pointers).
      /**
       * obj.reset(new Object(2))
       * hello obj = 2
       * p.unique() = 0
       * p.use_count() = 0
       * bye bye = 2
       */
    }
  }

  // 重新把 obj 和 weakObj 关联
  std::cout << "reLink..." << std::endl;
  weakObj = obj;
  // 是否已经失效
  // weakObj.use_count() == 0 返回true
  if (weakObj.expired()) {
    std::cout << "weakObj.expired() true" << std::endl;
  } else {
    std::cout << "weakObj.use_count() = " << weakObj.use_count() << std::endl;
    std::cout << "weakObj.expired() false" << std::endl;
    /**
     * weakObj.use_count() = 1
     * weakObj.expired() false
     * bye bye = 2
     */
  }
}

int main() {
  testParentAndChild();  // 循环引用
  // sharedPtrWithWeakPtr();

  return 0;
}