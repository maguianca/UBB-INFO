bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fopen,fprintf,fclose,fread,printf
import exit msvcrt.dll    
import fopen msvcrt.dll    
import fprintf msvcrt.dll    
import fclose msvcrt.dll    
import fread msvcrt.dll    
import printf msvcrt.dll    

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fisier db "r2.txt",0
    mod_acces db "r",0
    descriptor_fisier dd -1
    text times 100 db 0
    format db "%c",0
    afis db "Mesajul original este:",0
    count dd 100
    dimensiune dd 1
    sir resb 100
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
        
        push dword afis
        call [printf]
        add esp,4
        
    citire:
        push dword [descriptor_fisier]
        push dword [count]
        push dword [dimensiune]
        push dword sir
        call [fread]
        add esp, 4*4
        
        mov [len], eax
        
        mov esi, sir

        mov ecx, [len]
        cld
        jecxz finalizare_scriere
        
        mov eax, 0
    bucla:
        push ecx
        mov eax,0
        lodsb
        cmp al,' '
        je jump
        
        cmp al,'a'
        jae aici
        
        cmp al,'C'
        ja peste
        sub al,'A'
        mov dl,'Z'
        sub dl,al
        mov al,dl
        jmp jump
        
      aici:
        cmp al,'c'
        ja peste
        cmp al,'a'
        jb peste
        sub al,'a'
        mov dl,'z'
        sub dl,al
        mov al,dl
        jmp jump
        
        peste:
        sub al,3
        
        jump:
        push eax  ;afisare caracter
        push dword format
        call [printf]
        add esp,4*2
        
        pop ecx
        
        loop bucla
        
   
    
    finalizare_scriere:
        push dword [descriptor_fisier]
        call [fclose]
        add esp,4
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
