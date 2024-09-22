bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        



extern exit, fopen, fprintf, fclose, scanf,printf
import exit msvcrt.dll  
import fopen msvcrt.dll  
import fprintf msvcrt.dll
import fclose msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    n dd 0
    mesaj db "%d",0
    format_s db "n=",0
    mod_acces db "a",0
    nume_fisier db "input.txt",0
    descriptor_fisier dd -1
    text resb 100
    format db "%c",0
    cuvant times 100 db 0
    vocale db "aeiouAEIOU"
    len_v equ $-vocale
    form db "%c",0
    

; our code starts here
segment code use32 class=code
    reset:
        pushad
        mov ecx, 100
        cld
        mov edi, cuvant
        mov al, 0
        rep stosb
        
        popad
        ret
    start:
    
        push dword format_s 
        call [printf]      
        add esp, 4*1       
        
        push dword n      
        push dword mesaj
        call [scanf]       
        add esp, 4 * 2 
     
        
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 4 * 2
        cmp eax, 0
        je final ; eroare la deschiderea fisierului
        mov [descriptor_fisier], eax
    citire:
        mov ebx,0
    urmator:
        mov edi,cuvant
        mov ebx,0
        call reset
    repeta:
        push dword text
        push dword format
        call [scanf]
        add esp, 4*2
        
        mov eax,0
        mov al,byte[text]
        cmp al,'#'
        je finalizare_scriere
        cmp al,' '
        je numar_vocale
        
        stosb
        inc ebx
        jmp repeta
        
        
        finalizare_scriere:
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 4
        
        final:
        push    dword 0      
        call    [exit]  
    numar_vocale:
        mov edx,0
        mov ecx,ebx
        mov esi,cuvant
    repet_1:
        cld
        lodsb 
        push ecx
        mov ecx,len_v
        mov ebx,0
     repet_2:
        cmp al,[ebx+vocale]
        jne peste
        inc edx
     peste:
        inc ebx
        loop repet_2
        pop ecx
        loop repet_1
          
        
        cmp edx,dword[n]
        jb pest
        afis:
        push dword cuvant
        push dword form
        push dword [descriptor_fisier]
        call  [fprintf]
        add  esp,4*3
        pest:
        popad 
        jmp urmator
        
       
       
