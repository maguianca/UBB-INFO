bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        
    
extern exit, fopen, fread, fclose, printf
import exit msvcrt.dll  
import fopen msvcrt.dll  
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fisier db "input_ex11.txt", 0
    mod_acces db "r", 0
    descriptor_fisier dd 0
    
    dimensiune dd 1
    count dd 100
    
    sir resb 100
    lungime_sir dd 0
    cifra_min db 10
    
    format_afisare db "%d", 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
