bits 32
global start

extern exit, printf
import exit msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
	text db "ana are mere capac un cojoc otto "
    len equ $-text      ; numarul de caractere din text
    
    cuvant times 50 db 0    ; 00 00 00 00 00
    invers times 50 db 0    ; era
    
    format db "Cuvant: %s", 13, 10, 0
    
; 20. Se da un sir de octeti reprezentand un text (succesiune de cuvinte separate de spatii).
; Sa se identifice cuvintele de tip palindrom (ale caror oglindiri sunt similare cu cele de
; plecare): "cojoc", "capac" etc.
segment code use32 class=code
        ; reinitializez sirul cuvant
    reset:
        pushad
        mov ecx, 50
        cld
        mov edi, cuvant
        mov al, 0
        rep stosb
        
        popad
        ret

    ; aici incepe programul
    start:
        mov ecx, len
        cld
        mov esi, text       ; parcurg text
    urmator:
        mov edi, cuvant     ; parcurg cuvant
        mov ebx, 0          ; contor litere din fiecare cuvant
        call reset
    repeta:
        ; citesc caracter
        lodsb
        
        ; verific daca e SPATIU
        cmp al, ' '
        je verifica
        
        ; daca nu e SPATIU il stochez
        stosb
        inc ebx
        loop repeta
    
        push dword 0
        call [exit]
    
    ; inversez cuvantul curent
inverseaza:
    pushad
    mov ecx, ebx
    mov esi, cuvant
    mov edi, invers
    add edi, ebx
    dec edi
.repeta:
    cld
    lodsb
    std
    stosb
    loop .repeta
    
    popad
    ret
    
verifica:
    pushad
    
    ; inversez cuvantul curent
    call inverseaza
    
    ; verific daca e palindrom
    mov ecx, ebx        ; numarul de litere al cuvantului curent
    cld
    mov esi, cuvant
    mov edi, invers
    repe cmpsb
    
    cmp ecx, 0
    jne peste
    
    ; e palindrom
    ; printf(format, cuvant)
    push dword cuvant
    push dword format
    call [printf]
    add esp, 2*4
    
 peste:
    popad
    jmp urmator
