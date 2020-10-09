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