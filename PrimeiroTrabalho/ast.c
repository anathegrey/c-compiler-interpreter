// AST constructor functions

#include <stdlib.h> // for malloc
#include "ast.h" // AST header

Expr* ast_integer(int v) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_INTEGER;
  node->attr.value = v;
  return node;
}

Expr* ast_operation(int operator, Expr* left, Expr* right) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_OPERATION;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}

Expr *ast_var(char *var) {
  Expr *node = (Expr *)malloc(sizeof(Expr));
  node -> kind = E_VAR;
  node -> attr.var = var;
  return node;
}

BoolExpr *ast_boperation(int operator, Expr *left, Expr *right) {
  BoolExpr *node = (BoolExpr *)malloc(sizeof(BoolExpr));
  node -> bool_op.bool_operator = operator;
  node -> bool_op.left = left;
  node -> bool_op.right = right;
  return node;
}

CmdIf *if_operation(BoolExpr *if_state, CmdList *if_condition) {
  CmdIf *node = (CmdIf *)malloc(sizeof(CmdIf));
  node -> cmdif_kind = IF_STATEMENT;
  node -> cmdif_attr.if_statement.if_state = if_state;
  node -> cmdif_attr.if_statement.if_condition = if_condition;
  return node;
}

CmdIf *else_operation(BoolExpr *if_state, CmdList *if_condition, CmdList *else_condition) {
  CmdIf *node = (CmdIf *)malloc(sizeof(CmdIf));
  node -> cmdif_kind = ELSE_STATEMENT;
  node -> cmdif_attr.else_statement.if_state = if_state;
  node -> cmdif_attr.else_statement.if_condition = if_condition;
  node -> cmdif_attr.else_statement.else_condition = else_condition;
  return node;
}

CmdWhile *while_operation(BoolExpr *while_state, CmdList *while_condition) {
  CmdWhile *node = (CmdWhile *)malloc(sizeof(CmdWhile));
  node -> cmdwhile_attr.while_state = while_state;
  node -> cmdwhile_attr.while_condition = while_condition;
  return node;
}

Attrib *attrib_operation(char *var, Expr *expr) {
  Attrib *node = (Attrib *)malloc(sizeof(Attrib));
  node -> var = var;
  node -> attrib_kind = ATTRIB_EXPR;
  node -> attrib_attrib.expr = expr;
  return node;
}

Attrib *attribif_operation(char *var, CmdList *cmdif) {
  Attrib *node = (Attrib *)malloc(sizeof(Attrib));
  node -> var = var;
  node -> attrib_kind = ATTRIB_IF;
  node -> attrib_attrib.cmdif = cmdif;
  return node;
}

Readln *read_operation(char *var) {
  Readln *node = (Readln *)malloc(sizeof(Readln));
  node -> var = var;
  return node;
}

Println *print_operation(Expr *expr) {
  Println *node = (Println *)malloc(sizeof(Println));
  node -> expr = expr;
  return node;
}

CmdList *list_operation(CmdSeq *cmd, CmdList *next) {
  CmdList *node = (CmdList *)malloc(sizeof(CmdList));
  node -> cmd = cmd;
  node -> next = next;
  return node;
}
