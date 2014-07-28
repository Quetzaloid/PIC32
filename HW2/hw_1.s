#include <p32xxxx.h>  
#define Array_Size 10 
.global main /*define all global symbols here*/ 
.text  
.ent main /*directive that marks symbol 'main' as function*/ 
   main:  
         addi $t0, $0, 0 
         addi $t1, $0, Array_Size 
         add  $t2, $s1, $0   /*$s1 represents the first address 
*of A*/ 
         add  $t3, $s2, $0   /*$s2 represents the first address 
*of B*/    
   loop: 
         beq  $t0, $t1, exit 
         lw   $t4, 0($t2) 
         sw   $t4, 0($t3) 
         addi $t2, $t2, 4 
         addi $t3, $t3, 4 
         addi $t0, $t0, 1 
         j    loop 
         nop 
    exit:     
         nop 