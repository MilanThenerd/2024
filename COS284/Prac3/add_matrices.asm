;Milan Kruger - u04948123
extern malloc
section .text
    global addMatrices

addMatrices:
  push    rbp
  mov     rbp, rsp
  push    rbx
  sub     rsp, 0x48
  mov     qword [rbp-0x38], rdi
  mov     qword [rbp-0x40], rsi
  mov     dword [rbp-0x44], edx
  mov     dword [rbp-0x48], ecx
  cmp     dword [rbp-0x44], 0x0
  jle     handleZero

  cmp     dword [rbp-0x48], 0x0
  jg      allocateMemory

handleZero:
  mov     eax, 0x0
  jmp     done

allocateMemory:
  mov     eax, dword [rbp-0x44]
  cdqe    
  shl     rax, 0x3
  mov     rdi, rax
  call    malloc
  mov     qword [rbp-0x18], rax
  mov     dword [rbp-0x24], 0x0
  jmp     fillMemory

fillNextRow:
  mov     eax, dword [rbp-0x48]
  cdqe    
  shl     rax, 0x2
  mov     edx, dword [rbp-0x24]
  movsxd  rdx, edx
  lea     rcx, [rdx*8]
  mov     rdx, qword [rbp-0x18]
  lea     rbx, [rcx+rdx]
  mov     rdi, rax
  call    malloc
  mov     qword [rbx], rax
  add     dword [rbp-0x24], 0x1

fillMemory:
  mov     eax, dword [rbp-0x24]
  cmp     eax, dword [rbp-0x44]
  jl      fillNextRow

  mov     dword [rbp-0x20], 0x0
  jmp     processRows

processNextElement:
  mov     dword [rbp-0x1c], 0x0
  jmp     jump

addition:
  mov     eax, dword [rbp-0x20]
  cdqe    
  lea     rdx, [rax*8]
  mov     rax, qword [rbp-0x38]
  add     rax, rdx
  mov     rax, qword [rax]
  mov     edx, dword [rbp-0x1c]
  movsxd  rdx, edx
  shl     rdx, 0x2
  add     rax, rdx
  movss   xmm1, dword [rax]
  mov     eax, dword [rbp-0x20]
  cdqe    
  lea     rdx, [rax*8]
  mov     rax, qword [rbp-0x40]
  add     rax, rdx
  mov     rax, qword [rax]
  mov     edx, dword [rbp-0x1c]
  movsxd  rdx, edx
  shl     rdx, 0x2
  add     rax, rdx
  movss   xmm0, dword [rax]
  mov     eax, dword [rbp-0x20]
  cdqe    
  lea     rdx, [rax*8]
  mov     rax, qword [rbp-0x18]
  add     rax, rdx
  mov     rax, qword [rax]
  mov     edx, dword [rbp-0x1c]
  movsxd  rdx, edx
  shl     rdx, 0x2
  add     rax, rdx
  addss   xmm0, xmm1
  movss   dword [rax], xmm0
  add     dword [rbp-0x1c], 0x1

jump:
  mov     eax, dword [rbp-0x1c]
  cmp     eax, dword [rbp-0x48]
  jl      addition

  add     dword [rbp-0x20], 0x1

processRows:
  mov     eax, dword [rbp-0x20]
  cmp     eax, dword [rbp-0x44]
  jl      processNextElement

  mov     rax, qword [rbp-0x18]

done:
  mov     rbx, qword [rbp-0x8]
  leave
  retn
