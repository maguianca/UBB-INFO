bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        
extern exit
import exit msvcrt.dll


; 27. Dandu-se un sir de cuvinte, sa se calculeze
; cel mai lung subsir de cuvinte ordonate crescator din acest sir.

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s dw  99h, 88h, 77h, 55h, 11h, 33h, 44h, 66h
    len equ ($-s)/2
    
    lens times len db 0;stocheaza lungimile
    
    poz dd 0
    l_maxim db 0
    subs times len dw 0
    

; our code starts here
segment code use32 class=code
    start:
        ;1.determin nr de elemente ale tuturor subsirurilor posibile
        mov ecx, len-1         
        cmp ecx, 0
        je final
        mov esi, 0              
        mov ebx, 0
    repeta1:
        mov ax, [s+esi];citirea primului elem al subsirului
        
        mov dl, 1     ;numar elemente subsirului in dl
        mov edi, esi
        add edi, 2
        sus:
            cmp ax, [s+edi]     ;comparam s[esi]cu s[edi]
            jae mai_mic
            
            inc dl
            mov ax, [s+edi]
            
        mai_mic:
            add edi, 2
            cmp edi, 2*len
            jb sus
            
        mov [lens+ebx], dl      ; stochez lungimea subsirului/nr de elemente
        
        inc ebx
        add esi, 2
        loop repeta1
        
        ; 2. gasesc lungimea maxima a sirului
        ; initializez l_maxim cu valoarea primului element al sirului
        mov esi, 0          ; i = 0
        mov al, [lens+esi]
        inc esi
        mov [l_maxim], al   ; max = s[0]
        
        ; caut elementul care are valoarea maxima
        mov ecx, len-1      
        cmp ecx, 0
        je final
    repeta2:
        mov al, [lens+esi]
        cmp al, [l_maxim]
        jbe next
    
        ; s[i] > max
        ; stochez valoarea elementului
        mov [l_maxim], al
        ; stochez pozitia elementului
        lea ebx, [2*esi]
        mov [poz], ebx
        
        ; s[i] <= max, continuam cautarea
    next:
        inc esi             
        loop repeta2
        
        ; 3. Construim cel mai mare subsir de numere
        mov esi, [poz]
        mov edi, 0
        mov ax, [s+esi]
        mov [subs+edi], ax
        add esi, 2
    repeta3:
        mov ax, [s+esi]
        cmp [subs+edi], ax
        jae repetarepeta
        
        add edi, 2
        mov [subs+edi], ax
        
    repetarepeta:
        add esi, 2
        cmp esi, 2*len
        jb repeta3
        
    
    final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
