
bits 32
global start        
;ex11:Se da un nume de fisier (definit in segmentul de date). Sa se creeze un fisier cu numele dat, apoi sa se citeasca de la tastatura ;cuvinte si sa se scrie in fisier cuvintele citite pana cand se citeste de la tastatura caracterul '$'.


; declararea functiilor externe folosite de program
extern exit, fopen, fprintf, fclose, scanf
import exit msvcrt.dll  
import fopen msvcrt.dll  
import fprintf msvcrt.dll
import fclose msvcrt.dll
import scanf msvcrt.dll
                          
segment  data use32 class=date  
	format  db "%s", 0  
    mod_acces db "w", 0
    nume_fisier db "iesire.txt", 0
    descriptor_fisier dd 0
    text resb 100
    char db "%c",0
    
segment  code use32 class=code
    start:
        ; Deschiderea fisierului
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 4 * 2
        cmp eax, 0
        je final ; eroare la deschiderea fisierului
        mov [descriptor_fisier], eax

     citire:
        ; vom apela scanf(format, n) => se va citi un numar in variabila n
        ; punem parametrii pe stiva de la dreapta la stanga
        push  dword text       ; ! adresa lui n, nu valoarea
        push  dword char
        call  [scanf]       ; apelam functia scanf pentru citire
        add  esp, 4 * 2     ; eliberam parametrii de pe stiva; 4 = dimensiunea unui dword; 2 = nr de parametri
        
        ;convertim n la dword pentru a pune valoarea pe stiva 
        mov  eax,0
        mov  al,byte[text]
        cmp al, '$'
        je finalizare_scriere ; Daca am intalnit '$', iesim din bucla
        cmp al,' '
        je afis
        ;afisam mesajul si valoarea lui n
        push dword text
        push dword [descriptor_fisier]
        call  [fprintf]
        add  esp,4*2
        aici:
        
      loop citire
        
      finalizare_scriere:
        ; Inchidem fisierul
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 4
        ; exit(0)
       final:
        push  dword 0     ; punem pe stiva parametrul pentru exit
        call  [exit]       ; apelam exit pentru a incheia programul
    afis:
        push dword ' '  ; ASCII pentru spațiu
        push dword char
        push dword [descriptor_fisier]
        call [fprintf]
        add esp, 4 * 3
        jmp aici