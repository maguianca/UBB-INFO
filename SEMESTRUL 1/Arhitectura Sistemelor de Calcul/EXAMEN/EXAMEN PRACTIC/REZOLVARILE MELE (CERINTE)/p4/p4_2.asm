bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,scanf,printf
import exit msvcrt.dll    
import printf msvcrt.dll    
import scanf msvcrt.dll    

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    text resb 100
    nr db 0
    format db "%c",0
    format_afisare db "%s",0
    mesaj db "Dati o propozitie:",0
    len dd 0
    result times 100 db 0
    

; our code starts here
segment code use32 class=code
    start:
        push dword mesaj
        call [printf]
        add esp,4
        
        mov ecx,0
    citire:
        push dword text
        push dword format
        call [scanf]
        add esp,4*2
        
        mov eax,0
        mov al,byte[text]
        cmp al,'.'
        je afisare
        cmp al,' '
        je numara
        call litere
        
        jmp citire
        
        
    
     final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the progra
     litere:
        pushad 
        cmp al,'a'
        jb peste
        cmp al,'z'
        ja peste
        ;add byte[nr],1
        add ecx,1
        
        peste:
        popad
        ret
     numara:
        pushad
        mov eax,[len]
        add ecx,'0'
        mov[result+eax],ecx
        add dword[len],1
        mov ecx,0
        jmp citire
     afisare:
        push dword result
        push dword format_afisare
        call [printf]
        add esp,4*2
        jmp final