bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fopen,fclose,fprintf,scanf,printf
import exit msvcrt.dll    
import fopen msvcrt.dll    
import fclose msvcrt.dll    
import fprintf msvcrt.dll    
import scanf msvcrt.dll    
import printf msvcrt.dll    

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    mod_acces db "a",0
    nume_fisier db "voc.txt"
    mesaj db "n=",0
    n dd 0
    format_n db "%d",0
    descriptor_fisier dd 0
    sir times 100 db 0
    format db "%s",0
    vocale db "aeiouAEIOU"
    len_v db $-vocale
    

; our code starts here
segment code use32 class=code
    reset:
        pushad
        mov ecx, 100
        cld
        mov edi, sir
        mov al, 0
        rep stosb
        
        popad
        ret
    start:
        push dword mod_acces
        push dword nume_fisier 
        call [fopen]
        add esp,4*2
        
        cmp eax,0
        je finalizare_scriere
        mov [descriptor_fisier],0
        
        push dword mesaj
        call [printf]
        add esp,4
        
        push dword n
        push dword format_n
        call [scanf]
        add esp,4*2
     urmator:
        call reset
        
        push dword sir 
        push dword format 
        call [scanf]
        add esp,4*2
        
        call vocale
        
        jmp urmator
    
    
    finalizare_scriere:
        push dword [descriptor_fisier]
        call [fclose]
        add esp,4
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
    
 
    
