/*
 * @Author: Mengsen.Wang
 * @Date: 2020-03-26 08:07:42
 * @Last Modified by: Mengsen.Wang
 * @Last Modified time: 2020-03-26 08:41:33
 */

#include <iostream>
#include <memory>
#include <string>

class Obj {
 public:
  using pointer = std::shared_ptr<Obj>;
  Obj() { std::cout << "Obj" << std::endl; }
  virtual std::string debugName() const = 0;
  ~Obj() { std::cout << "Obj bye" << std::endl; }
  // virtual ~Obj() { std::cout << "Obj bye" << std::endl; }
};

class RealObj : public Obj {
 public:
  RealObj() { std::cout << "RealObj" << std::endl; }
  std::string debugName() const { return "RealObj"; }
  ~RealObj() { std::cout << "RealObj bye" << std::endl; }
};

void testObj(const Obj& obj) { std::cout << obj.debugName() << std::endl; }

int main() {
  // RealObj obj;
  // testObj(obj);
  std::shared_ptr<Obj> pobj = std::make_shared<RealObj>();
  // std::shared_ptr<Obj> p1 = pobj;
  // std::cout << pobj.use_count() << p1.use_count() << std::endl;
  // testObj(*pobj);
  // testObj(*p1);
  // std::unique_ptr<Obj> uObj = std::make_unique<RealObj>();
  // testObj(*uObj);
  return 0;
}