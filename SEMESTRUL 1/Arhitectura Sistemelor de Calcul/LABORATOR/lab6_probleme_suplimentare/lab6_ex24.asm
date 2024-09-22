bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
;Dandu-se un sir de dublucuvinte, sa se obtina un alt sir de dublucuvinte in care se vor pastra doar dublucuvintele din primul sir care au ;un numar par de biti cu valoare 1.
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s dd 11223344h, 11221111h,12233456h,23232321h
    len equ ($-s)/4
    rez times len dd 0

; our code starts here
segment code use32 class=code
    start:
        mov ecx,len
        jecxz final
        mov esi,s
        mov edi,rez
    repeta:
        push ecx
        lodsd 
        mov ecx,32
        mov bl,0
        mov edx,eax
    numara:
        shl edx,1
        adc bl,0
        loop numara 
        test bl,01h
        jnp nu
        
        stosd
    nu:
        pop ecx 
        loop repeta
        final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
