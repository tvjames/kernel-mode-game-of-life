/*
*  link.ld
*  original: http://arjunsreedharan.org/post/82710718100/kernel-101-lets-write-a-kernel
*/
OUTPUT_FORMAT(elf32-i386)
ENTRY(start)
SECTIONS
 {
   . = 0x100000;
   .text : { *(.text) }
   .data : { *(.data) }
   .bss  : { *(.bss)  }
 }