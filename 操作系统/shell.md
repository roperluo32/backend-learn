- 一个日志文件很大，vim打开很费时间，怎么快速搜索某个内容
    - 使用grep搜索. 
    ```shell
    grep 参数 文件名 | head     # 从头查找
	grep 参数 文件名 | wc- l    # 查看符合条件的有多少行
	cat 文件名 |grep 参数$	    # 输出以该参数结尾的行内容
    ```
    - [《linux使用grep条件搜索大文件的行数等操作》](https://zhuanlan.zhihu.com/p/128934433)
    - [《为什么 GNU grep 如此之快》](https://blog.csdn.net/zhu_xun/article/details/17138111)

- 抓包工具，有没有使用过tcpdump
    ```shell
    # 默认监听第一块网卡
    tcpdump 
    # 监听特定网卡
    tcpdump -i en0
    # 监听特定主机，所有出入的包
    tcpdump host 182.254.38.55
    # 特定来源
    tcpdump src host hostname
    # 特定目标地址
    tcpdump dst host hostname
    #特定端口
    tcpdump port 3000
    # 来源主机+端口+TCP
    tcpdump tcp port 22 and src host 123.207.116.169
    # 复杂的例子
    tcpdump tcp -i eth1 -t -s 0 -c 100 and dst port ! 22 and src net 192.168.1.0/24 -w ./target.cap
    (1)tcp: ip icmp arp rarp 和 tcp、udp、icmp这些选项等都要放到第一个参数的位置，用来过滤数据报的类型
    (2)-i eth1 : 只抓经过接口eth1的包
    (3)-t : 不显示时间戳
    (4)-s 0 : 抓取数据包时默认抓取长度为68字节。加上-S 0 后可以抓到完整的   数据包
    (5)-c 100 : 只抓取100个数据包
    (6)dst port ! 22 : 不抓取目标端口是22的数据包
    (7)src net 192.168.1.0/24 : 数据包的源网络地址为192.168.1.0/24
    (8)-w ./target.cap : 保存成cap文件，方便用ethereal(即wireshark)分析
    ```
    - [《Linux基础：用tcpdump抓包》](https://www.cnblogs.com/chyingp/p/linux-command-tcpdump.html)
    - [《tcpdump参数解析及使用详解》](https://blog.csdn.net/hzhsan/article/details/43445787)

- 查看进程id
    ```shell
    # 显示所有进程信息
    ps -A
    # 显示指定用户信息
    ps -u root
    # ps 与grep 常用组合用法，查找特定进程
    ps -ef|grep ssh
    # 列出目前所有的正在内存当中的程序
    ps aux
    # 列出类似程序树的程序显示
    ps -axjf
    ```
    - [《每天一个linux命令（41）：ps命令》](https://www.cnblogs.com/peida/archive/2012/12/19/2824418.html)

- 查看内存使用情况
    ```shell
    # 查看内存概要
    free -h
    # top
    top
    ```
    
- 查看打开了多少个fd
- 查看打开的文件or描述符
    - [《Linux：如何获取打开文件和文件描述符数量》](https://www.cnblogs.com/mfryf/p/5329770.html)
    - [《Linux 命令 —— lsof 查看打开的文件信息》](https://segmentfault.com/a/1190000015226993)

- 有一个日志文件，里面每一行都有ip、time、context等信息，怎么查询某个ip有多少个
    ```shell
        cat log.txt|grep 172.0.0.1|wc -l
    ```

- cmake的作用和用法
    - 通过编写一种平台无关的 CMakeList.txt 文件来定制整个编译流程，然后再根据目标用户的平台进一步生成所需的本地化 Makefile 和工程文件，如 Unix 的 Makefile 或 Windows 的 Visual Studio 工程。从而做到“Write once, run everywhere”
    - [《CMake 入门实战》](https://www.hahack.com/codes/cmake/)

- 解释top命令右上角的三个数字
    - load average: 1.15, 1.42, 1.44 — load average后面的三个数分别是1分钟、5分钟、15分钟的负载情况。
    - load average数据是每隔5秒钟检查一次活跃的进程数，然后按特定算法计算出的数值。如果这个数除以逻辑CPU的数量，结果高于5的时候就表明系统在超负荷运转了
    - [《每天一个linux命令（44）：top命令》](https://www.cnblogs.com/peida/archive/2012/12/24/2831353.html)

- 解释TOP命令中各个数据的属性

- top命令怎么查看线程
    ```shell
    # 列出由进程号为<pid>的进程创建的所有线程
    ps -T -p <pid>
    # 列出所有Linux线程
    top -H
    # 列出某个特定进程<pid>并检查该进程内运行的线程状况
    top -H -p <pid>
    ```
    - [《linux中用top、ps命令查看进程中的线程》](https://blog.csdn.net/inuyashaw/article/details/55095545)

- 怎么按照内存使用大小对进程排序
    - top，然后M即可让进程按内存大小排序

- Linux下的/var目录有什么用
    - /var 包括系统运行时要改变的数据。其中包括每个系统是特定的，即不能够与其他计算机共享的目录，如/var/log，/var/lock，/var/run
    - var目录存在的目的是把usr目录在运行过程中需要更改的文件或者临时生成的文件及目录提取出来，由此可以使usr目录挂载为只读的方式
    - 隐含要求var目录必须挂载为可以读写的方式
    - [《Linux下var目录介绍》](https://www.cnblogs.com/zhouhbing/p/4516522.html)

- linux的常用命令
    - find、grep、xargs、sort、uniq、tr、cut、paste、wc、sed、awk
    - [《Shell处理文本，find、grep、xargs、sort、uniq、tr、cut、paste、wc、sed、awk》](https://blog.csdn.net/coolwriter/article/details/80241606)

- xargs用法
    - [《xargs 命令教程》](https://www.ruanyifeng.com/blog/2019/08/xargs-tutorial.html)

- 假如有一万个单词，分别用空格隔开，统计重复单词的次数
    ```shell
        tr ' ' '\n'|sort | uniq -c|sort -n|head
    ```
    - [《tr命令》](https://man.linuxde.net/tr)
    - [《统计大数据中的单词词频》](https://blog.csdn.net/yymalu/article/details/9141925)

- 写一个匹配ip的正则表达式
    - 完整的表达式如下
    ```shell
    ((2(5[0-5]|[0-4]\d))|[0-1]?\d{1,2})(\.((2(5[0-5]|[0-4]\d))|[0-1]?\d{1,2})){3}
    ```
    - 其中
    ```shell
    # 匹配：200 ~ 255
    2(5[0-5]|[0-4]\d) 
    # 匹配：0 ~ 199
    [0-1]?\d{1,2}  
    #  0~255 对应的正则表达式为
    (2(5[0-5]|[0-4]\d))|[0-1]?\d{1,2}
    ```
    - [《正则表达式 - 匹配 IP 地址》](https://www.jianshu.com/p/82886d77440c)

- grep 命令的-r，-E选项
    - -r。在当前目录递归查找
    - -E。使用正则表达式查找


- ipcs命令
    - 查看进程间通信状态
    - ipcs -a命令可以查看当前使用的共享内存、消息队列及信号量所有信息
    - ipcs -p命令可以得到与共享内存、消息队列相关进程之间的消息
    - ipcs -u命令可以查看各个资源的使用总结信息，其中可以看到使用的信号量集的个数、信号量的个数，以及消息队列中当前使用的消息个数总数、占用的空间字节数。
    - ipcs -l命令可以查看各个资源的系统限制信息，可以看到系统允许的最大信号量集及信号量个数限制、最大的消息队列中消息个数等信息
    - [《ipcs命令详解》](https://www.cnblogs.com/machangwei-8/p/10388824.html)

## 数组和for的用法
- 定义数组
	- arr=("hello" "world" "small" "bird")

- 获取数组所有元素
    - ${arr[*]}


- 遍历数组所有元素
```
for item in ${arr[*]};do
	echo $item
done
```

## if用法
- 双括号写法
    - 只可以用于执行数字的比较.下例中cond如果是个字符串就会报错
```
    cond=1
    if (( cond == 1 ));then
        echo "cond is 1"
    else
        echo "cond is not 1"
    fi
```

- 方括号写法
    - 可以用于数字，字符串，文件的比较
    - 数字的比较
    ![](https://raw.githubusercontent.com/roperluo32/images/master/image20201021162055.png)
    - 字符串的比较
    ![](https://raw.githubusercontent.com/roperluo32/images/master/image20201021162135.png)
    - 文件&目录的比较
    ![](https://raw.githubusercontent.com/roperluo32/images/master/image20201021162207.png)

## 函数
- 定义

```
function hello {
	echo "hello world.param1:$1, param:$2"
}
# 或者
hello(){
    echo "hello world.param1:$1, param:$2"
}
```
    
- 调用
    
```
hello 3 5
``` 
    
    
- 返回值
    
    - 使用return返回特定数字返回码
    
![](https://raw.githubusercontent.com/roperluo32/images/master/image20201021171452.png)
    
    - 通过$()来获取函数的任意类型的返回值
    
![](https://raw.githubusercontent.com/roperluo32/images/master/image20201021171535.png)
    
## 执行命令并获取其输出的方法
- 使用反引号的方式
```
    for line in `ls -l`;do
      echo $line
    done
```
- 使用$()的方式
```
    for line in $(ls -l)`;do
      echo $line
    done
```