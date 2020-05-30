# 实训：科大语音
实现智能家居控制

第一天：安装Ubuntu和QT环境

第二天：语音识别环境的安装与测试

第三天：QT学习一下C++的语法知识并写一个简单的猫和狗故事的代码

第四天：学会写QT界面，并完成一个简单的登录；写一个计算器页面并完成相应功能

第五天：



## 第一天：

### 一. 语音识别环境（客户端）：

1. gec6818目录：实现语音控制的一个目录

   这个程序用到了：viocectl.c  common.c   libxml2.so

   但是我们没有libxml2.so这个库

   在线下载：(下载的文件会放在/usr/lib/x86_64-linux-gnu这个文件夹下)

   ```
   sudo apt-get install libxml2-dev
   ```

   在终端打开code/gec6818这个文件夹

   ![image-20200524105113310](C:\Users\13481\AppData\Roaming\Typora\typora-user-images\image-20200524105113310.png)

   ```
   gcc voicectl.c common.c -o voicectl -I./inc -L /usr/lib/x86_64-linux-gnu -lxml2
   ```

   编译

   ```
   make
   ```

2. 把网络关闭，打开另一个终端，执行下面的asr_record_demo 文件

3. 执行成功之后回到第一个终端界面，执行以下命令：

   ```
   ifconfig
   ```

   找到本机IP地址（inet  xxx.xxx.xxx.xxx）

   ```
   sudo ./voicectl  本机IP地址（其实应该是要连接的服务器的IP，只不过我这里服务器也是自己）
   ```

   出现正在录音这一行字的时候就要说话录音了

   这个程序的功能：

   1. 录音
   2. 发送音频文件到服务器IP
   3. 等待服务器的解析结果（结果是一个id号）
   4. 根据id号的不同，做不同的事情

通过看命令行上面的提示查看是否录音成功，成功即会返回相应id中的信息

### 二. 执行服务端asr_record_demo 文件（服务端）

![image-20200524093424677](C:\Users\13481\AppData\Roaming\Typora\typora-user-images\image-20200524093424677.png)

服务器程序：也是运行在Ubuntu上

在Ubuntu上找到科大语言识别这个文件夹的位置：

![image-20200524100451700](C:\Users\13481\AppData\Roaming\Typora\typora-user-images\image-20200524100451700.png)

问题分析：有这个库才能在64位的系统上执行32位的程序，所以根据你的系统，把这个库安装上即可。所使用的命令是：

```
sudo dpkg --add-architecture i1386
sudo apt install libc6:i386
```

安装好后重新执行

```
sudo ./asr_record_demo 
```

![image-20200524100706846](C:\Users\13481\AppData\Roaming\Typora\typora-user-images\image-20200524100706846.png)

构建语法失败

问题分析：因为该语音识别库只是一个演示版本，只有一个月的适用期（2016-10），所以要将系统时间调至该试用期间（注意：联网状态时间又会回到当前，所以最好是把所有需要联网的步骤都写完之后再关闭网络来做这一步）

修改时间：

```
 sudo date -s 2016-10-1
```

出现以下界面说明成功

![image-20200524105843257](C:\Users\13481\AppData\Roaming\Typora\typora-user-images\image-20200524105843257.png)



## 第二天：

### 语音控制的测试：

#### 一. 第一天客户端、服务端主要流程

1. ##### 语音识别的服务器： 科大讯飞的语音识别的程序。（服务端）

   打开bin目录并启动x86/bin/asr_recode_demo这个程序

   该程序语音识别的文字主要来源于cmd.cnf 脚本，设置了一个语言  

   功能：   等待客户端连接

   连接成功之后会进入下面这个while死循环，不断接收客户端发来的语音文件

    while(1)  {   

   1. 接收客户端发来的语音文件，

   2. 根据cmd.cnf  中定义好的语句，来解析这个语音文件：-----> 生成一个id   

   3. 发送这个 id 号 给 客户端。  

      } 

2. ##### gec6818目录中，录音的程序。（客户端）

   客户端：voicectl.c  common.c ----> voicectl    

   这个程序的功能：连接服务器

   while(1)  {   

   1. 录音 3 秒， 生成一个语音文件。

   2. 发送音频文件到 服务器的IP： 127.0.0.1

   3. 等待服务器解析结果 id

   4. 根据 id 号的不同，做不同的事情

   5. switch(id)     { 

      case 1: 开门 ； break;        

      case 2: 开窗 ;   break; 

       .........

      } 

------------------------------------------------------------------------

####  二. 客户端程序的讲解 

1. ##### voicectl.c文件里：

   ![image-20200524164449767](C:\Users\13481\AppData\Roaming\Typora\typora-user-images\image-20200524164449767.png)

   argc 是运行程序的，参数的个数。 

   argv 是数组，是参数的列表 

   例如： ./voicectl 127.0.0.1 

   在这个例子中：  

   argc = 2 

   char *argv[] = {"./voicectl ", "127.0.0.1"}; 

   argv[0]="./voicectl ",

   argv[1]="127.0.0.1";  

2. ##### mian函数里面的init_sock函数：

   功能：初始化了服务器的网络地址；连接了服务器

   ![image-20200524164336194](C:\Users\13481\AppData\Roaming\Typora\typora-user-images\image-20200524164336194.png)

   

3. ##### // arecord 程序，录音---->生成一个文件  cmd.pcm

   system(REC_CMD);  

   arecord 这个程序怎么来？ （如果自己系统没有安装的话再进行下面的这些步骤，已经安装好则不用）

   alsa-1.0.tar.gz 压缩包中包含了arecord这个程序  

   步骤：

   1. 把 alsa-1.0.tar.gz  复制到 /code目录下，然后解压，不能在共享目录解压  （windows文件系统与linux的文件系统不同，有些连接文件，不可以支持）

      ``` 
      cp  alsa-1.0.tar.gz  ~ 
      tar zxvf alsa-1.0.tar.gz
      cp  ~/Desktop/keda/code/alsa-1.0/bin/arecord /bin
      cp ~/Desktop/keda/code/alsa-1.0/bin/aplay  /bin
      ```

   2. 测试：（在/code/gec6818这个目录下执行）

      ```
       arecord 1.wav (录音)
       aplay 1.wav   (放音)    
      ```

4. ##### 关于播放文件（在/code/gec6818这个目录下执行）

```
madplay mp3/我在.mp3 
```

1. madplay 没有安装怎么办？ 

   ```
   sudo apt-get install madplay  
   ```

2. 我在.mp3 哪里来的？
   https://ai.baidu.com/tech/speech/tts  

   

   任务：把语言识别的系统搭建好。 

   1. arecord 录音程序 
   2. 唤醒功能。
   3. 控制功能。控制他开门，关门，放歌，讲故事.......
   4. .......  

## 第三天：

### QT的使用

1. 新建文件

2. 创建头文件

   一般来说会把类的定义写在头文件中

   成员变量一般使用私有访问权限

   成员函数可以访问私有权限的成员变量



## 第四天：

### 一. 继续QT，复习一下上节课的知识

在dog.h头文件中再创建一个类animal(父类，基类),将dog和cat类中相同的成员变量放进去

```
class animal{
// private：私有权限，子类不可以继承
// protected：保护权限，子类可以继承
     int age;
     char name[20];
     char sex;
}
```

让dog和cat类（派生类，子类）继承animal

：继承（复制）基类/父类的成员

class Cat : public animal{

}

### 二. 使用QT创建图形界面

1. 新建一个QT Widgets Application文件，选择好储存文件的路径

![image-20200529153913322](C:\Users\13481\AppData\Roaming\Typora\typora-user-images\image-20200529153913322.png)

2. 选择自己创建页面所需要的基类（这里我们选择QWidget）：

   基类：

   QMainWindow：带菜单栏的界面

   QWidget：普通界面

   QDialog：对话框界面

   ![image-20200529155054411](C:\Users\13481\AppData\Roaming\Typora\typora-user-images\image-20200529155054411.png)

3. 创建的工程一般包含以下几个文件：

   ```
   pro  工程文件
   widget.h  头文件（自定义了一个类widget：继承了一个QWidget基类）
      声明了一个构造函数
      声明了一个析构函数
   widget.cpp  源文件（上面的头文件的对应源文件）
      实现了.h中声明的那个构造函数
      实现了.h中声明的那个析构函数
   main.cpp  主文件
      创建对象
      对象显示
      等待事件循环
   widget.ui  界面设计文件
      我们可以在上面做界面
   ```

### 三. 使用asistant助手查看类的具体属性

菜单栏->帮助->索引

![image-20200529165159157](C:\Users\13481\AppData\Roaming\Typora\typora-user-images\image-20200529165159157.png)

输入要查看的类名称

![image-20200529165236784](C:\Users\13481\AppData\Roaming\Typora\typora-user-images\image-20200529165236784.png)

qDebug:在控制台打印输出相应消息

### 四. QT信号与槽机制

当有信号发生在对象上面的时候，会进入一个槽函数。

这个槽函数可以是自动才函数。

在.h类中：

```
private slots:
   void on_发生该点击事件的btn/laber...的名字（如：btn_ok）_clicked(); //自动槽函数的声明
       on_对象名_信号名();  //自动槽函数
```

### 五. 问题解决

linux下QT编译出现collect2:ld returned 1 exit status错误

解决方法：

```
终端输入
sudo apt install libgl1-mesa-dev
重启QT
```