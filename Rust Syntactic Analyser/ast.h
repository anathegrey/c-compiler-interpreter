// AST definitions
#ifndef __ast_h__
#define __ast_h__

// AST for expressions
#define bool int
#define true 1
#define false 0

typedef struct _Expr Expr; // Convenience typedef

struct _Expr {
  enum { E_INTEGER, E_OPERATION, E_VAR, E_BOOL, IF_CON, ELSE_CON }kind;
  union {
    int value; // for integer values
    char *var;
    bool b_value;
    struct { 
      int operator; // PLUS, MINUS, etc 
      struct _Expr* left;
      struct _Expr* right;
    }op; // for binary expressions
    struct {
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
      }if_op;
    }if_else;
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

typedef struct _Cmd Cmd;

struct _Cmd {
  enum { EXPR, CMD_WHILE, CMD_PRINT, CMD_READ, ATTRIB_EXPR, ATTRIB_IF }kind;
  union {
    struct _Expr *cmd;
    struct {
      char *var;
      union {
	struct _Expr *expr;
	struct _CmdList *cmdif;
      }attrib_op;
    }attrib;
    struct {
      struct _BoolExpr *while_state;
      struct _CmdList *while_condition;
    }while_op;
    struct {
      struct _Expr *expr;
    }print;
    struct {
      char *var;
      char *aux_var;
    }read;
  }cmd_attr;
};

typedef struct _CmdList CmdList;

struct _CmdList {
  struct _Cmd *cmd;
  struct _CmdList *next;
};

// Constructor functions (see implementation in ast.c)
Expr* ast_integer(int v);
Expr* ast_operation(int operator, Expr* left, Expr* right);
Expr *ast_equal(Expr *left, Expr *right);
Expr *ast_var(char *v);
Expr *ast_bool(bool v);
Expr *if_operation(BoolExpr *if_state, CmdList *if_condition);
Expr *else_operation(BoolExpr *if_state, CmdList *if_condition, CmdList *else_condition);

BoolExpr *ast_boperation(int operator, Expr *left, Expr *right);

Cmd *exp_operation(Expr *e);
Cmd *while_operation(BoolExpr *while_state, CmdList *while_condition);

Cmd *attrib_operation(char *var, Expr *expr);
//Cmd *attribif_operation(char *var, CmdList *cmdif);

Cmd *read_operation(char *var);

Cmd *print_operation(Expr *expr);

CmdList *list_operation(Cmd *head, CmdList *tail);

#endif
