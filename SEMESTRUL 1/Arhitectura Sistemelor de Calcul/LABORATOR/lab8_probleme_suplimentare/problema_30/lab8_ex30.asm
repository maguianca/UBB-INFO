bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,printf,fprintf,fopen,fclose,scanf
import exit msvcrt.dll    
import printf msvcrt.dll    
import fprintf msvcrt.dll    
import fopen msvcrt.dll    
import fclose msvcrt.dll    
import scanf msvcrt.dll    
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fisier db "output.txt",0
    mod_acces db "w",0
    descriptor_fisier dd -1
    format_afisare db "%s ",0
    cuvant times 100 db 0
    nr dd 0
    format_citire db "%c",0
    text resb 100

; our code starts here
segment code use32 class=code
    reset:
        pushad
        mov edi,cuvant
        mov ecx,100
        mov al,0
        cld
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
    urmator:
        call reset
        mov ebx,0
        mov eax,0
        mov dword[nr],0
        mov edi,cuvant
    citire:
        push dword text
        push dword format_citire
        call [scanf]
        add esp,4*2
        
        mov al,byte[text]
        cmp al,'$'
        je final
        cmp al,' '
        je numara 
        cmp al,'9'
        ja peste
        cmp al,'0'
        jb peste
        add dword[nr],1
        peste:
        add ebx,1
        stosb
        jmp citire
        
    finalizare_scriere:
        push dword [descriptor_fisier]
        call [fclose]
        add esp,4
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
    numara:
        cmp dword[nr],0
        je sari
        pushad 
        push dword cuvant
        push dword format_afisare
        push dword [descriptor_fisier]
        call [fprintf]
        add esp,4*3
        popad
        sari:
        jmp urmator
    final:
        cmp dword[nr],0
        je sare
        pushad 
        push dword cuvant
        push dword format_afisare
        push dword[descriptor_fisier]
        call [fprintf]
        add esp,4*3
        popad
        sare:
        jmp finalizare_scriere