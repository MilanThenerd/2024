; ==========================
; Group member 01: Milan_Kruger_04948123
; ==========================

extern malloc
section .text
    global createStudent

createStudent:
    push    rbp
    mov     rbp, rsp
    sub     rsp, 0x20
    mov     dword [rbp-0x14], edi
    mov     qword [rbp-0x20], rsi
    movss   dword [rbp-0x18], xmm0
    mov     edi, 0x48
    call    malloc
    mov     qword [rbp-0x8], rax
    mov     rax, qword [rbp-0x8]
    mov     edx, dword [rbp-0x14]
    mov     dword [rax], edx
    mov     dword [rbp-0xc], 0x0
    jmp     check_end_of_name

copy_name:
    mov     eax, dword [rbp-0xc]
    movsxd  rdx, eax
    mov     rax, qword [rbp-0x20]
    add     rax, rdx
    movzx   ecx, byte [rax]
    mov     rdx, qword [rbp-0x8]
    mov     eax, dword [rbp-0xc]
    cdqe    
    mov     byte [rdx+rax+0x4], cl
    add     dword [rbp-0xc], 0x1

check_end_of_name:
    mov     eax, dword [rbp-0xc]
    movsxd  rdx, eax
    mov     rax, qword [rbp-0x20]
    add     rax, rdx
    movzx   eax, byte [rax]
    test    al, al
    je      store_grade
    
    cmp     dword [rbp-0xc], 0x3e
    jle     copy_name

store_grade:
    mov     rax, qword [rbp-0x8]
    movss   xmm0, dword [rbp-0x18]
    movss   dword [rax+0x44], xmm0
    mov     rax, qword [rbp-0x8]
    leave
    retn
