#pragma once
#include <vector>
#include "Stmt.hh"
#include "ASTVisitor.hh"

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