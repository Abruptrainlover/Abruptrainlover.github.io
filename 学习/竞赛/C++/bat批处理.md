# bat批处理

摘自知乎”xiezhr“原文链接

[](https://zhuanlan.zhihu.com/p/367490411)

## **批处理常用符号**

### **4.1 @**

> 回显屏蔽

① 语法

```text
@
```

② 举例

```shell
rem 从本行开始关闭回显。一般批处理第一行都是这个
@echo off
```

### **4.2 重定向1 >与>>**

> 输出重定向命令 >清除文件中原有的内容后再写入 >>追加内容到文件末尾，而不会清除原有的内容。
>
> 主要将本来显示在屏幕上的内容输出到指定文件中,指定文件如果不存在，则自动生成该文件

① 语法

```text
[p读取数据的位置] > [写入数据的位置]

[p读取数据的位置] >> [写入数据的位置]
```

② 举例

```shell
rem 将dir输出stdin重定向到文件Dirlist.txt,> 每次文件都会被重新创建,>> 则是文件追加
dir 1 > dirlist.txt
dir > dirlist.txt

dir 1>> dirlist.txt
dir >> dirlist.txt

rem 将打印信息重定向到文件,使用>每次文件会被重新创建,>> 则是文件追加
echo abc>log.txt
echo abc>>log.txt

rem 将所有的IP信息存入文件,使用>每次文件会被重新创建,>> 则是文件追加
ipconfig>log.txt
ipconfig>>log.txt

rem 阻止输出显示,将默认输出位置(句柄)重定向为nul 使用>每次文件会被重新创建,>> 则是文件追加
echo invalie prompt >nul
echo invalie prompt 1>>nul
```

### **4.3 重定向2 <**

> 要从键盘或设备重定向命令输入

① 语法

```text
[相应处理] < [读取数据的位置]
```

② 举例

```shell
rem 重定向输入是来自文件,并将输入的文件内容按首字母排序
sort<xiezhr.txt 

rem 将从stdin输入重定向为从文件输入,只输入文件首行内容,stdin(0)是默认输入,可以省略
set /p var=0<xiezhr.txt
set /p var=<xiezhr.txt
echo %var%
```

### **4.4 管道符号 |**

> 传递作用,将前面一条命令的执行结果传递给后面一条命令继续执行

① 语法

```text
[]|[]
```

② 举例

```shell
rem 将dir的输出作为sort的输入
dir | sort

rem 查找当前目录中包含".txt"的文件名
dir | find ".txt"
```

### **4.5 转义符 ^**

> 用在特殊符号之前,取消特殊字符的作用

① 语法

```text
^ [特殊字符]
```

② 举例

```shell
rem &将作为字符输出
echo 非常^&批处理
```

### **4.6 逻辑命令符 &、&&、||**

> & 无论前面的命令是否成功执行 都执行后面的
> && 当前面的命令成功执行 再执行后面的命令 相当于逻辑与运算 || 当前面的命令没有成功执行 则执行后面的命令 可以作判断选择用 相当于逻辑或运算

① 语法

```text
[命令1]&[命令2]
[命令1]&&[命令2]
[命令1]||[命令2]
```

② 举例

```shell
rem & 
rem 虽然没有成功到“个人博客” 但还是会执行echo 命令,输出“字符中含有xiezhr”
echo xiezhrspace.cn | find "个人博客" & echo 字符中含有xiezhr


rem &&  
rem 没有成功到“个人博客” ,所以echo命令不会成功执行
echo xiezhrspace.cn | find "个人博客" && echo 字符中含有xiezhr

rem || 
rem 在xiezhrspace.cn中查找字符"个人博客",如果没有找到则继续执行后面的命令,即在屏幕中显示"字符中没有xiezhr",如果找到了,也就是如果前面是xiezhrspace.cn的话则停止继续执行||后面的命令,而是在屏幕中直接显示"xiezhrspace.cn".
echo xiezhrspace.cn | find "个人博客" || echo 字符中没有xiezhr
echo xiezhrspace.cn | find "xiezhr" || echo 字符中含有xiezhr
```

## **5 常用批处理**

> **注意：在cmd中输入命令+/?即可查看该命令的帮助信息。如cd /?**

### **5.1 文件夹管理**

### **5.1.1 cd**

> 显示当前目录名或改变当前目录

① 语法

```text
cd   rem 显示当前路径
cd   rem 进入根目录
cd /d d:sdk   rem 变更盘符目录
```

② 举例

```shell
rem 进入根目录
C:\Users\xiezhr>cd
C:\Users\xiezhr

rem 显示当前目录
D:\>cd
D:\

rem 切换到F:\xiezhrspace\hexo-xiezhrblog 目录
C:\Users\ye.ff>cd F:\xiezhrspace\hexo-xiezhrblog
F:\xiezhrspace\hexo-xiezhrblog>
```

### **5.1.3 rd**

> 删除一个目录

①语法

```text
rd [directoryname]

```

② 举例

```shell
rem 删除d盘xiezhr目录
rd d:xiezhr
```

### **5.1.4 dir**

> 显示目录中的文件和子目录列表

① 语法

```text
DIR [drive:][path][filename] 
        指定要列出的驱动器、目录和/或文件。
```

②举例

```shell
dir rem 显示当前目录中的文件和子目录
dir /a  rem 显示当前目录中的文件和子目录，包括隐藏文件和系统文件
dir c: /a:d rem 显示 C 盘当前目录中的目录
dir c: /a:-d rem 显示 C 盘根目录中的文件
dir c: /b/p rem /b只显示文件名，/p分页显示
dir *.exe /s rem 显示当前目录和子目录里所有的.exe文件
```

### **5.1.5 tree**

> 以图形显示驱动器或路径的文件夹结构

① 语法

```text
TREE [drive:][path] [/F] [/A]

   /F   显示每个文件夹中文件的名称。
   /A   使用 ASCII 字符，而不使用扩展字符。
```

② 举例

```shell
rem 显示D盘的文件目录结构
tree d:
```

### **5.1.6 path**

> 为可执行文件显示或设置一个搜索路径

① 语法

```text
PATH [[drive:]path[;...][;%PATH%]
PATH ;

键入 PATH 但不加参数，显示当前路径。
将 %PATH% 包括在新的路径设置中会将旧路径附加到新设置
```

② 举例

```shell
::设置要永久加入到path环境变量中的路径
@echo off
set My_PATH=D:\AppFolder
  
set PATH=%PATH%;%My_PATH%
reg add "HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Environment" /v "Path" /t REG_EXPAND_SZ /d "%PATH%" /f
exit

::设置要临时加入到path环境变量中的路径
@echo off
set My_PATH=D:\AppFolder
set PATH=%PATH%;%My_PATH%
pause
```

### **5.1.7 xcopy**

> 复制文件和目录树

① 语法

```text
XCOPY source [destination][参数]
```

② 举例

```text
rem 复制 d:xiezhr 文件夹、所有子文件夹和文件到 e: ，覆盖已有文件
rem 加 /i 表示如果 e: 没有 xiezhr 文件夹就自动新建一个，否则会有询问
xcopy d:xiezhr e:xiezhr /s/e/i/y
```

### **5.2 文件管理**

### **5.2.1 type**

> 显示文本文件的内容

① 语法

```text
TYPE [drive:][path]filename
```

② 举例

```text
rem 显示指定文件的内容(下面是显示d盘目录下xiezhr.txt文件的内容)
type d:xiezhr.txt

C:\Users\xiezhr>type d:xiezhr.txt
xiezhr的个人公众号：xiezhrspac

rem 显示当前目录里所有.txt文件的内容
type *.txt
```

### **5.2.2 copy**

> 将一份或多份文件复制到另一个位置

① 语法

```text
COPY [source] [destination]
```

② 举例

```text
rem 复制 c:test.txt 文件到 d: ，并重命名为 test.bak
copy c:xiezhr.txt d:xiezhr.bak

rem 从屏幕上等待输入，按 Ctrl+Z 结束输入，输入内容存为test.txt文件
rem con代表屏幕，prn代表打印机，nul代表空设备
copy con xiezhr.txt

rem 合并 1.txt 和 2.txt 的内容，保存为 3.txt 文件 如果不指定 3.txt ，则保存到 1.txt
copy 1.txt + 2.txt 3.txt

rem 复制文件到自己，实际上是修改了文件日期
copy test.txt +
```

### **5.2.3 del**

> 删除一个或数个文件

① 语法

```text
del [filename]
 filename         指定一个或多个文件或者目录列表。
                通配符可用来删除多个文件。
                如果指定了一个目录，该目录中的所
                有文件都会被删除。
```

② 举例

```text
rem 删除指定文件，不能是隐藏、系统、只读文件
del d:xiezhr.txt 

rem 删除 d:xiezhr 文件夹里面的所有文件，包括隐藏、只读、系统文件，不包括子目录
del /q/a/f d:xiezhr*.*

rem 删除 d:xiezhr 及子文件夹里面的所有文件，包括隐藏、只读、系统文件，不包括子目录
del /q/a/f/s d:xiezhr*.*
```

### **5.2.4 move**

> 移动文件并重命名文件和目录

①语法

```text
move [source] [destination]
```

② 举例

```text
rem 将D盘xiezhr.txt 移动到f盘
move xiezhr.txt f:

rem 将xiezhr.txt重命名为xiezhrspace.txt
move xiezhr.txt xiezhrspace.txt
```

### **5.2.5 ren**

> 重命名文件名

①语法

```text
REN [drive:][path]filename1 filename2.
```

②举例

```text
rem 将xiezhr文件夹重命名为xiezhrspace
ren d:xiezhr xiezhrspace
```

### **5.2.6 replace**

> 替换文件

① 语法

```text
REPLACE [drive1:][path1]filename [drive2:][path2] [/A] [/P] [/R] [/W]

 [drive1:][path1]filename 指定源文件。
 [drive2:][path2]         指定要替换文件的目录
```

②举例

```text
rem 添加新文件到目标目录: 将 xiezhr.bat 文件添加到 E 盘目录下
replace /A C:\xiezhr.bat E:\ 

rem 提示替换文件到目标目录: 将 xiezhr.txt 文本文件替换到 temp 目录中去,( temp 目录必须有 xiezhr.txt 文本文件)
replace /P C:\xiezhr.txt E:\temp
```

### **5.2.7 attrib**

> 显示或更改文件属性

① 语法

```text
ATTRIB [+R | -R] [+A | -A ] [+S | -S] [+H | -H] [+I | -I]
       [drive:][path][filename] [/S [/D] [/L]]

  +   设置属性。
  -   清除属性。
  R   只读文件属性。
  A   存档文件属性。
  S   系统文件属性。
  H   隐藏文件属性。
  I   无内容索引文件属性。
  X   无清理文件属性。
  V   完整性属性。
  [drive:][path][filename]
      指定 attrib 要处理的文件。
  /S  处理当前文件夹
      及其所有子文件夹中的匹配文件。
  /D  也处理文件夹。
  /L  处理符号链接和
      符号链接目标的属性
```

② 举例

```text
rem 查看d盘xiezhr目录下各个文件属性
D:\xiezhr>attrib /s
A            D:\xiezhr\logo.png
A            D:\xiezhr\公众号-xiezhrspace.txt

rem 设置logo.png文件的属性为系统实现、隐藏属性、只读属性
D:\xiezhr>attrib +s +h +r logo.png
D:\xiezhr>attrib /s
A  SHR       D:\xiezhr\logo.png
A            D:\xiezhr\公众号-xiezhrspace.txt

rem 设置logo.png 恢复原来属性
D:\xiezhr>attrib -s -h -r logo.png

D:\xiezhr>attrib /s
A            D:\xiezhr\logo.png
A            D:\xiezhr\公众号-xiezhrspace.txt
rem
```

### **5.2.7 find**

① 语法

```text
FIND [/V] [/C] [/N] [/I] [/OFF[LINE]] "string" [[drive:][path]filename[ ...]]

  /V         显示所有未包含指定字符串的行。
  /C         仅显示包含字符串的行数。
  /N         显示行号。
  /I         搜索字符串时忽略大小写。
  /OFF[LINE] 不要跳过具有脱机属性集的文件。
  "string" 指定要搜索的文本字符串。
  [drive:][path]filename
             指定要搜索的文件
```

② 举例

```text
rem 在 d:/xiezhr/xiezhr.txt 文件里查找含 "公众号：xiezhrspace" 字符串的行如果找不到，将设 errorlevel 返回码为1
C:\Users\xiezhr>find "公众号：xiezhrspace" d:/xiezhr/xiezhr.txt

---------- D:/XIEZHR/XIEZHR.TXT
公众号：xiezhrspace

rem 查找含 xiezhrspace 的行，忽略大小写
C:\Users\xiezhr>find /i "xiezhrspace" d:/xiezhr/xiezhr.txt

---------- D:/XIEZHR/XIEZHR.TXT
博客：www.xiezhrspace.cn
公众号：xiezhrspace
更多实用的文章和资源尽在公众号：XiezhrSpace,欢迎订


rem 显示含 xiezhrspace 的行的行数
C:\Users\ye.ff>find /c "xiezhrspace" d:/xiezhr/xiezhr.txt

---------- D:/XIEZHR/XIEZHR.TXT: 2
```

### **5.2.8 fc**

> 比较两个文件或两个文件集并显示它们之间的不同

① 语法

```text
FC /B [drive1:][path1]filename1 [drive2:][path2]filename2
[drive1:][path1]filename1
             指定要比较的第一个文件或第一个文件集。
[drive2:][path2]filename2
             指定要比较的第二个文件或第二个文件集。
```

② 举例

```text
rem 比较d盘xiezhr目录下的“公众号-xiezhrspace.txt” 和“xiezhr.txt”文件 。如下为比较结果
D:\xiezhr>fc xiezhr.txt 公众号-xiezhrspace.txt
正在比较文件 xiezhr.txt 和 公众号-XIEZHRSPACE.TXT
***** xiezhr.txt


微信号：xie_zhr

博客：www.xiezhrspace.cn

公众号：xiezhrspace

***** 公众号-XIEZHRSPACE.TXT
公众号：xiezhrspace
*****
```

### **5.3 网络命令**

### **5.3.1 ping**

> 确定本地主机是否能与另一台主机交换数据报

① 语法

```text
ping+IP地址或主机域名
ping+IP地址或主机域名+命令参数
ping+命令参数+IP地址或主机域名
```

② 举例

```text
rem 本机与192.168.205.9是否连通
ping 192.168.205.9

rem 网络是否畅通
ping www.baidu.com
```

### **5.3.2 ftp**

> 将文件传送到运行 FTP 服务器服务(经常称为后台程序)的计算机以及将文件从该计算机 传出。可以交互使用 Ftp。

① 语法

```text
ftp -v -d -i -n -g [主机名] 
-v 显示远程服务器的所有响应信息；
-n 限制ftp的自动登录，即不使用；.n etrc文件；
-d 使用调试方式；
-g 取消全局文件名
```

② 举例

```text
rem 将D盘xiezhr.txt文件上传到ftp 文件服务器
rem ftp服务器信息：ip:192.168.205.9 账号：xiezhr 密码：pswxiezhr

@Echo Off
Echo  open  192.168.205.9 > ftp .up
Echo xiezhr >> ftp .up
Echo pswxiezhr >> ftp .up
Echo Cd .\User >> ftp .up
Echo binary>> ftp .up
Echo put  "D:xiezhr.txt" >> ftp .up
Echo bye>> ftp .up
FTP -s: ftp .up
del  ftp .up  /q
Pause
```

### **5.3.3 net**

> 网络命令集及用户管理,根据使用的命令提供各种网络服务

① 语法

```text
net [variant]
```

② 举例

```text
rem 查看计算机的当前密码和登录限制。
net accounts

添加或删除附加到Windows域控制器的计算机。
net computer

rem 显示当前的服务器或工作组设置。
net config

rem 该命令可以用于查看特定用户帐户的详细信息。
net user

rem 该命令用于停止和启动特定的服务。
net stop/start

rem 显示工作站或服务器的网络统计信息。
net statistics

rem 连接或断开计算机与共享资源或显示有关连接的信息
net use
```

### **5.3.4 telnet**

> 查看某个端口是否可访问。我们在搞开发的时候，经常要用的端口就是 8080。那么你可以启动服务器，用telnet 去查看这个端口是否可用。

① 语法

```text
telnet IP 端口
telnet 域名 端口
```

② 举例

```text
rem 查看主机192.168.205.9 的8080端口是否可以访问
telnet 192.168.205.9 8080
```

### **5.3.5 ipconfig**

> 显示、修改TCP/IP设置

① 语法

```text
ipconfig
```

② 举例

```text
rem 查看本机IP地址
ipconfig 
无线局域网适配器 WLAN:
连接特定的 DNS 后缀 . . . . . . . :
IPv6 地址 . . . . . . . . . . . . : 2409:8a6c:72:41c0:5424:dc10:aa75:2782
临时 IPv6 地址. . . . . . . . . . : 2409:8a6c:72:41c0:1df7:d511:b10e:72c
本地链接 IPv6 地址. . . . . . . . : fe80::5424:dc10:aa75:2782%11
IPv4 地址 . . . . . . . . . . . . : 192.168.1.80
子网掩码  . . . . . . . . . . . . : 255.255.255.0
默认网关. . . . . . . . . . . . . : fe80::1%11
                                    192.168.1.1
```

### **5.3.5 msg**

> 给用户发送消息

① 语法

```text
MSG {username | sessionname | sessionid | @filename | *}
    [/SERVER:servername] [/TIME:seconds] [/V] [/W] [message]

  username            标识指定的用户名。
  sessionname         会话名。
  sessionid           会话 ID。
  @filename           识别这样一个文件，该文件含有将所发消息发送到的用户
                      名、会话名和会话标识号的列表。
  *                   给指定服务器上的所有会话发送信息。
  /SERVER:servername  要联系的服务器(默认值是当前值)。
  /TIME:seconds       等待接收器确认消息的时间延迟。
  /V                  显示有关执行的操作的信息。
  /W                  等待用户的响应，跟 /V 一起有用。
  message             要发送的消息。如果没有指定，发出提示，或者从 stdin
                      读取。
```

② 举例

```text
MSG /server:192.168.1.200 * "Hello"      ----------------->>>>>    运行成功，弹出消息对话框
```

### **5.4 系统管理**

### **5.4.1 shutdown**

> 关闭计算机，或者注销当前用户

① 语法

```text
Shutdown
```

②举例

```text
rem 如果执行批处理文件的用户具有相关权限，则计算机将被关闭。					
@echo off 
shutdown
```

### **5.4.2 Tasklist**

> 列出任务，包括任务名称和进程ID(PID)

① 语法

```text
Tasklist
```

② 举例

```text
rem 列出当前系统上的所有任务
@echo off 
Tasklist
```

### **5.4.3 Taskkill**

> 于结束一个或多个任务。

① 语法

```text
taskkill /im [taskname]
```

② 举例

```text
rem 将发送一个终止消息到MS Paint的任何打开的程序
@echo off 
Taskkill /im mspaint.exe
```

### **5.4.4 reg**

> 注册表是Windows系统的关键要素之一。 它包含有关操作系统各个方面的大量信息。 几乎所有安装在Windows系统上的应用程序都以某种形式与注册表交互 注册表包含两个基本元素:键和值

① 语法

```text
rem 1 从注册表中检索任何键的值。
REG QUERY [ROOT\]RegKey /v ValueName [/s] 
REG QUERY [ROOT\]RegKey /ve --This returns the (default) value

rem 2 向注册表添加值，需要在系统上拥有足够的权限才能执行此操作
REG ADD [ROOT\]RegKey /v ValueName [/t DataType] [/S Separator] [/d Data] [/f]
REG ADD [ROOT\]RegKey /ve [/d Data] [/f]

rem 3 从注册表中删除值，需要在系统上拥有足够的权限来执行此操作。
REG DELETE [ROOT\]RegKey /v ValueName [/f] 
REG DELETE [ROOT\]RegKey /ve [/f] 
REG DELETE [ROOT\]RegKey /va [/f]

rem 4 从注册表复制值，您需要在系统上拥有足够的权限才能在源位置和目标位置上执行此操作。
REG COPY [\\SourceMachine\][ROOT\]RegKey [\\DestMachine\][ROOT\]RegKey

rem 5 比较注册表项
REG COMPARE [ROOT\]RegKey [ROOT\]RegKey [/v ValueName] [Output] [/s]
REG COMPARE [ROOT\]RegKey [ROOT\]RegKey [/ve] [Output] [/s]
```

② 举例

```text
rem 1 查询注册表项HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Windows\ 下的所有键及其各自的值
@echo off R
EG QUERY HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Windows\

rem 2 在注册表 - HKEY_CURRENT_USER\Console 下添加一个键 键的名字是Test 分配给这个键的值是Test Data，它是默认的字符串类型
@echo off 
REG ADD HKEY_CURRENT_USER\Console /v Xiezhr /d "xiezhr"  

rem 3 删除注册表HKEY_CURRENT_USER\Console下的一个注册表项。 键的名称是Test
@echo off
REG DELETE HKEY_CURRENT_USER\Console /v Xiezhr /f

rem 4  将内容从位置HKEY_CURRENT_USER\Console复制到同一台机器上的HKEY_CURRENT_USER\Console\Xiezhr位置
@echo off 
REG COPY HKEY_CURRENT_USER\Console HKEY_CURRENT_USER\Console\Xiezhr

rem 5 比较注册表项HKEY_CURRENT_USER\Console & HKEY_CURRENT_USER\Console\Xiezhr之间的所有值
@echo off
REG COMPARE HKEY_CURRENT_USER\Console HKEY_CURRENT_USER\Console\Xiezhr
```

## **6 Batch 常用命令**

### **6.1 echo**

> 打开回显或关闭请求回显功能，或显示消息。如果没有任何参数，echo命令将显示当前回显设置。 ① 语法

```text
echo [{on|off}] [message]
```

② 例子

```text
rem 关闭单行回显
@  

rem 从下一行开始关闭回显
echo off  

rem 从本行开始关闭回显。一般批处理第一行都是这个
@echo off  

rem 从下一行开始打开回显
echo on 

rem 显示当前是 echo off 状态还是 echo on 状态
echo 

rem 输出一个”回车换行”，空白行
echo. 

rem 在实际应用中我们会把这条命令和重定向符号（也称为管道符号，一般用> >> ^）结合来实现输入一些命令到特定的文件中 命令会创建一个名为"test"的文本文件，并将"test"输入到文本文件中。
echo test>test.txt
```

### **6.2 rem 和 ::**

> 注释命令，类似于在编程语言中的/*--------*/，它并不会被执行，只是起一个注释的作用，只有在编辑批处理时才会被看到，主要用于方便修改

① 语法

```text
Rem [注释内容]
```

② 例子

```text
Rem 此处是注释内容。
```

### **6.3 pause**

> 暂停命令。运行 Pause 命令时，将显示下面的消息： Press any key to continue. . .（或：请按任意键继续. . .)

① 语法

```text
pause
```

② 例子

```text
C:\Users\xiezhr>pause
请按任意键继续. . .
```

### **6.4 call**

> 从一个批处理程序调用另一个批处理程序，并且不终止父批处理程序。还可以调用指定标号处后面的所有命令

① 语法

```text
call [drive:][path]filename [batch-parameters]

[drive:][path]filename：指定被调用的批处理文件名，当被调用的批处理文件与正在执行的批处理文件处于同一目录下时，可以省调盘符及路径
```

②举例 在D盘先分别建立test.bat 和 called.bat批处理文件 test.bat

```text
@echo off
echo 正在调用called.bat
call called.bat
echo called.bat 调用完毕
```

called.bat

```text
@echo off
@echo 已经进入到called.bat 中。。。
```

test.bat 和called.bat 创建完毕后，执行test.bat，当test.bat执行到call called.bat命令时便转向执行called.bat批处理文件中的内容。called.bat 执行完之后继续执行test.bat call called.bat 命令行后面的内容

### **6.5 start**

> 调用外部程序，所有的DOS命令和命令行程序都可以由start命令来调用

①语法

```text
START “programname”
```

② 举例

```text
rem 修改 DOS 窗口标题
start title "新标题"

rem 打开计算机 E 盘
start E:

rem 最小化打开记事本
start /min notepad.exe

rem 最大化打开计算器
start /max calc

rem 打开任务管理器
start taskmgr

rem 同时打开写字板和计算器 用 & 将两个要开启的程序连起来
start write & calc
```

### **6.6 cls**

> 清屏

① 语法

```text
cls
```

② 举例

```text
@echo off 
dir
cls
```

### **6.7 title**

> 设置控制台窗口中显示的标题。在实际工作中，我们会在一台服务器上启动很多服务，这时我们通过给不同的服务起不同的名字就很容易辨认出不同服务

① 语法

```text
TITLE [Tilename]
其中，tilename是要提供给命令提示符窗口标题的新名称
```

② 举例

```text
rem 将把窗口的标题改为“xiezhr的新窗口“。
@echo off 
Title “xiezhr的新窗口”
```

### **6.8 ver**

> 显示系统版本

① 语法

```text
ver
```

② 举例

```text
rem 下面命令将显示系统版本
@echo off 
ver
```

### **6.9 date**

> 用于获取当前系统时间。

① 语法

```text
date
```

② 举例

```text
rem 显示当前日期
@echo off 
echo %DATE%
```

### **6.10 time**

> 用于设置或显示时间

① 语法

```text
time
```

② 举例

```text
rem 显示系统当前时间
@echo off 
echo %TIME%
```

### **6.11 exit**

> 用于退出DOS控制台

① 语法

```text
exit
```

② 举例

```text
rem 退出doc控制台
exit
```

### **6.12 set**

> 设置变量。引用变量可在变量名前后加 % ，即 %变量名%

① 语法

```text
set
```

② 举例

```text
rem 显示当前系统上的环境变量列表
@echo off 
set

rem 进行四则运算
@echo off
set /a a=1+1,b=2+1,c=3+1
echo %a% %b% %c%
```