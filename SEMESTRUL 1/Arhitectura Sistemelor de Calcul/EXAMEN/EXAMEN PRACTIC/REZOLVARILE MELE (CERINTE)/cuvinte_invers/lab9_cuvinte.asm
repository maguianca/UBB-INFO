bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fclose,printf,fopen
import exit msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    mod_acces db "w",0
    nume_fisier db "in.txt",0
    descriptor_fisier dd -1
    
    nr dd 0
    cuv resb 50
    sir resb 100
    
    count dd 100
    dimensiune dd 1
    
    len dd 0
    len_cuv dd 0
    propozitie times 100 db 0

; our code starts here
segment code use32 class=code
    reset:
        pushad
        mov ecx, 100
        cld
        mov edi, propozitie
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
        mov [descriptor_fisier],eax
        
        push dword[descriptor_fisier]
        push dword[count]
        push dword[dimensiune]
        push dword sir
        
        mov [len],eax
        
        mov ecx,[len]
        jecxz finalizare_scriere
        
        mov esi,sir
   urmator:
        call reset
        mov edi,propozitie
        mov [nr_cuv],0
    repeta:
        lodsb 
        cmp al,' '
        jne peste_1
        inc nr_cuv
    peste_1:
        stosb
        cmp al,'.'
        jne peste_2
        inc nr_cuv
        
    peste_2:
        afis
        
        
        
    
    finalizare_scriere:
        push dword [descriptor_fisier]
        call [fclose]
        add esp,4
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
