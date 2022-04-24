#pragma once
#include "Token.hh"

class Expr
{
public:
  Expr();
};

class BinOpExpr : public Expr
{
public:
  BinOpExpr(Expr *left, Token::Kind op, Expr *right)
      : left(left), op(op), right(right), Expr() {}

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

private:
  Token::Kind op;
  Expr *expr;
};

class Number : public Expr
{
public:
  Number(int value) : value(value) {}

private:
  int value;
};

class Variable : public Expr
{
public:
  Variable(const char *name) : name(name) {}

private:
  const char *name;
};