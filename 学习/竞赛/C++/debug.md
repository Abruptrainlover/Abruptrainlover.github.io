## **GDB是什么**

参考网站

[参考网站]: http://c.biancheng.net/gdb/	"参考网站"

本文来源:

[GDB调试命令详解]: https://zhuanlan.zhihu.com/p/357360607



### **调试程序**

程序中出现的语法错误可以借助编译器解决；但逻辑错误则只能靠自己解决。实际场景中解决逻辑错误最高效的方法，就是借助调试工具对程序进行调试。

所谓调试（Debug），就是让代码一步一步慢慢执行，跟踪程序的运行过程。比如，可以让程序停在某个地方，查看当前所有变量的值，或者内存中的数据；也可以让程序一次只执行一条或者几条语句，看看程序到底执行了哪些代码。

也就是说，通过调试程序，我们可以监控程序执行的每一个细节，包括变量的值、函数的调用过程、内存中数据、线程的调度等，从而发现隐藏的错误或者低效的代码。

### **GDB的作用**

`GDB` 全称“GNU symbolic debugger”，从名称上不难看出，它诞生于 `GNU` 计划（同时诞生的还有 GCC、Emacs 等），是 `Linux` 下常用的程序调试器。发展至今，`GDB` 已经迭代了诸多个版本，当下的 `GDB` 支持调试多种编程语言编写的程序，包括 `C、C++、Go、Objective-C、OpenCL、Ada`等。实际场景中，`GDB` 更常用来调试 `C` 和 `C++`程序。

总的来说，借助 `GDB`调试器可以实现以下几个功能：

程序启动时，可以按照我们自定义的要求运行程序，例如设置参数和环境变量；

可使被调试程序在指定代码处暂停运行，并查看当前程序的运行状态（例如当前变量的值，函数的执行结果等），即支持断点调试；

程序执行过程中，可以改变某个变量的值，还可以改变代码的执行顺序，从而尝试修改程序中出现的逻辑错误。

### **GDB安装**

1、通过包管理器进行安装

```text
$ yum -y install gdb
```

2、源码安装GDB

在**[gdb源码包](https://link.zhihu.com/?target=http%3A//ftp.gnu.org/gnu/gdb/)**上面下载相应的版本进行安装即可。

3、查看GDB版本

输入`gdb -v`,即可查看当前安装的`gdb`的版本。

```text
$ gdb -v
GNU gdb (GDB) Red Hat Enterprise Linux 7.6.1-94.el7
Copyright (C) 2013 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-redhat-linux-gnu".
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
```

如果显示出`gdb`的版本，也说明了安装成功。

## **GDB的用法**

### **常用调试命令**

`GDB` 的主要功能就是监控程序的执行流程。这也就意味着，只有当源程序文件编译为可执行文件并执行时，并且该文件中必须包含必要的调试信息（比如各行代码所在的行号、包含程序中所有变量名称的列表（又称为符号表）等），`GDB`才会派上用场。

所以在编译时需要使用 `gcc/g++ -g` 选项编译源文件，才可生成满足 `GDB` 要求的可执行文件

![](C:\Users\杨志伟\OneDrive\桌面\学习\images\v2-f896025055ff57a63a6bd2de406e9ab1_1440w.jpg)

示例：

```text
$ ls
main.cpp
$ g++ -g -o test main.cpp
$ ls
main.cpp  test
$ gdb test         <-- 启动gdb进行调试
GNU gdb (GDB) Red Hat Enterprise Linux 7.6.1-94.el7
Copyright (C) 2013 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-redhat-linux-gnu".
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>...
Reading symbols from /home/zhuyong/project/linux/blog/gdb/test...done.
(gdb)
```

`gdb`启动时会默认打印一堆免责条款，通过添加 `--silent`（或者 `-q`、`--quiet`）选项，可将这部分信息屏蔽掉。

下面先用个例子运行下上述调试命令

```text
$ gdb test -q      <-- 启动gdb进行调试
Reading symbols from /home/zhudi/project/linux/blog/gdb/test...done.
(gdb) l            <-- 显示带行号的源代码
1 #include <iostream>
2 using namespace std;
3
4 int main() {
5     int sum = 0;
6     int n = 1;
7     while (n <= 100) {
8         sum += n;
9         n++;
10     }
(gdb)              <-- 默认情况下，l 选项只显示 10 行源代码，如果查看后续代码，按 Enter 回车键即可
11     cout << "sum = " << sum << endl;
12
13     return 0;
14 }
15
(gdb) b 7          <-- 在第7行源代码处打断点
Breakpoint 1 at 0x4008d3: file main.cpp, line 7.
(gdb) r            <-- 运行程序，遇到断点停止
Starting program: /home/zhudi/project/linux/blog/gdb/test

Breakpoint 1, main () at main.cpp:7
7     while (n <= 100) {
Missing separate debuginfos, use: debuginfo-install glibc-2.17-307.el7.1.x86_64 libgcc-4.8.5-39.el7.x86_64 libstdc++-4.8.5-39.el7.x86_64
(gdb) print n      <-- 查看代码中变量 n 的值
$1 = 1             <-- 当前 n 的值为 1，$1 表示该变量 表示该变量所在存储区的名称
(gdb) b 13
Breakpoint 2 at 0x40090e: file main.cpp, line 13.
(gdb) n            <-- 单步执行程序
8         sum += n;
(gdb) n            <-- 单步执行程序
9         n++;
(gdb) c            <-- 继续执行程序
Continuing.
sum = 5050

Breakpoint 2, main () at main.cpp:13
13     return 0;
(gdb) print sum     <-- 查看 sum 的值    
$2 = 5050           <-- 当前 sum 的值为 5050
(gdb) q             <-- 退出调试
A debugging session is active.

 Inferior 1 [process 8449] will be killed.

Quit anyway? (y or n) y     <-- 确认是否退出调试，y 为退出，n 为不退出
```

接下来分别介绍下各个命令的用法

### **GDB 断点调试**

### **启动程序**

根据不同场景的需要，`GDB` 调试器提供了多种方式来启动目标程序，其中最常用的就是`run` 指令，其次为 `start` 指令。也就是说，`run`和 `start` 指令都可以用来在 `GDB` 调试器中启动程序，它们之间的区别是：

- 默认情况下，`run` 指令会一直执行程序，直到执行结束。如果程序中手动设置有断点，则 `run`指令会执行程序至第一个断点处；
- `start` 指令会执行程序至`main()`主函数的起始位置，即在`main()`函数的第一行语句处停止执行（该行代码尚未执行）。

### **break命令**

`break` 命令（可以用`b` 代替）常用的语法格式有以下 2 种。

```text
1、(gdb) break location      // b location
2、(gdb) break ... if cond   // b .. if cond
```

1. 第一种格式中，`location` 用于指定打断点的具体位置，其表示方式有多种，如表 1 所示。

   ![](C:\Users\杨志伟\OneDrive\桌面\学习\images\v2-d1f6641cb4b5f65d28561685e9860372_r.jpg)

1. 第二种格式中，... 可以是表 1 中所有参数的值，用于指定打断点的具体位置；`cond` 为某个表达式。整体的含义为：每次程序执行到 ... 位置时都计算 `cond` 的值，如果为 `True`，则程序在该位置暂停；反之，程序继续执行。另外也可以用`condition` 为断点设置命中条件。

### **tbreak和rbreak命令**

`tbreak` 命令可以看到是 break 命令的另一个版本，`tbreak` 和 `break` 命令的用法和功能都非常相似，唯一的不同在于，使用 `tbreak` 命令打的断点仅会作用 1 次，即使程序暂停之后，该断点就会自动消失。

和 `break` 和 `tbreak` 命令不同，`rbreak`命令的作用对象是 `C`、`C++` 程序中的函数，它会在指定函数的开头位置打断点。语法格式

```text
(gdb) tbreak regex
```

其中 `regex` 为一个正则表达式，程序中函数的函数名只要满足 `regex`条件，`tbreak` 命令就会其内部的开头位置打断点。值得一提的是，`tbreak` 命令打的断点和 `break` 命令打断点的效果是一样的，会一直存在，不会自动消失。

### **示例**

```text
$ gdb test -q
Reading symbols from /home/zhudi/project/linux/blog/gdb/test...done.
(gdb) l
4 
5 void cb_one() {
6     cout << "cb_one" << endl;
7 }
8 void cb_second() {
9     cout << "cb_second" << endl;
10 }
11 
12 int main() {
13     int sum = 0;
(gdb) 
14     int n = 1;
15     while (sum < 100) {
16         sum += n;
17         n++;
18         cout << "sum = " << sum << endl;
19         sleep(1);
20         cb_one();
21         cb_second();
22     }
23     cout << "sum = " << sum << endl;
(gdb) b 16                  <-- 在第16行打断点
Breakpoint 1 at 0x400959: file main.cpp, line 16.
(gdb) r                     <-- 启动程序
Starting program: /home/zhudi/project/linux/blog/gdb/test 

Breakpoint 1, main () at main.cpp:16
16         sum += n;       <-- 在16行暂停
(gdb) b +2                  <--在当前位置之后的2行处设置断点
Breakpoint 2 at 0x400963: file main.cpp, line 18.
(gdb) c
Continuing.

Breakpoint 2, main () at main.cpp:18
18         cout << "sum = " << sum << endl;
(gdb) b 19 if sum>2         <-- 条件断点
Breakpoint 3 at 0x40098c: file main.cpp, line 19.
(gdb) c
Continuing.
sum = 1
cb_one
cb_second

Breakpoint 1, main () at main.cpp:16
16         sum += n;
(gdb) c
Continuing.

Breakpoint 2, main () at main.cpp:18
18         cout << "sum = " << sum << endl;
(gdb) c
Continuing.
sum = 3

Breakpoint 3, main () at main.cpp:19
19         sleep(1);
(gdb) p sum
$1 = 3
(gdb) rbreak cb_*            <-- 匹配所有以cb_开头的函数
Breakpoint 4 at 0x400901: file main.cpp, line 6.
void cb_one();
Breakpoint 5 at 0x400923: file main.cpp, line 9.
void cb_second();
Breakpoint 6 at 0x400a17: file main.cpp, line 26.
(gdb) c
Continuing.

Breakpoint 4, cb_one () at main.cpp:6
6     cout << "cb_one" << endl;     <-- 在cb_one函数的第一行暂停
(gdb) c
Continuing.
cb_one

Breakpoint 5, cb_second () at main.cpp:9
9     cout << "cb_second" << endl;  <-- 在cb_second函数的第一行暂停
```

### **删除或禁用断点**

**删除断点**

如果之前建立的断点不再需要或者暂时不需要，该如何删除或者禁用呢？常用的方式有 2 种：

1. 使用 `quit` 命令退出调试，然后重新对目标程序启动调试，此方法会将消除上一次调试操作中建立的所有断点；
2. 使用专门删除或禁用断点的命令，既可以删除某一个断点，也可以删除全部断点。

无论是普通断点、观察断点还是捕捉断点，都可以使用 `clear` 或者 `delete` 命令进行删除。

`clear` 命令可以删除指定位置处的所有断点，常用的语法格式如下所示：

```text
(gdb) clear location
```

参数`location` 通常为某一行代码的行号或者某个具体的函数名。当 `location` 参数为某个函数的函数名时，表示删除位于该函数入口处的所有断点。

`delete` 命令（可以缩写为 `d`）通常用来删除所有断点，也可以删除指定编号的各类型断点，语法格式如下：

```text
delete [breakpoints] [num]
```

其中，`breakpoints` 参数可有可无，`num` 参数为指定断点的编号，其可以是`delete` 删除某一个断点，而非全部。

如果不指定 `num`参数，则 `delete` 命令会删除当前程序中存在的所有断点。

**禁用断点**

禁用断点可以使用 `disable` 命令，语法格式如下：

```text
disable [breakpoints] [num...]
```

`breakpoints` 参数可有可无；`num...`表示可以有多个参数，每个参数都为要禁用断点的编号。如果指定 `num...`，`disable` 命令会禁用指定编号的断点；反之若不设定 `num...`，则 `disable` 会禁用当前程序中所有的断点。

对于禁用的断点，可以使用`enable` 命令激活，该命令的语法格式有多种，分别对应有不同的功能：

```text
enable [breakpoints] [num...]                        激活用 num... 参数指定的多个断点，如果不设定 num...，表示激活所有禁用的断点
enable [breakpoints] once num…                 临时激活以 num... 为编号的多个断点，但断点只能使用 1 次，之后会自动回到禁用状态
enable [breakpoints] count num...      临时激活以 num... 为编号的多个断点，断点可以使用 count 次，之后进入禁用状态
enable [breakpoints] delete num…               激活 num.. 为编号的多个断点，但断点只能使用 1 次，之后会被永久删除。
```

其中，`breakpoints` 参数可有可无；`num...`表示可以提供多个断点的编号，`enable`命令可以同时激活多个断点。

### **观察断点监控变量值的变化**

### **观察断点**

要知道，`GDB` 调试器支持在程序中打 3 种断点，分别为普通断点、观察断点和捕捉断点。其中 `break` 命令打的就是普通断点，而 `watch` 命令打的为观察断点。

使用 `GDB` 调试程序的过程中，借助观察断点可以监控程序中某个变量或者表达式的值，只要发生改变，程序就会停止执行。相比普通断点，观察断点不需要我们预测变量（表达式）值发生改变的具体位置

```text
(gdb) watch cond
```

和 `watch` 命令功能相似的，还有 `rwatch` 和`awatch` 命令。其中：

- `rwatch` 命令：只要程序中出现读取目标变量（表达式）的值的操作，程序就会停止运行；
- `awatch` 命令：只要程序中出现读取目标变量（表达式）的值或者改变值的操作，程序就会停止运行。

### **示例**

```text
$ gdb test -q
Reading symbols from /home/zhudi/project/linux/blog/gdb/test...done.
(gdb) start
Temporary breakpoint 1 at 0x400949: file main.cpp, line 13.
Starting program: /home/zhuyong/project/linux/blog/gdb/test 

Temporary breakpoint 1, main () at main.cpp:13
13     int sum = 0;
(gdb) l
8 void cb_second() {
9     cout << "cb_second" << endl;
10 }
11 
12 int main() {
13     int sum = 0;
14     int n = 1;
15     while (sum < 100) {
16         sum += n;
17         n++;
(gdb) watch sum        <-- 设置观察断点
Hardware watchpoint 2: sum
(gdb) c
Continuing.
Hardware watchpoint 2: sum

Old value = 0
New value = 1
main () at main.cpp:17
17         n++;       <-- sum值发生变化，程序暂停
```

### **查看变量或表达式的值**

对于在调试期间查看某个变量或表达式的值，`GDB` 调试器提供有 2 种方法，即使用 `print` 命令或者 `display`命令。

### **print 命令**

它的功能就是在 `GDB` 调试程序的过程中，输出或者修改指定变量或者表达式的值。

`print` 命令可以缩写为 `p`，最常用的语法格式如下所示：

```text
(gdb) print num
(gdb) p num
```

其中，参数 `num` 用来代指要查看或者修改的目标变量或者表达式。

当程序中包含多个作用域不同但名称相同的变量或表达式时，可以借助`::`运算符明确指定要查看的目标变量或表达式。`::`运算符的语法格式如下：

```text
(gdb) print file::variable
(gdb) print function::variable
```

其中 `file`用于指定具体的文件名，`funciton` 用于指定具体所在函数的函数名，`variable`表示要查看的目标变量或表达式。

另外，`print`也可以打印出类或者结构体变量的值。

\####　display 命令

和 `print` 命令一样，`display` 命令也用于调试阶段查看某个变量或表达式的值，它们的区别是，使用 `display` 命令查看变量或表达式的值，每当程序暂停执行（例如单步执行）时，`GDB` 调试器都会自动帮我们打印出来，而 `print` 命令则不会。

也就是说，使用 1 次 `print` 命令只能查看 1 次某个变量或表达式的值，而同样使用 1 次 `display` 命令，每次程序暂停执行时都会自动打印出目标变量或表达式的值。因此，当我们想频繁查看某个变量或表达式的值从而观察它的变化情况时，使用 `display` 命令可以一劳永逸。

`display` 命令没有缩写形式，常用的语法格式如下 2 种：

```text
(gdb) display expr
(gdb) display/fmt expr
```

> 注意，display 命令和 /fmt 之间不要留有空格。以 /x 为例，应写为 (gdb)display/x expr。

### **GDB单步调试**

根据实际场景的需要，`GDB` 调试器共提供了 3 种可实现单步调试程序的方法，即使用 `next`、`step` 和 `until` 命令。换句话说，这 3 个命令都可以控制 `GDB`调试器每次仅执行 1 行代码，但除此之外，它们各自还有不同的功能。

### **next命令**

`next` 是最常用来进行单步调试的命令，其最大的特点是当遇到包含调用函数的语句时，无论函数内部包含多少行代码，`next` 指令都会一步执行完。也就是说，对于调用的函数来说，`next` 命令只会将其视作一行代码。

`next` 命令可以缩写为`n` 命令，使用方法也很简单，语法格式如下：

```text
(gdb) next count
```

### **step命令**

通常情况下，`step` 命令和`next`命令的功能相同，都是单步执行程序。不同之处在于，当`step` 命令所执行的代码行中包含函数时，会进入该函数内部，并在函数第一行代码处停止执行。

`step` 命令可以缩写为 `s`命令，用法和 `next` 命令相同，语法格式如下：

```text
(gdb) step count
```

### **until命令**

`until` 命令可以简写为 `u` 命令，有 2 种语法格式，如下所示：

```text
1、(gdb) until
2、(gdb) until location
```

其中，参数 `location`为某一行代码的行号。

不带参数的 `until`命令，可以使 `GDB`调试器快速运行完当前的循环体，并运行至循环体外停止。注意，`until` 命令并非任何情况下都会发挥这个作用，只有当执行至循环体尾部（最后一行代码）时，`until`命令才会发生此作用；反之，`until`命令和 `next` 命令的功能一样，只是单步执行程序。

### **return命令**

实际调试时，在某个函数中调试一段时间后，可能不需要再一步步执行到函数返回处，希望直接执行完当前函数，这时可以使用 `finish`命令。与`finish` 命令类似的还有 `return` 命令，它们都可以结束当前执行的函数。

### **finish命令**

`finish` 命令和 `return`命令的区别是，`finish`命令会执行函数到正常退出；而 `return` 命令是立即结束执行当前函数并返回，也就是说，如果当前函数还有剩余的代码未执行完毕，也不会执行了。除此之外，`return`命令还有一个功能，即可以指定该函数的返回值。

### **jump命令**

`jump` 命令的功能是直接跳到指定行继续执行程序，其语法格式为：

```text
(gdb) jump location
```

其中，`location` 通常为某一行代码的行号。

也就是说，`jump` 命令可以略过某些代码，直接跳到 `location`处的代码继续执行程序。这意味着，如果你跳过了某个变量（对象）的初始化代码，直接执行操作该变量（对象）的代码，很可能会导致程序崩溃或出现其它 `Bug`。另外，如果 `jump`跳转到的位置后续没有断点，那么 `GDB`会直接执行自跳转处开始的后续代码。

### **GDB search 命令**

调试文件时，某些时候可能会去找寻找某一行或者是某一部分的代码。可以使用 list 显示全部的源码，然后进行查看。当源文件的代码量较少时，我们可以使用这种方式搜索。如果源文件的代码量很大，使用这种方式寻找效率会很低。所以 `GDB`中提供了相关的源代码搜索的的`search`命令。

`search` 命令的语法格式为：

```text
search <regexp>
reverse-search <regexp>
```

第一项命令格式表示从当前行的开始向前搜索，后一项表示从当前行开始向后搜索。其中`regexp` 就是正则表达式，正则表达式描述了一种字符串匹配的模式，可以用来检查一个串中是否含有某种子串、将匹配的子串替换或者从某个串中取出符合某个条件的子串。很多的编程语言都支持使用正则表达式。

### **查看堆栈信息**

### **backtrace 命令**

`backtrace` 命令用于打印当前调试环境中所有栈帧的信息，常用的语法格式如下：

```text
(gdb) backtrace [-full] [n]
```

其中，用 [ ] 括起来的参数为可选项，它们的含义分别为：

- `n`：一个整数值，当为正整数时，表示打印最里层的 `n` 个栈帧的信息；`n`为负整数时，那么表示打印最外层`n`个栈帧的信息；
- `-full`：打印栈帧信息的同时，打印出局部变量的值。

注意，当调试多线程程序时，该命令仅用于打印当前线程中所有栈帧的信息。如果想要打印所有线程的栈帧信息，应执行`thread apply all backtrace`命令。

### **frame 命令**

`frame`命令的常用形式有 2 个：

1. 根据栈帧编号或者栈帧地址，选定要查看的栈帧，语法格式如下：

```text
(gdb) frame spec
```

该命令可以将 `spec` 参数指定的栈帧选定为当前栈帧。`spec` 参数的值，常用的指定方法有 3 种：

1. 通过栈帧的编号指定。0 为当前被调用函数对应的栈帧号，最大编号的栈帧对应的函数通常就是 main() 主函数；
2. 借助栈帧的地址指定。栈帧地址可以通过 `info frame` 命令（后续会讲）打印出的信息中看到；
3. 通过函数的函数名指定。注意，如果是类似递归函数，其对应多个栈帧的话，通过此方法指定的是编号最小的那个栈帧。

除此之外，对于选定一个栈帧作为当前栈帧，`GDB` 调试器还提供有`up` 和`down`两个命令。其中，`up`命令的语法格式为：

```text
(gdb) up n
```

其中 `n`为整数，默认值为 1。该命令表示在当前栈帧编号（假设为 `m`）的基础上，选定 `m+n`为编号的栈帧作为新的当前栈帧。

相对地，`down` 命令的语法格式为：

```text
(gdb) down n
```

其中`n`为整数，默认值为 1。该命令表示在当前栈帧编号（假设为 `m`）的基础上，选定`m-n` 为编号的栈帧作为新的当前栈帧。

1. 借助如下命令，我们可以查看当前栈帧中存储的信息：

```text
(gdb) info frame
```

该命令会依次打印出当前栈帧的如下信息：

- 当前栈帧的编号，以及栈帧的地址；
- 当前栈帧对应函数的存储地址，以及该函数被调用时的代码存储的地址
- 当前函数的调用者，对应的栈帧的地址；
- 编写此栈帧所用的编程语言；
- 函数参数的存储地址以及值；
- 函数中局部变量的存储地址；
- 栈帧中存储的寄存器变量，例如指令寄存器（64位环境中用 rip 表示，32为环境中用`eip` 表示）、堆栈基指针寄存器（64位环境用 `rbp`表示，32位环境用 `ebp`表示）等。

除此之外，还可以使用`info args`命令查看当前函数各个参数的值；使用`info locals`命令查看当前函数中各局部变量的值。

### **调试正在执行的程序**

如果调试正在执行中的程序，首先需要找到正在运行程序的进程号`PID`，之后可以用下面三个命令进行调试，进入正常的调试流程。

```text
1) gdb attach PID
2) gdb 文件名 PID
3) gdb -p PID
```

### **示例：**

```text
# ps -aux | grep test           <-- 找到正在运行程序的进程号PID
root     17997  0.0  0.0  12540  1064 pts/0    S+   10:19   0:00 ./test
root     18088  0.0  0.0 112812   972 pts/1    S+   10:20   0:00 grep --color=auto test
    
# gdb attach 17997 -q           <-- 用gdb进行调试
attach: No such file or directory.
Attaching to process 17997
Reading symbols from /root/project/blog/gdb/test...done.
Reading symbols from /lib64/libstdc++.so.6...(no debugging symbols found)...done.
Loaded symbols for /lib64/libstdc++.so.6
Reading symbols from /lib64/libm.so.6...(no debugging symbols found)...done.
Loaded symbols for /lib64/libm.so.6
Reading symbols from /lib64/libgcc_s.so.1...(no debugging symbols found)...done.
Loaded symbols for /lib64/libgcc_s.so.1
Reading symbols from /lib64/libc.so.6...(no debugging symbols found)...done.
Loaded symbols for /lib64/libc.so.6
Reading symbols from /lib64/ld-linux-x86-64.so.2...(no debugging symbols found)...done.
Loaded symbols for /lib64/ld-linux-x86-64.so.2
0x00007f61ea02b840 in __nanosleep_nocancel () from /lib64/libc.so.6
```

注意，当 `GDB` 调试器成功连接到指定进程上时，程序执行会暂停。如上所示，程序暂停至第 6 行代码`num++`的位置，此时可以通过断点调试、逐步运行等方式监控程序的执行过程。例如：

```text
(gdb) l                        
warning: Source file is more recent than executable.
1 #include <iostream>
2 #include <unistd.h>
3 using namespace std;
4 
5 int main() {
6     int sum = 0;
7     int n = 1;
8     while (true) {
9         sum += n;
10         n++;
(gdb) 
11         cout << "sum = " << sum << endl;
12         sleep(1);
13     }
14     cout << "sum = " << sum << endl;
15 
16     return 0;
17 }
18
    
    
(gdb) b 10
Breakpoint 1 at 0x400869: file main.cpp, line 10.
(gdb) c
Continuing.

Breakpoint 1, main () at main.cpp:10
10         n++;
(gdb) p sum
$1 = 2145
(gdb) c
Continuing.

Breakpoint 1, main () at main.cpp:10
10         n++;
(gdb) p sum
$2 = 2211
(gdb)
```

注意，当调试完成后，如果想令当前程序进行执行，消除调试操作对它的影响，需手动将 `GDB` 调试器与程序分离，分离过程分为 2 步：

1. 执行 `detach` 指令，使`GDB`调试器和程序分离；
2. 执行 `quit`（或`q`）指令，退出`GDB`调试。

### **调试执行异常崩溃的程序**

在`Linux`操作系统中，当程序执行发生异常崩溃时，系统可以将发生崩溃时的内存数据、调用堆栈情况等信息自动记录下载，并存储到一个文件中，该文件通常称为`core` 文件，`Linux` 系统所具备的这种功能又称为核心转储（`core dump`）。幸运的是，`GDB` 对`core` 文件的分析和调试提供有非常强大的功能支持，当程序发生异常崩溃时，通过`GDB` 调试产生的 `core`文件，往往可以更快速的解决问题。

这里就先不写如何设置`core dump`文件目录了，可以自行了解。

写个程序验证一下：

```text
#include <stdio.h>

int main() {
    char *a = NULL;
    *a = 2;
    
    return 0;
}
```

编译运行

```text
$ g++ -g -o test core.cpp 
$ ./test
Segmentation fault (core dumped)      <-- 发生段错误，并生成了 core 文件
```

可以根据生成时间查找`core dump`文件

```cpp-objdump
ls /home/homework/coresave -hl | grep test
-rw-rw-rw- 1 root      root      400K Mar 13 15:08 core.test.27725.1615619332
-rw-rw-rw- 1 root      root      400K Mar 13 15:26 core.test.7791.1615620408
-rw-rw-rw- 1 root      root      540K Mar 11 10:29 core.test.1868.1615429740
-rw-rw-rw- 1 root      root      400K Mar 13 15:07 core.test.26880.1615619264
-rw-rw-rw- 1 root      root      404K Mar  3 19:42 core.test.28802.1614771771
```

用`gdb`进行调试

```text
$ gdb test /home/homework/coresave/core.test1.7791.1615620408 -q
Reading symbols from /home/zhudi/project/linux/blog/gdb/test...done.

warning: core file may not match specified executable file.
[New LWP 7791]
Core was generated by `./test'.
Program terminated with signal 11, Segmentation fault.
#0  0x00000000004005bd in main () at core.cpp:5
5     *a = 2;
```

由此可见，程序崩溃了在第五行，定位到了出现问题的代码位置。

本文参考