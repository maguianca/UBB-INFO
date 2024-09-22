; Declare the EntryPoint (a label defining the very first instruction of the program)
bits 32
global start        

extern exit, fopen, fread, fclose, printf
import exit msvcrt.dll  
import fopen msvcrt.dll  
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll

; Our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fisier db "output.txt", 0  ; File name to be created
    mod_acces db "w", 0              ; Open the file for writing
    len equ 100                      ; Maximum number of characters to read
    text times (len + 1) db 0        ; Buffer to store the input text
    descriptor_fis dd -1             ; File descriptor variable
    formatc db "Word with uppercase letter: %s", 13, 10, 0

; Our code starts here
segment code use32 class=code
    start:
        ; Open the file for writing
        ; eax = fopen(nume_fisier, mod_acces)
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 4*2                ; Free parameters from the stack

        mov [descriptor_fis], eax   ; Save the file descriptor

        ; Check if fopen was successful (if EAX != 0)
        cmp eax, 0
        je final                    ; Jump to final if fopen failed

    citire:
        ; Read words from the keyboard until '$' is encountered
        ; eax = fread(text, 1, len, descriptor_fis)
        push dword [descriptor_fis]
        push dword len
        push dword 1
        push dword text
        call [fread]
        add esp, 4*4                 ; Free parameters from the stack

        ; Check if '$' is encountered
        cmp byte [text], '$'
        je final                    ; Jump to final if '$' is encountered

        ; Check if the word contains at least one uppercase letter
        mov esi, 0
    verif_uper:
        cmp byte [text + esi], 0
        je citire                   ; Jump to citire if the end of the word is reached
        cmp byte [text + esi], 'A'
        jb  nu_majuscule            ; Jump to nu_majuscule if the character is not a letter
        cmp byte [text + esi], 'Z'
        jbe gasit_majuscule         ; Jump to gasit_majuscule if the character is an uppercase letter
    nu_majuscule:
        inc esi
        jmp verif_uper
    gasit_majuscule:
        ; Print the word with at least one uppercase letter
        push dword text
        push dword formatc
        call [printf]
        add esp, 4*2                ; Free parameters from the stack
        jmp citire

    final:
        ; Exit(0)
        push    dword 0            ; Push the parameter for exit onto the stack
        call    [exit]             ; Call exit to terminate the program
