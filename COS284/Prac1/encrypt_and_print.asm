; ==========================
; Group member 01: Milan_Kruger_04948123
; ==========================

section .data
    fmt db "%d", 0
    enterMSG db "Enter plaintext to encrypt:" , 0
    enterMSGlen equ $ - enterMSG
    cipherMSG db "The cipher text is:", 0
    cipherMSGlen equ $ - cipherMSG
    space_fmt db " ", 0       

section .bss
    userInput resb 5          
    inputLength resb 1        

section .text
    global encrypt_and_print
    extern printf

print_char_32:
    mov rsi, rax              
    mov rdi, fmt              
    xor rax, rax              
    call printf
    ret

print_space:
    mov rdi, space_fmt       
    xor rax, rax              
    call printf
    ret

encrypt_and_print:
    mov rax, 1               
    mov rdi, 1                 
    mov rsi, enterMSG     
    mov rdx, enterMSGlen
    syscall

    mov rax, 0              
    mov rdi, 0              
    mov rsi, userInput     
    mov rdx, 4
    syscall

    mov byte [rsi + rdx], 0

    mov rax, 1               
    mov rdi, 1               
    mov rsi, cipherMSG        
    mov rdx, cipherMSGlen            
    syscall

    mov rsi, userInput
    mov rbx, rsi               

.encrypt_loop:
    movzx rax, byte [rsi]

    test  rax, rax              
    jz    .done

    rol   rax, 4               
    xor   rax, 0x73113777 

    call  print_char_32
    call  print_space        
    mov   rsi, rbx
    movzx rax, byte [rsi]
    test  rax, rax            
    jz    .done                
    add   rbx, 1               
    mov   rsi, rbx
    jmp   .encrypt_loop

.done:
    ret
