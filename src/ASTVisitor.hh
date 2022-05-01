#pragma once
#include "ASTClasses.fwd.hh"

class ASTVisitor
{
public:
  virtual void visit(Program *program) = 0;

  virtual void visit(CompoundStmt *cstmt) = 0;
  // virtual void visit(Stmt *stmt) = 0; is virtual
  virtual void visit(DeclarationStmt *decl) = 0;
  virtual void visit(AssignStmt *assign) = 0;
  virtual void visit(SkipStmt *skip) = 0;
  virtual void visit(IfStmt *ifstmt) = 0;
  virtual void visit(WhileStmt *whilestmt) = 0;

  // virtual void visit(Expr *expr) = 0; is virtual
  virtual void visit(BinOpExpr *bexpr) = 0;
  virtual void visit(ArithmeticExpr *aexpr) = 0;
  virtual void visit(CompareExpr *cexpr) = 0;
  virtual void visit(UnOpExpr *uexpr) = 0;
  virtual void visit(Variable *var) = 0;
  virtual void visit(Number *num) = 0;
};
