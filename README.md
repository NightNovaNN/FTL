# FTL (Faster Than Light) — v0.0.1

FTL is a **safety-first, auditable systems programming language** focused on correctness, explicit behavior, and low-level control.

The project prioritizes:

- auditability over magic
- predictable compilation
- minimal hidden behavior

FTL is currently in **early development**. Expect breaking changes.

---

## Key Goals

- 🛡️ Safety-first language design
- 🔍 Audit-friendly compiler and runtime
- ⚙️ Low-level control without unnecessary abstraction
- 🧠 Clear semantics and well-defined behavior

---

## Tech Stack

Core implementation:

- **C** (primary)

Optional / supporting:

- **Fortran** (numerical / backend components)
- **Assembly** (architecture-specific logic)

---

## Project Structure

```sh
.
├── src/            # Current compiler and language sources
│   ├── asm/        # Assembly backends
│   ├── c/          # Core C implementation
│   ├── fortran/    # Optional Fortran components
│   └── spec/       # Language specifications
│
├── docs/           # High-level documentation
│   ├── api.md
│   ├── architecture.md
│   ├── compile.md
│   └── future.md
│
├── audit/          # Audit-related notes and experiments
├── legacy/         # Old / deprecated implementation (ignored in builds)
├── build/          # Build artifacts (gitignored)
│
├── Makefile
├── LICENSE
└── README.md
```

---

## Documentation

Start here if you’re new:

- `docs/start.md` — project overview
- `docs/architecture.md` — internal design
- `docs/compile.md` — build process
- `src/spec/` — language semantics & safety model

---

## Build (early-stage)

FTL currently uses a **Makefile-based** build system.

```bash
make
```

Build artifacts are placed in `build/` and are intentionally not tracked.

---

## Status

- 🚧 Early development
- 🧪 Actively experimenting with language design
- ❗ Not production-ready

---

## Contributing

Contributions are welcome, especially:

- compiler improvements
- safety analysis
- documentation
- audits and reviews

See `Contributing.md` for guidelines.

---

## License

Licensed under the terms in the `LICENSE` file.

---
