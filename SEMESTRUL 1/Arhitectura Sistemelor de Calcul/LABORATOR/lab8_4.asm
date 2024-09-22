;Se dau un nume de fisier si un text (definite in segmentul de date). Textul contine litere mici, litere mari, cifre si caractere speciale. Sa se inlocuiasca toate spatiile din textul dat cu caracterul 'S'. Sa se creeze un fisier cu numele dat si sa se scrie textul obtinut prin inlocuire in fisier.

bits 32

global start

extern exit,fprintf,fopen,fclose
import exit msvcrt.dll
import fprintf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll

segment data use32 class=data
    nume_fisier db "fis.txt",0
    text db "Ana* are 3 mere!",0
    len equ $-text
    mod_acces db "w",0
    descriptor_fisier dd 0
segment code use32 class=code
    start:
    mov ecx, len
    jecxz final
    mov edi, text
    cld
    repeta:
        mov al,' '
        scasb
        jne final_loop
        dec edi
        mov al,'S'
        stosb
        final_loop:
    loop repeta
    final:
    
    push dword mod_acces
    push dword nume_fisier
    call [fopen]
    add esp, 4*2
    cmp eax, 0
    je sfarsit
    mov [descriptor_fisier], eax
    
    push dword text
    push dword [descriptor_fisier]
    call [fprintf]
    add esp, 4*2
    
    push dword [descriptor_fisier]
    call [fclose]
    add esp, 4
    sfarsit:
    push dword 0
    call[exit]