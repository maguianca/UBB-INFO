bits 32

; Declare the EntryPoint (a label defining the very first instruction of the program)
global start        

extern exit, fopen, fread, fclose, printf
import exit msvcrt.dll  
import fopen msvcrt.dll  
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll

; Our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; Se da un fisier text. Sa se citeasca continutul fisierului, sa se determine caracterul special (diferit de litera) cu cea mai mare frecventa
    ; si sa se afiseze acel caracter, impreuna cu frecventa acestuia.
    ; Numele fisierului text este definit in segmentul de date.
    nume_fisier db "l8_p9.txt", 0  ; Numele fisierului care va fi creat
    mod_acces db "r", 0          ; Modul de deschidere a fisierului - 
                                 ; r - pentru scriere. Fisierul trebuie sa existe 
    len equ 100                  ; Numarul maxim de elemente citite din fisier.                            
    text times (len+1) db 0      ; Sirul in care se va citi textul din fisier (dimensiune len+1 explicata mai sus)
    descriptor_fis dd -1         ; Variabila in care vom salva descriptorul fisierului - necesar pentru a putea face referire la fisier
    formatc db "Caracterul cu cea mai mare frecventa este %c.", 13, 10, 0
    formatm db "Acesta apare de %d ori.", 13, 10, 0
    nr times 256 db 0            ; Array to store the frequency of each character (assuming ASCII characters)
    max dd 0                     ; Maximum frequency
    poz db 0                     ; Position of the character with maximum frequency

; Our code starts here
segment code use32 class=code
    start:
        ; Apelam fopen pentru a deschide fisierul
        ; Functia va returna in EAX descriptorul fisierului sau 0 in caz de eroare
        ; eax = fopen(nume_fisier, mod_acces)
        push dword mod_acces     
        push dword nume_fisier
        call [fopen]
        add esp, 4*2                ; Eliberam parametrii de pe stiva

        mov [descriptor_fis], eax   ; Salvam valoarea returnata de fopen in variabila descriptor_fis
        
        ; Verificam daca functia fopen a creat cu succes fisierul (daca EAX != 0)
        cmp eax, 0
        je final
        
        ; Citim textul in fisierul deschis folosind functia fread
        ; eax = fread(text, 1, len, descriptor_fis)
        push dword [descriptor_fis]
        push dword len
        push dword 1
        push dword text        
        call [fread]
        add esp, 4*4                 ; Dupa apelul functiei fread EAX contine numarul de caractere citite din fisier
        
        mov ecx, eax
        mov esi, 0
    repeta:
        mov edx, '?'
        cmp [text + esi], edx
        jae peste  ; Use jae instead of ja to also jump if the character is equal to '?'
    
        mov ebx, [text + esi]
        mov edx, '!'
        sub ebx, edx
        inc byte [nr + ebx]
        mov edx, [nr + ebx]
        cmp edx, [max]
        jbe subel
        mov [max], edx
        mov edx, [text + esi]
        mov [poz], dl
    subel:
        inc esi
        loop repeta

peste:
    push dword [poz]
    push dword formatc
    call [printf]
    add esp, 4*2
        
    push dword [max]
    push dword formatm
    call [printf]
    add esp, 4*2
        
final:
    ; Exit(0)
    push    dword 0      ; Push the parameter for exit onto the stack
    call    [exit]       ; Call exit to terminate the program
