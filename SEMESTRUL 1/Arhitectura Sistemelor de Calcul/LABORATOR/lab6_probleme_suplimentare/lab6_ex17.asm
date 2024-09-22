bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
;sir DD 12345678h 1256ABCDh, 12AB4344h
;rezultatul va fi
;1234ABCDh, 12565678h, 12AB4344h.
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    sir DD 12345678h,1256ABCDh,12AB4344h
    len equ ($-sir)/2

; our code starts here
segment code use32 class=code
    start:
        mov ecx,len 
        jecxz final
        dec ecx
        mov esi,0
     loop_1:
        mov ax,[sir+esi]
        mov ebx,esi
        add ebx,4
        loop_2:
            mov dx,[sir+ebx]
            cmp ax,dx
            ja no_swap
            
            mov [sir+ebx],ax
            mov [sir+esi],dx
        no_swap:
            add ebx,2
            cmp ebx,len
            jb loop_2
         
        next:
            add esi,4
            loop loop_1
        
    
    final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
