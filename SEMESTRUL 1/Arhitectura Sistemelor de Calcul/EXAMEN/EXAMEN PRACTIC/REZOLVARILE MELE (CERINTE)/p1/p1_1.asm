bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fclose,fopen,fread,printf,fscanf
import exit msvcrt.dll
import fclose msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import printf msvcrt.dll
import fscanf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    mod_acces db "r",0
    nume_fisier db "input.txt",0
    sir times 100 db 0
    count dd 100
    dimensiune dd 1
    descriptor_fisier dd 0
    result times 100 db 0
    cifra dd 0
    afisare db "%c ",0
    len dd 0
    format_citire db "%x",0
    n dd 0
    zece dd 9
    format_afisare db "%d ",0

; our code starts here
segment code use32 class=code
    start:
        push dword mod_acces
        push dword nume_fisier 
        call [fopen]
        add esp, 4*2
        
        cmp eax,0
        je finalizare_scriere
        mov [descriptor_fisier],eax
   citire:
        mov dword[cifra],9
        
        push dword n
        push dword format_citire
        push dword [descriptor_fisier]
        call [fscanf]
        add esp,4*3
        
        cmp eax,1
        jne finalizare_scriere
        
        mov eax,dword[n]
        mov edx,0
     repeta:
        div dword[zece]
        cmp edx,dword[cifra]
        ja sare
        mov [cifra],edx
        sare:
        cmp eax,0
        je afis
        mov edx,0
        jmp repeta
        
        
   finalizare_scriere:
        push dword[descriptor_fisier]
        call [fclose]
        add esp,4
        
        push dword 0
        call [exit]
    afis:
        push dword [cifra]
        push dword format_afisare
        call[printf]
        add esp,4*3
        jmp citire