bits 32
global start        

; declararea functiilor externe folosite de program
extern exit, printf, scanf
import exit msvcrt.dll     
import printf msvcrt.dll
import scanf msvcrt.dll
;ex:11 Sa se citeasca de la tastatura un numar in baza 16 si sa se afiseze valoarea acelui numar in baza 10.
;Exemplu: Se citeste: 1D; se afiseaza: 29
segment data use32 class=data
    n dd 0                   ; Variable to store the input number
    message db "Numarul citit este n= %d", 0  
    format_in db "%x", 0     ; Format specifier for scanf (hexadecimal input)
    format_out db "Decimal value: %d", 0 ; Format specifier for printf (decimal output)

segment code use32 class=code
    start:

    ; citim numarul hexazecimal de la tastatura
    lea eax, [n]             ; adresa lui n nu valoarea
    push eax                 
    push dword format_in
    call [scanf]             
    add esp, 4 * 2           ; curatam stiva de parametrii

    ; afisam rezultatul
    push dword [n]           ; Valoare lui n
    push dword format_out
    call [printf]            
    add esp, 4 * 2           

    ; iesim din program
    push dword 0             ; Exit code 0
    call [exit]              ; Call exit to end the program
