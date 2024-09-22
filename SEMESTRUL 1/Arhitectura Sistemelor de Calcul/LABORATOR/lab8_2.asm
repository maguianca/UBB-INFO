bits 32 
global start        


extern exit,printf,scanf              
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

;Sa se citeasca de la tastatura doua numere a si b (in baza 10) şi să se determine relaţia de ordine dintre ele (a < b, a = b sau a > b). Afisati rezultatul în următorul format: "<a> < <b>, <a> = <b> sau <a> > <b>".
segment data use32 class=data
    a dd 0
    b dd 0
    char db 0
    format db "%d","%d",0
    mesaj db "<%d> %c <%d>",0
segment code use32 class=code
    start:
        ;citire
        push dword b
        push dword a
        push dword format
        call [scanf]
        add esp, 4*3
        
        mov eax,[a]
        cmp eax,[b]
        
        jbe mai_mic_sau_egal
            mov byte [char],'>'
            jmp final
        mai_mic_sau_egal:
            je egal
                mov byte [char],'<'
                jmp final
            egal:
            mov byte [char],'='
        final:
        ;afisare
        push dword [b]
        push dword [char]
        push dword [a]
        push dword mesaj
        call [printf]
        add esp, 4*4
        
        push    dword 0      
        call    [exit]       
