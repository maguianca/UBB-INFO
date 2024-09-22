bits 32 
global start        


extern exit  
extern fopen
extern fprintf
extern fclose
extern scanf
import exit msvcrt.dll   
import fclose msvcrt.dll
import fprintf msvcrt.dll
import fopen msvcrt.dll
import scanf msvcrt.dll 


segment data use32 class=data
    mod_acces db "w",0
    format db "%s","%s", 0
    nume_fisier resb 15
    text resb 100
    descriptor_fisier dd 0
    
    
    
segment code use32 class=code
    start:
    
        push dword text
        push dword nume_fisier
        push dword format
        call [scanf]
        add esp, 4*2
    
        ;FILE * fopen(const char* nume_fisier, const char * mod_acces) *=>pointer, lucrez cu adresa
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 4 * 2
        cmp eax, 0
        je final ; eroare la deschiderea fisierului
        mov [descriptor_fisier], eax
        
        push dword text
        push dword [descriptor_fisier]
        call [fprintf]
        add esp, 4*2
        
        
        ;int fclose(FILE * descriptor)
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 4
        final:
        push    dword 0      
        call    [exit]       
