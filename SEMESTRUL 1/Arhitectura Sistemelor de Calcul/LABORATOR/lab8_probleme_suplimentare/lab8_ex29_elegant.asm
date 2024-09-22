bits 32 

global start        

; declare external functions needed by our program
extern exit, fopen, fread, fclose, fprintf ,fscanf
import exit msvcrt.dll  
import fopen msvcrt.dll  
import fread msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
import fscanf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fisier db "intrare.txt", 0
    mod_acces db "a+", 0
    descriptor_fisier dd 0
    
    dimensiune dd 1
    count dd 100

    sir resb 100
    lungime_sir dd 0
    maxim dd 1
    
    format_afisare db "%d   ", 0
    format_citire db "%d",0
    zece dd 10
    x dd 0
    
; our code starts here
segment code use32 class=code
    start:
        ; FILE * fopen(const char* nume_fisier, const char * mod_acces)
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 4 * 2
        
        cmp eax, 0
        je finalizare_scriere
        
        mov [descriptor_fisier], eax
        
    citire:
        push dword x
        push dword format_citire
        push dword[descriptor_fisier]
        call [fscanf]
        add esp,4*3
        
        cmp eax,1
        jne afisareNumar
        
        mov eax,dword[x]
        cmp dword[maxim],eax
        ja peste
        mov dword[maxim],eax
        
        peste:
        jmp citire
        
        afisareNumar:
            mov eax,[maxim]
            
            push dword eax
            push dword format_afisare
            push dword [descriptor_fisier]
            call [fprintf]
            add esp,4*3
        
        
        finalizare_scriere:
        push dword[descriptor_fisier]
        call [fopen]
        add esp,4
        
        push dword 0
        call [exit]
        
     
        
        
        
        
        
        
        
        