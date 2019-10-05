#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Exp
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

//Instr
typedef enum {ADDI, MULTI}OperI;
typedef struct Instr_ *Instr;

struct Instr_ {
  enum {PUSH, ADDI, MULTI}inst;
  int p;
};

Instr mkPush(int x) {
  Instr t = malloc(sizeof(*t));
  t -> inst = PUSH;
  t -> p = x;
  return t;
}

Instr mkOper(OperI opI) {
  Instr t = malloc(sizeof(*t));
  t -> inst = opI;
  return t;
}

typedef struct InstList_ *InstList;

struct InstList_ {
  Instr instr;
  InstList rest;
};

InstList append(InstList l1, InstList l2) {
  if(l1 == NULL)
    return l2;
  else
    return mkIList(l1 -> instr, append(l1 -> rest, l2));
}

InstList mkIList(Instr head, InstList tail) {
  InstList t = malloc(sizeof(*t));
  t -> instr = head;
  t -> rest = tail;
  return t;
}
