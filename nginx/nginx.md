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
3. 终端与进程

   1. 随着终端的推出，终端上运行的进程也会关闭，因为进程的父进程时shell
   2. 启动顺序 内核进程0->用户级进程1->gettty(终端进程)和kthread(线程)->login(登录进程)->shell(虚拟终端)->...
   3. 当终端断开后，OS会发送SIGHUP信号(终端断开信号)给session leader，大概率时shell进程，而后由shell发送给其下session中所有进程，最后session中所有进程都会终端，先杀session其他进程，再杀自己
   4. 孤儿进程会被init进程收养
   5. 可以使用新建信号组setid()函数，但是如果调用此函数的进程时一个进程组的组长，则不成功；signal函数来实现不会因为shell被终止，导致的子进程被回收；用setsid 命令创建进程，可以使进程的父进程编程init进程，而且单独属于一个进程组；用nohup启动进程，只是使得进程会忽略SIGHUP信号，对于其会话组或者父进程id没有影响，而且不会向屏幕输入，而是把输出重定义到当前目录的 nohup 文件中，而且是带有缓冲区的流输出
   6. 后台运行可以在后面加&，用 fg 命令可以切换到前台，但是进程运行和前后台没关系，也就是说，当杀掉一个shell，他的后台进程也会被杀掉

---

## 终端与shell进程
