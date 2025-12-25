# Safety in FTL

FTL is a **safety-first language system**.
Safety is not an add-on, a mode, or a compiler flag — it is the **default and non-negotiable behavior**.

This document defines what _safety_ means in FTL and how the compiler enforces it.

---

## What “Safety” Means in FTL

In FTL, _safe_ means:

- No undefined behavior
- No ambiguous semantics
- No silent failure
- No guessing programmer intent

If the compiler cannot prove something is safe, it **rejects the program**.

---

## Core Safety Principles

### 1. Fail Fast

FTL prefers **early failure** over late surprises.

- Invalid code → compilation error
- Unsafe construct → compilation error
- Internal invariant broken → immediate panic

Continuing in an unsafe state is forbidden.

---

### 2. Explicit Over Implicit

FTL rejects:

- Implicit control flow
- Hidden state changes
- Magic defaults

All behavior must be:

- Visible
- Traceable
- Explainable

If a human cannot reason about it, the compiler won’t allow it.

---

### 3. Determinism Is Safety

A program that behaves differently on different runs is unsafe.

FTL guarantees:

- Identical input → identical output
- No time-based behavior
- No randomness unless explicitly modeled

Nondeterminism is treated as a safety violation.

---

## Compiler-Enforced Safety

Safety is enforced **at every stage** of the compiler.

---

## Corona — Preprocessing Safety

Corona ensures:

- Source input is structurally valid
- Ambiguous syntax is rejected
- Invalid constructs never reach later stages

Corona does **not** attempt recovery.
Unclear input is unsafe input.

---

## Borealis — Structural Safety

Borealis enforces safety by:

- Building fully explicit IR
- Representing all control flow directly
- Attaching semantic and safety metadata

Every IR node:

- Has defined meaning
- Has defined constraints
- Cannot rely on host-language behavior

If meaning cannot be encoded safely, IR construction fails.

---

## Quark — Optimization Safety

Quark is the **most restricted** module.

Optimizations must:

- Preserve meaning exactly
- Be deterministic
- Be locally provable

Forbidden behaviors:

- “Probably safe” rewrites
- Heuristic-based transformations
- Optimizations that obscure logic

Performance never outranks safety.

---

## Photon — Execution Safety

Photon enforces safety at the execution boundary.

Photon guarantees:

- Strict IR → bytecode mapping
- No implicit execution rules
- No hidden runtime behavior

Bytecode must be:

- Fully specified
- Platform-independent
- Free of undefined behavior

Photon is allowed to be strict, slow, and boring.
That is a feature.

---

## Memory & State Safety

FTL aims to:

- Avoid implicit memory ownership
- Prevent untracked state mutation
- Make all effects explicit in IR

If memory behavior cannot be reasoned about, it is unsafe.

---

## Host Language Safety (C, etc.)

FTL may be **implemented in C**, but:

- C undefined behavior MUST NOT leak into FTL semantics
- Compiler correctness MUST NOT depend on UB
- Safety violations in host code are considered compiler bugs

The language is safer than its implementation language.

---

## What FTL Will Never Allow

FTL explicitly forbids:

- Undefined behavior for performance
- Silent overflow or truncation
- Implicit control flow
- Speculative execution
- “Trust me bro” semantics

If a feature requires trust, it does not belong.

---

## Safety vs Performance

FTL always chooses:

> **Correctness > Safety > Performance**

If performance requires sacrificing safety, the feature is rejected.

---

## Reporting Safety Issues

Any of the following are considered **critical issues**:

- Programs behaving inconsistently
- Compiler continuing after unsafe states
- Ambiguous or undocumented behavior

Safety bugs have priority over all features.

---

## Final Rule

If the compiler cannot:

- Prove it safe
- Explain it clearly
- Enforce it strictly

Then the program **does not compile**.

No exceptions.

---
