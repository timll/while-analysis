#pragma once
#include <vector>
#include "Stmt.hh"

class Program
{
public:
  Program() {}
  void addStmt(Stmt *stmt)
  {
    stmts.push_back(stmt);
  }

private:
  std::vector<Stmt *> stmts;
};