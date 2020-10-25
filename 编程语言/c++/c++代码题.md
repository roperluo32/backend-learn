- 计算下面几个类的大小
```C++
class A {}; : sizeof(A) = 1;
class A { virtual Fun(){} }; : sizeof(A) = 4(32位机器)/8(64位机器);
class A { static int a; }; : sizeof(A) = 1;
class A { int a; }; : sizeof(A) = 4;
class A { static int a; int b; }; : sizeof(A) = 4;
```

- 已知某类:
```C++
class A
{
public:
  A(int x){}
}
```
问： A a = 1; 是否正确, 如果正确, 那么它调用了哪些函数？

由于 A 类的构造函数没有声明为 explicit 因此可以 int 类型强制转换来。因此, 该表达式正确。
对于没有优化过的编译器: 先将 1 转化为 A 类型(构造函数), 再将其赋值给 a 变量(拷贝赋值函数)。
对于优化了的编译器: 直接用 1 来构造变量 a(构造函数)。

- 给一个类class Player1{private：int a; char b; double c; }; 有如下问题：
（1）给定初始化的实例化对象，Player1 A; 问 Player1 B = A; Player1 C = A; 两种方式的区别?（拷贝构造函数）
（2）sizeof(Player1)的大小？（字节优化对齐）
（3）给定class Player2{private：int a; char b; double c; public： virtual fun(c){}}, 问sizeof(Player2)的大小？（虚函数表）

- 实现单例模式

- 两个线程交叉打印A和B（设置两个信号量）

- 大端模式和小端模式的判断

- 实现一个线程安全的queue的方法；（加锁，CAS队列，lock-free queue，mutex等）

- int a[10]，求sizeof（a）和sizeof（a*）；

- int (*a)[10] 解释；（指针数组）

- malloc了解吗，说一说

- 写出完整版的strcpy函数
  ```c++
  char * strcpy( char *strDest, const char *strSrc ) 
  {
   assert( (strDest != NULL) && (strSrc != NULL) );
   char *address = strDest; 
   while( (*strDest++ = * strSrc++) != ‘\0’ ); 
   return address;

  }
  ```

## 要复习的题目
- [下面代码会出现什么问题](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=21056&query=&asc=true&order=&page=7)

- [分别给出BOOL，int，float，指针变量 与“零值”比较的 if 语句（假设变量名为var）](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=21059&query=&asc=true&order=&page=10)

- [写一个“标准”宏MIN，这个宏输入两个参数并返回较小的一个](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=21061&query=&asc=true&order=&page=12)
- [编写类String的构造函数、析构函数和赋值函数](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=21065&query=&asc=true&order=&page=16)
- [请写一个C函数，若处理器是Big_endian的，则返回0](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=21067&query=&asc=true&order=&page=18)
- [说一说c++中四种cast转换](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=31346&query=&asc=true&order=&page=24)
- [理解的c++中的smart pointer四个智能指针](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=31349&query=&asc=true&order=&page=27)
- [为什么析构函数必须是虚函数？为什么C++默认的析构函数不是虚函数](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=31358&query=&asc=true&order=&page=36)
- [请你来说一下map和set有什么区别，分别又是怎么实现的？](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=31362&query=&asc=true&order=&page=40)
- [介绍一下STL的allocaotr](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=31363&query=&asc=true&order=&page=41)
- [malloc的原理，另外brk系统调用和mmap系统调用的作用分别是什么](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=31368&query=&asc=true&order=&page=46)
- [说一说Linux虚拟地址空间](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=31380&query=&asc=true&order=&page=58)
- [说一说操作系统中的缺页中断](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=31382&query=&asc=true&order=&page=60)
- [fork和vfork的区别](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=31383&query=&asc=true&order=&page=61)
- [如何修改文件最大句柄数](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=31384&query=&asc=true&order=&page=62)
- [操作系统中的页表寻址](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=31387&query=&asc=true&order=&page=65)
- [线程间的同步方式，最好说出具体的系统调用](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=31391&query=&asc=true&order=&page=69)
- [死锁发生的条件以及如何解决死锁](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=31398&query=&asc=true&order=&page=76)
- [虚拟内存和物理内存怎么对应](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=31399&query=&asc=true&order=&page=77)
- [虚拟内存置换的方式](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=31402&query=&asc=true&order=&page=80)
- [简述一下TCP建立连接和断开连接的过程](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=31414&query=&asc=true&order=&page=92)
- [HTTP返回码](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=31418&query=&asc=true&order=&page=96)
- [mysql引擎以及其区别](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=31433&query=&asc=true&order=&page=111)
- [Redis的数据类型有哪些，底层怎么实现](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=31436&query=&asc=true&order=&page=114)
- [Redis的rehash怎么做的，为什么要渐进rehash，渐进rehash又是怎么实现的](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=31437&query=&asc=true&order=&page=115)
- [哈夫曼编码](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=31442&query=&asc=true&order=&page=120)
- [epoll怎么实现的](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=31447&query=&asc=true&order=&page=125)
- [Top(K)问题](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=31448&query=&asc=true&order=&page=126)
- [栈和堆的区别，以及为什么栈要快](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=31450&query=&asc=true&order=&page=128)
- [介绍一下各种排序算法及时间复杂度](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=31458&query=&asc=true&order=&page=136)
- [哈希表的桶个数为什么是质数，合数有何不妥](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=31463&query=&asc=true&order=&page=141)
- [单例模式的多线程安全问题](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=31471&query=&asc=true&order=&page=149)
- [OOP的设计模式的五项原则](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=31474&query=&asc=true&order=&page=152)
- [写个函数在main函数执行前先运行](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=31484&query=&asc=true&order=&page=162)
- [以下四行代码的区别是什么？](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=31487&query=&asc=true&order=&page=165)
- [C++函数栈空间的最大值](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=31493&query=&asc=true&order=&page=171)
- [RTTI](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=31496&query=&asc=true&order=&page=174)
- [说一说STL迭代器删除元素](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=31509&query=&asc=true&order=&page=187)