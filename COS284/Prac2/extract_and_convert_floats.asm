section .bss
    user_input resb 200               ; Reserve 200 bytes for user input
    floats_array resq 100             ; Reserve space for up to 100 float values

section .data
    prompt db "Enter values separated by whitespace enclosed in pipes (|):", 0xA, 0
    prompt_len equ $ - prompt
    fmt db "%lf", 0                   ; Format for printing floating-point numbers
    fmt_err db "Error: Invalid memory access or uninitialized pointer", 0xA, 0

section .text
    global extractAndConvertFloats   ; Declare symbol as global
    extern convertStringToFloat
    extern printf 

print_float_64:
    movq xmm0, rax              ; Move the floating-point value into xmm0 for printf
    mov rdi, fmt                ; Set format string
    xor rax, rax                ; Clear rax for variadic function
    call printf
    ret

print_error:
    mov rdi, fmt_err            ; Load the error message format string
    xor rax, rax                ; Clear rax for variadic function
    call printf
    ret

extractAndConvertFloats:
    ; Print the prompt
    mov rax, 1                      ; syscall: write
    mov rdi, 1                      ; file descriptor: stdout
    mov rsi, prompt                 ; pointer to the prompt
    mov rdx, prompt_len             ; length of the prompt
    syscall

    ; Read user input
    mov rax, 0                      ; syscall: read
    mov rdi, 0                      ; file descriptor: stdin
    mov rsi, user_input             ; pointer to input buffer
    mov rdx, 200                    ; max number of bytes to read
    syscall

    ; Initialize RSI to the start of the input buffer
    mov rsi, user_input

.parse_characters:
    mov   al , [rsi]                          
    test  al, al                     
    je    .done                        

    cmp al, '0'
    jb .parse_characters            
    cmp al, '9'
    jbe .digit_found                

    cmp al, '.'                     
    je .decimal_found               
    
    jmp .parse_characters          

.digit_found:
    sub al, '0'                     
    movzx rax, al                   
    push rax                       
    jmp .parse_characters  
             

.decimal_found:
    mov rdi, rax                    
    call convertStringToFloat       
    jmp .parse_characters           

.done:
    pop rax                         
    call print_float_64             
    ret