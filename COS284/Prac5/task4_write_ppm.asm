; External functions from C standard library
extern fopen
extern fclose
extern fprintf
extern fwrite

section .data
    format_p6 db "P6", 10, 0
    format_dims db "%d %d", 10, 0
    format_maxval db "255", 10, 0
    write_mode db "wb", 0
    format_rgb db "%c%c%c", 0

section .text
global writePPM

writePPM:
    ; Preserve registers according to ABI
    push rbp
    mov rbp, rsp
    push rbx
    push r12
    push r13
    push r14
    push r15
    sub rsp, 32

    ; Save parameters
    mov r12, rdi            ; filename
    mov r13, rsi           ; head pointer
    
    ; Check if head is NULL
    test r13, r13
    jz .end

    ; Count width and height
    mov rbx, r13           ; rbx = current node
    xor r14d, r14d        ; r14 = width
    xor r15d, r15d        ; r15 = height

    ; Count width
    mov rbx, r13
.count_width:
    test rbx, rbx
    jz .width_done
    inc r14d
    mov rbx, [rbx + 32]    ; next = current->right
    jmp .count_width
.width_done:

    ; Count height
    mov rbx, r13
.count_height:
    test rbx, rbx
    jz .height_done
    inc r15d
    mov rbx, [rbx + 16]    ; next = current->down
    jmp .count_height
.height_done:

    ; Open file
    mov rdi, r12           ; filename
    mov rsi, write_mode
    call fopen
    test rax, rax
    jz .end
    mov [rbp-8], rax      ; Save file pointer

    ; Write PPM header
    mov rdi, [rbp-8]      ; file pointer
    mov rsi, format_p6
    xor eax, eax          ; Clear AL register for printf family functions
    call fprintf

    ; Write dimensions
    mov rdi, [rbp-8]
    mov rsi, format_dims
    mov edx, r14d         ; width
    mov ecx, r15d         ; height
    xor eax, eax
    call fprintf

    ; Write max value
    mov rdi, [rbp-8]
    mov rsi, format_maxval
    xor eax, eax
    call fprintf

    ; Write pixel data
    mov rbx, r13          ; Reset to head
.write_rows:
    test rbx, rbx
    jz .write_done
    mov r14, rbx          ; Current node in row
    
.write_pixels:
    test r14, r14
    jz .next_row

    ; Write RGB values
    mov rdi, [rbp-8]      ; file pointer
    mov rsi, format_rgb
    movzx edx, byte [r14]      ; Red
    movzx ecx, byte [r14 + 1]  ; Green
    movzx r8d, byte [r14 + 2]  ; Blue
    xor eax, eax
    call fprintf

    mov r14, [r14 + 32]   ; Move to next pixel in row
    jmp .write_pixels

.next_row:
    mov rbx, [rbx + 16]   ; Move to next row
    jmp .write_rows

.write_done:
    ; Close file
    mov rdi, [rbp-8]
    call fclose

.end:
    ; Restore stack and registers
    add rsp, 32
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbx
    pop rbp
    ret