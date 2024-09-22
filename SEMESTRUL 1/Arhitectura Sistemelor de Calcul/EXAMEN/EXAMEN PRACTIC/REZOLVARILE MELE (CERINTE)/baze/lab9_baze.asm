bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fopen,fclose,scanf,fprintf
import exit msvcrt.dll    
import fopen msvcrt.dll    
import fclose msvcrt.dll    
import scanf msvcrt.dll    
import fprintf msvcrt.dll    
                          
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fisier db "input.txt",0
    mod_acces db "w",0
    n dd 0
    format_citire db "%d",0
    format_10 db "%d ",0
    format_16 db "%x ",0
    format_biti db "nr_biti:%d ",0
    descriptor_fisier dd -1
    text resb 100
    

; our code starts here
segment code use32 class=code

    afis:
        pushad
        push dword [n]
        push format_10
        push dword[descriptor_fisier]
        call [fprintf]
        add esp,4*3
        
        push dword [n]
        push format_16
        push dword[descriptor_fisier]
        call [fprintf]
        add esp,4*3
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
        
        mov ecx,100
        
    citeste:
        push ecx
        push dword n
        push format_citire
        call [scanf]
        add esp,4*2
        
        cmp dword [n],0
        je finalizare_scriere
        
        call afis
        
        mov bl,0
        mov ecx,8
        mov eax,[n]
    numara:
        shl al,1
        adc bl,0
        loop numara
        mov eax,0
        movzx eax,bl
        push eax
        push dword format_biti
        push dword [descriptor_fisier]
        call [fprintf]
        add esp,4*3
        pop ecx 
        loop citeste
        
        
        
    
    finalizare_scriere:
        push dword [descriptor_fisier]
        call [fclose]
        add esp,4
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
