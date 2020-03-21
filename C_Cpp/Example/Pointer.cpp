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
typedef std::unique_ptr<Object> UniqueObjectPtr;
void print(const UniqueObjectPtr& obj) {}
void transfer(UniqueObjectPtr obj) {
  std::cout << "obj.id() = " << obj->id() << std::endl;
}
void uniquePtr() {
  UniqueObjectPtr obj(new Object(1));
  auto p = obj.get();  // operator bool
  // 得到裸指针
  if (p) {
  }
  // more better
  if (obj) {
  }

  // operator-> *
  std::cout << "p->id() = " << p->id() << '\n'
            << "obj->id() = " << obj->id() << '\n'
            << "(*obj).id() = " << (*obj).id() << std::endl;
  print(obj);
  // 释放指针，交给系统或其他人管理，指针置空
  // 等价 obj.reset(nullptr);
  p = obj.release();
  delete p;
  obj.reset();
  obj.reset(new Object(2));  // 释放原有资源，管理新的指针
  // UniqueObjectPtr(const UniqueObjectPtr&) =delete;
  // UniqueObjectPtr(UniqueObjectPtr&&) = default;
  // 将资源转移
  transfer(std::move(obj));
  assert(obj == nullptr);
  // std::cout << "obj.id() = " << obj->id() << std::endl;

  obj.reset(new Object(3));
  // 转移资源
  ObjectPtr sharedObj(std::move(obj));
  assert(obj == nullptr);
}

class Parent;
typedef std::shared_ptr<Parent> ParentPtr;
typedef std::weak_ptr<Parent> WeakParent;
class Child : public std::enable_shared_from_this<Child> {
 public:
  WeakParent father;
  Child();
  ~Child();
  void checkRelation();
};

typedef std::shared_ptr<Child> ChildPtr;
typedef std::weak_ptr<Child> WeakChild;
class Parent : public std::enable_shared_from_this<Parent> {
 public:
  WeakChild son;
  Parent();
  ~Parent();
  void checkRelation();
};

Child::Child() { std::cout << "hi child \n"; }
Child::~Child() { std::cout << "bye child \n"; }
Parent::Parent() { std::cout << "hi parent \n"; }
Parent::~Parent() { std::cout << "bye parent \n"; }
void handleChildAndParent(const ParentPtr&, const ChildPtr&);
void Parent::checkRelation() {
  auto ps = son.lock();
  // 不靠谱的做法 ParentPtr p (this)
  // p 的析构调用了三次
  // 出if的作用域会调用一次析构
  if (ps) {
    handleChildAndParent(shared_from_this(), ps);
  }
  std::cout << "after call checkRelation\n";
}
void Child::checkRelation() {
  // we call handleChildANdParent
}

static void testParentAndChild() {
  ParentPtr p(new Parent());
  ChildPtr c(new Child());
  p->son = c;     // c 的 use_count 为 2
  c->father = p;  // p 的 use_count 为 2
  // 析构时智能指针的use_count 确实减一，但是他们管理的资源并未被释放掉
  // 在释放类内资源前类以及析构了
  // 类似死锁
  std::cout << "p.use_count() = " << p.use_count() << std::endl;
  std::cout << "c.use_count() = " << c.use_count() << std::endl;
  p->checkRelation();
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

void handleChildANdParentRef(const Parent& p, const Child& c) {
  auto cp = c.father.lock();
  auto pc = p.son.lock();
  if (cp.get() == &p && pc.get() == &c) {
    std::cout << "right relation\n";
  } else {
    std::cout << "oop!!!\n";
  }
}

void handleChildAndParent(const ParentPtr& p, const ChildPtr& c) {
  // 传入引用减少拷贝次数
  auto pc = p->son.lock();
  auto cp = c->father.lock();
  if (cp == p && pc == c) {
    std::cout << "right relation\n";
  } else {
    std::cout << "oop!!!\n";
  }
}

int main() {
  // testParentAndChild();  // 循环引用
  // sharedPtrWithWeakPtr();
  uniquePtr();

  return 0;
}