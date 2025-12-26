bits 32 
global start        

extern exit  
extern fopen
extern fprintf
extern fclose
extern scanf
import exit msvcrt.dll   
import fclose msvcrt.dll
import fprintf msvcrt.dll
import fopen msvcrt.dll
import scanf msvcrt.dll 

segment data use32 class=data
    mod_acces db "w", 0
    format db "%s", 0
    nume_fisier db "output.txt", 0
    text resb 100
    descriptor_fisier dd 0
    
segment code use32 class=code
    start:
        ; Deschiderea fisierului
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 4 * 2
        cmp eax, 0
        je final ; eroare la deschiderea fisierului
        mov [descriptor_fisier], eax
        
        ; Bucla de citire si scriere in fisier
    citire_scriere:
        ; Citim un cuvant de la tastatura
        push dword text
        push dword format
        call [scanf]
        add esp, 4 * 2
        
        ; Testam daca cuvantul este diferit de "$"
        mov eax, [text]
        cmp dword [eax], '$'
        je finalizare_bucla ; Daca am intalnit '$', iesim din bucla
        
        ; Scriem cuvantul in fisier
        push dword text
        push dword [descriptor_fisier]
        call [fprintf]
        add esp, 4 * 2
        
        jmp citire_scriere
    
    finalizare_bucla:
        ; Inchidem fisierul
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 4
    
    final:
        push dword 0      
        call [exit]
