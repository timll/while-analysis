#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "ASTPrinter.hh"
#include "Program.hh"
#include "Stmt.hh"
#include "Expr.hh"

void ASTPrinter::dumpToFile(std::string filename)
{
  std::ofstream file(filename, std::ios::trunc);
  if (file.fail())
    throw std::invalid_argument("Could not open the file.");
  file << "digraph {\n";
  for (DotNode *node : this->nodes)
    file << node->toDot();
  for (DotEdge *edge : this->edges)
    file << edge->toDot();
  file << "}";
}

void ASTPrinter::visit(Program *program)
{
  DotNode *node = new DotNode(program, "<Program>");
  this->nodes.push_back(node);
  for (Stmt *stmt : *program->getStmts())
  {
    DotEdge *edge = new DotEdge(program, stmt);
    this->edges.push_back(edge);
  }
}

void ASTPrinter::visit(CompoundStmt *cstmt)
{
  DotNode *node = new DotNode(cstmt, "<Compound>");
  this->nodes.push_back(node);
  for (Stmt *stmt : *cstmt->getStmts())
  {
    DotEdge *edge = new DotEdge(cstmt, stmt);
    this->edges.push_back(edge);
  }
}

void ASTPrinter::visit(Stmt *stmt)
{
}

void ASTPrinter::visit(DeclarationStmt *decl)
{
  std::string str = "<Decl>";
  DotNode *node = new DotNode(decl, str);
  DotNode *type = new DotNode(decl, "type", Token::toString(decl->getType()));
  DotEdge *lhsedge = new DotEdge(decl, decl->getLhs(), "lhs");
  DotEdge *rhsedge = new DotEdge(decl, decl->getRhs(), "rhs");
  DotEdge *typeedge = new DotEdge(decl, decl, "type", "type");
  this->nodes.push_back(node);
  this->nodes.push_back(type);
  this->edges.push_back(lhsedge);
  this->edges.push_back(rhsedge);
  this->edges.push_back(typeedge);
}

void ASTPrinter::visit(AssignStmt *assign)
{
  DotNode *node = new DotNode(assign, "<Assign>");
  DotEdge *lhsedge = new DotEdge(assign, assign->getLhs(), "lhs");
  DotEdge *rhsedge = new DotEdge(assign, assign->getRhs(), "rhs");
  this->nodes.push_back(node);
  this->edges.push_back(lhsedge);
  this->edges.push_back(rhsedge);
}

void ASTPrinter::visit(SkipStmt *skip)
{
  DotNode *node = new DotNode(skip, "<Skip>");
  this->nodes.push_back(node);
}

void ASTPrinter::visit(IfStmt *ifstmt)
{
  DotNode *node = new DotNode(ifstmt, "<If>");
  DotEdge *cedge = new DotEdge(ifstmt, ifstmt->getCondition(), "cond");
  DotEdge *tedge = new DotEdge(ifstmt, ifstmt->getTrueBody(), "true");
  this->nodes.push_back(node);
  this->edges.push_back(cedge);
  this->edges.push_back(tedge);
  if (ifstmt->hasElse())
  {
    DotEdge *eedge = new DotEdge(ifstmt, ifstmt->getElseBody(), "false");
    this->edges.push_back(eedge);
  }
}

void ASTPrinter::visit(WhileStmt *whilestmt)
{
  DotNode *node = new DotNode(whilestmt, "<While>");
  DotEdge *cedge = new DotEdge(whilestmt, whilestmt->getCondition(), "cond");
  DotEdge *bedge = new DotEdge(whilestmt, whilestmt->getBody(), "body");
  this->nodes.push_back(node);
  this->edges.push_back(cedge);
  this->edges.push_back(bedge);
}

void ASTPrinter::visit(Expr *expr)
{
}

void ASTPrinter::visit(BinOpExpr *bexpr)
{
  DotNode *node = new DotNode(bexpr, "<BinOpExpr>");
  DotEdge *ledge = new DotEdge(bexpr, bexpr->getLeft(), "l");
  DotNode *op = new DotNode(bexpr, "op", Token::toString(bexpr->getOp()));
  DotEdge *opedge = new DotEdge(bexpr, bexpr, "op", "op");
  DotEdge *redge = new DotEdge(bexpr, bexpr->getRight(), "r");
  this->nodes.push_back(node);
  this->nodes.push_back(op);
  this->edges.push_back(ledge);
  this->edges.push_back(opedge);
  this->edges.push_back(redge);
}

void ASTPrinter::visit(ArithmeticExpr *aexpr)
{
  visit((BinOpExpr *)aexpr);
}

void ASTPrinter::visit(CompareExpr *cexpr)
{
  visit((BinOpExpr *)cexpr);
}

void ASTPrinter::visit(UnOpExpr *uexpr)
{
  DotNode *node = new DotNode(uexpr, "<UnopExpr>\n" + Token::toString(uexpr->getOp()));
  DotEdge *edge = new DotEdge(uexpr, uexpr->getExpr());
  this->nodes.push_back(node);
  this->edges.push_back(edge);
}

void ASTPrinter::visit(Variable *var)
{
  DotNode *node = new DotNode(var, var->getName());
  this->nodes.push_back(node);
}

void ASTPrinter::visit(Number *num)
{
  DotNode *node = new DotNode(num, std::to_string(num->getValue()));
  this->nodes.push_back(node);
}
