# 操作系统运行机制

## 处理器状态
- CPU 由运算器，控制器，和一系列的寄存器以及高速缓存构成
- 两类寄存器
  - 用户可见：高级语言编译器通过优化算法分配并使用，以减少程序内存访问次数
  - 控制和状态寄存器：用于控制处理器的操作，通常由操作系统控制
- 常见的控制和状态寄存器
  - 程序计数器（PC: Program Counter）记录将要取出的指令地址
  - 指令寄存器（IR: Instruction Register）记录最近取出的指令
  - 程序状态字（PSW: Program Status World）记录处理器的运行状态如：条件码，模式，控制位等信息
- 操作系统的需求 - 保护
  - 操作系统的特征：并发，共享 -> 需要实现保护控制
  - 需要硬件提供基本运行机制：
    - 处理器有特权级别。不同的级别运行不同的指令集合
    - 硬件机制可以将 OS 与用户程序隔离（比如操作系统可以访问用户空间，用户不可用访问操作系统空间）
- 处理器的状态
  - 现代处理器将 CPU 状态设计为：2，3，4 种
  - 在程序状态寄存器 PSW 中专门设置一位，根据程序对资源和指令的使用权限而设置不同的 CPU 状态
- 操作系统的两种状态：
  - 内核态（Kernel Mode）
  - 用户态（User Mode）
  - 特权指令（Privilege）只能由操作系统完成的
  - 非特权指令，用户程序都可以使用
  - 特权指令：启动 I/O，内存清零，修改程序状态字，设置时钟，允许/禁止中断，停机...
    
## 实例 X86
- X86 提供 4 个处理器特权级别：R0, R1, R2, R3
  - 0 - 1 权力从高到低
  - R0 为内核态，R3 用户态
  - 大部分操作系统只选用：R0 和 R3 两个级别

## CPU 状态转换
  - 用户态 -> 内核态，唯一途径是：中断 / 异常 / 陷入机制 (通过陷入指令（访管指令）提供给用户程序的接口，用于调用系统的服务)
    - 例如：int, trap, syscall, sysenter / sysexit
  - 内核态 -> 用户态，设置程序状态字 PSW


# 中断与异常机制 Interrapt Exception
  - 中断 / 异常 对于操作系统就好比：汽车的发动机和飞机的引擎
    - 可以说：操作系统是由中断驱动或者事件驱动的
  - 主要作用：
    - 即使处理设备发来的中断请求
    - 使 OS 捕获用户程序提出的服务请求
    - 防止用户程序执行过程中的破坏性活动
    - ...
  - 概念：
    - CPU 对系统发生的某个事件作出的一种反应
    - CPU 暂停正在执行的程序，保留现场后自动去执行相应的事件，处理完之后回到断点，继续执行之前的程序
    - 事件的发生改变了处理器的控制流
    - 特点：
      - 随机的
      - 自动的
      - 可恢复的（被打断的程序可以之后继续执行）
  - 为何引入中断：
    - 为了支持 CPU 和设备之间的并行操作
    - 比如：CPU 启动 IO 设备后，IO 可以独立工作，CPU 转回到之前的工作，IO 设备完成后，像 CPU 发送中断报告和结果，CPU 决定之后的处理
  - 为何引入异常：
    - CPU 执行指令时本身出现问题：
      算术溢出，除零，StackOverFlow...这时硬件改变 CPU 执行的流程，传到响应的错误处理程序
  - 事件
    - 中断（外中断）：I/O，时钟，硬件故障
    - 异常（内中断）：系统调用，页故障/缺页，保护性异常，断点指令，程序性异常（算术溢出，除零...）
  - 小结
    - 中断（Interrupt）外部，异步，总是回到下一条命令。
    - 异常：都是同步
      - Trap 有意识的安排，返回下一条指令
      - Fault 可恢复的，返回当前指令
      - Abort 不可恢复，不会返回，退出，出错


## 中断 / 异常机制工作原理
- 硬件
  - 捕获中断 / 异常请求，响应并把控制权交给对应的处理
    - 处理器有一个中断寄存器
    - CPU 执行指令，每个指令结束后扫描中断寄存器，查看是否有中断信号，PSW 通过查找中断向量表引出处理程序，执行中断处理或者处理下一条指令
    - 中断向量表
      - 一个内存单元（起始和终止地址）
      - 存放中断处理程序的入口地址和所需要的处理器状态字
  - 软件，处理程序

- 例子
  - 打印机给 CPU 发中断信号
  - CPU 处理之前的指令后，检测到中断，发送确认信号
  - CPU 开始为中断做准备
    - 切换到内核态
    - 保存被中断的程序 context, 主要是程序计数器 PC，程序状态字 PSW
  - CPU 根据中断码查询中断向量表，获得该中断你的处理程序入口，将 PC 设置为该地址，CPU 控制转移到中断处理程序
  - 中断处理程序开始工作
    - 在系统栈中保存现场信息
    - 检查 I/O 设备状态，操作 I/O 设备并和内存间传数据
  - 中断处理结束时，CPU 检测到中断返回指令，恢复之前的程序 context，PSW，和 PC 回到之前的值，开始新的周期


## 系统调用( System calls )
- 用户在编程时调用的操作系统功能
  - 使 CPU 状态从用户态陷入到内核态
  - 系统调用类型，参考：https://www.ibm.com/developerworks/cn/linux/kernel/syscall/part1/appendix.html
    - 进程控制
    - 进程通信
    - 文件使用
    - 目录操作
    - 设备管理
    - 信息维护
    - ...
- 应用程序
  - 直接系统调用
  - 通过 C 库函数 / API 接口调用
- 系统调用机制的设计
  1. 中断 / 异常机制
  2. 陷入指令（访管指令），引发异常，完成用户态到内核态的切换
  3. 获得一个系统调用号，设置参数
  4. 系统调用表
- 参数传递过程
  - 实现用户程序的参数传递给内核
    - 由陷入指令自带参数，长度有限，且还要携带系统功能调用号
    - 通过寄存器传递，但是个数有限（通常用第二种）
    - 在内存中开辟专用的堆栈区来传递


## X86 的 Linux 系统调用
- 陷入指令选择 128 号，int $0x80
- 门描述符
  - 系统初始化时：对 IDT 表中的 128 号门初始化
  - 门描述的 2、3 两个字节：内核代码段选择符
  - 0、1、6、7 四个字节：偏移量（指向 system_call()）
  - 门类型：15，陷阱们
  - DPL: 特权级 3，与用户级别相同，允许用户进程使用该门描述
- 执行 INT $0x80 指令
  - 用户栈切换到内核栈
  - 内核栈
    - 





















