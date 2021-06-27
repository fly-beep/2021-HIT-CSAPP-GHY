#.section .data
.data
 pInt: .quad 0 #$varx
 arrayX: .quad 1,2,3,4,5,6,7,8,9,10
 .equ arraySize,(.-arrayX)/8
 varx: .int 124,-2345, 0x34,0x1234
 vary: .int 1,2,3,4
 varshort: .short 0x1234, 0x2345, 0x3456
 testval:  .byte 0x6a
 saveflags:.byte 0

 Rval: .int 0
 Xval: .int 26
 Yval: .int 30
 Zval: .int 40
msg:
     .ascii "Hello World! ---- X64 AT&T -----from linux-x64 system call\r\n"
msg_end:
msg01:
     .ascii "\n***this is from printf****\n"
     .asciz "*this is the 1th line of asciz*\n"
     .asciz "*this is the 2th line of asciz*\n"
     .equ len, msg_end - msg
     .equ SYS_write, 1
     .equ SYS_exit, 60
     .equ CNT, vary-varx
 dividend: .quad 0x80030020
 divisor:  .int 0x100 
 #.section .bss
 #BSS是英文Block Started by Symbol的简称
 #存放程序中未初始化的全局变量
  .bss
  .lcomm buffer, 1024  #保留1024字节给buffer
  
#.section .text
.text
.global _start
_start:
 mov  $0x12, %al
 mov  $0x12, %bl
 mov  $0x12, %cl
 mov  $0x12, %dl
 mov  $0x12, %el
 mov  $0x12, %sil
 mov  $0x111,%r8b 

 #mov  $0x123,%r8l #error no r8l

 mov  $0x456, %ah
 mov  $0x456, %bh
 mov  $0x456, %ah
 mov  $0x456, %ch
 mov  $0x456, %dh
 #mov  $0x123, %sih #error: no sih
  
 mov  $0x1234, %ax
 mov  $0x1234, %bx
 mov  $0x1234, %cx
 mov  $0x1234, %dx
 mov $0x12345678, %r8w

 movabsq $-1, %rax
 pushq varx
 push %rax
 pop %rsp
 movabsq $-1, %rbx
 mov $0xff, %cl
 movzbl %cl, %eax
 movzbq %cl, %rbx
 mov $0,%rcx
 mov $0,%rbx;
 mov $varx, %rbx
 mov $varx, %rax
 mov $123, %al
 mov $123, %ax
 mov $123, %eax
 mov $123, %rax
 movabsq $0x1020304050607080, %rbx
 #movl 2(%ebx),%eax
 movabsq  $123, %rax
 mov $(123*456+23/5), %ebx

 mov $-1, %rcx
 movq $varx,%rax
 mov varx,%ebx
 mov varx+4,%ecx
 mov (%rax),%edx

 xor %rbx,%rbx
 xor %rcx,%rcx
 xor %rdx,%rdx
 movabs $0x1122334455667788,%rbx # %rbx=?
 mov $0x1122334455667788,%rcx # %rcx=?
 mov $0x1122334455667788,%rdx # %rdx=?
 movq $0xfa4, %rax #%rax=0xfa4
 movzbq %al,%rbx
 movzbl %al,%ecx
 movsbl %al,%edx # %rdx=
 #movzlq %eax,%rdi no instruction movzlq

 movswl %ax,%ecx
 mov $CNT, %rbx
 movq 123,%rax
 mov $'f', %al
 mov dividend+4,%edx

mov dividend,%eax
#div %bx
divl divisor
divq dividend

mov $0x1000, %ax
mov $0x10,%bl
#div %bl #overflow
stc
lahf
clc
mov   %ah, saveflags    
mov   saveflags, %ah
sahf

        mov $3, %ebx
        mov $4, %ecx
        imul %eax,%ebx
        nop
        imul $5,%eax
        nop
        imul $5,%ecx,%eax
       jc L1
       jnc L1
	mov $msg01, %rdi
        xor %rcx,%rcx
        xor %rax,%rax
        xor %rbx,%rbx
        call printf
	mov   Xval ,%eax
	neg    %eax
	mov   Yval, %ebx
	sub    Zval, %ebx
	add   %ebx, %eax
	mov  %eax,Rval
L1:
        stc
        shr %rax
        shl %rax
        sal %rax
        sar %rax
        rol %rax
        ror %rax
        rcl %rax
        rcr %rax
L2:
       mov $msg01, %rax
    incw varx
    decw varx
    incl varx
    decl varx
    inc %eax
    dec %rbx

     MOV $123, %EAX #%eax
     mov  $varx, %rax
     mov varx+4,%eax
     shl $1, %eax
     shrb  $1, testval
     mov $0x12345678, %eax
     mov $0x98765432,%ecx
     #shld %ecx,$4, %eax
     shld $4, %ecx,%eax
     shrd $4,%ecx,%eax
     mov $4,%cl

     movl $0x01234567,varx
     shrd %cl,%eax,varx
     #shrd %cl, varx,%eax
     mov $'a', %al

     movabsq $msg01, %rdi
     call printf
     
     mov $SYS_write, %rax    # system call number
     mov $1, %rdi            # file descriptor (stdout)
     mov $msg, %rsi          # message to write
     mov $len, %rdx          # message length.
     syscall                 # previous 'int $0x80' in i386

     mov $SYS_exit, %rax     # system call number
     mov $0, %rdi            # exit (0)
     syscall                 # previous 'int $0x80' in i386
     
.type arraysum, @function #声明 area为函数
arraysum:                 #函数名字area的定义
   push %rcx         #保存rbx
   push %rdx
   xor %rax, %rax
   xor %rdx, %rdx
   test %rsi, %rsi
   je SumFinish
SumLoop: 
   add (%rdi,%rdx,8), %rax
   inc %rdx
   loop SumLoop
   mov %rsi, %rcx   
   SumFinish:
   ret  
#main difference from IA32 ASM:
#（1）system call  number
#      sys_write: in i368  is 4,  in  x86-64  is 1;
#      sys_exit:  in i386  is1, in x86_64 is 60； 
#（2）registers used to pass parameters
#     i386:ebx/ecx/edx/esi/edi/ebp
#     x86_64:rdi/rsi/rdx/r10/r8/r9, not as sample as just modify "e" to "r" 
#（3）instruction of system call
#    i386  uses "int 80"
#    x86-64 use "syscall"。

#与32位的主要区别：
#（1）系统调用号不同了，比如sys_write在i368中是4，x86-64中是1；sys_exit在i386中是1，而x86_64中是60； 
#（2）系统调用所使用的6个参数寄存器也变了，i386中分别是ebx/ecx/edx/esi/edi/ebp，x86_64中则使用rdi/rsi/rdx/r10/r8/r9，显然不只是“e”改成“r”那么简单； 
#（3）执行系统调用的指令，i386中使用“int 80”，而x86-64中使用“syscall”。
