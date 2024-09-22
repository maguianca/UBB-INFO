bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fread, fclose,fopen,printf
import exit msvcrt.dll    
import fclose msvcrt.dll    
import fopen msvcrt.dll    
import fread msvcrt.dll    
import printf msvcrt.dll    
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fisier db "input.txt",0
    mod_acces db "r",0
    descriptor_fisier dd -1
    sir times 100 db 0
    dimensiune dd 1
    count dd 100
    invers times 100 db 0
    propozitie times 100 db 0
    nr_propozitii dd 0
    nr_cuvinte dd 0
    len dd 0
    afisare_propozitie db "Propozitie: %s",0
    afisare_nr_cuvinte db "nr cuvinte: %d",0
    afisare_cuvant db "Primul cuvant: %s",0
    afisare_litere_cuvant db "are %d litere",0
    

; our code starts here
segment code use32 class=code
    reset_propozitie:
        pushad 
        mov ecx,dword[ma]
        mov esi,majuscule
        mov edi,inv_maj
        add edi,dword[maj]
        dec edi
      repeta_1:
        cld
        lodsb 
        std
        stosb
        loop repeta_1
        popad 
        jmp jos
    
    reset_cuvant:
        pushad 
        mov ecx,dword[min]
        mov esi,minuscule
        mov edi,inv_min
        add edi,dword[min]
        dec edi
      repeta_2:
        cld
        lodsb 
        std
        stosb
        loop repeta_2
        popad 
        jmp jos_2
    
    
    start:
        push dword mod_acces
        push dword nume_fisier 
        call [fopen]
        add esp,4*2
        
        cmp eax,0
        je finalizare_scriere
        mov [descriptor_fisier],eax
        
        push dword [descriptor_fisier]
        push dword[count]
        push dword[dimensiune]
        push dword sir 
        call [fread]
        add esp,4*4
        ;prima data aflam cate propozitii sunt 
        mov dword[len],eax
        mov ecx,dword[len]
        jecxz finalizare_scriere
        mov esi,sir
        mov edi,propozitie
        mov eax,0
    repeta:
        lodsb 
        cmp al,'.'
        je afis
        
        stosb 
        jnz peste
        add dword[nr_propozitii],1
        peste:
        loop repeta
        
        
    finalizare_scriere
        push dword [descriptor_fisier]
        call [fclose]
        add esp,4
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
    afis:
        