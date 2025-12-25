; exec.asm
; Photon execution backend (x86-64 Windows, NASM)
; Optional low-level execution / glue layer

global photon_exec

section .text

; int photon_exec(void* entry)
; RCX = entry point (function pointer)
; returns int status code
photon_exec:
    test rcx, rcx
    jz .fail

    ; call entry()
    call rcx

    ; success
    xor eax, eax
    ret

.fail:
    ; invalid entry point
    mov eax, 1
    ret
