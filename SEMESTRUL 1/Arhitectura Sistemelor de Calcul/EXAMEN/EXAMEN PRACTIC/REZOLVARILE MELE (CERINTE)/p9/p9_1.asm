bits 32 
global start        


extern exit  
extern fopen
extern fprintf
extern fclose
extern scanf,fscanf,fread
import exit msvcrt.dll   
import fclose msvcrt.dll
import fprintf msvcrt.dll
import fopen msvcrt.dll
import scanf msvcrt.dll 
import fscanf msvcrt.dll 
import fread msvcrt.dll 


segment data use32 class=data
    mod_acces db "w",0
    format db "%s", 0
    nume_fisier resb 15
    text resb 100
    descriptor_fisier dd 0
    fisier db "output.txt",0
    descriptor_fisier_2 dd 0
    
    count dd 100
    dimensiune dd 1
    sir resb 100
    
    mod_acces_read db "r",0
    
    
    
segment code use32 class=code
    start:
    
        push dword nume_fisier
        push dword format
        call [scanf]
        add esp, 4*2
    
        ;FILE * fopen(const char* nume_fisier, const char * mod_acces) *=>pointer, lucrez cu adresa
        push dword mod_acces_read
        push dword nume_fisier
        call [fopen]
        add esp, 4 * 2
        cmp eax, 0
        je final ; eroare la deschiderea fisierului
        mov [descriptor_fisier], eax
        
    
        push dword [descriptor_fisier]
        push dword [count]
        push dword [dimensiune]
        push dword sir
        call [fread]
        add esp, 4*4
        
        push dword mod_acces
        push dword fisier
        call [fopen]
        add esp,4*2
        cmp eax,0
        je final
        mov [descriptor_fisier_2],eax
        
        push dword sir
        push dword format
        push dword [descriptor_fisier_2]
        call [fprintf]
        add esp,4*3
        
        
        ;int fclose(FILE * descriptor)
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 4
        
        push dword [descriptor_fisier_2]
        call [fclose]
        add esp, 4
        final:
        push    dword 0      
        call    [exit]       
