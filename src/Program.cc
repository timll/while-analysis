#include "Program.hh"
#include "ASTVisitor.hh"
#include "Stmt.hh"

void Program::addStmt(Stmt *stmt)
{
  stmts.push_back(stmt);
}

void Program::accept(ASTVisitor *v)
{
  for (Stmt *stmt : this->stmts)
  {
    stmt->accept(v);
  }
  v->visit(this);
}