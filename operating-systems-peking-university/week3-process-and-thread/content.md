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
















