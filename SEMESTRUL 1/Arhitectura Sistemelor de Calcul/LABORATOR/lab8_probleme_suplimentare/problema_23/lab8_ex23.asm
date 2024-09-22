bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fopen,fclose,fprintf
import exit msvcrt.dll    
import fopen msvcrt.dll    
import fclose msvcrt.dll    
import fprintf msvcrt.dll    
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fisier db "output.txt",0
    mod_acces db "w",0
    descriptor_fisier dd -1
    a dw 124
    format_cifra db "%c",13,0
    result times 100 db 0
    len dd 0
    hexa db 16

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
        
        mov eax,0
        mov edx,0
        mov ax,word[a]
        mov esi,0
        mov ebx,0
    repeta:
        div byte[hexa]
        mov bl,ah
        cmp bl,9
        ja peste
        add bl,'0'
        jmp aici
        peste:
        sub bl,10 
        add bl,'a'
        aici:
        mov[esi+result],bl
        mov ah,0
        inc esi
        cmp al,0 
        jne repeta
        
        mov dword[len],esi
        mov ecx,dword[len]
        mov esi,result
    bucla:
        push ecx
        mov eax,0
        lodsb 
        push dword eax
        push dword format_cifra
        push dword [descriptor_fisier]
        call [fprintf]
        add esp,4*3
        pop ecx
        loop bucla
    
    finalizare_scriere:
        push dword[descriptor_fisier]
        call [fclose]
        add esp,4
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
