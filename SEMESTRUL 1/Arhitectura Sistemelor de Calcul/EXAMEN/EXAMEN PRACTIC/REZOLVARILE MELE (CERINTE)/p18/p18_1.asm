bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,printf,fread,fclose,fopen
import exit msvcrt.dll    
import printf msvcrt.dll    
import fread msvcrt.dll    
import fclose msvcrt.dll    
import fopen msvcrt.dll    

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    mod_acces db "r",0
    nume_fisier db "input.txt"
    descriptor_fisier dd 0
    sir resb 100
    len dd 0
    dimensiune dd 1
    count dd 100
    invers times 100 db 0
    
    format db "%s",13,10,0

; our code starts here
segment code use32 class=code
    inversare:
        pushad
        mov ecx,[len]
        mov esi,sir
        mov edi,invers
        add edi,ecx
        dec edi
      repeta:
        cld
        lodsb
        std 
        stosb 
        loop repeta
        popad
        ret
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
        push dword [dimensiune]
        push dword sir
        call [fread]
        add esp,4*4
        
        mov [len],eax
        
        call inversare
        
        push dword invers 
        push dword format 
        call [printf]
        add esp,4*2
        
    
    finalizare_scriere:
        push dword[descriptor_fisier]
        call [fclose]
        add esp,4
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
