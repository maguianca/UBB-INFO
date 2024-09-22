bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,scanf,printf,fprintf, fopen,fclose         
import exit msvcrt.dll    
import scanf msvcrt.dll    
import printf msvcrt.dll    
import fprintf msvcrt.dll    
import fopen msvcrt.dll    
import fclose msvcrt.dll    

; our data is declared here (the variables needed by our program)
segment data use32 class=data
   n dd 0
   a dd 0
   mod_acces db "w",0
   nume_fisier db "output.txt"
   descriptor_fisier dd 0
   suma_par dd 0
   suma_impar dd 0
   dif dd 0
   afisare db "%x  ",0
   mesaj db "n=",0
   format db "%d",0
   char db "%c",0

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
  
        push dword mesaj
        call [printf]
        add esp,4
        
        push dword n
        push dword format
        call[scanf]
        add esp,4*2
        
        cmp dword[n],0
        je finalizare_scriere
        
        mov ecx,[n]
    repeta:
        push ecx
        push dword a
        push dword format
        call[scanf]
        add esp,4*2
        
        mov eax,[a]
        test eax, 01h
        jz e_par
        
        add dword[suma_impar],eax
        jmp aici
        
        e_par:
        add dword[suma_par],eax
        aici:
        pop ecx
        loop repeta
        
        mov eax,[suma_par]
        mov ebx,[suma_impar]
        sub eax,ebx
        mov [dif],eax
        
        push dword [suma_par]
        push dword afisare
        push dword [descriptor_fisier]
        call [fprintf]
        add esp,4*3
        
        push dword 10
        push dword char
        push dword[descriptor_fisier]
        call [fprintf]
        add esp,4*3
      
        push dword [suma_impar]
        push dword afisare
        push dword [descriptor_fisier]
        call [fprintf]
        add esp,4*3
        
        push dword 10
        push dword char
        push dword[descriptor_fisier]
        call [fprintf]
        add esp,4*3
        
        push dword [dif]
        push dword afisare
        push dword [descriptor_fisier]
        call [fprintf]
        add esp,4*3
        
     
    finalizare_scriere:
        push dword [descriptor_fisier]
        call [fclose]
        add esp,4
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
