#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "ASTVisitor.hh"

class ContextAnalysis : public ASTVisitor
{
public:
  void visit(Program *program);

  void visit(CompoundStmt *cstmt);
  void visit(Stmt *stmt);
  void visit(DeclarationStmt *decl);
  void visit(AssignStmt *assign);
  void visit(SkipStmt *skip);
  void visit(IfStmt *ifstmt);
  void visit(WhileStmt *whilestmt);

  void visit(Expr *expr);
  void visit(BinOpExpr *bexpr);
  void visit(ArithmeticExpr *aexpr);
  void visit(CompareExpr *cexpr);
  void visit(UnOpExpr *uexpr);
  void visit(Variable *var);
  void visit(Number *num);

private:
  std::unordered_map<std::string, DeclarationStmt *> decls;
};