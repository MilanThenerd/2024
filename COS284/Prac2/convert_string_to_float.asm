section .data                ; Format for printing floating-point numbers
    fmt_err db "Error: Invalid memory access or uninitialized pointer", 0xA, 0

section .text
    global convertStringToFloat
    extern printf

print_error:
    mov rdi, fmt_err            ; Load the error message format string
    xor rax, rax                ; Clear rax for variadic function
    call printf
    ret

convertStringToFloat:
    mov rsi, rdi        
    test rsi, rsi       
    jz error_handler

;     xor rax, rax        ; Clear RAX for accumulating the result (integer part)
;     xor rbx, rbx        ; Clear RBX for the current digit
;     mov rcx, 10         ; Set RCX as the multiplier (10 for decimal)
;     xor rdx, rdx        ; Clear RDX (used for tracking decimal position)
;     xor r8, r8          ; R8 used for decimal flag
;     xor r9, r9          ; R9 used for negative flag
;     xor r10, r10        ; R10 used for decimal places count

;     mov al, [rsi]       ; Load the first character from the string
;     test al, al         ; Check if the first character is null
;     jz error_handler    ; If null, jump to error handler

;     cmp al, '-'         ; Check if it is a negative sign
;     je handle_negative
;     jmp parse_digits

; handle_negative:
;     mov r9, 1           ; Set the negative flag
;     inc rsi             ; Increment the string pointer

; parse_digits:
;     mov al, [rsi]       ; Load the next character
;     test al, al         ; Check for end of string
;     jz end_conversion

;     cmp al, '.'         ; Check if the character is a decimal point
;     je start_fractional

;     cmp al, '0'         ; Check if the character is below '0'
;     jb end_conversion   ; If below, exit the loop
;     cmp al, '9'         ; Check if the character is above '9'
;     ja end_conversion   ; If above, exit the loop

;     sub al, '0'         ; Convert character to integer
;     movzx rbx, al       ; Move character value to RBX
;     imul rax, rcx       ; Multiply the accumulated value by 10
;     add rax, rbx        ; Add the current digit

;     inc rsi             ; Move to the next character
;     jmp parse_digits

; start_fractional:
;     inc rsi             ; Skip the decimal point
;     mov r8, 1           ; Set the fractional flag
;     jmp parse_fractional_digits

; parse_fractional_digits:
;     mov al, [rsi]       ; Load the next character
;     test al, al         ; Check for end of string
;     jz end_conversion

;     cmp al, '0'         ; Check if the character is below '0'
;     jb end_conversion   ; If below, exit the loop
;     cmp al, '9'         ; Check if the character is above '9'
;     ja end_conversion   ; If above, exit the loop

;     sub al, '0'         ; Convert character to integer
;     movzx rbx, al       ; Move character value to RBX
;     imul rdx, rcx       ; Multiply the fractional part by 10
;     add rdx, rbx        ; Add the current digit to the fractional part
;     inc r10             ; Increment the decimal places count

;     inc rsi             ; Move to the next character
;     jmp parse_fractional_digits

; end_conversion:
;     ; Adjust the result for the decimal places
;     test r8, r8         ; Check if there was a decimal point
;     jz check_negative

;     mov rbx, 1
;     mov rcx, r10        ; Move decimal place count to RCX
; adjust_result:
;     cmp rcx, 0
;     je apply_sign
;     imul rbx, 10
;     dec rcx
;     jmp adjust_result

;     ; Convert RAX and RDX to double precision float in RAX
; apply_sign:
;     ; Combine integer and fractional parts to form the final result
;     cvtsi2sd xmm0, rax  ; Convert integer part to double in xmm0
;     mov rdi, rbx        ; Move divisor to RDI
;     cvtsi2sd xmm1, rdx  ; Convert fractional part to double in xmm1
;     divsd xmm1, xmm0    ; Divide by the divisor to shift the decimal
;     addsd xmm0, xmm1    ; Combine integer and fractional parts

; check_negative:
;     test r9, r9         ; Check if negative flag is set
;     jz exit_conversion
;     xorpd xmm0, xmm0    ; Negate the result if negative flag is set

; exit_conversion:
;     ret

error_handler:
    call print_error    ; Print error message
    ret