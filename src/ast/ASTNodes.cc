#include "ASTNodes.hh"
#include <typeinfo>
#include "./visitor/ASTVisitor.hh"

void Program::addStmt(Stmt *stmt)
{
  stmts.push_back(stmt);
}

void Program::accept(ASTVisitor *v)
{
  for (Stmt *stmt : this->stmts)
  {
    stmt->accept(v);
  }
  v->visit(this);
}

CompoundStmt::CompoundStmt()
{
}

void CompoundStmt::addStmt(Stmt *stmt)
{
  stmts.push_back(stmt);
}

void CompoundStmt::accept(ASTVisitor *v)
{
  for (Stmt *stmt : stmts)
  {
    stmt->accept(v);
  }
  v->visit(this);
}

void DeclarationStmt::accept(ASTVisitor *v)
{
  this->lhs->accept(v);
  this->rhs->accept(v);
  v->visit(this);
}

void AssignStmt::accept(ASTVisitor *v)
{
  this->lhs->accept(v);
  this->rhs->accept(v);
  v->visit(this);
}


void SkipStmt::accept(ASTVisitor *v)
{
  v->visit(this);
}

void IfStmt::accept(ASTVisitor *v)
{
  this->condition->accept(v);
  this->trueBody->accept(v);
  if (this->hasElse())
    this->elseBody->accept(v);
  v->visit(this);
}

void WhileStmt::accept(ASTVisitor *v)
{
  this->condition->accept(v);
  this->body->accept(v);
  v->visit(this);
}

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

void Expr::setVar(TACVariable *var)
{
  this->var = var;
}

TACVariable *Expr::getVar()
{
  return this->var;
}

void Variable::setDeclarator(DeclarationStmt *declarator)
{
  this->declarator = declarator;
  this->type = declarator->getType();
}
