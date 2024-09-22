bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,printf,scanf
import exit msvcrt.dll  
import printf msvcrt.dll  
import scanf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    cuvant times 100 db 0
    invers times 100 db 0
    len dd 0
    text resb 100
    format db "%s",0
    afisare db "%s ",0
    result times 100 db 0
    

; our code starts here
segment code use32 class=code
    reset:
          pushad 
          mov ecx,100
          mov edi, cuvant
          cld
          mov al,0
          rep stosb
          popad 
          ret
    start:
        call reset
        mov edi,cuvant
        mov ebx,0
    citire:
         push dword text
         push dword format 
         call [scanf]
         add esp,4*2
         
         inc ebx
         
         mov al,byte[text]
         cmp al,'.'
         je afis
         
         cmp al,' '
         je inverseaza
         stosb 
         jmp citire
         
    final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]   
    inverseaza:
        pushad 
        mov ecx,ebx
        mov esi,cuvant
        mov edi,invers
        add edi,ebx
        dec ebx
    repeta:
        cld 
        lodsb 
        std
        stosb
        loop repeta
        mov ecx,ebx
        mov esi,invers
        mov edi,result
    repeta_2:
        movsb
        loop repeta_2
        add dword[len],ebx
        mov ebx,[len]
        mov byte[result+ebx],' '
        jmp start
    afis:
        push dword result
        push dword format 
        call [printf]
        add esp,4*2
        jmp final