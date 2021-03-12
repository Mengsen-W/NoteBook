<!--
 * @Date: 2021-03-11 15:22:20
 * @Author: mengsen
 * @LastEditors: mengsen
 * @LastEditTime: 2021-03-11 15:31:37
 * @FilePath: \NoteBook\UNIX编程\Unix网络编程.md
-->

# Unix 网络通信

## 基础函数

1. 字节序转化

   1. htons/htonl/ntohs/ntohl ip地址和端口号都可以
   2. inet_pton/inet_ntop 只用于ip地址

2. sockaddr

   1. sockaddr已经废弃了
   2. 这个结构体后续转化成了 sockaddr_in
   3. sin_family 地址族协议
   4. sin_port 端口号 注意字节序的转化
   5. sin_addr ip地址，这个成员本身又是一个结构体，此结构体仅有一个成员 s_addr 为实际Ip

3. socket函数

   1. domain 判断协议
   2. type 通信协议 流式协议默认tcp 报式协议默认udp等等
   3. protocol 协议号，传0表示默认，即流式协议的默认是tcp
   4. 成功返回文件描述符，失败返回-1设置errno

4. bind

   1. fd 文件描述符
   2. socket_addr 描述传出的协议族，ip port
   3. addrlen 长度
   4. 成功返回0，失败返回-1，设置errno

5. listen

   1. 监听连接，处理三次握手
   2. 指定同时允许多少个客户都与我建立连接
   3. 也就是处于3此握手状态的连接数目, backlog参数就是用来限制这种未决连接数量
   4. sockfd
   5. 数量

6. accept

   1. sockfd
   2. sockaddr_in 是一个传出参数，是客户端的信息
   3. socketlen 传入传出参数，传入初始化长度，返回实际长度
   4. 成功返回新的socketFD，用来与客户端通信，返回-1则失败设置errno

7. connect

   1. 客户端建立连接
   2. sockfd 传入参数
   3. sockaddr_in 传入参数 写出和那个服务端连接
   4. socklen 传入参数
   5. 失败返回-1，设置errno，成功返回0

8. read/write

   1. 大于0，则返回的就是读取到字节数
   2. 只有对端关闭后才会读到0，如果对端没有关闭只会阻塞等待
   3. 返回-1是出现异常了

      1. errno == EINTR 信号中断 选择restart/quit
      2. errno == EAGAIN(EWOULDBLOCK) 非阻塞方式读，并且没有数据
      3. 其他值，出现错误

## C/S 网络模型

1. server端

   1. socket() -> bind() -> listen() -> accept() -> read() -> write() ...

2. client端

   1. socket() -> (bind()可以隐式绑定) -> connect() -> write() -> read() ...
