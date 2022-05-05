#pragma once
#include <vector>
#include "./visitor/ASTVisitor.hh"
#include "./../parser/Token.hh"

class ASTNode
{
};

class Program : public ASTNode
{
public:
  Program() {}
  void addStmt(Stmt *stmt);
  void accept(ASTVisitor *v);
  const std::vector<Stmt *> *getStmts() { return &stmts; }

private:
  std::vector<Stmt *> stmts;
};

class Stmt : ASTNode
{
public:
  Stmt() {}
  virtual void accept(ASTVisitor *v) = 0;
};

class CompoundStmt : ASTNode
{
public:
  CompoundStmt();
  void addStmt(Stmt *stmt);
  void accept(ASTVisitor *v);
  const std::vector<Stmt *> *getStmts() { return &stmts; }

private:
  std::vector<Stmt *> stmts;
};

class AssignStmt : public Stmt
{
public:
  AssignStmt(Variable *lhs, Expr *rhs) : lhs(lhs), rhs(rhs) {}
  void accept(ASTVisitor *v);
  Variable *getLhs() { return lhs; }
  const Expr *getRhs() { return rhs; }

private:
  Variable *lhs;
  Expr *rhs;
};

class DeclarationStmt : public Stmt
{
public:
  DeclarationStmt(Token::Kind type, Variable *lhs, Expr *rhs) : type(type), lhs(lhs), rhs(rhs) {}
  void accept(ASTVisitor *v);
  Token::Kind getType() { return type; }
  Variable *getLhs() { return lhs; }
  const Expr *getRhs() { return rhs; }

private:
  Token::Kind type;
  Variable *lhs;
  Expr *rhs;
};

class SkipStmt : public Stmt
{
public:
  SkipStmt() {}
  void accept(ASTVisitor *v);
};

class IfStmt : public Stmt
{
public:
  IfStmt(Expr *condition, CompoundStmt *trueBody)
      : condition(condition), trueBody(trueBody), elseBody(nullptr) {}
  IfStmt(Expr *condition, CompoundStmt *trueBody, CompoundStmt *elseBody)
      : condition(condition), trueBody(trueBody), elseBody(elseBody) {}
  void accept(ASTVisitor *v);
  const Expr *getCondition() { return condition; }
  const CompoundStmt *getTrueBody() { return trueBody; }
  const CompoundStmt *getElseBody() { return elseBody; }
  const bool hasElse() { return elseBody != nullptr; }

private:
  Expr *condition;
  CompoundStmt *trueBody;
  CompoundStmt *elseBody;
};

class WhileStmt : public Stmt
{
public:
  WhileStmt(Expr *condition, CompoundStmt *body) : condition(condition), body(body) {}
  void accept(ASTVisitor *v);
  const Expr *getCondition() { return condition; }
  const CompoundStmt *getBody() { return body; }

private:
  Expr *condition;
  CompoundStmt *body;
};

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
      : Expr(), left(left), op(op), right(right) {}
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
