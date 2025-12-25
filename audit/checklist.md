# FTL Audit Checklist

This checklist turns FTL’s safety and audit philosophy into **daily practice**.

Every significant change to the compiler **must be reviewed against this checklist**.
Unchecked items are treated as **red flags**, not suggestions.

---

## How to Use This Checklist

- Reviewers should actively check items, not skim
- Authors should self-review before submitting changes
- If an item cannot be checked, the change is not ready

This checklist complements:

- `audit/invariants.md`
- `spec/compiler.md`
- `safety.md`
- `semantics.md`

---

## 1. General Change Checklist

Before merging any change:

- [ ] Can this change be explained clearly to another human?
- [ ] Does this change preserve all documented semantics?
- [ ] Does this change preserve determinism?
- [ ] Is all behavior explicit and specified?
- [ ] Does this avoid introducing undefined or ambiguous behavior?

If any answer is **no**, stop.

---

## 2. Stage Responsibility Checklist

Confirm the change is in the correct stage:

- [ ] Corona changes affect only preprocessing
- [ ] Borealis changes affect only IR construction
- [ ] Quark changes affect only optimization
- [ ] Photon changes affect only bytecode generation

No stage may perform work belonging to another.

---

## 3. Corona Checklist (Preprocessing)

- [ ] Does this reject ambiguous or malformed input?
- [ ] Does this avoid guessing programmer intent?
- [ ] Is the output canonical and deterministic?
- [ ] Are errors explicit and early?

Corona must never recover silently.

---

## 4. Borealis Checklist (IR)

- [ ] Is all control flow explicitly represented?
- [ ] Are all IR nodes fully defined and valid?
- [ ] Is IR independent of host-language behavior?
- [ ] Is unsafe input rejected during IR construction?

IR correctness is non-negotiable.

---

## 5. Quark Checklist (Optimization)

- [ ] Does the optimization preserve semantics exactly?
- [ ] Is the transformation deterministic?
- [ ] Can the correctness be proven locally?
- [ ] Does the program behave correctly with this optimization disabled?

If proof is unclear, the optimization is invalid.

---

## 6. Photon Checklist (Bytecode)

- [ ] Does bytecode exactly reflect IR semantics?
- [ ] Is all bytecode behavior fully specified?
- [ ] Is the output platform-independent?
- [ ] Are there no hidden execution rules?

Photon must obey IR, not reinterpret it.

---

## 7. Error Handling Checklist

- [ ] Are all errors explicit?
- [ ] Does the compiler fail fast on invalid states?
- [ ] Are internal invariant violations treated as bugs?
- [ ] Is there no silent recovery?

Error handling must never hide problems.

---

## 8. Safety & Security Checklist

- [ ] Does this change strengthen or preserve safety?
- [ ] Does this avoid increasing the trusted code base?
- [ ] Does this reduce or maintain attack surface?
- [ ] Can this be audited by inspection?

Security through clarity, not obscurity.

---

## 9. Compatibility Checklist

- [ ] Does this introduce a breaking change?
- [ ] Is the breaking change documented clearly?
- [ ] Is the reason for the break justified?
- [ ] Are users warned explicitly?

Silent breaks are forbidden.

---

## 10. Final Gate

Before merging or releasing:

- [ ] All relevant checklist items are checked
- [ ] No invariants are violated
- [ ] The change improves or preserves auditability

If any doubt remains, **do not merge**.

---

## Closing Rule

> **When in doubt, choose clarity.
> When still in doubt, reject the change.**

This checklist exists to protect FTL from accidental complexity.

---
