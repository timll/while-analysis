#include "ASTVisitor.hh"
#include "Stmt.hh"
#include "Expr.hh"

CompoundStmt::CompoundStmt()
{
}

void CompoundStmt::addStmt(Stmt *stmt)
{
  stmts.push_back(stmt);
}

void CompoundStmt::accept(ASTVisitor *v)
{
  for (Stmt *stmt : stmts)
  {
    stmt->accept(v);
  }
  v->visit(this);
}

void DeclarationStmt::accept(ASTVisitor *v)
{
  this->lhs->accept(v);
  this->rhs->accept(v);
  v->visit(this);
}

void AssignStmt::accept(ASTVisitor *v)
{
  this->lhs->accept(v);
  this->rhs->accept(v);
  v->visit(this);
}


void SkipStmt::accept(ASTVisitor *v)
{
  v->visit(this);
}

void IfStmt::accept(ASTVisitor *v)
{
  this->condition->accept(v);
  this->trueBody->accept(v);
  if (this->hasElse())
    this->elseBody->accept(v);
  v->visit(this);
}

void WhileStmt::accept(ASTVisitor *v)
{
  this->condition->accept(v);
  this->body->accept(v);
  v->visit(this);
}
