# Audit in FTL

This directory defines how **FTL earns trust**.

FTL is a safety-first language system.
Safety claims are meaningless unless they can be **audited**.

The purpose of `audit/` is to make the compiler:

- Inspectable
- Verifiable
- Explainable
- Hard to accidentally break

This is documentation, not tooling.
Audit starts with **discipline**, not scripts.

---

## What “Audit” Means in FTL

In FTL, _audit_ means:

> A human can reasonably inspect the compiler and determine
> whether it behaves correctly, deterministically, and safely.

Audit is not:

- Blind trust
- Testing alone
- Security theater

Audit is about **evidence and invariants**.

---

## What This Directory Is For

The `audit/` directory exists to:

- Define non-negotiable compiler rules
- Document assumptions explicitly
- Prevent accidental design drift
- Provide a shared mental model for reviewers

Every major design decision in FTL should be **defensible using these documents**.

---

## What This Directory Is NOT For

`audit/` does **not** contain:

- Implementation code
- Test harnesses
- Scripts or automation
- One-off notes

Those belong elsewhere.

Audit documents define **standards**, not mechanisms.

---

## Files in This Directory

### `README.md`

This file.

Explains:

- Why audit exists
- How to read the other audit documents
- How audit fits into FTL’s philosophy

---

### `invariants.md`

Defines **compiler invariants**.

Invariants are rules that must **always** hold:

- Across all compiler stages
- Across all versions
- Across all platforms

If an invariant is violated, it is a **compiler bug**, not undefined behavior.

---

### `checklist.md`

Defines **practical audit discipline**.

This file contains:

- Review checklists
- Pre-merge questions
- Release sanity checks

It exists to turn philosophy into habit.

---

## Who This Is For

This directory is written for:

- Compiler contributors
- Security reviewers
- Language designers
- Future maintainers (including future you)

It assumes:

- Familiarity with systems programming
- Willingness to read carefully
- Preference for correctness over convenience

---

## Audit and the Compiler Pipeline

FTL’s compiler pipeline is:

```
Corona   → Preprocessing
Borealis → IR Construction
Quark    → Optimization
Photon   → Bytecode Generation
```

Audit applies **across all stages**.

No stage is trusted more than another.
No stage is allowed to violate invariants “temporarily”.

---

## Relationship to Other Documentation

Audit documents are **foundational**.

- `architecture.md` explains structure
- `spec/compiler.md` explains required behavior
- `safety.md` explains constraints
- `semantics.md` explains meaning

Audit documents answer:

> “How do we know these guarantees are actually upheld?”

If there is a conflict:

- Audit and invariants take precedence

---

## Audit Is a Process, Not a Phase

Audit does not happen:

- Only before release
- Only after bugs
- Only by experts

Audit happens:

- During design
- During implementation
- During review
- During maintenance

Every change either strengthens auditability or weakens it.

---

## Design Rule

If a feature:

- Cannot be explained clearly
- Cannot be checked against invariants
- Cannot be reviewed with a checklist

Then it **must not be added**.

---

## Final Principle

FTL does not ask users to trust the compiler.

FTL is designed so that:

> Trust can be _earned_ through inspection.

This directory exists to make that possible.

---
