bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        
;Se dau un nume de fisier si un text (definite in segmentul de date). Textul contine litere mici si spatii. Sa se inlocuiasca toate literele de pe pozitii pare cu numarul pozitiei. Sa se creeze un fisier cu numele dat si sa se scrie textul obtinut in fisier.
; declare external functions needed by our program
extern exit,fprintf,fwrite,fclose,fopen      
import exit msvcrt.dll    
import fprintf msvcrt.dll    
import fclose msvcrt.dll    
import fopen msvcrt.dll    
import fwrite msvcrt.dll    
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    text db "ana are  mere";0n2 4r6  m10r12
    len equ $-text
    mod_acces db "w",0
    nume_fisier db "ex20.txt",0
    descriptor_fisier dd 0
    result times 100 db 0
    format_scriere db "%c",0
    format_pozitie db "%d",0

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
        
        mov ecx,len
        mov esi,text
        mov ebx,0
        cld
    bucla:
        lodsb
        cmp al,'z'
        ja peste
        cmp al,'a'
        jb peste
        test bl,01h
        jz e_par
        jmp peste
    e_par:
        jmp printare_par
    peste:
        call printare_impar
    inapoi:
        inc ebx
        mov eax,0
        loop bucla
   
    finalizare_scriere:
        push dword [descriptor_fisier]
        call [fclose]
        add esp,4
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
    printare_par:
        pushad 
        push dword ebx
        push dword format_pozitie
        push dword [descriptor_fisier]
        call [fprintf] 
        add esp,4*3
        popad
        jmp inapoi
    printare_impar:
        pushad 
        push dword eax
        push dword format_scriere
        push dword [descriptor_fisier]
        call [fprintf]
        add esp,4*3
        popad
        ret