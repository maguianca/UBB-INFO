bits 32

global start

extern exit
import exit msvcrt.dll


segment data use32 class=data
	s dw 1432h, 8675h, 0ADBCh, ...
    
    d times 4 db 0      ; 01 04 03 02
    
segment code use32 class=code
    sort:
        
        loop loop_3

        jmp continua

    ; de aici incepe programul
    start:
    loop_1:
        loop_2:
        
            loop loop_2
            
        ; d e complet
        jmp sort
        
    continua:    
        loop loop_1
        
        ; exit(0)
        push dword 0
        call [exit]
