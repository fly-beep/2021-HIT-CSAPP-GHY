.data # ���ݶ�����  as -o hello.o hello.s
 pInt: .quad 0 #$varx
 varx: .int 124,-2345, 0x34,0x1234
 vary: .int 1,2,3,4
 char: .byte 'a'
 output : .asciz "This is from printf()!\r\n"
 msg : .ascii "Hello World! ---------  AT&T ASM\r\n"
 len = . - msg # �ִ�����
 dividend: .quad 0x80030020
 divisor:  .int 0x100 
.text # ���������
.global _start # ָ����ں���

_start: # ����Ļ����ʾһ���ַ���
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
  
  movl $len, %edx # ���������ַ�������
  movl $msg, %ecx # ��������Ҫ��ʾ���ַ���
  movl $1, %ebx # ����һ���ļ�������(stdout)
  movl $4, %eax # ϵͳ���ú�(sys_write)
  int $0x80 # �����ں˹���

  # �˳�����
  movl $0,%ebx # ����һ���˳�����
  movl $1,%eax # ϵͳ���ú�(sys_exit)
  int $0x80 # �����ں˹���
