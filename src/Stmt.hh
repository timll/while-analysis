#pragma once
#include <vector>
#include "ASTVisitor.hh"

class Stmt
{
public:
  Stmt() {}
  virtual void accept(ASTVisitor *v) = 0;
};

class CompoundStmt
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
  const Variable *getLhs() { return lhs; }
  const Expr *getRhs() { return rhs; }

private:
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