#include <stdexcept>
#include "ASTVisitor.hh"
#include "Expr.hh"
#include "Stmt.hh"

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

void Boolean::accept(ASTVisitor *v)
{
  v->visit(this);
}

bool Boolean::getValue()
{
  return this->value;
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

void Expr::setType(Token::Kind type)
{
  this->type = type;
}

Token::Kind Expr::getType() const
{
  return this->type;
}

void Variable::setDeclarator(DeclarationStmt *declarator)
{
  this->declarator = declarator;
  this->type = declarator->getType();
}
