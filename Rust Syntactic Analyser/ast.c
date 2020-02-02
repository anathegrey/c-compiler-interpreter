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

Expr *ast_bool(bool v) {
  Expr *node = (Expr *)malloc(sizeof(Expr));
  node -> kind = E_BOOL;
  node -> attr.b_value = v;
  return node;
}

Expr *if_operation(BoolExpr *if_state, CmdList *if_condition) {
  Expr *node = (Expr *)malloc(sizeof(Expr));
  node -> kind = IF_CON;
  node -> attr.if_else.if_op.if_statement.if_state = if_state;
  node -> attr.if_else.if_op.if_statement.if_condition = if_condition;
  return node;
}

Expr *else_operation(BoolExpr *if_state, CmdList *if_condition, CmdList *else_condition) {
  Expr *node = (Expr *)malloc(sizeof(Expr));
  node -> kind = ELSE_CON;
  node -> attr.if_else.if_op.else_statement.if_state = if_state;
  node -> attr.if_else.if_op.else_statement.if_condition = if_condition;
  node -> attr.if_else.if_op.else_statement.else_condition = else_condition;
  return node;
}

BoolExpr *ast_boperation(int operator, Expr *left, Expr *right) {
  BoolExpr *node = (BoolExpr *)malloc(sizeof(BoolExpr));
  node -> bool_op.bool_operator = operator;
  node -> bool_op.left = left;
  node -> bool_op.right = right;
  return node;
}

Cmd *exp_operation(Expr *e) {
  Cmd *node = (Cmd *)malloc(sizeof(Cmd));
  node -> kind = EXPR;
  node -> cmd_attr.cmd = e;
  return node;
}

Cmd *while_operation(BoolExpr *while_state, CmdList *while_condition) {
  Cmd *node = (Cmd *)malloc(sizeof(Cmd));
  node -> kind = CMD_WHILE;
  node -> cmd_attr.while_op.while_state = while_state;
  node -> cmd_attr.while_op.while_condition = while_condition;
  return node;
}

Cmd *attrib_operation(char *var, Expr *expr) {
  Cmd *node = (Cmd *)malloc(sizeof(Cmd));
  node -> kind = ATTRIB_EXPR;
  node -> cmd_attr.attrib.var = var;
  node -> cmd_attr.attrib.attrib_op.expr = expr;
  return node;
}

/*Cmd *attribif_operation(char *var, CmdList *cmdif) {
  Cmd *node = (Cmd *)malloc(sizeof(Cmd));
  node -> kind = ATTRIB_IF;
  node -> cmd_attr.attrib.var = var;
  node -> cmd_attr.attrib.attrib_op.cmdif = cmdif;
  return node;
}*/

Cmd *read_operation(char *var) {
  Cmd *node = (Cmd *)malloc(sizeof(Cmd));
  node -> kind = CMD_READ;
  node -> cmd_attr.read.var = var;
  return node;
}

Cmd *print_operation(Expr *expr) {
  Cmd *node = (Cmd *)malloc(sizeof(Cmd));
  node -> kind = CMD_PRINT;
  node -> cmd_attr.print.expr = expr;
  return node;
}

CmdList *list_operation(Cmd *head, CmdList *tail) {
  CmdList *node = (CmdList *)malloc(sizeof(CmdList));
  node -> cmd = head;
  node -> next = tail;
  return node;
}
