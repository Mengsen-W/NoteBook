<!--
 * @Date: 2021-03-11 15:22:20
 * @Author: mengsen
 * @LastEditors: mengsen
 * @LastEditTime: 2021-03-11 15:31:16
 * @FilePath: \NoteBook\UNIX编程\IPC.md
-->

# 进程间通讯

---

## pipe

  1. 内核提供，单工，自同步机制，必须有双方

### 匿名管道

  1. pipe() 有血缘关系的进程间
  2. 机制得益于fork时的全复制特性

### 命名管道

  1. mkfifo()
  2. 线性的以文件的形式创建一个管道

---

## 消息队列

1. ftok()
2. msgget()
3. msgsnd/msgrcv
4. msgctl

---

## 信号量数组

---

## 共享内存

---

## socket
