bits 32
global start        

extern exit, printf
import exit msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    s dw 33h, 44h, 22h, 11h, 55h, 66h, 77h, 88h
    ; s dw 11h, 33h, 44h, 22h, 55h, 66h, 77h, 88h
    ; s dw 77h, 55h, 11h, 33h, 44h, 66h
    len equ ($-s)/2
    
    lens times len db 0
    
    pos dd 0
    max_len db 0
    subs times len dw 0
    
    format db "%x ", 0
    format_d db "Length: %d", 13, 10, 0
    text db "Substring: ", 0

; 27. Dandu-se un sir de cuvinte, sa se calculeze
; cel mai lung subsir de cuvinte ordonate crescator din acest sir.
segment code use32 class=code
        ; 1. Compute the length of each possible substring
    start:
        mov ecx, len-1          ; iterez de len-1 ori
        cmp ecx, 0
        je final
        mov esi, 0              
        mov ebx, 0
    loop_1:
        mov ax, [s+esi]
        
        mov dl, 1               ; primul element e cel din AX
        mov edi, esi
        add edi, 2
        parse:
            cmp ax, [s+edi]     ; cmp s[esi], s[edi]
            jae .next
            
            inc dl
            mov ax, [s+edi]
            
        .next:
            add edi, 2
            cmp edi, 2*len
            jb parse
            
        mov [lens+ebx], dl      ; stochez lungimea subsirului
        
        inc ebx
        add esi, 2
        loop loop_1
        
        ; 2. Find the maximum length
        ; initializez max cu valoarea primului element al sirului
        mov esi, 0          ; i = 0
        mov al, [lens+esi]
        inc esi
        mov [max_len], al   ; max = s[0]
        
        ; caut elementul care are valoarea maxima
        mov ecx, len-1      ; iterez de len-1 ori
        cmp ecx, 0
        je final
    loop_2:
        mov al, [lens+esi]
        cmp al, [max_len]
        jbe .next
    
        ; s[i] > max
        ; stochez valoarea elementului
        mov [max_len], al
        ; stochez pozitia elementului
        lea ebx, [2*esi]
        mov [pos], ebx
        
        ; s[i] <= max, continuam cautarea
    .next:
        inc esi             ; i++
        loop loop_2
        
        ; 3. Build the longest substring
        mov esi, [pos]
        mov edi, 0
        mov ax, [s+esi]
        mov [subs+edi], ax
        add esi, 2
    loop_3:
        mov ax, [s+esi]
        cmp [subs+edi], ax
        jae .next
        
        add edi, 2
        mov [subs+edi], ax
        
    .next:
        add esi, 2
        cmp esi, 2*len
        jb loop_3
        
        ; 4. Print the longest substring of ordered words
        xor eax, eax
        mov al, [max_len]
        push eax
        push dword format_d
        call [printf]
        add esp, 2*4
        
        push dword text
        call [printf]
        add esp, 1*4
        
        cld
        mov esi, subs
    loop_4:
        xor eax, eax
        lodsw
        cmp ax, 0
        je final
        
        push eax
        push dword format
        call [printf]
        add esp, 2*4        
        
        jmp loop_4
    
    final:
        push dword 0
        call [exit]
