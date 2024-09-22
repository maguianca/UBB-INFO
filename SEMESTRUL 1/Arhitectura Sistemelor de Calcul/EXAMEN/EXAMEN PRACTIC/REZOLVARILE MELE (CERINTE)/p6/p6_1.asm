bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fclose,fopen,printf,fscanf
import exit msvcrt.dll    
import fclose msvcrt.dll    
import fopen msvcrt.dll    
import printf msvcrt.dll    
import fscanf msvcrt.dll    
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fisier db "numere.txt",0
    mod_acces db "r",0
    descriptor_fisier dd -1
    format_citire db "%d",0
    format_pare db "Pare (P):%s",13,10,0
    format_impare db"Inpare (N):%s",13,10,0
    pare times 100 db 0
    lp dd 0
    impare times 100 db 0
    li dd 0
    x dd 0
    zece dd 10

; our code starts here
segment code use32 class=code
    start:
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp,4*2
        
        cmp eax,0
        je finalizare_scriere
        mov [descriptor_fisier],eax
    citire:
        push dword x 
        push dword format_citire 
        call [fscanf]
        add esp,4*2
        
        cmp eax,1
        jne finalizare_scriere
        
        mov eax,dword[x]
        test eax,01h
        jz e_par
        ;mov [impar+li],eax
        ;add dword[li],1
        call impare
        jmp peste
        ;impar
        
        e_par:
        ;mov [par+lp],eax
        ;add dword[lp],1
        call pare
        
        peste:
        jmp citire
    
    finalizare_scriere
        push dword [descriptor_fisier]
        call [fclose]
        add esp,4
        push    dword 0      
        call    [exit]       
    impare:
        pushad
        mov eax,0
        mov edx,0
    bucla_impare:
        div dword[zece]
        cmp eax,0
        je sare_1
        mov
        
        
        
        sare_1
        popad 
        ret