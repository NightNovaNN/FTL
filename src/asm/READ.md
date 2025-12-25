# For Contributors

### If you came here from `Contributing.md`, please read this carefully

Currently, my development environment is limited to **x86-64 Windows**, and I’m unable to test or maintain platform-specific ASM code for other architectures or operating systems.

This does **not** affect general development:

- The **C backend is always the reference and fallback**
- ASM and Fortran backends are **optional optimizations only**

If you wish to add or improve an **ASM backend** for another architecture or OS, your help is very welcome.

---

### Adding a new ASM backend

If you are working on an architecture or OS other than **x86-64 Windows**, you may:

- Write and test a `.asm` file for your target
- Ensure it cleanly falls back to the C backend on failure

After implementation:

- Test your changes (see `docs/compile.md`)
- Add a new subfolder under `src/asm` using the format:

  - `Architecture-OS`
  - Example: `ARM64-Linux`

- Include a `docs.md` file describing:

  - Architecture and OS compatibility
  - Build and compile instructions
  - Common errors
  - Debugging tips

---
