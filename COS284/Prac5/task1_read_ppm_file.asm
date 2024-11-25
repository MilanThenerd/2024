; External functions from C library
extern fopen
extern fgets
extern sscanf
extern fclose
extern fread
extern printf
extern malloc
extern free

section .data
    read_mode db "rb", 0
    error_msg db "Error: Not a valid P6 PPM file", 10, 0
    magic_format db "P6", 0
    dim_format db "%d %d", 0
    color_format db "%d", 0
    pixel_format db "Pixel (%d, %d): R=%d, G=%d, B=%d", 10, 0

section .bss
    buffer resb 100
    width resd 1
    height resd 1
    max_color resd 1
    pixel resb 3  ; Buffer for one pixel (RGB)
    pixels_array resq 1  ; Pointer to the array of PixelNodes

section .text
global readPPM

readPPM:
    push rbp
    mov rbp, rsp
    sub rsp, 32

    ; Save the filename pointer
    mov [rbp-8], rdi

    ; Call read_header
    mov rdi, [rbp-8]
    call .read_header

    ; Call read_pixel_data if header read was successful
    test rax, rax
    jz .end
    mov rdi, [rbp-8]
    call .read_pixel_data

    ; If successful, return pointer to top-left pixel
    test rax, rax
    jz .end
    mov rax, [pixels_array]  ; Return pointer to first PixelNode

.end:
    add rsp, 32
    pop rbp
    ret

.read_header:
    push rbp
    mov rbp, rsp
    sub rsp, 32

    ; Open the file
    mov rsi, read_mode
    call fopen
    test rax, rax
    jz .open_error

    ; Save file pointer
    mov [rbp-8], rax

    ; Read magic number
.read_magic:
    mov rdi, buffer
    mov rsi, 100
    mov rdx, [rbp-8]
    call fgets
    test rax, rax
    jz .format_error

    cmp byte [buffer], '#'
    je .read_magic

    mov rdi, buffer
    mov rsi, magic_format
    mov rdx, 2
    call strncmp
    test eax, eax
    jnz .format_error

    ; Read dimensions
.read_dimensions:
    mov rdi, buffer
    mov rsi, 100
    mov rdx, [rbp-8]
    call fgets
    test rax, rax
    jz .format_error

    cmp byte [buffer], '#'
    je .read_dimensions

    mov rdi, buffer
    mov rsi, dim_format
    mov rdx, width
    mov rcx, height
    xor eax, eax
    call sscanf
    cmp eax, 2
    jne .format_error

    ; Read max color value
.read_max_color:
    mov rdi, buffer
    mov rsi, 100
    mov rdx, [rbp-8]
    call fgets
    test rax, rax
    jz .format_error

    cmp byte [buffer], '#'
    je .read_max_color

    mov rdi, buffer
    mov rsi, color_format
    mov rdx, max_color
    xor eax, eax
    call sscanf
    cmp eax, 1
    jne .format_error

    ; Return success
    mov rax, 1
    jmp .header_end

.open_error:
.format_error:
    mov rdi, error_msg
    xor eax, eax
    call printf
    xor eax, eax  ; Return 0 for failure

.header_end:
    add rsp, 32
    pop rbp
    ret

.read_pixel_data:
    push rbp
    mov rbp, rsp
    sub rsp, 64

    ; Open the file
    mov rsi, read_mode
    call fopen
    test rax, rax
    jz .read_error

    ; Save file pointer
    mov [rbp-8], rax

    ; Skip header
    call .skip_header

    ; Allocate memory for PixelNodes array
    mov eax, [width]
    imul eax, [height]
    mov edi, eax
    imul edi, 40  ; Size of PixelNode struct (40 bytes)
    call malloc
    test rax, rax
    jz .malloc_error
    mov [pixels_array], rax

    ; Initialize pixel counters
    mov dword [rbp-12], 0  ; y counter
.y_loop:
    mov dword [rbp-16], 0  ; x counter
.x_loop:
    ; Read one pixel
    mov rdi, pixel
    mov rsi, 1
    mov rdx, 3
    mov rcx, [rbp-8]
    call fread

    ; Check if fread was successful
    cmp rax, 3
    jne .read_error

    ; Print pixel data
    mov rdi, pixel_format
    mov esi, [rbp-16]  ; x
    mov edx, [rbp-12]  ; y
    xor eax, eax
    movzx ecx, byte [pixel]    ; R
    movzx r8d, byte [pixel+1]  ; G
    movzx r9d, byte [pixel+2]  ; B
    ; call printf

    ; Create PixelNode
    mov edi, [rbp-12]  ; y
    mov esi, [rbp-16]  ; x
    call .create_pixel_node

    ; Increment x counter
    inc dword [rbp-16]
    mov eax, [rbp-16]
    cmp eax, [width]
    jl .x_loop

    ; Increment y counter
    inc dword [rbp-12]
    mov eax, [rbp-12]
    cmp eax, [height]
    jl .y_loop

    ; Close file
    mov rdi, [rbp-8]
    call fclose

    ; Link PixelNodes
    call .link_pixel_nodes

    ; Return success
    mov rax, 1
    jmp .read_end

.read_error:
.malloc_error:
    mov rdi, error_msg
    xor eax, eax
    call printf
    ; Close file if it was opened
    cmp qword [rbp-8], 0
    je .cleanup
    mov rdi, [rbp-8]
    call fclose

.cleanup:
    ; Free allocated memory if any
    cmp qword [pixels_array], 0
    je .read_end
    mov rdi, [pixels_array]
    call free

.read_end:
    add rsp, 64
    pop rbp
    ret

.create_pixel_node:
    ; edi = y, esi = x
    push rbp
    mov rbp, rsp
    
    ; Calculate index in pixels_array
    imul edi, [width]
    add edi, esi
    imul edi, 40  ; Size of PixelNode struct (40 bytes)
    add rdi, [pixels_array]

    ; Set RGB values
    movzx eax, byte [pixel]
    mov [rdi], al      ; Red
    movzx eax, byte [pixel+1]
    mov [rdi+1], al    ; Green
    movzx eax, byte [pixel+2]
    mov [rdi+2], al    ; Blue

    ; Initialize other fields
    mov byte [rdi+3], 0  ; CdfValue
    mov qword [rdi+8], 0   ; up
    mov qword [rdi+16], 0  ; down
    mov qword [rdi+24], 0  ; left
    mov qword [rdi+32], 0  ; right

    pop rbp
    ret

.link_pixel_nodes:
    push rbp
    mov rbp, rsp
    sub rsp, 16

    ; Initialize counters
    mov dword [rbp-4], 0  ; y counter
.link_y_loop:
    mov dword [rbp-8], 0  ; x counter
.link_x_loop:
    ; Calculate current index
    mov eax, [rbp-4]
    imul eax, [width]
    add eax, [rbp-8]
    mov edi, eax
    imul edi, 40  ; Size of PixelNode struct (40 bytes)
    add rdi, [pixels_array]

    ; Link up
    cmp dword [rbp-4], 0
    je .skip_up
    mov eax, [width]
    imul eax, 40
    neg rax
    add rax, rdi
    mov [rdi+8], rax   ; up
.skip_up:

    ; Link down
    mov eax, [rbp-4]
    inc eax
    cmp eax, [height]
    je .skip_down
    mov eax, [width]
    imul eax, 40
    add rax, rdi
    mov [rdi+16], rax  ; down
.skip_down:

    ; Link left
    cmp dword [rbp-8], 0
    je .skip_left
    mov rax, rdi
    sub rax, 40
    mov [rdi+24], rax  ; left
.skip_left:

    ; Link right
    mov eax, [rbp-8]
    inc eax
    cmp eax, [width]
    je .skip_right
    mov rax, rdi
    add rax, 40
    mov [rdi+32], rax  ; right
    jmp .continue_loop
.skip_right:
    mov qword [rdi+32], 0  ; Set right pointer to null for rightmost nodes

.continue_loop:
    ; Increment x counter
    inc dword [rbp-8]
    mov eax, [rbp-8]
    cmp eax, [width]
    jl .link_x_loop

    ; Increment y counter
    inc dword [rbp-4]
    mov eax, [rbp-4]
    cmp eax, [height]
    jl .link_y_loop

    add rsp, 16
    pop rbp
    ret

.skip_header:
    ; Skip 3 non-comment lines
    mov ecx, 3
.skip_loop:
    push rcx
.read_line:
    mov rdi, buffer
    mov rsi, 100
    mov rdx, [rbp-8]
    call fgets
    test rax, rax
    jz .skip_error
    cmp byte [buffer], '#'
    je .read_line
    pop rcx
    loop .skip_loop
    ret
.skip_error:
    add rsp, 8  ; clean up stack in case of error
    jmp .read_error

strncmp:
    push rcx
    xor ecx, ecx
.loop:
    mov al, [rdi + rcx]
    cmp al, [rsi + rcx]
    jne .not_equal
    test al, al
    jz .equal
    inc ecx
    cmp ecx, edx
    jl .loop
.equal:
    xor eax, eax
    pop rcx
    ret
.not_equal:
    mov eax, 1
    pop rcx
    ret