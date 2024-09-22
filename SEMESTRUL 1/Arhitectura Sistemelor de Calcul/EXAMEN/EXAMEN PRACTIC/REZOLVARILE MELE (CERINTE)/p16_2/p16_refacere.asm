bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fclose,fopen,fread,printf
import exit msvcrt.dll    
import fclose msvcrt.dll    
import fopen msvcrt.dll    
import fread msvcrt.dll    
import printf msvcrt.dll              

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fisier db "input.txt",0
    mod_acces db "r",0
    descriptor_fisier dd -1
    
    sir times 100 db 0
    dimensiune dd 1
    count dd 100
    nr dd 0
    len dd 0
    zece dd 10
    suma dd 0
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
        
        push dword[descriptor_fisier]
        push dword[count]
        push dword[dimensiune]
        push dword sir 
        call [fread]
        add esp,4*4
        
        mov dword[len],eax
        mov esi,sir
        mov ecx,dword[len]
        jecxz finalizare_scriere
        cld
        mov eax,0
    repeta:
        push eax
        lodsb 
        mov bl,al
        pop eax
        
        cmp bl,' '
        je afis
        cmp bl,0
        je afisare_final
        mul dword[zece]
        sub bl,'0'
        add al,bl
        aici:
    loop repeta
    
    afisare_final:
        push dword[suma]
        push dword format_afisare 
        call [printf]
        add esp,4*2
       
    finalizare_scriere:
        push dword [descriptor_fisier]
        call [fclose]
        add esp,4
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
    
    afis:
        cmp eax,8
        jb peste
        add dword[suma],eax
        peste:
        mov eax,0
        jmp aici