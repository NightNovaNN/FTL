# Compiling FTL

This document explains how to **build FTL from source**, what each build step does, and how to debug common issues.

FTL uses a **simple, explicit build pipeline**. No magic. No hidden scripts.

---

## Requirements

### Mandatory

- **C compiler**

  - GCC or Clang recommended

- **Make**
- **POSIX-compatible shell**

### Optional

- **Fortran compiler** (for Fortran-based modules)
- **Assembler** (if enabling ASM components)

FTL is designed to compile on minimal systems.

---

## Repository Structure (Relevant to Build)

```sh
build/
├── bin/        # Final static libraries / binaries
└── obj/        # Intermediate object files

audit/          # Safety and audit tooling
docs/           # Documentation
```

Source files are compiled into object files and then linked into static libraries.

---

## Basic Build

From the project root:

```sh
make
```

This will:

1. Compile all C source files
2. Compile optional Fortran / ASM files (if enabled)
3. Produce static libraries in `build/bin`

Example output:

```
build/bin/libftl.a
```

---

## Build Stages (What Actually Happens)

FTL builds in **clear stages**, mirroring the architecture.

### 1. Corona — Preprocessor

- Compiled first
- No dependency on IR or optimizer
- Produces frontend logic only

---

### 2. Borealis — IR Builder

- Depends on Corona
- Compiles IR construction logic
- Produces object files for IR handling

---

### 3. Quark — Optimizer

- Depends on Borealis
- Compiles optimization passes
- No backend dependencies

---

### 4. Photon — Bytecode Generator

- Final compilation stage
- Depends on optimized IR
- Produces bytecode emission logic

---

## Object File Layout

Compiled objects are grouped by language:

```sh
build/obj/
├── c/          # C object files
├── fortran/    # Fortran object files (optional)
└── asm/        # Assembly object files (optional)
```

This separation keeps the build auditable and debuggable.

---

## Cleaning the Build

To remove all compiled artifacts:

```sh
make clean
```

This deletes:

- `build/obj/*`
- `build/bin/*`

Source files are never touched.

---

## Debug Build

To compile with debug symbols:

```sh
make DEBUG=1
```

Typical effects:

- `-g` enabled
- Optimizations reduced or disabled
- Extra diagnostics available

Recommended when hacking Borealis or Quark.

---

## Common Build Errors & Fixes

### ❌ `cc: command not found`

Install a C compiler (GCC or Clang)

---

### ❌ Undefined references during linking

Ensure:

- All required object files are included
- Optional Fortran/ASM components are either enabled or disabled consistently

---

### ❌ Fortran compiler errors

Either:

- Install a Fortran compiler
- Or disable Fortran components in the Makefile

---

## Portability Notes

- FTL avoids compiler-specific extensions
- Static linking is preferred
- Platform-specific logic must be isolated

If it builds, it should behave the same everywhere.

---
