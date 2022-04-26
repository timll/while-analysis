#include "Expr.hh"
#include "ASTVisitor.hh"

Expr::Expr() {}

void BinOpExpr::accept(ASTVisitor *v)
{
  this->left->accept(v);
  this->right->accept(v);
  v->visit(this);
}

void UnOpExpr::accept(ASTVisitor *v)
{
  this->expr->accept(v);
  v->visit(this);
}

void Number::accept(ASTVisitor *v)
{
  v->visit(this);
}

int Number::getValue()
{
  return this->value;
}

void Variable::accept(ASTVisitor *v)
{
  v->visit(this);
}

const char *Variable::getName()
{
  return this->name;
}
