bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,scanf,fprintf,fclose,fopen
import exit msvcrt.dll    
import scanf msvcrt.dll    
import fprintf msvcrt.dll    
import fclose msvcrt.dll    
import fopen msvcrt.dll    

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    m dd 0
    n dd 0
    a dd 0
    zece dd 10
    format db "%d",0
    descriptor_fisier dd 0
    cif dd 0
    mod_acces db "w",0
    nume_fisier db "output.txt",0
    format_afisare db "%d ",0
    
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
        
        push dword m
        push dword format
        call [scanf]
        add esp,4*2
        
        push dword n 
        push dword format
        call [scanf]
        add esp,4*2
        
        mov ecx,dword[m]
        
   citire:
        push ecx
        push dword a
        push dword format
        call [scanf]
        add esp,4*2
        
        mov eax,0
        mov al,byte[a]
        mov edx,0
        mov dword[cif],0
   repeta:
        div dword[zece]
        test edx,01h
        jnz nu_par
        add dword[cif],1
        
    nu_par:
         mov edx,0
         cmp eax,0
         je peste
         jmp repeta
    peste:
         mov ebx, dword[cif]
         cmp ebx,dword [n]
         jae afis
         inapoi:
         pop ecx
         mov dword[cif],0
        loop citire
    finalizare_scriere:
        push dword[descriptor_fisier]
        call [fclose] 
        add esp,4
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
    afis:
        pushad
        push dword [a]
        push dword format_afisare
        push dword [descriptor_fisier]
        call [fprintf]
        add esp,4*3
        popad
        jmp inapoi
        
