#pragma once
#include "Token.hh"
#include "ASTVisitor.hh"
#include "Program.hh"

class Expr : ASTNode
{
public:
  Expr();
  virtual void accept(ASTVisitor *v) = 0;
  void setType(Token::Kind type);
  Token::Kind getType() const;

protected:
  Token::Kind type;
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

class Boolean : public Expr
{
public:
  Boolean(bool value) : value(value) {}
  void accept(ASTVisitor *v);
  bool getValue();

private:
  bool value;
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
  void setDeclarator(DeclarationStmt *declarator);

private:
  char *name;
  DeclarationStmt *declarator;
};