bits 32
global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
	s dd 11223344h, 55667788h, 99AABBCCh, 0DDEEFF11h
    len equ ($-s)/4         ; numarul de elemente ale sirului s (in cuvinte)
    b1 times len db 0
    b2 times len db 0
    
;EX:12 Se da un sir A de dublucuvinte. Cunstruiti doua siruri de octeti  
; - B1: contine ca elemente partea inferioara a cuvintelor inferioara din A
; - B2: contine ca elemente partea superioara a cuvintelor superioare din A
segment code use32 class=code
    start:
        mov ecx, len        
        jecxz final         
        cld                 
        mov esi, s          
        mov ebx, b2         
        mov edi, b1         
    repeta:
        lodsd               
        stosb              
        
        push edi   
        mov edi, ebx
        ror eax, 24
        stosb   
        mov ebx, edi        
        pop edi             
        loop repeta
        
    final:
        push dword 0
        call [exit]
