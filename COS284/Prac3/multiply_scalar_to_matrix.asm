;Milan Kruger - u04948123
section .text
    global multiplyScalarToMatrix

multiplyScalarToMatrix: 
  push    rbp
  mov     rbp, rsp
  mov     qword [rbp-0x18], rdi ; array
  movss   dword [rbp-0x1c], xmm0 ; scalar
  mov     dword [rbp-0x20], esi ; total row
  mov     dword [rbp-0x24], edx ; total col
  mov     dword [rbp-0x8], 0x0 ; row count
  jmp     checkRow

newRow:
  mov     dword [rbp-0x4], 0x0 ; set column count to 0
  jmp     newCol

scalarMultiply:
  mov     eax, dword [rbp-0x8] ; set row count to eax
  cdqe    
  lea     rdx, [rax*8] ; let rdx = rax
  mov     rax, qword [rbp-0x18] ; rax = base array pointer (dereference)
  add     rax, rdx ; let rdx = rax
  mov     rax, qword [rax] ; dereference the array to get 2d array
  mov     edx, dword [rbp-0x4] ; let edx = col count
  movsxd  rdx, edx ; let rdx = rdx
  shl     rdx, 0x2 ; let rdx << 2
  add     rax, rdx ; rax += rdx
  movss   xmm0, dword [rax] ; let xmm0 = the objet reference
  mov     eax, dword [rbp-0x8] ; let eax = row count
  cdqe    
  lea     rdx, [rax*8] ; repeat for 2d element
  mov     rax, qword [rbp-0x18]
  add     rax, rdx
  mov     rax, qword [rax]
  mov     edx, dword [rbp-0x4]
  movsxd  rdx, edx
  shl     rdx, 0x2
  add     rax, rdx
  mulss   xmm0, dword [rbp-0x1c] ; multiply scalar with xmm0 , where xmm0 was the pointer to the 2d element
  movss   dword [rax], xmm0 ; make the pointer to the element equal the new value
  add     dword [rbp-0x4], 0x1 ; increase col count

newCol:
  mov     eax, dword [rbp-0x4] ; mov col count to eax
  cmp     eax, dword [rbp-0x24] ; check total col amount with col count
  jl      scalarMultiply ; go to math

  add     dword [rbp-0x8], 0x1 ; if col count = total col then increase row count

checkRow:
  mov     eax, dword [rbp-0x8] ; mov row count to eax
  cmp     eax, dword [rbp-0x20] ; check total row amount with row count
  jl      newRow

  nop     
  nop     
  pop     rbp
  retn     
