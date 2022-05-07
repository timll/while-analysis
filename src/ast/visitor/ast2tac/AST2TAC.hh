#pragma once
#include <vector>
#include "../ASTVisitor.hh"
#include "./../../../cfg/TACStmts.hh"

class AST2TAC : public ASTVisitor
{
public:
  std::vector<TACNode *> *getCode()
  {
    return &code;
  }

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
  void visit(Boolean *boolean);

private:
  TACAtom *getAtomic(Expr *expr);
  TACAtom *toAtomic(Expr *expr);
  TACVariable *getTemp();
  void addCode(TACNode *node);

  std::vector<TACNode *> code;
  int temp_counter = 0;
};
