#pragma once
#include "Token.hh"
#include "ASTVisitor.hh"

class Expr
{
public:
  Expr();
  virtual void accept(ASTVisitor *v) = 0;
};

class BinOpExpr : public Expr
{
public:
  BinOpExpr(Expr *left, Token::Kind op, Expr *right)
      : left(left), op(op), right(right), Expr() {}
  void accept(ASTVisitor *v);
  const Expr *getLeft() { return left; };
  Token::Kind getOp() { return op; };
  const Expr *getRight() { return right; };

private:
  Expr *left;
  Token::Kind op;
  Expr *right;
};

class ArithmeticExpr : public BinOpExpr
{
public:
  ArithmeticExpr(Expr *left, Token::Kind op, Expr *right)
      : BinOpExpr(left, op, right) {}
};

class CompareExpr : public BinOpExpr
{
public:
  CompareExpr(Expr *left, Token::Kind op, Expr *right)
      : BinOpExpr(left, op, right) {}
};

class UnOpExpr : public Expr
{
public:
  UnOpExpr(Token::Kind op, Expr *expr)
      : op(op), expr(expr) {}
  void accept(ASTVisitor *v);
  Token::Kind getOp() { return op; };
  const Expr *getExpr() { return expr; };

private:
  Token::Kind op;
  Expr *expr;
};

class Number : public Expr
{
public:
  Number(int value) : value(value) {}
  void accept(ASTVisitor *v);
  int getValue();

private:
  int value;
};

class Variable : public Expr
{
public:
  Variable(char *name) : name(name) {}
  void accept(ASTVisitor *v);
  const char *getName();

private:
  char *name;
};