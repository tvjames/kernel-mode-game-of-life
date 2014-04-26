;; entry.asm
;; Source: http://arjunsreedharan.org/post/82710718100/kernel-101-lets-write-a-kernel
bits 32
section .text
    ;multiboot spec
    align 4
    dd 0x1BADB002            ;magic
    dd 0x00                  ;flags
    dd - (0x1BADB002 + 0x00) ;checksum. m+f+c should be zero
    
global start
extern kmain

start:
  cli
  call kmain
  hlt
