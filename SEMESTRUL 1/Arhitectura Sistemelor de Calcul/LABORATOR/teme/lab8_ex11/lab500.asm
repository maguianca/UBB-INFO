bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

extern exit, fopen, fprintf, fclose, scanf
import exit msvcrt.dll  
import fopen msvcrt.dll  
import fprintf msvcrt.dll
import fclose msvcrt.dll
import scanf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fisier db "output000.txt", 0
    mod_acces db "w", 0
    descriptor_fisier dd 0
    text resb 100
    format db "%c", 0

; our code starts here
segment code use32 class=code
    start:
        ; FILE * fopen(const char* nume_fisier, const char * mod_acces)
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 4 * 2
        cmp eax, 0
        je final ; eroare la deschiderea fisierului
        mov [descriptor_fisier], eax
        
    citire_scriere:
        ; Citim un cuvant de la tastatura
        
        push dword format
        lea eax, [text]
        push eax
        call [scanf]
        add esp, 4 * 2
        
        ; Scriem cuvantul in fisier
        push dword text
        push dword [descriptor_fisier]
        call [fprintf]
        add esp, 4 * 2
        
        ; Testam daca cuvantul este diferit de "$"
        mov eax, [text]
        cmp dword [eax], '$'
        jne citire_scriere ; Daca nu am intalnit '$', reluam bucla
        
        ; Inchidem fisierul
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 4
    
    final:
        push dword 0      
        call [exit]
