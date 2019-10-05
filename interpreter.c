#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//2) Implemente uma estrutura (struct/union) equivalente ao data Expr
typedef enum {ADD, MULT} Oper;
typedef struct Exp_ *Exp;

struct Exp_ {
  enum {IntExp, OpExp} kind; //funciona como uma flag para saber em que campo da union está
  int num;
  union { // "ou"
    int num;
    struct {Oper oper; Exp left; Exp right;}op; //struct funciona como "&&"
  }u;
};

//3) Implemente um interpretador para expressões int interp (Exp e)

Exp mkNum (int n) {
  Exp p = malloc(sizeof(*p));
  p -> kind = IntExp;
  p -> u.num = n;
  return p;
}

Exp mkOpExp (Oper o, Exp l, Exp r) {
  Exp p = malloc(sizeof(*p));
  p -> kind = OpExp;
  p -> u.op.oper = o;
  p -> u.op.left = l;
  p -> u.op.right = r;
  return p;
}

int interp (Exp e) {
  int a, b;
  switch (e -> kind) {                 
  case IntExp:
    return e -> u.num;
  case OpExp:
    a = interp(e -> u.op.left);
    b = interp(e -> u.op.right);
    switch(e -> u.op.oper) {
    case ADD:
      return a + b;
    case MULT:
      return a * b;
    }
  }
  return 0;
}

int main() {
  Exp p = mkOpExp (MULT, mkNum(2), mkNum(10));
  int n = interp(p);
  printf("%d\n", n);
  return 0;
}
