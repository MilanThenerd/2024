; ==========================
; Group member 01: Milan_Kruger_04948123
; ==========================

extern malloc
section .text
    global addStudentToList

addStudentToList:
    push    rbp
    mov     rbp, rsp
    sub     rsp, 0x40
    mov     qword [rbp-0x28], rdi
    mov     qword [rbp-0x30], rsi
    movss   dword [rbp-0x34], xmm0
    mov     edi, 0x48
    call    malloc
    mov     qword [rbp-0x10], rax
    mov     dword [rbp-0x20], 0x0
    jmp     jump1

jump3:
    mov     eax, dword [rbp-0x20]
    movsxd  rdx, eax
    mov     rax, qword [rbp-0x30]
    add     rax, rdx
    movzx   ecx, byte [rax]
    mov     rdx, qword [rbp-0x10]
    mov     eax, dword [rbp-0x20]
    cdqe    
    mov     byte [rdx+rax+0x4], cl
    add     dword [rbp-0x20], 0x1

jump1:
    mov     eax, dword [rbp-0x20]
    movsxd  rdx, eax
    mov     rax, qword [rbp-0x30]
    add     rax, rdx
    movzx   eax, byte [rax]
    test    al, al
    je      jump2

    cmp     dword [rbp-0x20], 0x3e
    jle     jump3

jump2:
    mov     rdx, qword [rbp-0x10]
    mov     eax, dword [rbp-0x20]
    cdqe    
    mov     byte [rdx+rax+0x4], 0x0
    mov     rax, qword [rbp-0x10]
    movss   xmm0, dword [rbp-0x34]
    movss   dword [rax+0x44], xmm0
    mov     edi, 0x10
    call    malloc
    mov     qword [rbp-0x8], rax
    mov     rax, qword [rbp-0x8]
    mov     rdx, qword [rbp-0x10]
    mov     qword [rax], rdx
    mov     rax, qword [rbp-0x8]
    mov     qword [rax+0x8], 0x0
    mov     rax, qword [rbp-0x28]
    mov     rax, qword [rax]
    test    rax, rax
    jne     jump4

    mov     rax, qword [rbp-0x28]
    mov     rdx, qword [rbp-0x8]
    mov     qword [rax], rdx
    mov     rax, qword [rbp-0x8]
    mov     rax, qword [rax]
    mov     dword [rax], 0x1
    jmp     jump5

jump4:
    mov     rax, qword [rbp-0x28]
    mov     rax, qword [rax]
    mov     qword [rbp-0x18], rax
    mov     dword [rbp-0x1c], 0x1
    jmp     jump6

jump8:
    mov     rax, qword [rbp-0x18]
    mov     rax, qword [rax]
    mov     eax, dword [rax]
    cmp     dword [rbp-0x1c], eax
    jge     jump7

    mov     rax, qword [rbp-0x18]
    mov     rax, qword [rax]
    mov     eax, dword [rax]
    mov     dword [rbp-0x1c], eax

jump7:
    mov     rax, qword [rbp-0x18]
    mov     rax, qword [rax+0x8]
    mov     qword [rbp-0x18], rax

jump6:
    mov     rax, qword [rbp-0x18]
    mov     rax, qword [rax+0x8]
    test    rax, rax
    jne     jump8

    mov     rax, qword [rbp-0x18]
    mov     rax, qword [rax]
    mov     eax, dword [rax]
    cmp     dword [rbp-0x1c], eax
    jge     jump9

    mov     rax, qword [rbp-0x18]
    mov     rax, qword [rax]
    mov     eax, dword [rax]
    mov     dword [rbp-0x1c], eax

jump9:
    mov     rax, qword [rbp-0x18]
    mov     rdx, qword [rbp-0x8]
    mov     qword [rax+0x8], rdx
    mov     rax, qword [rbp-0x8]
    mov     rax, qword [rax]
    mov     edx, dword [rbp-0x1c]
    add     edx, 0x1
    mov     dword [rax], edx

jump5:
    nop     
    leave
    retn

