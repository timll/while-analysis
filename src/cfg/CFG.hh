#pragma once
#include "TACStmts.hh"
#include "./../ast/ASTNodes.hh"

class CFG
{
public:
  CFG(Program *p);
  void dumpToFile(std::string filename);
  void printCode();

private:
  void toNode(TACNode *node);
  void toEdge(TACNode *from, TACNode *to, std::string label);

  AST2TAC *a2t;
  TACNode *entry;
  std::vector<std::string> nodes;
  std::vector<std::string> edges;
};
