# The Future of FTL

FTL is intentionally minimal today.
This document defines **where FTL is going**, **what will be added**, and **what will never be compromised**.

This file is a contract with future contributors — including future you.

---

## Guiding Philosophy

FTL exists to be:

- **Auditable**
- **Deterministic**
- **Safety-first**
- **Independent of host languages**

Every future change must strengthen these principles.

---

## Versioned Roadmap

## v0.0.2 — Photon Introduction

**Status:** Planned

### Photon: Bytecode Generator

Photon will be introduced **after v0.0.2** as a first-class module.

#### Goals

- Lower optimized IR into bytecode
- Eliminate ambiguous backend behavior
- Increase safety by enforcing strict IR-to-bytecode rules

Photon is expected to be **more restrictive than earlier stages**, not more permissive.

> The closer code gets to execution, the stricter the rules become.

---

## v0.0.3 — Standard Library + Independence

**Status:** Planned

### Standard Library (stdlib)

A minimal, safety-focused standard library will be added.

#### Characteristics

- Explicit APIs
- No hidden allocations
- Deterministic behavior only
- Fully auditable implementation

The stdlib will be treated as **part of the language contract**, not a convenience layer.

---

### Removal of C Dependency

As of v0.0.3, FTL aims to be **independent of C test drivers**.

#### Current State

- FTL currently requires a `.c` test driver
- Execution and testing rely on host C code

#### Target State

- Native FTL entry points
- No mandatory C glue code
- Clear runtime boundary

C may still be used internally — but it will no longer be required to _use_ FTL.

---

## Near-Term Goals (General)

### Stable IR Specification

- Lock Borealis IR semantics
- Version IR explicitly
- Document every IR construct

---

### Stronger Validation

- More aggressive preprocessing checks
- Earlier rejection of unsafe constructs
- Clearer diagnostics

Fail-fast remains a feature.

---

### Safer Optimizations

- Expand Quark passes
- Preserve strict determinism
- Reject unclear transformations

Optimization will never outrank safety.

---

## Medium-Term Ideas (Exploration Zone)

These ideas are possible, but not guaranteed.

- Alternative backends
- IR visualization tools
- Audit and verification tooling
- Debug-focused bytecode formats

Only ideas that **expose internals** are welcome.

---

## Long-Term Vision

FTL aims to become:

- A reference safety-first language
- A teaching-grade compiler architecture
- A foundation for secure systems work

Performance matters.
Correctness matters more.

---

## Explicit Non-Goals

FTL will never include:

- JIT compilation
- Runtime guessing
- Undefined behavior for speed
- Implicit execution paths
- Optimizations that obscure intent

If something cannot be explained clearly, it does not belong.

---

## Backward Compatibility

- Source compatibility preferred
- IR compatibility versioned
- Bytecode compatibility explicit

Breaking changes must be obvious and justified.

---

## Final Word

FTL is not trying to be clever.
FTL is trying to be **right**.

That choice guides every version.

---
