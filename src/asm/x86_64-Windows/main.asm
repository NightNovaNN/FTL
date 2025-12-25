; main.asm
; Quark ASM backend (x86-64 Windows, NASM)
; Optional optimizer backend
; Returns 1 if optimization applied, 0 otherwise

global quark_asm_opt

section .text

; int quark_asm_opt(ftl_ir_inst* ir, size_t count)
; Windows x64 ABI:
; RCX = ir pointer
; RDX = count
quark_asm_opt:
    ; no-op backend
    ; report "not applied"

    xor eax, eax        ; return 0
    ret
