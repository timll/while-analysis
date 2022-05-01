#pragma once
#include <string>
#include <vector>
#include "ASTVisitor.hh"
#include "DotGraph.hh"

class ASTPrinter : public ASTVisitor
{
public:
  void dumpToFile(std::string filename);

  void visit(Program *program);

  void visit(CompoundStmt *cstmt);
  // void visit(Stmt *stmt);
  void visit(DeclarationStmt *decl);
  void visit(AssignStmt *assign);
  void visit(SkipStmt *skip);
  void visit(IfStmt *ifstmt);
  void visit(WhileStmt *whilestmt);

  // void visit(Expr *expr);
  void visit(BinOpExpr *bexpr);
  void visit(ArithmeticExpr *aexpr);
  void visit(CompareExpr *cexpr);
  void visit(UnOpExpr *uexpr);
  void visit(Variable *var);
  void visit(Number *num);

private:
  std::vector<DotNode *> nodes;
  std::vector<DotEdge *> edges;
};