# 伯克利Socket

## 头文件
1. sys/socket.h     // 函数和数据结构定义
2. netinet/in.h     // IPv4和IPv6相关协议族信息
3. sys/un.h         // Unix 机器间通信的相关信息
4. arpa/inet.h      // 处理数字从操作系统字节序列到网络字节序--从小端到大端
5. netdb.h          // 映射服务到IP地址

## API函数
1. socket()         // 创建socket
2. bind()           // 绑定socket到IP地址和端口
3. listen()         // 服务器监听客户端的连接
4. connect()        // 客户端连接到服务器
5. accept()         // 应用程序接受完成3次握手的客户端连接
6. send() recv()    // 机器间相互发送数据
7. close()          // 关闭socket, 包括发给对方和自己接受的
8. gethostbyname()  // IPv4专用
9. gethostbyaddr()  // IPv4专用
10. select() poll() // 处理多个连接的读写和错误信息
11. getsocketopt()  // 得到对应socket的选项值
12. setsocketopt()  // 得到对应socket的选项值