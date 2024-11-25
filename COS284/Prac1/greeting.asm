; ==========================
; Group member 01: Milan_Kruger_04948123
; ==========================

section .data
  greetingMSG db "Welcome agent. What do you want to do, Encrypt[1] or Decrypt[2]?", 0x0A , 0
  greetingsMSGlen equ $ - greetingMSG

section .text
    global greeting

greeting:
    mov rax , 1 
    mov rdi , 1
    mov rsi ,greetingMSG
    mov rdx, greetingsMSGlen
    syscall
    ret                         