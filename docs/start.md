# Getting Started with FTL 🚀

Welcome to **FTL (Faster Than Light)** 👋
FTL is a **safety-first, auditable programming language** designed to be simple to understand and hard to misuse.

This guide is for:

- Beginners
- Curious devs
- People who want to _read and hack the code_, not fight it

No compiler PhD required 🧠✨

---

## What Is FTL? 🤔

FTL is a language system built around one idea:

> If something is unsafe or unclear, the compiler should stop.

FTL prefers:

- Explicit behavior
- Deterministic execution
- Human-readable internals

It is _not_ trying to be fancy.
It _is_ trying to be correct.

---

## How FTL Works (Big Picture)

FTL processes code in **four clear stages**:

```sh
Corona   → cleans & preprocesses code
Borealis → turns code into IR (structure + meaning)
Quark    → safely optimizes the IR
Photon   → generates bytecode
```

Each stage has **one job**.
Nothing sneaky happens behind your back

---

## What You Need 🛠️

### Required

- A **C compiler** (GCC or Clang)
- **Make**
- A terminal
- A little curiosity

### Optional

- Fortran compiler (optional modules)
- Assembler (optional modules)

FTL keeps dependencies minimal on purpose.

---

## Building FTL 🧱

From the project root, run:

```sh
make
```

If everything works, you’ll see build outputs in:

```
build/bin/
```

Example:

```
libftl.a
```

Congrats 🎉 you built FTL.

---

## Running Tests / Experiments 🧪

Right now, FTL uses a **C test driver** to experiment with the system.

Example:

```sh
gcc test.c build/bin/libftl.a -o test
./test
```

> ⚠️ Note
> This is temporary.
> FTL plans to remove the C dependency after **v0.0.3**.

---

## Where Should Beginners Start Reading Code?

If you’re new, **don’t read everything at once**. Start here

### 1️⃣ `corona/` – Preprocessing

Good for understanding:

- Input handling
- Early validation
- How FTL rejects bad code

---

### 2️⃣ `borealis.c` – IR Builder

This is the **heart of FTL** ❤️
You’ll learn:

- How code becomes structure
- How meaning is represented safely

---

### 3️⃣ `quark/` – Optimizer

Only read this once you’re comfy.
This is about:

- Improving IR
- Never changing meaning

---

### 4️⃣ `photon/` – Bytecode (later)

Photon comes after v0.0.2 and focuses on:

- Lowering IR
- Safe execution formats

---

## Beginner Rules (Very Important)

- Don’t add features everywhere — **pick the right module**
- If behavior is unclear, **reject it**
- Small, boring code is good code
- Read `architecture.md` before big changes

FTL rewards patience.

---

## How to Contribute (First Steps) 🤝

Good beginner contributions:

- Better error messages
- Comments & docs
- Small validation rules
- Simple IR helpers

You don’t need to be fast — you need to be careful.

---

## If You’re Confused, That’s Normal 😄

FTL is designed so that:

- Confusion means the design can improve
- Questions are signals, not weakness

Open issues. Ask questions. Read slowly.

---
