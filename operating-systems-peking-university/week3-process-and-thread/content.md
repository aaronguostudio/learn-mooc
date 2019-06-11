# 进程/线程模型

## 进程

- 多道程序设计 Multiprogramming
  - 允许多个程序同时进入内存运行
  - 轮流执行，宏观上看是并发执行

- Process
  - 进程是具有独立功能的程序关于某个数据集上的一次运行活动，是系统进行资源分配和调度的独立单位，又称：Task or Job
  - 是正在运行程序的抽象
  - 将一个 CPU 变为多个虚拟的 CPU
  - 每个进程有一个独立的地址空间
  - 操作系统将 CPU 调度给需要的进程

- 进程控制块 PCB
  - PCB - Process Control Block
    - 又称：进程描述符，进程属性
    - 操作系统用于管理进程的一个专门的数据结构
    - 记录进程的各种属性，描述进程的动态变化过程
  - PCB 是系统感知进程存在的唯一标志
  - 进程表，PCB 的一个集合

- 进程需要记录什么
  - 进程描述信息
    - PID
    - name
    - UID
    - 进程组关系
  - 控制信息
    - 当前状态
    - 优先级
    - 代码执行入口地址
    - 程序的磁盘地址
    - 运行统计信息（执行时间，页面调度）
    - 进程间同步和通信
    - 进程的队列指针
    - 进程的消息队列指针
  - 资源和使用
  - CPU 的现场信息
    - 通用寄存器
    - 程序计数器 PC
    - 程序状态字 PSW
    - 栈指针
    - 指向该进程页表的指针
  - Linux 中 PCB 叫 task_struct
  - Windows 中 PCB 叫 EPROCESS, KPROCESS, PEB

## 进程的状态
- 运行态 Running
  - 占有 CPU，并在 CPU 上运行
- 就绪态 Ready
  - 已经具备运行条件，但是由于没有空闲 CPU 暂时不能运行
- 等待态 Waiting / Blocked
  - 比如正在读盘
- 创建 New
- 终止 Terminated
- 挂起 Suspend
- 阻塞挂起 Blocked


## Linux 状态示意图
- fork() -> TASK_RUNNING
- schedule() -> 占有 CPU
- sheep_on() / shedule() -> TASK_UNINTERRUPTABLE              -> wake_up() -> TASK_RUNNING
                         -> TASK_INTERRUPTABLE 前度睡眠        ->
- do_exit() -> TASK_ZOMBIE
- ptrace() -> TASK_STOPPED

## 进程队列
- 操作系统为每一类进程建立一个或多个队列
- 队列元素为 PCB
- 状态的改变就是 PCB 在队列之间的转换

<!-- will start from here -->
https://www.coursera.org/learn/os-pku/lecture/jJSlc/jin-cheng-kong-zhi

## 进程控制
- 原语（ primitive or atomic action ）
  - 完成某种特定功能的一段程序，具有原子性，联系，不可中断
- 进程创建
  - id, PCB
  - 分配内存地址
  - 初始化
  - 设置相应的队列
    - Unix: fork/exec
    - Win: CreateProcess
- 结束进程 / 撤销
  - 回收资源
  - 撤销 PCB
    - Unix: exit
    - Win: TerminateProcess
- 进程阻塞
  - Unix: wait
  - Win: WaitForSingleObject
- 唤醒
- Unix 的 fork() 实现
  - 为子进程分配一个空闲的进程描述符 PCB（数据结构为 proc 结构）
  - 分配 pid 给子进程
  - 以一次一页的方式复制父进程地址空间
    - 这样做是有弊端的，因为子进程很可能不需要父进程的资源，所以 Unix 的 Fork 会花费比较多的时间
    - Linux 采用写时肤质技术 COW（ Copy-On-Write ）加快创建进程，只是传递指针，并且是只读
      - 只有写的时候才把父进程的数据复制到子进程
  - 从父进程继承共享资源，比如打开文件，和当前的工作目录
  - 将子进程状态设置为就绪，插入到队列
  - 对子进程返回标识符 0
  - 向父进程返回子进程的 pid

```c
// fork() 实例
#include <sys/types.h>
#include <studio.h>
#include <unistd.h>

void main(int argc, char *argv[])
{
  pid_t pid;

  pid = fork();
  if (pid < 0) {
    fprintf(stderr, "fork failed");
    exit(-1);
  }
  else if (pid == 0) {  // 子进程
    execlp(...)
  }
  else {  // 父进程
    wait(NULL);  // 等待子进程结束
    printf("child complete);
    exit(0);
  }
}
```

## 关于进程的讨论
- 进程的分类
  - 系统进程，优先级比较高
  - 用户进程
  - 前台进程
  - 后台进程
  - CPU 密集型进程
  - I/O 密集型进程
- 进程层次结构
  - UNIX 进程家族树：init 为根
  - Windows 进程比较平等


## 线程

- 为何需要线程
  - 应用的需要
    - 比如文字排版，存储，编辑，比如 Android 的网络请求
    - Web 服务器，
  - 开销的考虑
    - 快
    - 少
    - 无需动用内核
    - 共享同一个进程的内存空间

- 进程
  - 资源的拥有者
  - CPU 调度单位
    - 线程继承了 CPU 的调度

## 线程的实现
- 用户级线程
  - POSIX 线程库 - PTHREAD
    - POSIX( Portable Operating System Interface )
    - 多线程编程接口，以线程库的方式提供给用户
      - Pthread_create
      - Pthread_exit
      - Pthread_join
      - pthread_yield
        - 线程资源让出 CPU
      - pthread_attr_init
      - pthread_attr_destroy
- 核心级线程
  - 内核管理所有的线程，并向应用提供 API 接口
  - 内核维护线程和进程
  - 线程切换需要内核支持
  - 以线程为基础进行调度
- 混合
  - 线程的创建在用户空间完成
  - 线程调度等在核心态完成
  - Solaris 系统采用这个方式


