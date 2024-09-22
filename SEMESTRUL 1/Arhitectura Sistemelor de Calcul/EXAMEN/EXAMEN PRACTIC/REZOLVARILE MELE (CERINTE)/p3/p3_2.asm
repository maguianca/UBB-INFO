bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,printf,scanf,fclose,fopen,fprintf
import exit msvcrt.dll  
import printf msvcrt.dll  
import scanf msvcrt.dll
import fclose msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    cuvant times 100 db 0
    invers times 100 db 0
    len dd 0
    text resb 100
    format db "%c",0
    afisare db "%s ",0
    
    mod_acces db "w",0
    nume_fisier db "output.txt",0
    descriptor_fisier dd 0
    

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
    reset_invers:
          pushad 
          mov ecx,100
          mov edi, invers
          cld
          mov al,0
          rep stosb
          popad 
          ret
    start:
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp,4*2
        
        cmp eax,0
        je final 
        mov[descriptor_fisier],eax
   urmator:     
        call reset
        call reset_invers
        mov edi,cuvant
        mov ebx,0
    citire:
         push dword text
         push dword format 
         call [scanf]
         add esp,4*2
         
         mov eax,0
         mov al,byte[text]
         cmp al,'.'
         je final
         
         cmp al,' '
         je inverseaza
         inc ebx
         stosb 
         jmp citire
         
    finalizare_scriere:
        push dword[descriptor_fisier]
        call [fclose]
        add esp,4
    
        push    dword 0      
        call    [exit]   
    inverseaza:
        pushad 
        mov ecx,ebx
        mov esi,cuvant
        mov edi,invers
        add edi,ebx
        dec edi
    repeta:
        cld 
        lodsb 
        std
        stosb
        loop repeta
    afis:
        cld 
        push dword invers
        push dword afisare
        push dword [descriptor_fisier]
        call [fprintf]
        add esp,4*3
        popad
        jmp urmator
    final: ;pentru .
        pushad 
        mov ecx,ebx
        mov esi,cuvant
        mov edi,invers
        add edi,ebx
        dec edi
    loop1:
        cld 
        lodsb 
        std
        stosb
        loop loop1
    afis_2:
        cld 
        push dword invers
        push dword afisare
        push dword [descriptor_fisier]
        call [fprintf]
        add esp,4*3
        popad
        jmp finalizare_scriere