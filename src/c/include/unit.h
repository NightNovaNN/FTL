#ifndef FTL_UNIT_H
#define FTL_UNIT_H

// Borealis IR opcodes
typedef enum {
    OP_INVALID = 0,

    // variables
    OP_VAR_DECL,
    OP_VAR_META,
    OP_ASSIGN,

    // templates
    OP_VARTEMP_DEF,
    OP_VARTEMP_USE,

    // functions
    OP_FUNC_BEGIN,
    OP_FUNC_END,
    OP_RETURN,
    OP_RETURN_EXPR,
    OP_CALL,

    // control flow
    OP_IF,
    OP_ELSE_IF,
    OP_ELSE,

    // arithmetic
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_FMA,

    // builtins
    OP_ECHO,
    OP_ECHOF,

    OP_COUNT
} ftl_opcode_borealis;

#endif // FTL_UNIT_H
