- 有一个运行的进程突然挂掉，怎么查看它是哪里出问题了？
    - 查看系统日志/var/log/messages。是否有Out of memory，内存不足被杀掉了
    - 确认进程退出后是否有core文件生成，如果有说明程序发生了段错误，可以用gdb调试core文件
    - [《linux 环境下进程被 killed掉原因分析和解决方法》](https://blog.csdn.net/ktigerhero3/article/details/80004315)
    - [《Linux 下使用 gdb 调试 core 文件》](https://blog.csdn.net/K346K346/article/details/48344263)

- 如何调试core文件

- 内存泄漏怎么调试，valgrind怎么用

- 程序挂掉了，怎么调试？有什么工具？怎么做？
    - [《在Linux下检查内存泄露》](https://blog.csdn.net/weixin_36343850/article/details/77856051)
    - [《linux下core dump【总结】》](https://www.cnblogs.com/Anker/p/6079580.html)
    - [《使用 Valgrind 检测 C++ 内存泄漏》](http://senlinzhan.github.io/2017/12/31/valgrind/)
    -  [《系统级性能分析工具perf的介绍与使用》](https://www.cnblogs.com/arnoldlu/p/6241297.html)

- Linux怎么查看进程的CPU消耗？

- 当发现内存泄漏或CPU占用满了，怎么办

- 如果发现系统负载过高，应该怎么排查原因，如何解决

- cpp内存泄漏检查
    - 手动封装malloc打印文件行数
    - 动态检查valgrind
    - 语言层面避免，比如智能指针
    - [《内存泄漏排查攻略之：Show me your Memory》](https://www.cnblogs.com/yougewe/p/11334342.html)

- 平时调试用什么，linux的gdb用过没
    - [《gdb调试命令》](https://www.cnblogs.com/wuyuegb2312/archive/2013/03/29/2987025.html)

- gdb怎么查看某个线程
    - [《gdb 多线程调试》](https://www.cnblogs.com/xuxm2007/archive/2011/04/01/2002162.html)

- 如何调试多线程程序

- Gdb调试多进程

- 单例模式运行（文件记录pid linux下 /var/run/pid） 如果挂了怎么办（手动清除pid文件） 提示如何自动清理（想到应该IPC 文件锁）
    - [《linux下/var/run目录下的pid文件作用》](https://blog.csdn.net/shanzhizi/article/details/23272437)

- 压测关注的指标

- 对服务器怎么进行压测的，压测指标是什么，服务器有没有部署在云上？
    - nload看网络负载
    - ab工具
[   - 《全链路压测平台（Quake）在美团中的实践》](https://tech.meituan.com/2018/09/27/quake-introduction.html)
[   - 《后端服务性能压测实践》](https://www.cnblogs.com/wangiqngpei557/p/7953453.html)

- 怎么探查网络数据带宽，在不占满的情况下
	- 原理:源端以速率R发送一列(K个)测量包，目的端根据收到的测量包观察通路的延迟状况，并绘出延迟曲线。若R大于链路可用带宽Bw，链路就会出现短时拥塞，延迟曲线会有明显的上升趋势。目的端将延迟信息反馈给源端，源端会按照一定的调整策略改变速率R，重复此过程，直到通路中没有拥塞现象发生，延迟曲线比较平稳，无明显的波动趋势。此时的R近似于通路可用带宽
    - [《一种网络剩余带宽探测方法及其应用》](https://patents.google.com/patent/CN105553755A/zh)

- Linux的grub指令用过吗
    - [《grub命令》](https://man.linuxde.net/grub)
    - [《Grub引导项修复详解》](https://blog.csdn.net/gatieme/article/details/59127020)

- 内存泄漏如何查询？

- 了解编译优化吗，说说看
    - [《gcc编译优化-O0 -O1 -O2 -O3 -OS解析》](https://blog.csdn.net/wuxing26jiayou/article/details/96132721)

- 栈怎么检测避免溢出？mmap，mprotect


