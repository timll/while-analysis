#include "ContextAnalysis.hh"
#include "ContextError.hh"
#include "Stmt.hh"
#include "Expr.hh"

void ContextAnalysis::visit(Program *program) {}

void ContextAnalysis::visit(CompoundStmt *cstmt) {}
void ContextAnalysis::visit(Stmt *stmt) {}

void ContextAnalysis::visit(DeclarationStmt *decl)
{
  Variable *var = decl->getLhs();
  const char *name = var->getName();
  auto find = this->decls.find(std::string(name));
  if (find != this->decls.end())
  {
    // already defined
    throw VariableRedefined(name);
  }

  const Expr *expr = decl->getRhs();
  if (decl->getType() != expr->getType())
  {
    throw TypeMismatch(decl->getType());
  }

  var->setType(decl->getType());
  this->decls.insert(std::make_pair(std::string(var->getName()), decl));
}

void ContextAnalysis::visit(AssignStmt *assign)
{
  Variable *var = assign->getLhs();
  const Expr *expr = assign->getRhs();
  if (var->getType() != expr->getType())
  {
    throw TypeMismatch(var->getType());
  }
}

void ContextAnalysis::visit(SkipStmt *skip) {}

void ContextAnalysis::visit(IfStmt *ifstmt)
{
  const Expr *cond = ifstmt->getCondition();
  if (cond->getType() != Token::Kind::Bool)
  {
    throw TypeMismatch(cond->getType());
  }
}

void ContextAnalysis::visit(WhileStmt *whilestmt)
{
  const Expr *cond = whilestmt->getCondition();
  if (cond->getType() != Token::Kind::Bool)
  {
    throw TypeMismatch(cond->getType());
  }
}

void ContextAnalysis::visit(Expr *expr) {}

void ContextAnalysis::visit(BinOpExpr *bexpr)
{
  const Expr *lhs = bexpr->getLeft();
  const Expr *rhs = bexpr->getRight();
  if (lhs->getType() != Token::Kind::Int || rhs->getType() != Token::Kind::Int)
  {
    // type mismatch
    throw TypeMismatch(lhs->getType());
  }
  bexpr->setType(Token::Kind::Bool);
}

void ContextAnalysis::visit(ArithmeticExpr *aexpr)
{
  visit((BinOpExpr *)aexpr);
}

void ContextAnalysis::visit(CompareExpr *cexpr)
{
  visit((BinOpExpr *)cexpr);
}

void ContextAnalysis::visit(UnOpExpr *uexpr)
{
  const Expr *expr = uexpr->getExpr();
  if (uexpr->getOp() == Token::Kind::Sub)
  {
    if (expr->getType() != Token::Kind::Int)
    {
      // type mismatch
      throw TypeMismatch(expr->getType());
    }
    uexpr->setType(Token::Kind::Int);
  }
  else if (uexpr->getOp() == Token::Kind::Not)
  {
    if (expr->getType() != Token::Kind::Bool)
    {
      // type mismatch
      throw TypeMismatch(expr->getType());
    }
    uexpr->setType(Token::Kind::Bool);
  }
}

void ContextAnalysis::visit(Variable *var)
{
  const char *name = var->getName();
  auto find = this->decls.find(std::string(name));
  if (find != this->decls.end())
  {
    var->setDeclarator(find->second);
  }
}

void ContextAnalysis::visit(Number *num)
{
  num->setType(Token::Kind::Int);
}

void ContextAnalysis::visit(Boolean *num)
{
  num->setType(Token::Kind::Bool);
}
