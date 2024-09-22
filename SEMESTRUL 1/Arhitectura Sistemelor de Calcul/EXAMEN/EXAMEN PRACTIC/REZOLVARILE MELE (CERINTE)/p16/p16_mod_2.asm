bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fclose,fopen,printf,fscanf
import exit msvcrt.dll  
import fclose msvcrt.dll  
import fopen msvcrt.dll  
import printf msvcrt.dll  
import fscanf msvcrt.dll  

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    mod_acces db "r",0
    nume_fisier db "intrare.txt",0
    descriptor_fisier dd -1
    sir times 100 db 0
    suma dd 0
    x dd 0
    format_citire db "%d",0
    format_afisare db "%d ",0

; our code starts here
segment code use32 class=code
    start:
        push dword mod_acces
        push dword nume_fisier 
        call [fopen]
        add esp,4*2
        
        cmp eax,0
        je finalizare_scriere
        mov [descriptor_fisier],eax
        
    citire:
        push dword x
        push dword format_citire
        push dword[descriptor_fisier]
        call [fscanf]
        add esp,4*3
        
        cmp eax,1
        jne afisare_scriere
        
        cmp dword[x],8
        jb peste
        mov eax,dword[x]
        add dword[suma],eax
        
        peste:
        jmp citire
        
    afisare_scriere:
        push dword [suma]
        push dword format_afisare 
        call [printf]
        add esp,4*2
        
        finalizare_scriere:
        push dword[descriptor_fisier]
        call [fclose]
        add esp,4
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
