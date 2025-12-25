# FTL API Reference

This document describes the internal APIs of the FTL compiler/runtime.
Each section corresponds to a source file and documents **every function** with a short, practical description.

> Philosophy: small functions, explicit intent, safety-first behavior.

---

## `borealis.c`

**Purpose:** Core utilities for diagnostics, logging, and runtime sanity checks.

### `void ftl_panic(const char *msg)`

Immediately aborts execution with a fatal error message.
Used when the program reaches an unrecoverable state.

---

### `void ftl_warn(const char *msg)`

Prints a non-fatal warning message.
Execution continues, but the issue should be inspected.

---

### `void ftl_info(const char *msg)`

Prints an informational message for debugging or verbosity modes.

---

### `int ftl_assert(int condition, const char *msg)`

Checks a condition at runtime.

- If `condition` is false, triggers `ftl_panic`
- Returns `1` if condition is true

Used for enforcing invariants across the compiler.

---

## `corona.c`

**Purpose:** Frontend processing and high-level compilation flow.

### `void corona_init(void)`

Initializes Corona’s internal state.
Must be called before any Corona-related operation.

---

### `int corona_parse(const char *source)`

Parses a source string into internal structures.

- Returns `0` on success
- Non-zero on parse failure

---

### `int corona_validate(void)`

Performs semantic and safety validation passes.
Ensures the parsed program follows FTL’s safety rules.

---

### `void corona_shutdown(void)`

Cleans up all Corona-allocated resources.
Safe to call multiple times.

---

## `optimizer.c`

**Purpose:** Optimization passes applied after validation.

### `void optimizer_init(void)`

Initializes optimizer state and pass registry.

---

### `void optimizer_run(void)`

Executes all registered optimization passes in order.
Should only be called after successful validation.

---

### `void optimizer_cleanup(void)`

Frees optimizer-specific memory and state.

---

### `int optimizer_constant_fold(void)`

Performs constant folding on expressions.

- Returns number of optimizations applied

---

### `int optimizer_dead_code_elim(void)`

Removes unreachable or unused code paths.
Improves safety and output size.

---

## General Notes for Contributors

- All functions are **explicit by design** — no hidden side effects
- Fatal paths must go through `ftl_panic`
- Validation **always** happens before optimization
- Optimizers must be deterministic and auditable

If you’re new:

1. Start with `corona_parse`
2. Follow the flow into validation
3. Study optimizers last

---
