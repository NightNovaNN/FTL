# FTL Architecture

FTL (Faster Than Light) is a **modular, safety-first language system** designed for auditability, determinism, and explicit control.

The system is divided into **four strictly ordered modules**, each with a single responsibility and a clean interface.

So far, only `Corona`, `Borealis` and `Quark` exist, Photon will come after `v0.0.2`.

---

## High-Level Pipeline

```py
Source Code
   ↓
[ Corona ]   – Preprocessing
   ↓
[ Borealis ] – IR Construction
   ↓
[ Quark ]    – Optimization
   ↓
[ Photon ]   – Bytecode Generation
```

Each module:

- Consumes a well-defined input
- Produces a deterministic output
- Does not skip or merge responsibilities

No stage performs work that belongs to another.

---

## Core Design Principles

### Safety First

FTL rejects unsafe or invalid programs immediately.

- No undefined behavior
- No silent recovery
- No speculative execution

If the system is unsure, it **fails fast**.

---

### Explicit Control Flow

There are:

- No hidden passes
- No implicit transformations
- No magical state changes

Every transformation is intentional and traceable.

---

### Auditable by Humans

FTL is written so that:

- A C developer can read it
- A security reviewer can audit it
- A contributor can extend it confidently

Small modules. Small functions. Clear naming.

---

## Module Breakdown

---

## Corona — Preprocessor

**Role:** Prepare raw source code for compilation.

### Responsibilities

- Source normalization
- Macro handling (if any)
- Include / dependency resolution
- Early syntax sanity checks

### Output

- Cleaned, canonical source representation

Corona **does not**:

- Build IR
- Optimize
- Generate bytecode

Its job is simple:

> “Turn messy input into something safe to analyze.”

---

## Borealis — IR Builder

**Role:** Convert preprocessed source into a structured Intermediate Representation (IR).

### Responsibilities

- Build AST / IR nodes
- Encode control flow explicitly
- Attach type and safety metadata

### Output

- Fully-formed IR suitable for analysis and optimization

Borealis is where **meaning becomes structure**.

---

## Quark — Optimizer

**Role:** Improve IR without changing semantics.

### Responsibilities

- Constant folding
- Dead code elimination
- Structural simplifications

### Rules

- Optimizations must be deterministic
- Optimizations must preserve meaning
- Optimizations must be auditable

If an optimization is clever but hard to prove — it doesn’t belong here.

---

## Photon — Bytecode Generator

**Role:** Lower optimized IR into executable bytecode.

### Responsibilities

- Instruction selection
- Bytecode emission
- Metadata generation for runtime or tooling

### Output

- Platform-independent bytecode

Photon **never**:

- Rewrites logic
- Performs optimizations
- Infers intent

Photon obeys the IR. Nothing more.

---

## Data Flow Guarantees

- Corona output is immutable once Borealis starts
- Borealis IR is frozen before Quark runs
- Quark produces a final IR snapshot
- Photon consumes IR in read-only mode

This guarantees:

- No cross-stage corruption
- Easier debugging
- Safe parallel development

---

## Error Handling Model 🚨

FTL follows a **fail-fast** philosophy.

| Situation                 | Action     |
| ------------------------- | ---------- |
| Invalid input             | Hard error |
| Unsafe construct          | Hard error |
| Internal invariant broken | Panic      |
| Optional issue            | Warning    |

There is no undefined state.

---

## Extending FTL

### Adding a new preprocessing rule

→ Corona

### Adding a new language feature

→ Borealis (IR)

### Adding a new optimization

→ Quark

### Adding a new backend / format

→ Photon

If you’re unsure where something belongs — it probably doesn’t belong anywhere yet.

---
