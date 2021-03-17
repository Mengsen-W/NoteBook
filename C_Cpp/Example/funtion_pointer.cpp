/*
 * @Date: 2021-03-17 20:22:56
 * @Author: Mengsen Wang
 * @LastEditors: Mengsen Wang
 * @LastEditTime: 2021-03-17 20:36:10
 * @FilePath: \algorithm\test.cpp
 * @Description: file content
 */

int* d(int x) {
  x += 1;
  return nullptr;
}

int a() { return 0; }

int main() {
  (*d)(1024);
  int(d)(1024);
  // int (*d)(1024)
  int (*pf)();
  pf = a;
  pf();
  return 0;
}