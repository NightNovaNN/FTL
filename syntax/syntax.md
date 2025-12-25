# FTL Syntax Specification

**Version:** v0.0.1
**Status:** Minimal, foundational, intentionally limited

---

## 1. Overview

FTL (Faster Than Light) syntax is designed to be:

- explicit
- predictable
- auditable
- directly mappable to IR

FTL v0.0.1 prioritizes **semantic clarity over expressiveness**.
Many familiar language features are intentionally absent.

This document describes **only what is currently implemented**.

---

## 2. Design Principles

FTL syntax follows these rules:

- No hidden transformations
- No macro system
- No implicit behavior
- No syntax that cannot be directly lowered to IR
- Minimal preprocessing

If behavior is not explicitly written, it does not exist.

---

## 3. Source Structure

FTL source code is:

- line-oriented
- semicolon-terminated
- whitespace-insensitive (outside tokens)
- processed top-to-bottom

Each statement must appear on a single line.

---

## 4. Preprocessing (`Corona` stage)

### 4.1 Include directive

FTL supports **file inclusion only**.

```ftl
include("file.ftl")
```

Rules:

- The path is resolved relative to the current file
- Included files are expanded inline
- Includes are recursive
- No include guards exist yet
- No macros or conditional compilation exist

After preprocessing, the compiler operates on a **single flattened source**.

---

## 5. Lexical Elements

### 5.1 Identifiers

Identifiers consist of:

- letters
- digits
- underscores

They must not start with a digit.

Examples:

```ftl
x
my_var
temp123
```

---

### 5.2 Integer literals

Only **base-10 integer literals** are supported.

Examples:

```ftl
0
42
12345
```

Floating point literals are not supported in v0.0.1.

---

## 6. Variable Declarations

### Syntax

```ftl
<type> <identifier> = <integer>;
```

Example:

```ftl
int x = 5;
```

Notes:

- The type is parsed but **not yet semantically enforced**
- Only integer initialization is supported
- Declaration also performs assignment

---

## 7. Assignment Statements

### Syntax

```ftl
<identifier> = <integer>;
```

Example:

```ftl
x = 10;
```

Notes:

- Assignment from expressions is not supported yet
- The right-hand side must be an integer literal

---

## 8. Binary Arithmetic Expressions

FTL supports explicit binary operations.

### Syntax

```ftl
<dest> = <lhs> <operator> <rhs>;
```

Supported operators:

- `+`
- `-`
- `*`
- `/`

Example:

```ftl
z = x + y;
```

Notes:

- No operator precedence exists
- Expressions must be fully explicit
- Nested expressions are not supported

---

## 9. Return Statements

### Syntax

```ftl
return <lhs> <operator> <rhs>;
```

Example:

```ftl
return x + y;
```

Notes:

- Returning a single value (`return x;`) is not supported yet
- Only binary expressions may be returned

---

## 10. Function Calls

### Syntax

```ftl
<identifier>();
```

Example:

```ftl
print();
```

Notes:

- Function arguments are not supported
- Calls emit a call instruction only
- No return value handling exists yet

---

## 11. Control Flow Markers

FTL currently supports **structural control markers only**.

### Supported keywords

```ftl
if
else if
else
fn
```

Example:

```ftl
fn main
if condition
else if other
else
```

Notes:

- Conditions are not parsed
- No blocks (`{}`) exist yet
- These statements emit IR markers only
- Full control flow semantics will be added in later versions

---

## 12. Whitespace and Empty Lines

- Empty lines are ignored
- Leading and trailing whitespace is ignored
- Statements must still be complete and valid

---

## 13. Unsupported Features (by design)

FTL v0.0.1 does **not** support:

- blocks `{ }`
- scopes
- function parameters
- return values without expressions
- floating point values
- structs or arrays
- macros or metaprogramming
- operator overloading
- implicit conversions

These features may be introduced incrementally in future versions.

---

## 14. Example Program (Complete)

```ftl
include("math.ftl")

fn main

int x = 10;
int y = 20;

z = x + y;
z = z * x;

print();

if condition
else if other_condition
else

return z + y;
```

---

## 15. Summary

FTL v0.0.1 syntax is intentionally minimal.

Its purpose is to:

- validate compiler architecture
- ensure semantic correctness
- enable auditing and reasoning

Syntax complexity will only be added when it can be justified by correctness.

---
