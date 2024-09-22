bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fclose,fopen,printf,fscanf,fread
import exit msvcrt.dll    
import fclose msvcrt.dll    
import fopen msvcrt.dll    
import printf msvcrt.dll    
import fscanf msvcrt.dll  
import fread msvcrt.dll  
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fisier db "numere.txt",0
    mod_acces db "r",0
    descriptor_fisier dd -1
    format_citire db "%d",0
    format_pare db "Pare (P):%s",13,10,0
    format_impare db"Inpare (N):%s",13,10,0
    pare times 100 db 0
    lp dd 0
    impare times 100 db 0
    li dd 0
    dimensiune dd 1
    count dd 100
    sir times 100 db 0
    zece dd 10
    numar dd 0
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
        
        mov dword[len],eax
        mov ecx,[len]
        jecxz finalizare_scriere
        mov eax,0
        mov ebx,0
        mov esi,sir
        cld
    bucla:
        push eax
        lodsb 
        mov bl,al
        pop eax
        cmp bl,' '
        je numara 
        
        mul dword[zece]
        sub bl,'0'
        add al,bl
        add dword[numar],1
        aici:
        loop bucla
    afisare:
        push dword impare
        push dword format_impare
        call [printf]
        add esp,4*2
        
        push dword pare
        push dword format_pare
        call [printf]
        add esp,4*2
        
        
        
    finalizare_scriere:
        push dword[descriptor_fisier]
        call [fclose]
        add esp,4
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
    numara:
        pushad
        test eax,01h
        jz e_par
        impar:
        cld
        dec esi
        sub esi,dword[numar]
        mov edi,impare
        add edi,dword[li]
        mov al,' '
        repe scasb
        mov ebx,dword[numar]
        add dword[li],ebx
        jmp peste
        
        e_par:
        cld
        dec esi
        sub esi,dword[numar]
        mov edi,pare
        add esi,dword[lp]
        mov al,' '
        repe scasb
        mov ebx,dword[numar]
        add dword[lp],ebx
        peste:
        popad
        mov dword[numar],0
        jmp aici