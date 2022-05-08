#include <queue>
#include <unordered_set>
#include <iostream>
#include <fstream>
#include "./../ast/visitor/ast2tac/AST2TAC.hh"
#include "CFG.hh"

CFG::CFG(Program *p)
{
  this->a2t = new AST2TAC();
  p->accept(this->a2t);
  this->entry = this->a2t->getCode()->front(); 
}

void CFG::printCode()
{
  for (TACNode *node : *this->a2t->getCode())
  {
    std::cout << node->toString() << "\n";
  }
}

void CFG::dumpToFile(std::string filename)
{
  std::unordered_set<TACNode *> visited;
  std::queue<TACNode *> q;
  q.push(entry);
  while (!q.empty())
  {
    TACNode *node = q.front();
    q.pop();
    visited.insert(node);
    toNode(node);
    std::vector<TACNode *> succs = *(node->getSuccs());
    for (TACNode *succ : succs)
    {
      toEdge(node, succ, "");
      if (visited.find(succ) == visited.end())
        q.push(succ);
    }
  }

  std::ofstream file(filename, std::ios::trunc);
  if (file.fail())
    throw std::invalid_argument("Could not open the file.");
  file << "digraph {\nrankdir=TD; ordering=out;\n";
  for (std::string node : this->nodes)
    file << node;
  for (std::string edge : this->edges)
    file << edge;
  file << "}";
}

void CFG::toNode(TACNode *node)
{
  std::string n_str = "n" + std::to_string((size_t) node) + "[label=\"" + node->toString() + "\"];\n";
  this->nodes.push_back(n_str);
}

void CFG::toEdge(TACNode *from, TACNode *to, std::string label)
{
  std::string e_str = "n" + std::to_string((size_t) from) + "->" + "n" + std::to_string((size_t) to) + "[label=\"" + label + "\"];\n";
  this->edges.push_back(e_str);
}