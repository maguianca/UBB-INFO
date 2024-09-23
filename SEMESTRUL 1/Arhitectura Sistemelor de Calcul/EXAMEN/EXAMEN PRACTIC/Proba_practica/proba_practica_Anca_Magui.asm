bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fread,printf,scanf,fclose,fopen,fscanf
import exit msvcrt.dll    
import fopen msvcrt.dll    
import fclose msvcrt.dll    
import printf msvcrt.dll    
import fread msvcrt.dll    
import scanf msvcrt.dll    
import fscanf msvcrt.dll    
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    n dd 0
    char dd 0
    text resb 100
    citire resb 100
    format_nume_fisier db "%s",13,0
    format_citire_numar db "%d",0
    format_citire_caracter db "%c",13,10,0
    format_scriere_buna db "Numarul de aparitii a caracterului %c este: %d",0
    format_scriere_proasta db "Numarul de aparitii a caracterului %c nu este: %d",0
    sir times 100 db 0
    dimensiune dd 1
    count dd 100
    mod_acces db "r",0
    descriptor_fisier dd -1
    len dd 0
    aparitii dd 0

; our code starts here
segment code use32 class=code
    start:
        push dword text
        push dword format_nume_fisier
        call [scanf]
        add esp,4*2
        
        push dword char 
        push dword format_citire_caracter
        call [scanf]
        add esp,4*2
        
        push dword n
        push dword format_citire_numar
        call [scanf]
        add esp,4*2
    
        push dword mod_acces
        push dword text
        call [fopen]
        add esp,4*2
        
        cmp eax,0
        je finalizare_scriere
        mov [descriptor_fisier],eax
        
        push dword [descriptor_fisier]
        push dword [count]
        push dword [dimensiune]
        push dword sir 
        call [fread]
        add esp,4*4
        
        mov dword[len],eax
        mov ecx,dword[len]
        jecxz finalizare_scriere
        mov esi,sir
        cld
        mov eax,0
        mov dword[aparitii],0
    bucla:
        lodsb
        mov bl,byte[char]
        cmp al,bl
        jne peste
        add dword[aparitii],1
    
        peste:
        loop bucla
        cld 
        mov eax,dword[aparitii]
        cmp eax,dword[n]
        jne sari
        push dword[n]
        push dword[char]
        push dword format_scriere_buna
        call [printf]
        add esp,4*3
        jmp aici
   
        sari:
            push dword[n]
            push dword[char]
            push dword format_scriere_proasta
            call [printf]
            add esp,4*3
        aici:
        finalizare_scriere:
        push dword [descriptor_fisier]
        call [fclose]
        add esp,4
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
