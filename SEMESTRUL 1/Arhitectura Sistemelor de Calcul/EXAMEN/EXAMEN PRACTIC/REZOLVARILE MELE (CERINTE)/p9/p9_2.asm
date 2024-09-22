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
    format_ascii db "%d",0
    nume_fisier resb 15
    text resb 100
    descriptor_fisier dd 0
    fisier_out db "ou.txt",0
    fisier_in db "in.txt",0
    descriptor_fisier_2 dd 0
    
    count dd 100
    dimensiune dd 1
    sir resb 100
    
    mod_acces_read db "r",0
    
    
    
segment code use32 class=code
    start:
    
        ;FILE * fopen(const char* nume_fisier, const char * mod_acces) *=>pointer, lucrez cu adresa
        push dword mod_acces_read
        push dword fisier_in
        call [fopen]
        add esp, 4 * 2
        cmp eax, 0
        je final ; eroare la deschiderea fisierului
        mov [descriptor_fisier], eax
        
        push dword mod_acces
        push dword fisier_out
        call [fopen]
        add esp,4*2
        cmp eax,0
        je final
        mov [descriptor_fisier_2],eax
        
    
        push dword [descriptor_fisier]
        push dword [count]
        push dword [dimensiune]
        push dword sir
        call [fread]
        add esp, 4*4
        
        mov esi, sir
        mov edi, sir
    convert_loop:
        movzx eax, byte [esi]
        cmp eax, 0
        je end_convert
        cmp eax, 'a'
        jl not_lowercase
        cmp eax, 'z'
        jg not_lowercase
        sub eax, 'a'
        add eax, '0'
        ;sub eax,'0'
        mov [edi], al
        jmp next_char
        not_lowercase:
            mov [edi], al
        next_char:
            inc esi
            inc edi
            jmp convert_loop
    end_convert:
        
        
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
