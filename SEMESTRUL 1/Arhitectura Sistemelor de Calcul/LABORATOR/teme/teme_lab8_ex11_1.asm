bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        
;ex:11 Sa se citeasca de la tastatura un numar in baza 16 si sa se afiseze valoarea acelui numar in baza 10.
;Exemplu: Se citeste: 1D; se afiseaza: 29

extern exit,printf,scanf             
import exit msvcrt.dll 
import printf msvcrt.dll
import scanf msvcrt.dll  

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    n dd 0
    format db "%x",0
    mesaj db "Numarul in baza 10 este:%d",0

; our code starts here
segment code use32 class=code
    start:
        ;citire
        push dword n
        push dword format
        call [scanf]
        add esp,4*2
        
        ;afisare
        push dword[n]
        push dword mesaj
        call [printf]
        add esp,4*2
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
