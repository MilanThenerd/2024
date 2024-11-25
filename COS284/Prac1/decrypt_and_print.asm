section .data
    fmt db "%c", 0
    enterMSG db "Enter cipher text to decrypt:", 0
    enterMSGlen equ $ - enterMSG
    plainMSG db "The plain text is: ", 0
    plainMSGlen equ $ - plainMSG
    countMSG db "Number of integers: ", 0
    countMSGlen equ $ - countMSG

section .bss
    userInput resb 255
    inputNumbers resd 255
    output_char resb 1
       
section .text
global decrypt_and_print

extern printf
extern scanf


print_char_32:
    mov   rsi, rax
    mov   rdi, fmt
    xor   rax, rax
    call  printf
    ret

decrypt_and_print:
    mov   rax, 1               
    mov   rdi, 1                 
    mov   rsi, enterMSG         
    mov   rdx, enterMSGlen
    syscall

    mov   rax, 0               
    mov   rdi, 0               
    mov   rsi, userInput       
    mov   rdx, 255
    syscall


    mov byte [rsi + rax - 1], 0 

    mov   rax, 1               
    mov   rdi, 1               
    mov   rsi, plainMSG        
    mov   rdx, plainMSGlen           
    syscall

    mov   rsi, userInput
    mov   rdi, inputNumbers 
    call  parse_loop

    xor   rcx, rcx
    mov   rsi, inputNumbers
    mov   rbx, rsi

print_loop:
    mov   rax, [rsi]
    test  rax , rax
    jz    done_printing

    ror   rax, 4                       
    xor   rax, 0x73113777

    call  print_char_32                               
    add   rbx, 4               
    mov   rsi, rbx    
    jmp   print_loop
                                                                 
              
done_printing:
    ret

parse_loop:
    xor   rbx, rbx      ; Clear the accumulator for the current number
    xor   rcx, rcx      ; Clear the index counter
    mov   rdx, 1        ; Initialize to handle the first number

next_char:
    movzx rax, byte [rsi] ; Load the current character
    test  rax, rax        ; Check if it's the end of the string
    jz    store_final     ; Jump to store_final if it's the end

    cmp   rax, ' '        ; Check if it's a space
    je    store_integer   ; Jump to store_integer if it's a space

    cmp   rax, 10         ; Check if it's a newline (ASCII 10)
    je    store_integer   ; Jump to store_integer if it's a newline

    sub   rax, '0'        ; Convert ASCII digit to integer
    imul  rbx, rbx, 10    ; Multiply current number by 10
    add   rbx, rax        ; Add the new digit
    add   rsi, 1          ; Move to the next character
    jmp   next_char       ; Continue parsing

store_integer:
    mov   [rdi + rcx*4], rbx ; Store the parsed number in the array
    add   rcx, 1              ; Move to the next index
    xor   rbx, rbx            ; Clear the accumulator for the next number
    add   rsi, 1              ; Move past the space or newline
    jmp   next_char           ; Continue parsing

store_final:
    test  rbx, rbx           ; Check if there is any remaining number
    jz    end_parse          ; Jump to end_parse if no number to store
    mov   [rdi + rcx*4], rbx ; Store the last number
    mov   rcx, rcx           ; Increment counter for the final number
    jmp   end_parse          ; Finish parsing

end_parse:
    ret

