bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fprintf,fopen,fclose
import exit msvcrt.dll   
import fprintf msvcrt.dll   
import fopen msvcrt.dll   
import fclose msvcrt.dll   
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fisier db "output.txt",0
    mod_acces db "w",0
    descriptor_fisier dd -1
    a dd 18567
    sir times 100 db 0
    invers times 100 db 0
    format_afisare db "%c",13,0
    len dd 0
    zece dd 10
    format_sir db "%s",0

; our code starts here
segment code use32 class=code
    inversare:
        pushad
        mov esi,sir
        mov edi,invers
        mov ecx,dword[len]
        add edi,ecx
        dec edi
    bucla:
        cld
        lodsb 
        std 
        stosb
        loop bucla
        popad
        ret
    start:
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp,4*2
        
        cmp eax,0
        je finalizare_scriere
        mov dword[descriptor_fisier],eax
        mov edx,0
        mov eax,dword[a]
        mov esi,0
    repeta:
        div dword[zece]
        mov ebx,edx
        add ebx,'0'
        mov [esi+sir],ebx
        inc esi
        mov edx,0
        add dword[len],1
        cmp eax,0
        jnz repeta
        
        ;call inversare
        ;cld
        ;push dword invers
        ;push dword format_sir
        ;push dword [descriptor_fisier]
        ;call [fprintf]
        ;add esp,4*3
        
        call inversare
        cld
        mov ecx,dword[len]
        mov esi,invers
        mov eax,0
    bucla_2:
        lodsb 
        push ecx
        push dword eax
        push dword format_afisare
        push dword[descriptor_fisier]
        call [fprintf]
        add esp,4*3
        mov eax,0
        pop ecx
        loop bucla_2
        
        finalizare_scriere:
        push dword [descriptor_fisier]
        call [fclose]
        
        add esp,4
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
