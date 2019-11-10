#include <stdio.h>
#include "parser.h"

void printExpr(Expr *exp) {
  if(exp == 0)
    yyerror("Null expression!!");
  else if(exp -> kind == E_INTEGER)
    printf("%d ", exp -> attr.value);
  else if(exp -> kind == E_OPERATION) {
    printExpr(exp -> attr.op.left);
    printExpr(exp -> attr.op.right);
    switch(exp -> attr.op.operator) {
    case PLUS:
      printf("+ ");
      break;
    case SUB:
      printf("- ");
      break;
    case MULT:
      printf("* ");
      break;
    case DIV:
      printf("/ ");
      break;
    case REST:
      printf("mod ");
      break;
    default: yyerror("Unknown operator!");
    }
  }
}

void printBool(BoolExpr *b) {
  printExpr(b -> bool_op.left);
  printExpr(b -> bool_op.right);
  switch(b -> bool_op.bool_operator) {
  case EQUALS:
    printf("==");
    break;
  case DIFF:
    printf("!=");
    break;
  case LESS:
    printf("<");
    break;
  case BIG:
    printf(">");
    break;
  case LESS_EQUAL:
    printf("<=");
    break;
  case BIG_EQUAL:
    printf(">=");
    break;
  default: yyerror("Unknown operator!");
  }
}

void printCmd(CmdList *command) {
  switch(command -> cmd -> cmdseq_kind) {
  case CMD_ATTRIB:
    printf("let %s = ", command -> cmd -> cmdseq_attr.cmdAttrib -> var);
    if(command -> cmd -> cmdseq_attr.cmdAttrib -> attrib_kind = ATTRIB_EXPR)
      printExpr(command -> cmd -> cmdseq_attr.cmdAttrib -> attrib_attrib.expr);
    else if(command -> cmd -> cmdseq_attr.cmdAttrib -> attrib_kind = ATTRIB_IF)
      printCmd(command -> cmd -> cmdseq_attr.cmdAttrib -> attrib_attrib.cmdif);
    break;
  case CMD_IF:
    if(command -> cmd -> cmdseq_attr.cmdIf -> cmdif_kind = IF_STATEMENT) {
      printf("if ");
      printBool(command -> cmd -> cmdseq_attr.cmdIf -> cmdif_attr.if_statement.if_state);
      printf("{ ");
      while(command -> next != NULL) 
	printCmd(command -> cmd -> cmdseq_attr.cmdIf -> cmdif_attr.if_statement.if_condition);
      printf("} ");
    }
    else if(command -> cmd -> cmdseq_attr.cmdIf -> cmdif_kind = ELSE_STATEMENT) {
      printf("if ");
      printBool(command -> cmd -> cmdseq_attr.cmdIf -> cmdif_attr.else_statement.if_state);
      printf("{ ");
      while(command -> next != NULL)
	printCmd(command -> cmd -> cmdseq_attr.cmdIf -> cmdif_attr.else_statement.if_condition); 
      printf("} else { ");
      while(command -> next != NULL)
	printCmd(command -> cmd -> cmdseq_attr.cmdIf -> cmdif_attr.else_statement.else_condition);
      printf("} ");
    }
    break;
  case CMD_PRINT:
    printf("println!(\"{}\",");
    printExpr(command -> cmd -> cmdseq_attr.cmdPrint -> expr);
    break;
  case CMD_READ:
    printf("let %s = String::new();\nlet %s = std::io::stdin().read_line(&mut %s).unwrap();", (command -> cmd -> cmdseq_attr.cmdRead -> var), (command -> cmd -> cmdseq_attr.cmdRead -> aux_var), (command -> cmd -> cmdseq_attr.cmdRead -> var));
    break;
  case CMD_WHILE:
    printf("while ");
    printBool(command -> cmd -> cmdseq_attr.cmdWhile -> cmdwhile_attr.while_state);
    printf(" { ");
    while(command -> next != NULL)
      printCmd(command -> cmd -> cmdseq_attr.cmdWhile -> cmdwhile_attr.while_condition);
    printf(" } ");
    break;
  }
  printf("\n");
}

int main(int argc, char** argv) {
  --argc; ++argv;
  if (argc != 0) {
    yyin = fopen(*argv, "r");
    if (!yyin) {
      printf("'%s': could not open file\n", *argv);
      return 1;
    }
  } //  yyin = stdin
  if (yyparse() == 0) {
    printCmd(root);
    printf("\n");
    root = root -> next;
  }
  return 0;
}
