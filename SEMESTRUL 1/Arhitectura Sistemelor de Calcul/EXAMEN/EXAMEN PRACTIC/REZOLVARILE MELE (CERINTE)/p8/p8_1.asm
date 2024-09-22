bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fopen,fprintf,fclose,scanf               
import exit msvcrt.dll    
import fopen msvcrt.dll    
import fclose msvcrt.dll    
import fprintf msvcrt.dll    
import scanf msvcrt.dll    

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    mod_acces db "w",0
    nume_fisier db "string.txt"
    descriptor_fisier dd 0
    
    text resb 100
    format db "%c",0
    
    majuscule times 100 db 0
    maj dd 0
    minuscule times 100 db 0
    min dd 0
    
    inv_maj times 100 db 0
    inv_min times 100 db 0
    
    format_afisare db "%s",0
   

; our code starts here
segment code use32 class=code
     inverseaza_majuscule:
        pushad 
        mov ecx,dword[maj]
        mov esi,majuscule
        mov edi,inv_maj
        add edi,dword[maj]
        dec edi
      repeta_1:
        cld
        lodsb 
        std
        stosb
        loop repeta_1
        popad 
        ret
    inverseaza_minuscule:
        pushad 
        mov ecx,dword[min]
        mov esi,minuscule
        mov edi,inv_min
        add edi,dword[min]
        dec edi
      repeta_2:
        cld
        lodsb 
        std
        stosb
        loop repeta_2
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
    citire:
        push dword text
        push dword format
        call [scanf]
        add esp,4*2
        
        mov eax,0
        mov al,byte[text]
        cmp al,'.'
        je afisare
        cmp al,'A'
        jb peste
        cmp al,'Z'
        ja sare
        mov ebx,dword[maj]
        mov [majuscule+ebx],al
        add dword[maj],1
        jmp peste
        sare:
        cmp al,'z'
        ja peste
        cmp al,'a'
        jb peste
        mov ebx,dword[min]
        mov [minuscule+ebx],al
        add dword[min],1
        peste:
        jmp citire
        
        
    afisare:
        call inverseaza_majuscule
        call inverseaza_minuscule
        
        push dword inv_maj  ;majuscule
        push dword format_afisare
        push dword [descriptor_fisier]
        call [fprintf]
        add esp,4*3
        
        push dword inv_min   ;minuscule
        push dword format_afisare
        push dword [descriptor_fisier]
        call [fprintf]
        add esp,4*3
    
    finalizare_scriere:
        push dword [descriptor_fisier]
        call [fclose]
        add esp,4
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
   