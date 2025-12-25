# ============================
# FTL Makefile (truly portable)
# ============================

CC   = gcc
FC   = gfortran
NASM = nasm

BUILD = build
OBJ   = $(BUILD)/obj
BIN   = $(BUILD)/bin

CFLAGS   = -std=c11 -Wall -Wextra -O2
INCLUDES = -Isrc/c/include

USE_ASM     ?= 1
USE_FORTRAN ?= 1

ifeq ($(OS),Windows_NT)
    EXE = .exe
    ASM_FORMAT = win64
    NULL = nul
else
    EXE =
    ASM_FORMAT = elf64
    NULL = /dev/null
endif

# ---------------- Sources ----------------

C_SRC = \
    src/c/borealis.c \
    src/c/corona.c \
    src/c/optimizer.c

C_OBJ = $(C_SRC:src/c/%.c=$(OBJ)/c/%.o)

F_SRC = \
    src/fortran/binder.f90 \
    src/fortran/handler.f90

F_OBJ = $(F_SRC:src/fortran/%.f90=$(OBJ)/fortran/%.o)

ASM_DIR = src/asm/x86_64-Windows

ASM_SRC = \
    $(ASM_DIR)/main.asm \
    $(ASM_DIR)/exec.asm

ASM_OBJ = $(ASM_SRC:$(ASM_DIR)/%.asm=$(OBJ)/asm/%.o)

TARGET = build/bin/libftl.a

# ---------------- Default ----------------

all: dirs $(TARGET)

# ---------------- Dirs (portable) ----------------

dirs:
	@mkdir $(BUILD) 2>$(NULL) || true
	@mkdir $(OBJ) 2>$(NULL) || true
	@mkdir $(OBJ)/c 2>$(NULL) || true
	@mkdir $(OBJ)/fortran 2>$(NULL) || true
	@mkdir $(OBJ)/asm 2>$(NULL) || true
	@mkdir $(BIN) 2>$(NULL) || true

# ---------------- Link ----------------

$(TARGET): $(C_OBJ) $(F_OBJ) $(ASM_OBJ)
	ar rcs build/bin/libftl.a $(C_OBJ) $(F_OBJ) $(ASM_OBJ)

# ---------------- C ----------------

$(OBJ)/c/%.o: src/c/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# ---------------- Fortran (optional) ----------------

$(OBJ)/fortran/%.o: src/fortran/%.f90
ifeq ($(USE_FORTRAN),1)
	@$(FC) --version >$(NULL) 2>&1 || (echo warning: gfortran not found && exit 0)
	$(FC) -c $< -o $@
else
	@echo skipping Fortran: $<
endif

# ---------------- ASM (optional) ----------------

$(OBJ)/asm/%.o: $(ASM_DIR)/%.asm
ifeq ($(USE_ASM),1)
	@$(NASM) -v >$(NULL) 2>&1 || (echo warning: nasm not found && exit 0)
	$(NASM) -f $(ASM_FORMAT) $< -o $@
else
	@echo skipping ASM: $<
endif

# ---------------- Clean ----------------

clean:
	@rm -rf $(BUILD) 2>$(NULL) || true

.PHONY: all clean dirs
