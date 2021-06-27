.data # 数据段声明  as -o hello.o hello.s
 pInt: .quad 0 #$varx
 varx: .int 124,-2345, 0x34,0x1234
 vary: .int 1,2,3,4
 char: .byte 'a'
 output : .asciz "This is from printf()!\r\n"
 msg : .ascii "Hello World! ---------  AT&T ASM\r\n"
 len = . - msg # 字串长度
 dividend: .quad 0x80030020
 divisor:  .int 0x100 
.text # 代码段声明
.global _start # 指定入口函数

_start: # 在屏幕上显示一个字符串
  nop
  # mov $0x123,%sil#erro in %sil
  mov dividend+4,%edx
  mov dividend,%eax
  #div %bx
  divl divisor
  pushl $output
  mov $output, %edx
  call printf
  add $4, %esp
  
  movl $len, %edx # 参数三：字符串长度
  movl $msg, %ecx # 参数二：要显示的字符串
  movl $1, %ebx # 参数一：文件描述符(stdout)
  movl $4, %eax # 系统调用号(sys_write)
  int $0x80 # 调用内核功能

  # 退出程序
  movl $0,%ebx # 参数一：退出代码
  movl $1,%eax # 系统调用号(sys_exit)
  int $0x80 # 调用内核功能
