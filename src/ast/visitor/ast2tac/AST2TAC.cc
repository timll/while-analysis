#include <typeinfo>
#include <stdexcept>
#include "AST2TAC.hh"
#include "./../../ASTNodes.hh"

void AST2TAC::visit(Program *program)
{
  auto stmts = program->getStmts();
  size_t size = stmts->size();
  for (size_t i = 1; i < size; i++)
  {
    for (TACNode *back : stmts->at(i - 1)->back)
      addEdge(back, stmts->at(i)->front);
  }
}

void AST2TAC::visit(CompoundStmt *cstmt)
{
  auto stmts = cstmt->getStmts();
  size_t size = stmts->size();
  for (size_t i = 1; i < size; i++)
  {
    for (TACNode *back : stmts->at(i - 1)->back)
      addEdge(back, stmts->at(i)->front);
  }
}

void AST2TAC::visit(Stmt *stmt) {}

void AST2TAC::visit(DeclarationStmt *decl)
{
  TACExpr *rhs = getAtomic(decl->getRhs());
  TACAssign *tac = new TACAssign(new TACVariable(decl->getLhs()->getName()), rhs);
  addCode(tac);
  if (decl->getRhs()->tacNodes.size() == 0)
    decl->front = tac;
  else
    decl->front = decl->getRhs()->tacNodes.front();
  decl->back.push_back(tac);
  addEdge(&decl->getRhs()->tacNodes, tac);
}

void AST2TAC::visit(AssignStmt *assign)
{
  TACExpr *rhs = getAtomic(assign->getRhs());
  TACAssign *tac = new TACAssign(new TACVariable(assign->getLhs()->getName()), rhs);
  addCode(tac);
  if (assign->getRhs()->tacNodes.size() == 0)
    assign->front = tac;
  else
    assign->front = assign->getRhs()->tacNodes.front();
  assign->back.push_back(tac);
  addEdge(&assign->getRhs()->tacNodes, tac);
}

void AST2TAC::visit(SkipStmt *skip)
{
  TACSkip *tac = new TACSkip();
  addCode(tac);
  skip->front = tac;
  skip->back.push_back(tac);
}

void AST2TAC::visit(IfStmt *ifstmt)
{
  TACIf *tac = new TACIf(ifstmt->getCondition()->getVar());
  addCode(tac);
  addEdge(&ifstmt->getCondition()->tacNodes, tac);
  addEdge(tac, ifstmt->getTrueBody()->getStmts()->front()->front);
  if (ifstmt->getCondition()->tacNodes.size() == 0)
    ifstmt->front = tac;
  else
    ifstmt->front = ifstmt->getCondition()->tacNodes.front();
  for (TACNode *back : ifstmt->getTrueBody()->getStmts()->back()->back)
    ifstmt->back.push_back(back);
  if (ifstmt->hasElse())
  {
    addEdge(tac, ifstmt->getElseBody()->getStmts()->front()->front);
    for (TACNode *back : ifstmt->getElseBody()->getStmts()->back()->back)
      ifstmt->back.push_back(back);
  }
  else
  {
    ifstmt->back.push_back(tac);
  }
}

void AST2TAC::visit(WhileStmt *whilestmt)
{
  TACWhile *tac = new TACWhile(whilestmt->getCondition()->getVar());
  addCode(tac);
  addEdge(&whilestmt->getCondition()->tacNodes, tac);
  addEdge(tac, whilestmt->getBody()->getStmts()->front()->front);
  for (TACNode *back : whilestmt->getBody()->getStmts()->back()->back)
    addEdge(back, tac);
  if (whilestmt->getCondition()->tacNodes.size() == 0)
    whilestmt->front = tac;
  else
    whilestmt->front = whilestmt->getCondition()->tacNodes.front();
  whilestmt->back.push_back(tac);
}

void AST2TAC::visit(Expr *expr) {}

void AST2TAC::visit(BinOpExpr *bexpr)
{
  TACBinOpExpr *tac = new TACBinOpExpr(bexpr->getLeft()->getVar(), bexpr->getOp(), bexpr->getRight()->getVar());
  TACVariable *tmp = getTemp();
  bexpr->setVar(tmp);
  TACAssign *assgn = new TACAssign(tmp, tac);
  std::vector<TACNode *> merge = bexpr->getLeft()->tacNodes;
  merge.insert(merge.end(), bexpr->getRight()->tacNodes.begin(), bexpr->getRight()->tacNodes.end());
  bexpr->tacNodes = merge;
  bexpr->tacNodes.push_back(assgn);
  addCode(assgn);
}

void AST2TAC::visit(ArithmeticExpr *aexpr)
{
  visit((BinOpExpr *)aexpr);
}

void AST2TAC::visit(CompareExpr *cexpr)
{
  visit((BinOpExpr *)cexpr);
}

void AST2TAC::visit(UnOpExpr *uexpr)
{
  TACUnOpExpr *tac = new TACUnOpExpr(uexpr->getOp(), uexpr->getExpr()->getVar());
  TACVariable *tmp = getTemp();
  uexpr->setVar(tmp);
  TACAssign *assgn = new TACAssign(tmp, tac);
  uexpr->tacNodes = uexpr->getExpr()->tacNodes;
  uexpr->tacNodes.push_back(assgn);
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
  num->tacNodes.push_back(assgn);
  addCode(assgn);
}

void AST2TAC::visit(Boolean *boolean)
{
  TACVariable *tmp = getTemp();
  boolean->setVar(tmp);
  TACAssign *assgn = new TACAssign(tmp, toAtomic(boolean));
  boolean->tacNodes.push_back(assgn);
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
  this->code.push_back(node);
}

void AST2TAC::addEdge(TACNode *from, TACNode *to)
{
  to->addPred(from);
  from->addSucc(to);
}

void AST2TAC::addEdge(std::vector<TACNode *> *nodes, TACNode *to)
{
  size_t size = nodes->size();
  for (size_t i = 1; i < size; i++)
  {
    addEdge(nodes->at(i - 1), nodes->at(i));
  }
  addEdge(nodes->back(), to);
}
