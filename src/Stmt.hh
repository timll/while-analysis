#pragma once
#include <vector>
#include "Expr.hh"

class Stmt
{
};

class CompoundStmt
{
public:
  CompoundStmt();
  void addStmt(Stmt *stmt);

private:
  std::vector<Stmt *> stmts;
};

class AssignStmt : public Stmt
{
public:
  AssignStmt(Variable *lhs, Expr *rhs) : lhs(lhs), rhs(rhs) {}

private:
  Variable *lhs;
  Expr *rhs;
};

class SkipStmt : public Stmt
{
public:
  SkipStmt() {}
};

class IfStmt : public Stmt
{
public:
  IfStmt(Expr *condition, CompoundStmt *trueBody)
      : condition(condition), trueBody(trueBody), hasElseCase(false) {}
  IfStmt(Expr *condition, CompoundStmt *trueBody, CompoundStmt *elseBody)
      : condition(condition), trueBody(trueBody), elseBody(elseBody), hasElseCase(true) {}

private:
  Expr *condition;
  CompoundStmt *trueBody;
  CompoundStmt *elseBody;
  bool hasElseCase;
};

class WhileStmt : public Stmt
{
public:
  WhileStmt(Expr *condition, CompoundStmt *body) : condition(condition), body(body) {}

private:
  Expr *condition;
  CompoundStmt *body;
};