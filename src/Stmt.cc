#include "Stmt.hh"

CompoundStmt::CompoundStmt() 
{

}

void CompoundStmt::addStmt(Stmt *stmt)
{
  stmts.push_back(stmt);
}