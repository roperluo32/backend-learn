- 有一个运行的进程突然挂掉，怎么查看它是哪里出问题了？
    - 查看系统日志/var/log/messages。是否有Out of memory，内存不足被杀掉了
    - 确认进程退出后是否有core文件生成，如果有说明程序发生了段错误，可以用gdb调试core文件
    - [《linux 环境下进程被 killed掉原因分析和解决方法》](https://blog.csdn.net/ktigerhero3/article/details/80004315)

- 如何调试core文件
    - 打开ulimit限制。ulimit -c unlimited，则表示 core 文件的大小不受限制
    - 使用 gdb 调试 core 文件的步骤
        - 启动 gdb，同时指定程序与 core 文件
        ```shell
        gdb EXEFILE COREFILE
        #或
        gdb -c | --core COREFILE EXEFILE
        #或
        gdb COREFILE
        file EXEFILE
        ```
        - 在进入 gdb 后，查找段错误位置，使用 where 或者bt

    - [《Linux 下使用 gdb 调试 core 文件》](https://blog.csdn.net/K346K346/article/details/48344263)
    - [《linux下core dump【总结】》](https://www.cnblogs.com/Anker/p/6079580.html)

- 内存泄漏怎么调试，valgrind怎么用
    - step1, 定位是哪个进程
        - top命令或者监控视图查看进程内存占用情况
    - step2, 定位是哪个函数
        - 静态分析。mtrace
        - 动态分析。valgrind工具定位进程内存泄露的函数
    ```shell
    valgrind --tool=memcheck --leak-check=full  ./main_c
    ```
    - [《使用 Valgrind 检测 C++ 内存泄漏》](http://senlinzhan.github.io/2017/12/31/valgrind/)
    - [《在Linux下检查内存泄露》](https://blog.csdn.net/weixin_36343850/article/details/77856051)

- Linux怎么查看进程的CPU消耗？
    - top
    - ps aux

- 如果发现系统负载过高，应该怎么排查原因，如何解决
    - 通过top命令定位是哪个进程占用CPU或者内存过多
    - 使用valgrind命令分析内存泄露
    - 使用perf分析哪些函数占用cpu和内存过多
        - 使用perf top或者perf stat整体定位性能瓶颈
        - perf recode 分析单个进程性能
        ```shell
        perf record -e cpu-clock -g ./main
        # -g选项是告诉perf record额外记录函数的调用关系
        # -e cpu-clock 指perf record监控的指标为cpu周期
        # 程序运行完之后，perf record会生成一个名为perf.data的文件
        ```
        - perf report 生成性能报告
        ```
        perf report -i perf.data
        ```
    - [《perf使用教程》](https://blog.csdn.net/qq_15437667/article/details/50724330)
    -  [《系统级性能分析工具perf的介绍与使用》](https://www.cnblogs.com/arnoldlu/p/6241297.html)

- cpp内存泄漏检查
    - 手动封装malloc打印文件行数
    - 动态检查valgrind
    - 语言层面避免，比如智能指针
    - [《内存泄漏排查攻略之：Show me your Memory》](https://www.cnblogs.com/yougewe/p/11334342.html)

- 平时调试用什么，linux的gdb用过没
    ```
    1）进入GDB　　#gdb test

    　　test是要调试的程序，由gcc test.c -g -o test生成。进入后提示符变 为(gdb) 。

    2）查看源码(gdb) l

    　　源码会进行行号提示。

    　　如果需要查看在其他文件中定义的函数，在l后加上函数名即可定位到这个函数的定义及查看附近的其他源码。或者：使用断点或单步运行，到某个函数处使用s进  入这个函数。

    3）设置断点(gdb) b 6

    　　这样会在运行到源码第6行时停止，可以查看变量的值、堆栈情况等；这个行号是gdb的行号。

     4）查看断点处情况　　(gdb) info b

    　　可以键入"info b"来查看断点处情况，可以设置多个断点；

    5）运行代码　　(gdb) r

    6）显示变量值　　(gdb) p n

    　　在程序暂停时，键入"p 变量名"(print)即可；

    　　GDB在显示变量值时都会在对应值之前加上"$N"标记，它是当前变量值的引用标记，以后若想再次引用此变量，就可以直接写作"$N"，而无需写冗长的变量名；

    7）观察变量　　(gdb) watch n

     在某一循环处，往往希望能够观察一个变量的变化情况，这时就可以键入命令"watch"来观察变量的变化情况，GDB在"n"设置了观察点；

    8）单步运行　　(gdb) n

    9）程序继续运行　　(gdb) c

    　　使程序继续往下运行，直到再次遇到断点或程序结束；

    10）退出GDB　　(gdb) q


    ```
    - [《gdb调试命令》](https://www.cnblogs.com/wuyuegb2312/archive/2013/03/29/2987025.html)

- gdb调试多线程程序
    ```
    info threads 显示当前可调试的所有线程，每个线程会有一个GDB为其分配的ID，后面操作线程的时候会用到这个ID。 前面有*的是当前调试的线程。

    thread ID 切换当前调试的线程为指定ID的线程。

    break thread_test.c:123 thread all 在所有线程中相应的行上设置断点

    thread apply ID1 ID2 command 让一个或者多个线程执行GDB命令  command。 

    thread apply all command 让所有被调试线程执行GDB命令command。

    set scheduler-locking off|on|step
    ```
    - [《gdb 多线程调试》](https://www.cnblogs.com/xuxm2007/archive/2011/04/01/2002162.html)


- 单例模式运行（文件记录pid linux下 /var/run/pid） 如果挂了怎么办（手动清除pid文件） 提示如何自动清理（想到应该IPC 文件锁）
    - pid文件的内容：pid文件为文本文件，内容只有一行, 记录了该进程的ID
    - pid文件的作用：防止进程启动多个副本。只有获得pid文件(固定路径固定文件名)写入权限(F_WRLCK)的进程才能正常启动并把自身的PID写入该文件中
    - 编程技巧
        ```
        调用fcntl设置pid文件的锁定F_SETLK状态，其中锁定的标志位F_WRLCK。


        如果成功锁定，则写入进程当前PID，进程继续往下执行。


        如果锁定不成功，说明已经有同样的进程在运行了，当前进程结束退出
        ```
    - [《linux下/var/run目录下的pid文件作用》](https://blog.csdn.net/shanzhizi/article/details/23272437)

- 压测过程及关注的指标
    - 准备阶段
        - 是单机压测，还是整条链路压测
        - 测试数据
            - 模拟数据
            - 线上数据抓包重放
            - 调整权重导流压测
    - 关注指标。最好能有业务的监控视图
        - 机器CPU，内存，IO，网络负载
        - QPS和TPS
        - 压测的并发数
        - 请求响应时间
        - 数据库查询时间
        - 垃圾回收GC时间
    - [《全链路压测平台（Quake）在美团中的实践》](https://tech.meituan.com/2018/09/27/quake-introduction.html)
    - [《后端服务性能压测实践》](https://www.cnblogs.com/wangiqngpei557/p/7953453.html)
- 压测相关的工具？
    - nload看网络负载
    - ab工具发包
    ```shell
    ab -n 1000 -c 100 https://baidu.com
    # -n : 本次测试执行 N 个请求数
    # -c : 指的是并发连接数

    ab -n 1 -c 1  -T application/json -p 1.json  "http://127.0.0.1:3301/anal/api/test"
    # -p 定义 post 方法需要传输的 file
    # file 默认是寻找 /root 路径下目标文件，可以通过 tab 确认
    # file 可能需要注意换行符等问题（目前我这边没有问题）
    # -T 是和-p 搭配使用，指定 header
    ```


- 怎么探查网络数据带宽，在不占满的情况下
	- 原理:源端以速率R发送一列(K个)测量包，目的端根据收到的测量包观察通路的延迟状况，并绘出延迟曲线。若R大于链路可用带宽Bw，链路就会出现短时拥塞，延迟曲线会有明显的上升趋势。目的端将延迟信息反馈给源端，源端会按照一定的调整策略改变速率R，重复此过程，直到通路中没有拥塞现象发生，延迟曲线比较平稳，无明显的波动趋势。此时的R近似于通路可用带宽
    - [《一种网络剩余带宽探测方法及其应用》](https://patents.google.com/patent/CN105553755A/zh)

- Linux的grub指令用过吗
    - [《grub命令》](https://man.linuxde.net/grub)
    - [《Grub引导项修复详解》](https://blog.csdn.net/gatieme/article/details/59127020)

- 了解编译优化吗，说说看
    - [《gcc编译优化-O0 -O1 -O2 -O3 -OS解析》](https://blog.csdn.net/wuxing26jiayou/article/details/96132721)

- 栈怎么检测避免溢出？mmap，mprotect


