bits 32 
global start        

; declare external functions needed by our program
extern exit, fopen, fread, fclose, printf
import exit msvcrt.dll  
import fopen msvcrt.dll  
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fisier db "input.txt", 0
    mod_acces db "r", 0
    descriptor_fisier dd 0
    
    dimensiune dd 1
    count dd 100

    sir resb 100
    lungime_sir dd 0
    maxim dd 1
    
    format_afisare db "%d   ", 0
    zece dd 10
    suma dd 0
    
; our code starts here
segment code use32 class=code
    start:
        ; FILE * fopen(const char* nume_fisier, const char * mod_acces)
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 4 * 2
        
        cmp EAX, 0
        je iesireBucla
        
        mov [descriptor_fisier], EAX
        
        ; int fread(void * str, int size, int count, FILE * stream)
        push dword [descriptor_fisier]
        push dword [count]
        push dword [dimensiune]
        push dword sir
        call [fread]
        add esp, 4*4
        
        mov [lungime_sir], EAX
        
        mov esi, sir
        mov ecx, [lungime_sir]
        cld
        jecxz iesireBucla
        
        mov eax, 0
        
        bucla:
            push eax
            lodsb ; AL
            mov BL, AL
            pop eax
            
            cmp BL, ' '
            je numar
            
            cmp BL, 0
            je afisareNumar
            
            mul dword [zece]
            sub BL, '0'
            add AL, BL
            
            finalBucla:
            loop bucla
        
        afisareNumar:
            ;mov eax,[maxim]
            
            push dword [suma]
            push dword format_afisare
            call [printf]
            add esp,4*2
      
        iesireBucla:
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 4
        
        push    dword 0      
        call    [exit]       
    numar:
        cmp eax,8
        jb peste
        add dword[suma],eax
        peste:
        mov eax,0
        jmp finalBucla
        
        
        
        
        
        
        
        