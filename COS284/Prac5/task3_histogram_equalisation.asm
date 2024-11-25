section .data
  half_value dd 0.5 , 0; constant value

section .text
    global applyHistogramEqualisation

applyHistogramEqualisation:

  ;prologue
  push    rbp
  mov     rbp, rsp
  sub     rsp, 40
  ;initialize list
  mov     qword [rbp-40], rdi ; get head/first row pointer
  mov     rax, qword [rbp-40] ; set rax = first row 
  mov     qword [rbp-16], rax ; pust first row onto stack for later use

  jmp     check_next_row

go_next_row:
  mov     rax, qword [rbp-16] ; load row
  mov     qword [rbp-8], rax  
  jmp     pixel_loop

calc_cdf:
  mov     rax, qword [rbp-8] 
  movzx   eax, byte [rax+3] ; load cdf

  pxor    xmm1, xmm1   ; clear xmm1

  cvtsi2sd xmm1, eax    ; convert to double
  movsd   xmm0, qword [half_value] ; load 0.5
  addsd   xmm0, xmm1   ; add 0.5
  cvttsd2si eax, xmm0  ; convert to int

  ;check if cdf value is bigger than 255
  mov     dword [rbp-20], eax
  cmp     dword [rbp-20], 255
  jle     check_cdf_less_than_zero

  ;if cdf value is bigger than 255 set cdf value to 255
  mov     dword [rbp-20], 255
  jmp     set_pixel_cdf

check_cdf_less_than_zero:
  ;check if cdf value is less than 0
  cmp     dword [rbp-20], 0
  jge     set_pixel_cdf

  ;if cdf value is less than 0 set cdf value to 0
  mov     dword [rbp-20], 0

set_pixel_cdf:
  mov     edx, dword [rbp-20] ; load cdf value
  mov     rax, qword [rbp-8]   ; load pixel pointer

  mov     byte [rax], dl       ; update R

  mov     byte [rax+1], dl    ; update G

  mov     byte [rax+2], dl    ; update B

  mov     rax, qword [rax+32] ; move to next pixel
  mov     qword [rbp-8], rax  ; move pointer of next pixel onto stack

pixel_loop:
  cmp     qword [rbp-8], 0 ; check for more pixels
  jne     calc_cdf ; go to calc if there are more pixels in row

  ;else move to next row
  mov     rax, qword [rbp-16]  ; get current row
  mov     rax, qword [rax+16]  ; set current row to next row
  mov     qword [rbp-16], rax ; update current row pointer

check_next_row:
  ;check if next row exists
  cmp     qword [rbp-16], 0 
  jne     go_next_row

  ;if not exit , epilogue
  add     rsp , 40
  pop     rbp
  ret