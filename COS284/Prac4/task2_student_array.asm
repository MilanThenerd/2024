; ==========================
; Group member 01: Milan_Kruger_04948123
; ==========================

extern malloc
section .text
    global addStudent

addStudent:
    push    rbp
    mov     rbp, rsp
    mov     qword [rbp-0x18], rdi
    mov     dword [rbp-0x1c], esi
    mov     qword [rbp-0x28], rdx
    movss   dword [rbp-0x20], xmm0
    mov     dword [rbp-0x10], 0x0
    mov     dword [rbp-0xc], 0x0
    jmp     jump1

jump3:
    mov     eax, dword [rbp-0xc]
    movsxd  rdx, eax
    mov     rax, rdx
    shl     rax, 0x3
    add     rax, rdx
    shl     rax, 0x3
    mov     rdx, rax
    mov     rax, qword [rbp-0x18]
    add     rax, rdx
    mov     eax, dword [rax]
    cmp     dword [rbp-0x10], eax
    jge     jump2

    mov     eax, dword [rbp-0xc]
    movsxd  rdx, eax
    mov     rax, rdx
    shl     rax, 0x3
    add     rax, rdx
    shl     rax, 0x3
    mov     rdx, rax
    mov     rax, qword [rbp-0x18]
    add     rax, rdx
    mov     eax, dword [rax]
    mov     dword [rbp-0x10], eax

jump2:
    add     dword [rbp-0xc], 0x1

jump1:
    mov     eax, dword [rbp-0xc]
    cmp     eax, dword [rbp-0x1c]
    jl      jump3

    mov     dword [rbp-0x8], 0x0
    jmp     jump4

jump10:
    mov     eax, dword [rbp-0x8]
    movsxd  rdx, eax
    mov     rax, rdx
    shl     rax, 0x3
    add     rax, rdx
    shl     rax, 0x3
    mov     rdx, rax
    mov     rax, qword [rbp-0x18]
    add     rax, rdx
    mov     eax, dword [rax]
    test    eax, eax
    jne     jump5

    mov     eax, dword [rbp-0x8]
    movsxd  rdx, eax
    mov     rax, rdx
    shl     rax, 0x3
    add     rax, rdx
    shl     rax, 0x3
    mov     rdx, rax
    mov     rax, qword [rbp-0x18]
    add     rax, rdx
    mov     edx, dword [rbp-0x10]
    add     edx, 0x1
    mov     dword [rax], edx
    mov     dword [rbp-0x4], 0x0
    jmp     jump6

jump8:
    mov     eax, dword [rbp-0x4]
    movsxd  rdx, eax
    mov     rax, qword [rbp-0x28]
    lea     rsi, [rdx+rax]
    mov     eax, dword [rbp-0x8]
    movsxd  rdx, eax
    mov     rax, rdx
    shl     rax, 0x3
    add     rax, rdx
    shl     rax, 0x3
    mov     rdx, rax
    mov     rax, qword [rbp-0x18]
    lea     rcx, [rdx+rax]
    movzx   edx, byte [rsi]
    mov     eax, dword [rbp-0x4]
    cdqe    
    mov     byte [rcx+rax+0x4], dl
    add     dword [rbp-0x4], 0x1

jump6:
    mov     eax, dword [rbp-0x4]
    movsxd  rdx, eax
    mov     rax, qword [rbp-0x28]
    add     rax, rdx
    movzx   eax, byte [rax]
    test    al, al
    je      jump7

    cmp     dword [rbp-0x4], 0x3e
    jle     jump8

jump7:
    mov     eax, dword [rbp-0x8]
    movsxd  rdx, eax
    mov     rax, rdx
    shl     rax, 0x3
    add     rax, rdx
    shl     rax, 0x3
    mov     rdx, rax
    mov     rax, qword [rbp-0x18]
    add     rdx, rax
    mov     eax, dword [rbp-0x4]
    cdqe    
    mov     byte [rdx+rax+0x4], 0x0
    mov     eax, dword [rbp-0x8]
    movsxd  rdx, eax
    mov     rax, rdx
    shl     rax, 0x3
    add     rax, rdx
    shl     rax, 0x3
    mov     rdx, rax
    mov     rax, qword [rbp-0x18]
    add     rax, rdx
    movss   xmm0, dword [rbp-0x20]
    movss   dword [rax+0x44], xmm0
    jmp     jump9

jump5:
    add     dword [rbp-0x8], 0x1

jump4:
    mov     eax, dword [rbp-0x8]
    cmp     eax, dword [rbp-0x1c]
    jl      jump10

jump9:
    pop     rbp
    retn
