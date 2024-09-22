bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,scanf,printf,fopen,fclose,fprintf
import exit msvcrt.dll    
import printf msvcrt.dll    
import scanf msvcrt.dll    
import fclose msvcrt.dll    
import fopen msvcrt.dll    
import fprintf msvcrt.dll    

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    text resb 100
    nr dd 0
    format db "%c",0
    format_afisare db "%d ",0
    mesaj db "Dati o propozitie:",0
    len dd 0
    result times 100 db 0
    mod_acces db "w",0
    nume_fisier db "output.txt",0
    descriptor_fisier dd -1
    

; our code starts here
segment code use32 class=code
    start:
        push dword mesaj
        call [printf]
        add esp,4
        
        mov ecx,0
        
        push dword mod_acces
        push dword nume_fisier 
        call [fopen]
        
        cmp eax, 0
        je finalizare_scriere
        mov [descriptor_fisier],eax
        mov dword[nr],0
    citire:
        push dword text
        push dword format
        call [scanf]
        add esp,4*2
        
        mov eax,0
        mov al,byte[text]
        cmp al,'.'
        je numara_2
        cmp al,' '
        je numara
        call litere
        
        aici:
        jmp citire
        
        
    
     finalizare_scriere:
        push dword [descriptor_fisier]
        call [fclose]
        add esp,4
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the progra
     litere:
        pushad 
    lit_mare:
        cmp al,'A'
        jb peste
        cmp al,'Z'
        ja lit_mica
        jmp aduna
    lit_mica:
        cmp al,'a'
        jb peste
        cmp al,'z'
        ja peste 
    aduna:
        add dword[nr],1
        
        peste:
        popad
        ret
     numara:
        pushad
        push dword [nr]
        push dword format_afisare
        push dword [descriptor_fisier]
        call [fprintf]
        add esp,4*3
        popad
        mov dword[nr],0
        jmp aici
     numara_2:
        pushad
        push dword [nr]
        push dword format_afisare
        push dword [descriptor_fisier]
        call [fprintf]
        add esp,4*3
        popad
        mov dword[nr],0
        jmp finalizare_scriere