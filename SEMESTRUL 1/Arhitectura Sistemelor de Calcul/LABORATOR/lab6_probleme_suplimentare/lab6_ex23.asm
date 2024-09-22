bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    sir db 2, 4, 2, 5, 2, 2, 4, 4 
    len equ $-sir
    rez times len+1 dw 0
    nr db 0

; our code starts here
segment code use32 class=code
    start:
        ;1.sortam sirul strict crescator
        mov ecx,len
        mov esi,0
        dec ecx
    loop_1:
        mov al,[sir+esi]
        mov ebx,esi
        inc ebx
    loop_2:
        mov dl,[sir+ebx]
        cmp al,dl
        jb no_swap
        
        mov [sir+ebx],al
        mov [sir+esi],dl
        mov al,dl
    no_swap:
        inc ebx
        cmp ebx,len
        jb loop_2
    next:
        inc esi
        loop loop_1
    ;2.parcurgem sirul si introducem in sirul rez
        ;mov esi,0
        ;mov bl,[sir+esi]
        ;inc esi
        ;mov edi,0
        ;mov ecx,len
        ;dec ecx
        ;mov byte[nr],1
    ;repeta:
        ;mov al,[esi+sir]
        ;cmp bl,al
        ;jne peste
        ;jmp aici
        ;peste:
        ;mov dl,byte[nr]
        ;mov [edi+rez],bl
        ;mov [edi+1+rez],dl
        ;add edi,2
        ;mov byte[nr],1
        ;jmp aici_2
        ;aici:
        ;add byte[nr],1
        ;aici_2:
        ;inc esi
        ;mov bl,al
        ;loop repeta
        mov esi,sir
        mov edi,rez
        lodsb
        mov bl,al
        mov ecx,len
        dec ecx
        mov byte[nr],1
    repeta:
        lodsb
        cmp al,bl
        je sari
        stosb
        mov al,byte[nr]
        stosb
        mov byte[nr],1
    sari:
        add byte[nr],1
        loop repeta
        mov al,bl
        stosb
        mov al,byte[nr]
        stosb
        ;mov dl,byte[nr]
        ;mov [edi+rez],bl
        ;mov [edi+1+rez],dl
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
