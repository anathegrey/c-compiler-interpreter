// AST constructor functions

#include <stdlib.h> // for malloc
#include "ast.h" // AST header

Expr* ast_integer(int v) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_INTEGER;
  node->attr.value = v;
  return node;
}

Expr* ast_operation
(int operator, Expr* left, Expr* right) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_OPERATION;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}

BoolExpr *ast_boperation(int operator, Expr *left, Expr *right) {
  BoolExpr *node = (BoolExpr *)malloc(sizeof(BoolExpr));
  node -> bool_op.bool_operator = operator;
  node -> bool_op.left = left;
  node -> bool_op.right = right;
  return node;
}
