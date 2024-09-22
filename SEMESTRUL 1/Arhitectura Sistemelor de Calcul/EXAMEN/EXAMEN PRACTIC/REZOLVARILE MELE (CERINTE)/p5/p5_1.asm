bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,scanf,printf
import exit msvcrt.dll    
import scanf msvcrt.dll    
import printf msvcrt.dll    

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    mari times 100 db 0
    l1 dd 0
    mici times 100 db 0
    l2 dd 0
    speciale db ".,/;'(){}[]!@#$%^&*"
    len_s equ $-speciale
    format db "%c",0
    text resb 100
    format_afisare db "%s ",0

; our code starts here
segment code use32 class=code
    verifica:
        push esi
        mov ecx, len_s
        mov esi, 0
    cauta:
        mov dl, [speciale+esi]
        
        cmp al, dl
        je e_special
        
        inc esi
        loop cauta
        
        mov edx, 0
        jmp nu_e
        
    e_special:
        mov edx, 1
        
    nu_e:
        pop esi
        ret

    start:
        push dword text
        push dword format
        call [scanf]
        add esp,4*2
        
        mov eax,0
        mov al,byte[text]
        mov edx,0
        cmp al,'.'
        je afis
        call verifica
        cmp edx,1
        je sare
        cmp al,'Z'
        jb peste
        mov ebx,[l1]
        mov [mici+ebx],al
        add dword[l1],1
        jmp sare
        peste:
        mov ebx,[l2]
        mov [mari+ebx],al
        add dword[l2],1
        sare:
        jmp start
        
    
    final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
    afis:
        push dword mici
        push dword format_afisare 
        call [printf]
        add esp,4*2
        
        push dword mari
        push dword format_afisare
        call [printf]
        add esp,4*2
        jmp final