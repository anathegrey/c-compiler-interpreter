
// AST definitions
#ifndef __ast_h__
#define __ast_h__

// AST for expressions
typedef struct _Expr Expr; // Convenience typedef

struct _Expr {
  enum { 
    E_INTEGER, E_OPERATION, E_VAR, E_BOOL }kind;
  union {
    int value; // for integer values
    char *var;
    struct { 
      int operator; // PLUS, MINUS, etc 
      struct _Expr* left;
      struct _Expr* right;
    } op; // for binary expressions
  } attr;
};

typedef struct _BoolExpr BoolExpr;

struct _BoolExpr {
  struct {
    int bool_operator;
    struct _Expr *left;
    struct _Expr *right;
  }bool_op;
};

typedef struct _CmdSeq CmdSeq;

struct _CmdSeq {
  enum { CMD_ATTRIB, CMD_IF, CMD_PRINT, CMD_READ, CMD_WHILE }cmdseq_kind;
  union {
    struct _Attrib *cmdAttrib;
    struct _CmdIf *cmdIf;
    struct _Println *cmdPrint;
    struct _Readln *cmdRead;
    struct _CmdWhile *cmdWhile;
  }cmdseq_attr;
};

typedef struct _CmdList CmdList;

struct _CmdList {
  struct _CmdSeq *cmd;
  struct _CmdList *next;
};

typedef struct _CmdIf CmdIf;

struct _CmdIf {
  enum { IF_STATEMENT, ELSE_STATEMENT }cmdif_kind;
  union {
    struct {
      struct _BoolExpr *if_state;
      struct _CmdList *if_condition;
    }if_statement;
    struct {
      struct _BoolExpr *if_state;
      struct _CmdList *if_condition;
      struct _CmdList *else_condition;
    }else_statement;
  }cmdif_attr;
};


typedef struct _CmdWhile CmdWhile;

struct _CmdWhile {
  struct {
    struct _BoolExpr *while_state;
    struct _CmdList *while_condition;
  }cmdwhile_attr;
};


typedef struct _Attrib Attrib;

struct _Attrib {
  char *var;
  enum { ATTRIB_EXPR, ATTRIB_IF }attrib_kind;
  union {
    struct _Expr *expr;
    struct _CmdList *cmdif;
  }attrib_attrib;
};


typedef struct _Readln Readln;

struct _Readln {
  char *var;
  char *aux_var;
};


typedef struct _Println Println;

struct _Println {
  struct _Expr *expr;
};

// Constructor functions (see implementation in ast.c)
Expr* ast_integer(int v);
Expr* ast_operation(int operator, Expr* left, Expr* right);
Expr *ast_var(char *v);

BoolExpr *ast_boperation(int operator, Expr *left, Expr *right);

CmdIf *if_operation(BoolExpr *if_state, CmdList *if_condition);
CmdIf *else_operation(BoolExpr *if_state, CmdList *if_condition, CmdList *else_condition);

CmdWhile *while_operation(BoolExpr *while_state, CmdList *while_condition);

Attrib *attrib_operation(char *var, Expr *expr);
Attrib *attribif_operation(char *var, CmdList *cmdif);

Readln *read_operation(char *var);

Println *print_operation(Expr *expr);

CmdList *list_operation(CmdSeq *cmd, CmdList *next);

#endif
