[TOC]

## C++特性
- C++面向对象的特性
    - 封装。可以隐藏实现细节，使得代码模块化
    - 继承。实现代码复用
    - 多态。实现接口复用
  
    - 参考： [《c++面向对象的三个特点，并简述》](https://blog.csdn.net/IOT_SHUN/article/details/79674293)

- C++ 语言的特性
    - C++ 是面向对象的语言, 自然有面向对象的语言的特性: 封装, 继承, 多态。
    - C++ 也是泛型编程语言, 自然也有泛型编程语言的特性。

- C++ 与 C 的区别
    - C++ 包含 C 几乎全部功能。
    - C++ 比 C 多面向对象语言部分。
    - C++ 比 C 多泛型编程部分。
    - C++ 比 C 多 STL 部分

## 基础知识
- volatile的作用    
    - 变量被volatile修饰，编译器将不会把它保存到寄存器中，而是每一次都去访问内存中实际保存该变量的位置上
    - 在多线程中，volatile可以保证volatile修饰的变量不被编译器优化，每次读取都能从内存中读到原始值
    - 在编写多线程程序中使用volatile的关键四点：

      - 将所有的共享对象声明为volatile；

      - 不要将volatile直接作用于基本类型；

      - 当定义了共享类的时候，用volatile成员函数来保证线程安全；

      - 多多理解和使用volatile和LockingPtr！（强烈建议）
    - 参考
        - [《详解volatile在C++中的作用》](https://www.cnblogs.com/s5279551/archive/2010/09/19/1831258.html)

- extern关键字用法
    - extern 变量。表示声明的变量来自于其它文件
    - extern "C"。表示按照类C的编译和连接规约来编译和连接

- new和malloc的区别
![](http://images-1251273400.cosgz.myqcloud.com/20201011202812.png)
    - [《细说new与malloc的10点区别》](https://www.cnblogs.com/qg-whz/p/5140930.html)
- new一定会用到malloc吗？
    - 不一定，可以重载operator new，定义自己的内存分配
    - 重载new的场景
        - 检测代码中的内存错误
        - 优化性能
        - 获得内存使用的统计数据
- 在C++里面，怎样去重载new操作符？ （这里我回答的是写法）
    - 全局重载
    ![](http://images-1251273400.cosgz.myqcloud.com/20201012222221.png)
    - 类中的局部重载
    ![](http://images-1251273400.cosgz.myqcloud.com/20201012222254.png)

- C++内存分配有哪些
    - 堆，栈，全局/静态存储区，自由存储区（由new分配的内存），常量存储区

- C与C++编译生成的符号表的区别
    - 符号表有内存地址和函数/变量的对应关系，编译时节点的各种属性（类型，作用域，分配空间大小，（函数）的参数类型）等

- 引用和指针的区别？
    - 指针是一个变量，只不过这个变量存储的是一个地址，指向内存的一个存储单元；而引用跟原来的变量实质上是同一个东西，只不过是原变量的一个别名而已
    - 可以有const指针，但是没有const引用；
    - 指针可以有多级，但是引用只能是一级（int **p；合法 而 int &&a是不合法的）
    - 指针的值可以为空，但是引用的值不能为NULL，并且引用在定义的时候必须初始化；
    - 指针的值在初始化后可以改变，即指向其它的存储单元，而引用在进行初始化后就不会再改变了。
    - "sizeof引用"得到的是所指向的变量(对象)的大小，而"sizeof指针"得到的是指针本身的大小；
    - 指针和引用的自增(++)运算意义不一样

- 函数指针与指针函数分别是什么，函数指针与指针函数辨别
    - 指针函数即返回指针的函数
    ```c++
    int *pfun(int, int);
    ```
    - 指针函数。一个指向函数的指针
    ```c++
    int (*pfun)(int, int);
    ```
    通过括号强行将pfun首先与“*”结合，也就意味着，pfun是一个指针，接着与后面的“()”结合，说明该指针指向的是一个函数，然后再与前面的int结合，也就是说，该函数的返回值是int。由此可见，pfun是一个指向返回值为int的函数的指针。
    - [《函数指针与指针函数》](http://yulingtianxia.com/blog/2014/04/17/han-shu-zhi-zhen-yu-zhi-zhen-han-shu/)

    
- inline内联函数是否可以递归
    - 函数的inline规范只是一个提示。 编译器可以（并且经常）完全忽略inline限定符的存在或不存在
    - 编译器可以选择有限地展开，或者完全采取不内联的方式（发现展开层次太多）

- 声明和定义的区别
    - 变量定义：用于为变量分配存储空间，还可为变量指定初始值。程序中，变量有且仅有一个定义。  
    - 变量声明：用于向程序表明变量的类型和名字。  
    - 定义也是声明：当定义变量时我们声明了它的类型和名字。    
    - extern关键字：通过使用extern关键字声明变量名而不定义它
    - 一个变量只能定义一次，但可以声明多次

- 结构体的对齐方式？判断一个结构体的大小？如何强制不对齐？
    - 在结构中，编译器为结构的每个成员按其自然边界（alignment）分配空间。各个成员按照它们被声明的顺序在内存中顺序存储，第一个成员的地址和整个结构的地址相同。
    - 为了使CPU能够对变量进行快速的访问,变量的起始地址应该具有某些特性,即所谓的”对齐”. 比如4字节的int型,其起始地址应该位于4字节的边界上,即起始地址能够被4整除.
    - 使用伪指令#pragma pack (n)，C编译器将按照n个字节对齐
    - __attribute__ ((packed))，取消结构在编译过程中的优化对齐，按照实际占用字节数进行对齐
    - [《C语言字节对齐、结构体对齐最详细的解释》](https://blog.csdn.net/lanzhihui_10086/article/details/44353381)
- 字节序的概念？（LINUX大端小端的概念，字节存储的顺序高低位）
    - 计算机电路先处理低位字节，效率比较高，因为计算都是从低位开始的。所以，计算机的内部处理都是小端字节序
    - 人类还是习惯读写大端字节序。所以，除了计算机的内部处理，其他的场合几乎都是大端字节序，比如网络传输和文件储存
    - [《理解字节序》](https://www.ruanyifeng.com/blog/2016/11/byte-order.html)

- 野指针的产生，危害，段错误怎么发生的？使用悬空指针一定会段错误吗？什么时候会，什么时候不会
    - 野指针是指向不可用内存区域的指针（非法内存，垃圾内存）。野指针不是NULL指针，是指向“垃圾”内存的指针
    - 产生原因：
        - 指针变量没有被初始化；没有初始化的指针值是随机的
        - 指针p被free/delete之后，没有置为NULL
        - 指针操作超越了变量的作用范围


- fwrite和write的区别，那是不是可以用write代替fwrite，read同理
    - fwrite和fread是带用户态缓冲的写和读
    - 以读为例，每次fread时，会从系统缓冲区中多读一些到用户态缓冲区，这样下次读的时候可以直接从用户态缓冲直接返回，而不需要陷入内核态读取

- memcpy与memmove的区别
    - memcpy不会检查src和dest是否重叠
    - memmove会检查src和dest重叠，因此是比较安全的
    ```c++
    #include <stddef.h> /* for size_t */
    void *memmove(void *dest, const void *src, size_t n)
    {
        unsigned char *pd = dest;
        const unsigned char *ps = src;
        if (__np_anyptrlt(ps, pd))
            for (pd += n, ps += n; n--;)
                *--pd = *--ps;
        else
            while(n--)
                *pd++ = *ps++;
        return dest;
    }
    ```
    - [《memcpy与memmove的区别》](https://www.jianshu.com/p/9c3784d8d8ad)

- malloc是如何进行内存分配的
    - malloc 函数的实质是它有一个将可用的内存块连接为一个长长的列表的所谓空闲链表
    - 调用 malloc（）函数时，它沿着连接表寻找一个大到足以满足用户请求所需要的内存块。 然后，将该内存块一分为二（一块的大小与用户申请的大小相等，另一块的大小就是剩下来的字节） ，将分配给用户的那块内存存储区域传给用户，并将剩下的那块（如果有的话）返回到连接表上
    - 调用 free 函数时，它将用户释放的内存块连接到空闲链表上。 到最后，空闲链会被切成很多的小内存片段
    - 如果用户申请一个大的内存片段， 那么空闲链表上可能没有可以满足用户要求的片段了。于是，malloc（）函数请求延时，并开始在空闲链表上检查各内存片段，对它们进行内存整理，将相邻的小空闲块合并成较大的内存块
    - [《linux-malloc底层实现原理》](https://blog.csdn.net/mmshixing/article/details/51679571)
    - [《malloc和free的实现原理解析》](https://jacktang816.github.io/post/mallocandfree/)

## 类
- class {} 内部实现的函数
    - 一般认为: 默认构造函数, 默认析构函数, 拷贝赋值函数, (移动构造函数, 移动赋值函数)
    - 《深度探索C++对象模型》中讲到, 不一定会生成这些函数, 然后blabla…(太多了, 这里不细说)
    - 构造函数、析构函数、拷贝构造函数、赋值运算符重载函数、取地址操作符重载、const修饰的取地址操作符重载
    - [《详解c++中类的六个默认的成员函数》](https://blog.csdn.net/peiyao456/article/details/51834981)


- 构造函数中是否能抛出异常
    - 构造函数中抛出异常，会导致析构函数不能被调用，所以可能会造成内存泄露或系统资源未被释放
    - 析构函数的执行不应该抛出异常。发生异常时会调用析构函数释放资源，此时如果再发生异常，系统将变得非常危险，也许很长时间什么错误也不会发生；但也许你的系统有时就会莫名奇妙地崩溃而退出了，而且什么迹象也没有
    - [《C++中构造函数和析构函数抛出异常问题》](https://blog.csdn.net/u012611878/article/details/78945586)

- C++中struct和class当作类使用时的区别
    - 默认的继承访问权限。struct是public的，class是private的
    - struct作为数据结构的实现体，它默认的数据访问控制是public的，而class作为对象的实现体，它默认的成员变量访问控制是private的

- 构造函数怎么做可以减少内存拷贝次数，与C++11无关，不要讲移动拷贝构造函数


- 讲一讲this指针
    - 对象的this指针并不是对象本身的一部分，不会影响sizeof(对象)的结果
    - 编译器自动为类的非静态函数插入隐含的this指针参数
    - this只能在成员函数中使用
    - this指针会因编译器不同而有不同的放置位置。可能是栈，也可能是寄存器，甚至全局变量
    - [《C++中this指针的用法详解》](http://blog.chinaunix.net/uid-21411227-id-1826942.html)

- this指针是怎么传进去的
    - 编译器在编译的时候，就把this指针以参数的形式传递给了成员函数

- C++中public，protected，private的区别，怎样可以访问protected
    - private,public,protected的访问范围:
        - private: 只能由该类中的函数、其友元函数访问,不能被任何其他访问，该类的对象也不能访问.
        - protected: 可以被该类中的函数、子类的函数、以及其友元函数访问,但不能被该类的对象访问
        - public: 可以被该类中的函数、子类的函数、其友元函数访问,也可以由该类的对象访问
        - 注：友元函数包括两种：设为友元的全局函数，设为友元类中的成员函数
    - 类的继承后方法属性变化
        - 使用private继承,父类的所有方法在子类中变为private;
        - 使用protected继承,父类的protected和public方法在子类中变为protected,private方法不变;
        - 使用public继承,父类中的方法属性不发生改变;
    - [《C++中public、protected、private的区别》](https://blog.csdn.net/scottly1/article/details/24354489)


- 成员初始化列表概念，可以在成员初始化列表中初始化父类成员吗？为什么
    - 不可以，因为成员初始化列表是成员定义+赋值两个操作，因此在初始化列表中初始化父类成员相当于会把父类成员重复定义一次，肯定会报错
    - 由于构造函数内的初始化相当于赋值了，所以为了效率，以及某些情况必须使用成员初始化列表，有如下几种情况：
        - 需要初始化的数据成员是对象的情况（为了效率，避免执行拷贝构造和赋值构造函数）
        - 需要初始化const修饰的类成员
        - 需要初始化引用成员数据


- 拷贝构造函数应用场景。和operator = 的比较。有没有默认拷贝构造函数
    - 拷贝构造函数必须以引用的方式传递参数。这是因为，在值传递的方式传递给一个函数的时候，会调用拷贝构造函数生成函数的实参。如果拷贝构造函数的参数仍然是以值的方式，就会无限循环的调用下去，直到函数的栈溢出。
    - 拷贝构造函数也是一种构造函数，那么它的功能就是创建一个新的对象实例
    - 赋值运算符是执行某种运算，将一个对象的值复制给另一个对象
    - 调用的是拷贝构造函数还是赋值运算符，主要是看是否有新的对象实例产生
    - 调用拷贝构造函数主要有以下场景
        - 对象作为函数的参数，以值传递的方式传给函数。　
        - 对象作为函数的返回值，以值的方式从函数返回
        - 使用一个对象给另一个对象初始化
    - [《C++ 拷贝构造函数和赋值运算符》](https://www.cnblogs.com/wangguchangqing/p/6141743.html)

- 空类是多大，能否实例化
    - 空类实例化后的大小为1，是为了取地址时能取到地址
    - 类的大小：
        - 为类的非静态成员数据的类型大小之和．    
        - 有编译器额外加入的成员变量的大小，用来支持语言的某些特性（如：指向虚函数的指针）
        - 为了优化存取效率，进行的边缘调整． 
        - 与类中的构造函数，析构函数以及其他的成员函数无关
    - [《sizeof 空类》](https://www.cnblogs.com/my_life/articles/3716594.html)

- 什么是虚拟继承
    - 虚继承的特点是，在任何派生类中的virtual基类总用同一个（共享）对象表示
    ![](http://images-1251273400.cosgz.myqcloud.com/20201012223733.png)
    - [《C++ 虚拟继承》](https://www.cnblogs.com/heyonggang/p/3255155.html)

- 菱形继承（虚基类指针） 虚基类指针指向哪个 简画子类对象内存
    - [《图解C++菱形继承、虚继承对象的内存分布》](https://blog.csdn.net/AgoniAngel/article/details/105893798)
  
- 讲一下C++ 类的内存布局，继承，多继承，虚继承
  
- C++的子类虚继承两个父类的内存模型。
    - [《(好)C++ 多继承和虚继承的内存布局》](https://blog.csdn.net/yockie/article/details/50603236)

- 编译器默认初始化cpp空类几个函数（默认构造，默认拷贝构造，operator=，默认析构）
    - C++11可能会有默认移动构造） 编译器会生成6个成员函数： 一个缺省的构造函数、一个拷贝构造函数、一个析构函数、一个赋值运算符、两个取址运算符

- class怎么防止继承
    - 不能直接将类的构造函数设为private，因为这样的话，这个类也无法实例化对象，没有意义
    ![](http://images-1251273400.cosgz.myqcloud.com/20201012223501.png)
    - [《c++如何防止一个类被其他类继承》](https://blog.csdn.net/zhang1308299607/article/details/76100430)

- C++中的RAII机制
    - RAII是Resource Acquisition Is Initialization（wiki上面翻译成 “资源获取就是初始化”）的简称，是C++语言的一种管理资源、避免泄漏的惯用法。
    - 由于系统的资源不具有自动释放的功能，而C++中的类具有自动调用析构函数的功能。如果把资源用类进行封装起来，对资源操作都封装在类的内部，在析构函数中进行释放资源。当定义的局部变量的生命结束时，它的析构函数就会自动的被调用，如此，就不用程序员显示的去调用释放资源的操作了。
    - [《C++中的RAII机制》](https://www.jianshu.com/p/b7ffe79498be)

- 类模板和模板类的区别
    - 类模板只是一个抽象的描述,在应用时在内存中是不占空间的,  
  而模板类是一个具体的东西
    - 模板类是类模板的实例
    
## 多态与虚函数
- 多态与虚函数
    - 多态。多态性(polymorphism)可以简单地概括为“一个接口，多种方法”。分为静态多态（函数重载）与动态多态（虚拟函数）
    - 虚函数。虚函数是C++中用于实现多态的机制，允许在派生类中重新定义与基类同名的函数，并且可以通过基类指针或引用来访问基类和派生类中的同名函数
![](http://images-1251273400.cosgz.myqcloud.com/20201008154929.png)

- 多态的类型(静态、动态)， 分别如何实现
    - 静态多态。通过函数重载和模版（泛型编程）来实现
    - 动态多态。动态多态通过虚函数实现。最常见的用法就是声明基类的指针，利用该指针指向任意一个子类对象，调用相应的虚函数，可以根据指向的子类的不同而调用不同的方法。
    - [《C++ 多态的两种形式》](https://blog.csdn.net/K346K346/article/details/82774937)

- 虚函数表
    - C++的编译器应该是保证虚函数表的指针存在于对象实例中最前面的位置（这是为了保证取到虚函数表的有最高的性能——如果有多层继承或是多重继承的情况下）。 这意味着我们通过对象实例的地址得到这张虚函数表，然后就可以遍历其中函数指针，并调用相应的函数。

- 虚析构函数及其作用
    - 通过父指针释放对象时，能够调用到子对象的析构函数
- 如果基类的析构函数没有声明为虚函数，会发生什么
    - 会直接调用掉基类的析构函数，无法执行子类的析构函数造成内存泄露

- 虚函数与纯虚函数的区别
    - 虚函数。虚函数的作用是允许在派生类中重新定义与基类同名的函数，并且可以通过基类指针或引用来访问基类和派生类中的同名函数
    - 纯虚函数。在很多情况下，基类本身生成对象是不合情理的。例如，动物作为一个基类可以派生出老虎、孔雀等子类，但动物本身生成对象明显不合常理

- 哪些情况必须要把析构函数写成虚函数
    - 若存在类的继承关系,而且基类指针指向派生类对象时,一般需要将析构函数声明为虚函数,不然在使用基类指针进行析构时会无法调用派生类的析构函数而造成内存泄漏等问题

- 构造函数是否可以为虚函数
    - 构造函数不需要是虚函数，也不允许是虚函数，因为创建一个对象时我们总是要明确指定对象的类型
    - 从存储空间角度，虚函数对应一个指向vtable虚函数表的指针；如果构造函数是虚的，就需要通过 vtable来调用，可是对象还没有实例化，也就是内存空间还没有，怎么找vtable呢
    - [《构造函数为什么不能是虚函数》](https://www.cnblogs.com/youxin/p/4355946.html)

- 基类里private成员函数可以声明为虚函数吗
    - 可以。一个成员函数被定义为private属性，标志着其只能被当前类的其他成员函数(或友元函数)所访问。而virtual修饰符则强调父类的成员函数可以在子类中被重写，因为重写之时并没有与父类发生任何的调用关系，故而重写是被允许的
    - 而要想在其它函数中使用父类指针调用private虚函数，需要将该函数声明为父类的友元函数
    - [《虚函数能否为private》](https://blog.csdn.net/shltsh/article/details/45999929)
    - [《父类的私有虚函数》](https://blog.csdn.net/u014587123/article/details/80457383)


- 基类的虚函数有没有必要加virtual，为什么
    - 基类的虚函数必须要加virtual，子类的虚函数可以不加
    - 如果父类或者祖先类中函数func()为虚函数，则子类及后代类中，函数func()是否加virtual关键字，都将是虚函数。为了提高程序的可读性，建议后代中虚函数都加上virtual关键字。



## static和const用法
- static的用法
    - 全局变量。该全局变量只能在当前文件访问，存储位置为全局（静态）存储区，即DATA段或BSS段
    - 局部变量。该局部变量的生命周期延长到程序结束
    - 函数。该函数只能在当前文件内访问
    - 类中的变量和函数。则该变量或函数所属于类，而不是类的实例。可以通过类直接调用static的变量和函数，static函数不能调用类的非static函数
    - 参考： 
        - [《const、static变量存放位置》](https://blog.csdn.net/lxw907304340/article/details/79982824)
        - [《C/C++ 中 static 的用法全局变量与局部变量》](https://www.runoob.com/w3cnote/cpp-static-usage.html)

- const用法
    - 普通变量
    - 指针变量。常量指针(const int *p)和指针常量(int * const p)
    - 函数的参数和返回值。对于函数参数，一般针对指针，防止被函数篡改；对于函数返回值，既不能被赋值，也不能被修改，以避免用户修改返回值
    - 类成员函数。避免类成员函数修改任何类成员
    - 参考：
        - [C++ const 关键字小结](https://www.runoob.com/w3cnote/cpp-const-keyword.html)

- const函数和非const函数可以实现重载吗？
  - 可以
  ```c++
  Class A {
    int function ();
    int function () const;
   };
  ```
  - 且在调用时，只用A类的const对象才能调用const版本的function函数，而非const对象可以调用任意一种，通常非const对象调用不是const版本的function函数
  - 按照函数重载的定义，函数名相同而形参表有本质不同的函数称为重载。在类中，由于隐含的this形参的存在，const版本的function函数使得作为形参的this指针的类型变为指向const对象的指针，而非const版本的使得作为形参的this指针就是正常版本的指针。此处是发生重载的本质。重载函数在最佳匹配过程中，对于const对象调用的就选取const版本的成员函数，而普通的对象调用就选取非const版本的成员函数。

## c++11
- c++11有哪些新特性
    - auto
    - 后置返回类型（方便模板定义的类型推导decltype）
    - 元组类型
    - lambda
    - 智能指针

    - 基于范围的for循环
    - 空指针常量nullptr （NULL是常量0，会造成一些类型错误。比如想要空指针类型，结果是int）
    - **以go作为类比来看c++11的一些新特性**
    ```go
    func A() (int, error) { //后置返回类型; 元组
        m := make(map[string]int, 100)  //auto; 智能指针
        
        defer func (){      //lambda匿名函数
        }()

        for k, v := range m {   //基于范围的for循环
            
        }
        return 0, nil   //空指针常量nullptr
    }
    ```
    - long long int 类型
    - std::bind和std::function函数封装器

    - 线程支持
    - 显式override和final（避免子类重写虚函数时意外地创建新的虚函数）
    - 模板别名

    - 参考：
        - [《十大必掌握C++11新特性》](https://blog.csdn.net/FX677588/article/details/70157088)

- auto怎么实现
  - auto的实现原理是基于模板类型推断
  - [《理解auto类型推断》](https://www.cnblogs.com/harlanc/p/10628321.html)
  - 作用：
    - 拥有初始化表达式的复杂类型变量声明时简化代码
    - 避免类型声明时的麻烦而且避免类型声明时的错误
    - [《C++ 11新特性的用法之auto》](https://blog.csdn.net/hushujian/article/details/43196589)
  
- auto变量不给初始值可以吗
  - 必须要有初始值


- auto关键字用过吗，类型推导有什么限制。如果用来声明函数要注意什么
- 
- std::enable_if了解吗

#### 智能指针
- 智能指针
    不需要手动去delete释放指针，退出作用域后自动释放（不管是正常退出，还是异常退出，类似golang的defer)
    有下面几种只能指针
    - auto_ptr。C++11中已经废弃。一个auto_ptr A赋值给auto_ptr B时，A会变成null指针，存在访问null指针导致程序崩溃的风险
    - unique_ptr。对于同一个指针，允许一个unique_ptr持有对其的引用，重复赋值会导致编译不通过。unique_ptr适用于比较固定的指针。
    - shared_ptr。允许多个shared_ptr指向同一个指针，内部采用引用计数来计算对指针的引用数，当引用数为0时，指针就会被释放
    - 参考
        - [《C++中的智能指针》](https://www.nowcoder.com/ta/review-c/review?tpId=22&tqId=31357&query=&asc=true&order=&page=35)

- 智能指针的实现原理是什么
    - 利用了一种叫做RAII（资源获取即初始化）的技术对普通的指针进行封装，这使得智能指针实质是一个对象，行为表现的却像一个指针
    - 智能指针的作用是防止忘记调用delete释放内存和程序异常的进入catch块忘记释放内存。另外指针的释放时机也是非常有考究的，多次释放同一个指针会造成程序崩溃，这些都可以通过智能指针来解决。
    - 智能指针就是模拟指针动作的类。所有的智能指针都会重载 -> 和 * 操作符
    - 智能指针类将一个计数器与类指向的对象相关联，引用计数跟踪该类有多少个对象共享同一指针
    ```c++
    #include <iostream>
    #include <memory>

    template<typename T>
    class SmartPointer {
    private:
        T* _ptr;
        size_t* _count;
    public:
        SmartPointer(T* ptr = nullptr) :
                _ptr(ptr) {
            if (_ptr) {
                _count = new size_t(1);
            } else {
                _count = new size_t(0);
            }
        }

        SmartPointer(const SmartPointer& ptr) {
            if (this != &ptr) {
                this->_ptr = ptr._ptr;
                this->_count = ptr._count;
                (*this->_count)++;
            }
        }

        SmartPointer& operator=(const SmartPointer& ptr) {
            if (this->_ptr == ptr._ptr) {
                return *this;
            }

            if (this->_ptr) {
                (*this->_count)--;
                if (this->_count == 0) {
                    delete this->_ptr;
                    delete this->_count;
                }
            }

            this->_ptr = ptr._ptr;
            this->_count = ptr._count;
            (*this->_count)++;
            return *this;
        }

        T& operator*() {
            assert(this->_ptr == nullptr);
            return *(this->_ptr);

        }

        T* operator->() {
            assert(this->_ptr == nullptr);
            return this->_ptr;
        }

        ~SmartPointer() {
            (*this->_count)--;
            if (*this->_count == 0) {
                delete this->_ptr;
                delete this->_count;
            }
        }

        size_t use_count(){
            return *this->_count;
        }
    };
    ```
    - [《C++11中智能指针的原理、使用、实现》](https://www.cnblogs.com/wxquare/p/4759020.html)


- shared_ptr基本用法
  - 初始化。通过构造函数、std::make_shared<T>辅助函数和reset方法来初始化shared_ptr
  ```c++
    std::shared_ptr<Person> p1(new Person(1));// Person(1)的引用计数为1

    std::shared_ptr<Person> p2 = std::make_shared<Person>(2);

    p1.reset(new Person(3));// 首先生成新对象，然后引用计数减1，引用计数为0，故析构Person(1)
                            // 最后将新对象的指针交给智能指针

    std::shared_ptr<Person> p3 = p1;//现在p1和p3同时指向Person(3)，Person(3)的引用计数为2

    p1.reset();//Person(3)的引用计数为1
    p3.reset();//Person(3)的引用计数为0，析构Person(3)
  ```
  - 注意点
    - 不要用一个原始指针初始化多个shared_ptr，原因在于，会造成二次销毁
   ```c++
    int *p5 = new int;
    std::shared_ptr<int> p6(p5);
    std::shared_ptr<int> p7(p5);// logic error
   ```
    - 禁止通过shared_from_this()返回this指针，这样做可能也会造成二次析构
    - 不要在函数实参中创建shared_ptr。因为C++的函数参数的计算顺序在不同的编译器下是不同的。正确的做法是先创建好，然后再传入
    ```c++
    function(shared_ptr<int>(new int), g());
    ```
    - 避免循环引用。智能指针最大的一个陷阱是循环引用，循环引用会导致内存泄漏。解决方法是AStruct或BStruct改为weak_ptr。
    - [《智能指针shared_ptr的用法》](https://www.cnblogs.com/jiayayao/p/6128877.html)
    - 
- 用过shared_ptr和weak_ptr吗？为什么要搭配使用？看过shared_ptr的源码吗？说一下
    - shared_ptr共享被管理对象，同一时刻可以有多个shared_ptr拥有对象的所有权，当最后一个shared_ptr对象销毁时，被管理对象自动销毁
    - weak_ptr不拥有对象的所有权，但是它可以判断对象是否存在和返回指向对象的shared_ptr类型指针；它的用途之一是解决多个对象内部含有shared_ptr循环指向，导致对象无法释放的问题
    - [《share_ptr与weak_ptr的区别与联系》](https://blog.csdn.net/weixin_41066529/article/details/89480260)

- share_ptr一定能保证内存不泄露吗？写代码说明（写完以后又问了如何避免）
    - 不能，如果存在循环引用会导致内存泄露
    - 引入weak_ptr来打破循环引用


- unique_ptr怎么实现
    - unique_ptr本身是一个类，在其析构函数中执行指针的释放
    - 删除拷贝构造函数和赋值构造函数（=delete），从而实现只有一个实例能持有指针
    - 有一个例外，支持移动拷贝构造函数和移动赋值构造函数，从而能够在函数中返回右值unique_ptr
    ```c++
    /* 从函数返回一个unique_ptr */
    unique_ptr<int> clone(int p ){
        return unique_ptr<int>(new int(p));
    }
    ```
    - [《C++ 之实现自己的 unique_ptr》](https://blog.csdn.net/liushengxi_root/article/details/80672901)



- shared_ptr、unique_ptr是线程安全的吗，底层实现
    - 不是线程安全的
    - 虽然引用计数是用原子操作，但是指向的对象不是原子的，也没有加锁
    - ![](http://images-1251273400.cosgz.myqcloud.com/20201014080203.png)
    - ![](http://images-1251273400.cosgz.myqcloud.com/20201014080222.png)
    - [《shared_ptr的线程安全性》](https://blog.csdn.net/D_Guco/article/details/80155323)
- shared_ptr循环引用，a->b,b->a,最后引用计数是多少
- RAII是什么？全称呢？和智能指针什么关系
  

#### 移动构造函数和移动赋值
- 移动构造函数和移动赋值运算符
  - 如果拷贝或者赋值的对象是一个右值引用，那么就可以安全地移动它，而不是拷贝它
  - 在新建，拷贝对象时，如果是一个右值引用，那就能够使用移动构造和赋值函数，来节省拷贝的成本
  ```c++
      unique_ptr& operator=(unique_ptr&& source)   // note the rvalue reference
        {
            if (this != &source)    // beware of self-assignment
            {
                delete ptr;         // release the old resource

                ptr = source.ptr;   // acquire the new resource
                source.ptr = nullptr;
            }
            return *this;
        }
    };
  ```
  - [《翻译：怎样理解 C++ 11中的move语义（深入）》](https://www.cnblogs.com/tingshuo/archive/2013/01/22/2871328.html)
  
- std::move的作用与意义是什么
  - 有时候，我们可能想转移左值，也就是说，有时候我们想让编译器把左值当作右值对待，以便能使用转移构造函数，即便这有点不安全
  - 出于这个目的，C++ 11在标准库的头文件<utility>中提供了一个模板函数std::move
  - 简单来说，std::move就是一个强制类型转换
  


- 左值与右值,左值引用与右值引用
    - 左值就是有名字的变量，可以被赋值
    - 右值就是临时变量（对象），没有名字，不能被赋值
    - 左值引用就是平时看到的引用，是对左值的引用
    - 右值引用是c++11中增加的特性，用&&符号表示。用来延长右值的生命周期，减少临时对象的生成
    - [《C++ 11 左值，右值，左值引用，右值引用》](https://blog.csdn.net/xiaolewennofollow/article/details/52559306)

- nullptr比NULL优势（指针地址和整数的歧义？）
    -  NULL的值其实就是0，在有如下函数重载时，调用bar(a, NULL)调用的其实是第二个函数
    ```c++
    void bar(sometype1 a, sometype2 *b);
    void bar(sometype1 a, int i);
    ```
    - 使用nullptr不会有这种歧义，调用bar(a, nullptr)始终执行的是第一个函数
    - [《史上最明白的 NULL、0、nullptr 区别分析》](https://www.cnblogs.com/porter/p/3611718.html)


- std里的bind()使用成员函数和普通函数有什么区别？
    - 使用成员函数需要注意补充this参数
    - [《C++11 中std::function和std::bind的用法》](https://blog.csdn.net/liukang325/article/details/53668046)

- lambda用法
    - lambda完整声明
    ```c++
    [capture list] (params list) mutable exception-> return type { function body }
    ```
    - 变量捕获符的用法
    ![](http://images-1251273400.cosgz.myqcloud.com/20201015070645.png)

## 模板
- 模板了解多少
- 模板偏特化了解吗
    - 有时为了需要，针对特定的类型，需要对模板进行特化，也就是所谓的特殊处理。比如有以下的一段代码：
    ```c++
    #include <iostream>
    using namespace std;

    template <class T>
    class TClass
    {
    public:
         bool Equal(const T& arg, const T& arg1);
    };

    template <class T>
    bool TClass<T>::Equal(const T& arg, const T& arg1)
    {
         return (arg == arg1);
    }
    ```
    - 类里面就包括一个Equal方法，用来比较两个参数是否相等；上面的代码运行没有任何问题；但是，你有没有想过，在实际开发中是万万不能这样写的，对于float类型或者double的参数，绝对不能直接使用“==”符号进行判断
    - 对于float或者double类型，我们需要进行特殊处理，处理如下,这就是全特化。全特化的模板已经不具有模板的意思了。偏特化就是
    ```c++
    template <class T>
    class Compare
    {
    public:
         bool IsEqual(const T& arg, const T& arg1);
    };

    // 已经不具有template的意思了，已经明确为float了
    template <>
    class Compare<float>
    {
    public:
         bool IsEqual(const float& arg, const float& arg1);
    };

    // 已经不具有template的意思了，已经明确为double了
    template <>
    class Compare<double>
    {
    public:
         bool IsEqual(const double& arg, const double& arg1);
    };

    ```
    - 偏特化是指提供另一份template定义式，而其本身仍为templatized
    ```c++
    template <class _Iterator>
    struct iterator_traits
    {
         typedef typename _Iterator::iterator_category  iterator_category;
         typedef typename _Iterator::value_type        value_type;
         typedef typename _Iterator::difference_type   difference_type;
         typedef typename _Iterator::pointer           pointer;
         typedef typename _Iterator::reference         reference;
    };

    // specialize for _Tp*
    template <class _Tp>
    struct iterator_traits<_Tp*> 
    {
         typedef random_access_iterator_tag iterator_category;
         typedef _Tp                         value_type;
         typedef ptrdiff_t                   difference_type;
         typedef _Tp*                        pointer;
         typedef _Tp&                        reference;
    };
    ```
    - [《C++ 模板，特化，与偏特化》](https://www.jianshu.com/p/4be97bf7a3b9)



## 多线程和锁
- unique_lock和lock_guard的区别
    - lock_guard是RAII模板类的简单实现，功能简单。lock_guard 在构造函数中进行加锁，析构函数中进行解锁
    - unique_lock比lock_guard使用更加灵活，功能更加强大.允许延迟锁定、锁定的有时限尝试、递归锁定、所有权转移和与条件变量一同使用
    - [《std::unique_lock与std::lock_guard区别示例》](https://www.cnblogs.com/xudong-bupt/p/9194394.html)

- pthread_once的作用及实现
    - 在多线程环境中，有些事仅需要执行一次，pthread_once就是确保某个初始化函数只会执行一次，类似于golang的sync.Once
    - 使用互斥锁和条件变量保证由pthread_once()指定的函数执行且仅执行一次
    - [《pthread_once()函数详解》](https://blog.csdn.net/hustyangju/article/details/46607811)

- 条件变量应用场景
    - 条件变量（condition_variable）实现多个线程间的同步操作；当条件不满足时，相关线程被一直阻塞，直到某种条件出现，这些线程才会被唤醒
    - 条件变量类似于golang中的channel
    - [《C++11条件变量使用详解》](https://blog.csdn.net/c_base_jin/article/details/89741247)

- 线程池怎么使用锁，muduo中是使用什么锁，使用的是互斥锁，并不是使用读写锁。
- 对比过muduo的异步日志效率跟别的日志系统吗？
- 线程池是怎么实现的?线程池是用自己写的还是用的系统api
    - [《基于C++11的线程池》](https://www.cnblogs.com/lzpong/p/6397997.html)

- 两个线程什么情况会出现死锁
    - 忘记释放锁
    - 单线程重复申请锁
    - 双线程多锁申请（两者以不同的顺序加锁）
    - 环形锁申请
    - [《C++ 死锁及解决办法》](https://blog.csdn.net/weixin_38416696/article/details/90598963 )

- 如何控制线程执行顺序,顺序打印ABC
    ```c++
    #include<iostream>
    #include<vector>
    #include<thread>
    #include<condition_variable>
    using namespace std;
    mutex mu;
    std::condition_variable cond_var;
    int num=0;
    void func(char ch)
    {
    	int n=ch-'A';
    	for(int i=0;i<10;i++)
    	{
    		std::unique_lock<std::mutex> mylock(mu);
    		cond_var.wait(mylock,[n]{return n==num;});
    		cout<<ch;
    		num=(num+1)%3;
    		mylock.unlock();
    		cond_var.notify_all();
    	}
    }
    int main()
    {
    	vector<thread> pool;
    	pool.push_back(thread(func,'A'));
    	pool.push_back(thread(func,'B'));
    	pool.push_back(thread(func,'C'));
    	for(auto iter=pool.begin();iter!=pool.end();iter++)
    	{
    		iter->join();
    	}
    	return 0;
    }
    ```
- std::function和std::bind
    - [《C++11 中的std::function和std::bind》](https://www.jianshu.com/p/f191e88dcc80)
- std::placeholders
    - 占位符可以用来调换bind中参数的顺序
    ```c++
    void function(arg1,arg2,arg3,arg4,arg5)
    {
            //do something
    }
    auto g = bind(function,a,b,_2,c,_1);
    ```
    - [《标准库bind函数中使用占位符placeholders》](https://www.cnblogs.com/houjun/p/4802190.html)

- 讲讲std::thread 和操作系统级别的线程有什么区别
    - thread库可以看做对不同平台多线程API的一层包装,因此使用新标准提供的线程库编写的程序是跨平台的
    - [《C++ std::thread概念介绍》](https://www.cnblogs.com/yssjun/p/11533346.html)

- 了解C++11 的原子操作吗，C++11多线程内存模型知道吗


- 无锁编程，release acquire语义

