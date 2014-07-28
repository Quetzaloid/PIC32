#include<p32xxxx.h>
.global main 
.text
.ent main
   main:
         add  $s0, $0, 19999
         nop
   Loop:
		 beq  $s0, $0, exit
		 addi $s0, $s0, -1
		 j    Loop
   exit:
         jr   $ra
.end main
