bits 32
global start

extern exit, printf
import exit msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    s db 4, 2, 7, 1, 9, 8, 3, 5, 6
    len equ $-s     ; numarul de elemente ale sirului s (in octeti)
    max db 0
    pos dd 0
    
    text db "Maxim: %d Pozitia: %d", 13, 10, 0
    
; Se dă un șir de octeți s.
; Să se determine valoarea și poziția elementului din șirul s care are valoarea maximă.
segment code use32 class=code
    start:
        ; initializez max cu valoarea primului element al sirului
        mov esi, 0          ; i = 0
        mov al, [s+esi]     ; AL = s[0]
        inc esi             ; i++
        mov [max], al       ; max = s[0]
        
        ; caut elementul care are valoarea maxima
        mov ecx, len-1      ; iterez de len-1 ori
        jecxz final
    loop_1:
        mov al, [s+esi]     ; AL = s[i]
        inc esi             ; i++
        
        cmp al, [max]
        jbe continua
        
        ; s[i] > max
        ; stochez valoarea elementului
        mov [max], al
        ; calculez pozitia elementului
        mov ebx, len
        sub ebx, ecx
        mov [pos], ebx
        
        ; s[i] <= max, continuam cautarea
    continua:
        loop loop_1
        
        ; afisez maximul si pozitia sa din sir
        ; printf("Maxim: %d Pozitia: %d", max, pos)
        push dword [pos]
        mov al, [max]
        cbw
        cwde
        push eax
        push dword text
        call [printf]
        add esp, 3*4
    
    final:
        push dword 0
        call [exit]
