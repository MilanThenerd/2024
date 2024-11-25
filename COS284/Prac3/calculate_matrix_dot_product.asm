; Milan Kruger 04948123
segment .text
    global calculateMatrixDotProduct

calculateMatrixDotProduct:
  push    rbp
  mov     rbp, rsp
  mov     qword [rbp-0x18], rdi          ; matrixA
  mov     qword [rbp-0x20], rsi          ; matrixB
  mov     dword [rbp-0x24], edx          ; numRows
  mov     dword [rbp-0x28], ecx          ; numCols
  pxor    xmm0, xmm0
  movss   dword [rbp-0xc], xmm0          ; dotProduct
  mov     dword [rbp-0x8], 0x0          ; rowIdx
  jmp     checkCols

initializeColIdx:
  mov     dword [rbp-0x4], 0x0          ; colIdx
  jmp     computeDotProduct

computeDotProduct:
  mov     eax, dword [rbp-0x8]
  cdqe
  lea     rdx, [rax*8]
  mov     rax, qword [rbp-0x18]
  add     rax, rdx
  mov     rax, qword [rax]
  mov     edx, dword [rbp-0x4]
  movsxd  rdx, edx
  shl     rdx, 0x2
  add     rax, rdx
  movss   xmm1, dword [rax]
  mov     eax, dword [rbp-0x8]
  cdqe
  lea     rdx, [rax*8]
  mov     rax, qword [rbp-0x20]
  add     rax, rdx
  mov     rax, qword [rax]
  mov     edx, dword [rbp-0x4]
  movsxd  rdx, edx
  shl     rdx, 0x2
  add     rax, rdx
  movss   xmm0, dword [rax]
  mulss   xmm0, xmm1
  movss   xmm1, dword [rbp-0xc]
  addss   xmm0, xmm1
  movss   dword [rbp-0xc], xmm0
  add     dword [rbp-0x4], 0x1

  mov     eax, dword [rbp-0x4]
  cmp     eax, dword [rbp-0x28]
  jl      computeDotProduct

  add     dword [rbp-0x8], 0x1

checkCols:
  mov     eax, dword [rbp-0x8]
  cmp     eax, dword [rbp-0x24]
  jl      initializeColIdx

  movss   xmm0, dword [rbp-0xc]
  pop     rbp
  retn
