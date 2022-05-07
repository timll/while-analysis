#include <typeinfo>
#include <stdexcept>
#include "AST2TAC.hh"
#include "./../../ASTNodes.hh"

void AST2TAC::visit(Program *program) {}

void AST2TAC::visit(CompoundStmt *cstmt) {}
void AST2TAC::visit(Stmt *stmt) {}

void AST2TAC::visit(DeclarationStmt *decl) 
{
  TACExpr *rhs = getAtomic(decl->getRhs());
  TACAssign *tac = new TACAssign(new TACVariable(decl->getLhs()->getName()), rhs);
  addCode(tac);
  decl->pred = tac;
}

void AST2TAC::visit(AssignStmt *assign) 
{
  TACExpr *rhs = getAtomic(assign->getRhs());
  TACAssign *tac = new TACAssign(new TACVariable(assign->getLhs()->getName()), rhs);
  addCode(tac);
  assign->pred = tac;
}

void AST2TAC::visit(SkipStmt *skip) 
{
  TACSkip *tac = new TACSkip();
  addCode(tac);
  skip->pred = tac;
}

void AST2TAC::visit(IfStmt *ifstmt) 
{
  TACIf *tac = new TACIf(ifstmt->getCondition()->getVar());
  addCode(tac);
  ifstmt->pred = tac;
}

void AST2TAC::visit(WhileStmt *whilestmt) 
{
  TACWhile *tac = new TACWhile(whilestmt->getCondition()->getVar());
  addCode(tac);
  whilestmt->pred = tac;
  // tac->setTrueSucc(whilestmt->getBody()->getStmts()->front()->pred);
}

void AST2TAC::visit(Expr *expr) {}

void AST2TAC::visit(BinOpExpr *bexpr)
{
  TACBinOpExpr *tac = new TACBinOpExpr(bexpr->getLeft()->getVar(), bexpr->getOp(), bexpr->getRight()->getVar());
  TACVariable *tmp = getTemp();
  bexpr->setVar(tmp);
  TACAssign *assgn = new TACAssign(tmp, tac);
  addCode(assgn);
}

void AST2TAC::visit(ArithmeticExpr *aexpr) 
{
  visit((BinOpExpr *) aexpr);
}

void AST2TAC::visit(CompareExpr *cexpr) 
{
  visit((BinOpExpr *) cexpr);
}

void AST2TAC::visit(UnOpExpr *uexpr) 
{
  TACUnOpExpr *tac = new TACUnOpExpr(uexpr->getOp(), uexpr->getExpr()->getVar());
  TACVariable *tmp = getTemp();
  uexpr->setVar(tmp);
  TACAssign *assgn = new TACAssign(tmp, tac);
  addCode(assgn);
}

void AST2TAC::visit(Variable *var) 
{
  var->setVar(new TACVariable(var->getName()));
}

void AST2TAC::visit(Number *num)
{
  TACVariable *tmp = getTemp();
  num->setVar(tmp);
  TACAssign *assgn = new TACAssign(tmp, toAtomic(num));
  addCode(assgn);
}

void AST2TAC::visit(Boolean *boolean) 
{
  TACVariable *tmp = getTemp();
  boolean->setVar(tmp);
  TACAssign *assgn = new TACAssign(tmp, toAtomic(boolean));
  addCode(assgn);
}

TACAtom *AST2TAC::getAtomic(Expr *expr)
{
  // if (expr->isAtomic())
  //   return toAtomic(expr);
  return expr->getVar();
}

TACAtom *AST2TAC::toAtomic(Expr *expr)
{
  if (typeid(*expr) == typeid(Variable))
    return new TACVariable(((Variable *)expr)->getName());
  else if (typeid(*expr) == typeid(Number))
    return new TACNumber(((Number *)expr)->getValue());
  else if (typeid(*expr) == typeid(Boolean))
    return new TACNumber(((Boolean *)expr)->getValue());
  throw std::invalid_argument("No atomic");
}

TACVariable *AST2TAC::getTemp()
{
  char *buf = new char[12];
  snprintf(buf, 11, "t%i", temp_counter++);
  return new TACVariable(buf);
}

void AST2TAC::addCode(TACNode *node)
{
  // if (this->code.size() > 0)
  // {
  //   this->code.back();
  // }
  this->code.push_back(node);
}