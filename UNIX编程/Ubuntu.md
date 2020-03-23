# 环境配置

## 编译环境
1. apt update
2. apt upgrade
3. sudo apt-get install libboost-all-dev
4. sudo apt-get install mysql-server mysql-client libmysqlclient-dev
5. ldd --version
6. apt install git
7. apt install bison
8. apt install texinfo
9. apt install autoconf
10. apt install ragel
11. apt install psmisc
12. apt install openssl-devel
13. apt install libssl-dev
14. apt install net-tools
15. apt install htop

## zsh
1. apt install zsh
2. chsh -s /bin/zsh
3. sh -c "$(wget https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh -O -)"
4. theme = ys

## vim
1. 推荐使用vimPlus https://github.com/chxuan/vimplus.git

## C/Cpp 环境
1. 安装GUN/gcc
   1. cd /usr/local √
   2. wget https://ftp.gnu.org/gnu/gcc/gcc-9.3.0/gcc-9.3.0.tar.gz √
   3. tar -xvf √
   4. mkdir build √
   5. ../contrib/download_prerequisites √
   6. ../configure --prefix=/usr/local/gcc  --enable-bootstrap  --enable-checking=release --enable-languages=c,c++ --disable-multilib √
   7. make && make install √
   8. echo "export PATH=/usr/local/gcc/bin:$PATH" >> /etc/profile.d/gcc.sh
   9. source /etc/profile.d/gcc.sh
   10. ln -snv /usr/local/gcc/include/ /usr/include/gcc
   11. echo "/usr/local/gcc/lib64" >> /etc/ld.so.conf.d/gcc.conf

2. 安装GUN/GBK
   1. wget http://ftp.gnu.org/gnu/gdb/gdb-9.1.tar.xz
   2. tar xvf gdb-9.1.tar.xz
   3. cd gdb-9.1 && mkdir build
   4. ../configure --prefix=
   5. make && make install
   6. cp -r include /usr/include/...
   7. 要不就apt install gdb 然后一个一个软连接过去 我懒得弄了


## node 环境
1. apt install nodejs
2. apt install npm
3. npm install -g n
4. n lts
5. n lts
6. node -v
7. npm i -g npm
8. npm config set registry https://registry.npm.taobao.org
9. npm install -g cnpm --registry=https://registry.npm.taobao.org
10. cnpm install -g hexo-cli

## 太长不看版
1. 下包
2. 拆包
3. 看依赖条件
4. 配置
5. make
6. 直接复制过去吧
7. 写echoPATH和次conf

## 一点都不想弄版
1. 大神没时间 --- 去Docker找个配置好的
2. 小白 -- 请你的运维或是楼上大神吃个饭