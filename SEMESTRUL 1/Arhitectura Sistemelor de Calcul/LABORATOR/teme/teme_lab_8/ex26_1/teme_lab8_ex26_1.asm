bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        
;EX:26 Se citesc de la tastatura doua numere a si b. Sa se calculeze valoarea expresiei (a-b)*k, k fiind o constanta definita in segmentul ;de date. Afisati valoarea expresiei (in baza 16).
; declare external functions needed by our program

extern exit,printf,scanf             
import exit msvcrt.dll 
import printf msvcrt.dll
import scanf msvcrt.dll  

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    k dd 8
    a dd 0
    b dd 0
    rez dd 0
    format db "%d","%d",0
    mesaj db "%x",0

; our code starts here
segment code use32 class=code
    start:
        ;citire
        push dword b
        push dword a
        push dword format
        call [scanf]
        add esp, 4*3
        
        mov eax,[a]
        sub eax,[b]
        mul dword [k]
        mov [rez],eax
        ;afisare
        push dword[rez]
        push dword mesaj
        call [printf]
        add esp, 4*2
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
