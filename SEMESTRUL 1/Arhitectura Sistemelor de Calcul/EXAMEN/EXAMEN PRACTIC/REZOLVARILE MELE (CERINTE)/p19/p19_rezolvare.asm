bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fclose,fopen,fprintf,scanf,printf
import exit msvcrt.dll    
import scanf msvcrt.dll    
import fprintf msvcrt.dll    
import fopen msvcrt.dll    
import fclose msvcrt.dll    
import printf msvcrt.dll    
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    n dd 0
    mod_acces db "w",0
    nume_fisier db "output.txt",0
    descriptor_fisier dd 0
    
    cuvant times 100 db 0
    len dd 0
    format_afisare db "%s ",0
    format_citire db "%c",0
    text resb 100
    format db "%d",13,10,0
    mesaj db "n=",0

; our code starts here
segment code use32 class=code
    reset:
        pushad
        mov edi,cuvant
        mov ecx,100
        mov al,0
        rep stosb
        popad 
        ret
    start:
        push mesaj
        call [printf]
        add esp,4
        
        push dword n
        push dword format
        call [scanf]
        add esp,4*2
        
        push dword mod_acces
        push dword nume_fisier 
        call [fopen]
        add esp,4*2
        
        cmp eax,0
        je finalizare_scriere
        mov [descriptor_fisier],eax
        
    urmator:
        call reset
        mov dword[len],0
        mov edi,cuvant
    citire:
        push dword text
        push dword format_citire
        call [scanf]
        add esp,4*2
        
        mov eax,0
        mov al,byte[text]
        cmp al,'#'
        je finalizare_scriere
        cmp al,' '
        je afis
        stosb 
        add dword[len],1
        jmp citire

    finalizare_scriere:
        push dword [descriptor_fisier]
        call [fclose]
        add esp,4
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
    afis:
        pushad
        mov eax,dword[n]
        cmp dword[len],eax
        jb peste
        mov eax,0
        mov ebx,0
        mov esi,cuvant 
        cld
        lodsb;inc automat
        dec esi
        mov bl,al
        add esi,dword[len]
        dec esi
        lodsb 
        cmp al,bl 
        jne peste
        
        cld
        push dword cuvant
        push dword format_afisare
        push dword [descriptor_fisier]
        call [fprintf]
        add esp,4*3
        
        peste:
        popad
        jmp urmator
