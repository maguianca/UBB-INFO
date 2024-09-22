bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fread,fclose,fopen,printf,fscanf
import exit msvcrt.dll  
import fclose msvcrt.dll  
import fopen msvcrt.dll  
import fread msvcrt.dll  
import printf msvcrt.dll  
import fscanf msvcrt.dll  
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fisier db "input.txt",0
    mod_acces db "r",0
    descriptor_fisier db -1
    count dd 100
    dimensiune dd 1
    sir resb 100
    nr dd 0
    len dd 0
    format_citire db "%x",0
    x dd 0
    format_afisare db "%X-%d",13,10,0

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
        
    repeta:
    
        push dword x
        push dword format_citire
        push dword[descriptor_fisier]
        call [fscanf]
        add esp,4*3
        
        cmp eax,1
        jnz finalizare_scriere
        
        mov eax,0
        mov ebx,0
        mov eax,dword[x]
        mov edx,eax
        mov ecx,32
    numara:
        shl eax,1
        adc ebx,0
    loop numara
        mov dword[nr],ebx
        
        push dword [nr]
        push dword edx
        push dword format_afisare
        call [printf]
        add esp,4*3
        
        jmp repeta
        
    finalizare_scriere:
        push dword [descriptor_fisier]
        call [fclose]
        add esp,4
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
