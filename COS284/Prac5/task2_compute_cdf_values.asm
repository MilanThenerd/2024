section .data
    RED_WEIGHT   dd 0.299
    GREEN_WEIGHT dd 0.587
    BLUE_WEIGHT  dd 0.114
    float255     dd 255.0
    zero         dd 0
    max255       dd 255

section .bss
    histogram        resd 256   ; Frequency count
    cumulativeHist   resd 256   ; Cumulative histogram
    totalPixels      resd 1
    cdfMin           resd 1

section .text
global computeCDFValues

computeCDFValues:
    push rbp
    mov rbp, rsp
    push rbx
    push r12
    push r13
    push r14
    push r15

    ; Save head pointer for both passes
    mov r15, rdi        ; Keep original head pointer in r15
    mov r12, rdi        ; r12 will be our row pointer
    
    ; Clear histogram array
    push rdi
    mov rcx, 256
    mov rdi, histogram
    xor eax, eax
    rep stosd
    pop rdi

    ; Initialize variables
    mov dword [totalPixels], 0

    ; First pass - compute histogram
.first_pass:
    test r12, r12
    jz .end_first_pass

    mov r13, r12        ; r13 = current pixel in row

.process_row:
    test r13, r13
    jz .next_row

    ; Convert to grayscale using floating point
    xorps xmm0, xmm0    ; Clear xmm0
    xorps xmm1, xmm1    ; Clear xmm1
    
    ; Red component
    movzx eax, byte [r13]
    cvtsi2ss xmm0, eax
    mulss xmm0, [RED_WEIGHT]
    
    ; Green component
    movzx eax, byte [r13 + 1]
    cvtsi2ss xmm1, eax
    mulss xmm1, [GREEN_WEIGHT]
    addss xmm0, xmm1
    
    ; Blue component
    movzx eax, byte [r13 + 2]
    cvtsi2ss xmm1, eax
    mulss xmm1, [BLUE_WEIGHT]
    addss xmm0, xmm1

    ; Convert to integer (0-255)
    cvtss2si eax, xmm0
    
    ; Store grayscale in CdfValue
    mov byte [r13 + 3], al
    
    ; Update histogram
    movzx eax, byte [r13 + 3]
    inc dword [histogram + eax*4]
    inc dword [totalPixels]

    mov r13, [r13 + 32]    ; Move to next pixel using right pointer
    jmp .process_row

.next_row:
    mov r12, [r12 + 16]    ; Move to next row using down pointer
    jmp .first_pass

.end_first_pass:
    ; Calculate cumulative histogram
    mov ecx, 0              ; Current index
    mov edx, 0              ; Running sum
    mov dword [cdfMin], -1  ; Initialize cdfMin to -1

.cumulative_loop:
    mov eax, [histogram + ecx*4]
    add edx, eax
    mov [cumulativeHist + ecx*4], edx
    
    ; Update cdfMin if needed
    test eax, eax
    jz .skip_cdfmin
    cmp dword [cdfMin], -1
    jne .skip_cdfmin
    mov [cdfMin], edx
    
.skip_cdfmin:
    inc ecx
    cmp ecx, 256
    jl .cumulative_loop

    ; Second pass - normalize and update CdfValues
    mov r12, r15            ; Reset to original head pointer

.second_pass:
    test r12, r12
    jz .end_second_pass

    mov r13, r12            ; Start at first pixel in row

.normalize_row:
    test r13, r13
    jz .next_row_second

    ; Get original grayscale value
    movzx eax, byte [r13 + 3]
    
    ; Calculate normalized CDF value
    mov edx, [cumulativeHist + eax*4]
    sub edx, [cdfMin]
    cvtsi2ss xmm0, edx
    
    mov edx, [totalPixels]
    sub edx, [cdfMin]
    cvtsi2ss xmm1, edx
    
    divss xmm0, xmm1
    mulss xmm0, [float255]
    cvtss2si eax, xmm0
    
    ; Clamp to 0-255
    cmp eax, 0
    cmovl eax, [zero]
    cmp eax, 255
    cmovg eax, [max255]
    
    ; Store normalized value
    mov byte [r13 + 3], al

    mov r13, [r13 + 32]     ; Next pixel using right pointer
    jmp .normalize_row

.next_row_second:
    mov r12, [r12 + 16]     ; Move to next row using down pointer
    jmp .second_pass

.end_second_pass:
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbx
    mov rsp, rbp
    pop rbp
    ret