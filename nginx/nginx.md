# nginx 学习笔记
---
## nginx 进程结构--多进程
1. master和worker进程概览
   1. master进程
      1. 属于 root 用户权限高
      2. 父进程是 init(1) 进程
   2. worker进程
      1. 属于 nobody 用户权限低安全性高
      2. 父进程是master进程
2. nginx进程模型
   1. 只能有1个master进程，1到多个worker进程
      1. 保证nginx稳定灵活运行
      2. master是监控和管理worker进程
      3. worker进程是处理事务进程
      4. master和worker通讯可以用信号和共享内存等通讯
      5. 多核计算机优先使worker运行在每一个单独的核上可以达到更高的效率
      6. 在热升级时，通过更新worker和master实现