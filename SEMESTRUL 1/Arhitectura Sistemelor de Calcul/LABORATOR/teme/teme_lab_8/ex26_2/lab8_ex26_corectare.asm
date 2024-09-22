
bits 32
global start        
;ex 26:Se da un nume de fisier (definit in segmentul de date). Sa se creeze un fisier cu numele dat, apoi sa se citeasca de la tastatura ;cuvinte pana cand se citeste de la tastatura caracterul '$'. Sa se scrie in fisier doar cuvintele care contin cel putin o litera mare ;(uppercase).
; declararea functiilor externe folosite de program
extern exit, fopen, fprintf, fclose, scanf
import exit msvcrt.dll  
import fopen msvcrt.dll  
import fprintf msvcrt.dll
import fclose msvcrt.dll
import scanf msvcrt.dll
                          
segment  data use32 class=data
	n db 0       ; in aceasta variabila se va stoca valoarea citita de la tastatura
	format  db "%s", 0  ; %d <=> un numar decimal (baza 10)
    mod_acces db "w", 0
    nume_fisier db "output.txt", 0
    descriptor_fisier dd 0
    text resb 100
    char db "%c",0
    cuvant times 50 db 0
    format_afisare db "%s ",0
    
segment  code use32 class=code
    reset:
        pushad 
        mov ecx,50
        mov edi,cuvant
        mov al,0
        rep stosb
        popad 
        ret
    start:
        ; Deschiderea fisierului
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 4 * 2
        cmp eax, 0
        je final ; eroare la deschiderea fisierului
        mov [descriptor_fisier], eax
    urmator:
        call reset
        mov edi,cuvant
        mov ebx,0
     citire:
        push  dword text       
        push  dword char
        call  [scanf]       
        add  esp, 4 * 2     
        
        mov  eax,0
        mov  al,byte[text]
        cmp al, '$'
        je finalizare_scriere ; Daca am intalnit '$', iesim din bucla
        cmp al,' '
        je numara
        
        stosb 
        inc ebx
        
        
      jmp citire
        
      finalizare_scriere:
        ; Inchidem fisierul
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 4
        ; exit(0)
       final:
        push  dword 0     ; punem pe stiva parametrul pentru exit
        call  [exit]       ; apelam exit pentru a incheia programul
       
    numara:
       pushad
       mov esi,cuvant
       mov ecx,ebx
       mov dl,0
    loop_1:
       lodsb 
       cmp al,'Z'
       ja peste
       cmp al,'A'
       jb peste
       inc dl
       peste:
       loop loop_1
       cmp dl,0
       jz sare
       
        push dword cuvant
        push dword format_afisare
        push dword [descriptor_fisier]
        call  [fprintf]
        add  esp,4*3
        
        sare:
        popad
        jmp urmator