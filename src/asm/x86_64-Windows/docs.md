# x86_64-Windows ASM Backend

This directory contains the **optional x86-64 Windows assembly backend** for FTL.

The ASM backend is **not required** for correctness or functionality.
It exists only as a **performance-oriented, best-effort optimization layer**.

If this backend is unavailable, fails to assemble, or fails at runtime,  
FTL will **automatically fall back to the reference C backend**.

---

## Architecture

- Architecture: x86-64 (AMD64)
- Operating System: Windows
- Assembler: NASM
- ABI: Windows x64 ABI

All ASM entry points must follow the Windows x64 calling convention.

---

## Purpose

The current ASM implementation is intentionally minimal.

Its goals are:

- Define a stable ABI for future optimization work
- Provide a safe extension point for contributors
- Ensure zero impact on correctness if ASM is disabled

At present, the ASM backend performs **no semantic transformations**.

---

## Build Notes

- NASM must be available in `PATH`
- ASM is enabled only when explicitly requested via build flags
- Failure to assemble or link this backend does **not** fail the build

Refer to `docs/compile.md` for full build instructions.

---

## Fallback Behavior

If the ASM backend:

- is missing
- fails to assemble
- fails to link
- reports failure at runtime

FTL will emit a warning similar to:

```sh
warning: asm and fortran failed, C backend fallback deployed
```

Compilation and execution will continue using the C backend.

---

## Debugging Tips

- If you encounter issues, first disable ASM and verify the C backend
- ASM functions should return `0` if no optimization is applied
- Avoid memory allocation, I/O, or global state in ASM
- Keep changes small and isolated

When in doubt, return failure and let the C backend handle execution.

---

## Contributor Notes

- You are **not required** to modify ASM when changing C code
- ASM backends must never be relied upon for correctness
- All behavior must match the C backend exactly when enabled

This backend is designed to be safe, replaceable, and optional.

---
