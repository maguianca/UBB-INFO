bits 32
global start

extern exit
import exit msvcrt.dll


segment data use32 class=data
    ;    0  1  2  3  4  5  6  7
    s db 1, 2, 3, 4, 5, 6, 7, 8
    len equ $-s         ; numarul de elemente ale sirului s
    s1 db 3, 4, 5
    len1 equ $-s1       ; numarul de elemente ale subsirului s1
    d times len db 0    ; noul sir obtinut prin eliminare
    
    pos dd 0
	
; 28. Dandu-se un sir de octeti si un subsir al sau,
; sa se elimine din primul sir toate aparitiile subsirului.
segment code use32 class=code
        ; verifica existenta celorlalte elemente din subsir
    verifica:
        push ecx
        push esi
        
        mov ecx, len1-1
        mov esi, [pos]
        inc esi
        mov edi, 1
        mov ebx, 0          ; EBX = 1, apar toate elementele
    loop_1:
        mov al, [s+esi]
        cmp al, [s1+edi]
        je .next
        
        jmp .out
      
    .next:
        inc esi
        inc edi
        loop loop_1
        
        mov ebx, 1
    
    .out:
        pop esi
        pop ecx
        ret
        
        ; mut elementele ramase din s
    elimina:
        pushad
        
        ; mut elementele
        mov ecx, len
        sub ecx, len1
        mov esi, [pos]      ; 2
        mov edi, [pos]      ; 2 + len1
        add edi, len1
   loop_2:
        mov al, [s+edi]
        mov [s+esi], al
        inc esi
        inc edi
        loop loop_2
        
        ; adaug zerouri
        mov esi, [pos]
        add esi, len1
    loop_3:
        mov byte [s+esi], 0
        inc esi
        cmp esi, len
        jb loop_3
    
        popad
        ret

    ; aici incepe programul
    start:
        mov ecx, len
        mov esi, 0          ; i = 0
    repeta:
        ; citesc s[i]
        mov al, [s+esi]
        
        ; caut s1[0]
        cmp al, [s1+0]      ; verific primul element din subsir
        jne mai_departe
        
        ; stochez pozitia curenta
        mov [pos], esi
        ; verific si celelalte elemente
        call verifica
        cmp ebx, 1
        jne mai_departe
        
        call elimina

     mai_departe:
        inc esi
        loop repeta
    
        push dword 0
        call [exit]
