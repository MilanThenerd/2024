; ==========================
; Group member 01: Milan_Kruger_04948123
; ==========================

section .bss
  userInput resb 2
section .data
    choiceMSG db "Choice: " , 0
    choiceMSGlen equ $ - choiceMSG

section .text
    global get_user_choice

extern greeting
extern encrypt_and_print             
extern decrypt_and_print 

get_user_choice:
    call greeting

    mov rax, 1
    mov rdi, 1
    mov rsi, choiceMSG
    mov rdx, choiceMSGlen
    syscall

    

    mov rax, 0        
    mov rdi, 0        
    mov rsi, userInput
    mov rdx, 2        
    syscall

    sub byte [userInput], '0'

    cmp byte [userInput] , 1
    je encrypt

    cmp byte [userInput], 2
    je decrypt
    ret

encrypt:
  call encrypt_and_print
  ret

decrypt:
  call decrypt_and_print
  ret