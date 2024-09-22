bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fread,fclose,fopen,fwrite
import exit msvcrt.dll    
import fread msvcrt.dll    
import fclose msvcrt.dll    
import fopen msvcrt.dll    
import fwrite msvcrt.dll    
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    mod_acces db "r+",0
    nume_fisier db "ex24.txt",0
    descriptor_fisier dd -1
    count dd 100
    dimensiune dd 1
    sir times 100 db 0
    result times 100 db 0
    len dd 0

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
        
        push dword[descriptor_fisier]
        push dword [count]
        push dword[dimensiune]
        push dword sir
        call [fread]
        add esp,4*4
        
        cmp eax,0
        je finalizare_scriere
        mov dword[len],eax
        mov ecx,dword[len]
        mov esi,sir
        mov edi,result
    bucla:
        lodsb 
        cmp al,'9'
        ja peste
        cmp al,'0'
        jb peste
        mov al,'C'
        peste:
        stosb
        loop bucla
        
        push dword[descriptor_fisier]
        push dword[len]
        push dword 1
        push dword result
        call [fwrite]
        add esp,4*4
    
    finalizare_scriere:
        push dword [descriptor_fisier]
        call [fclose]
        add esp,4
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
