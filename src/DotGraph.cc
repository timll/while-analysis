#include "DotGraph.hh"

std::string DotNode::toDot()
{
  return "n" + std::to_string((size_t)this->ptr) + "[label=\"" + this->label + "\"]\n";
}

std::string DotEdge::toDot()
{
  return "n" + std::to_string((size_t)this->from) + "->" + "n" + std::to_string((size_t)this->to) + "[label=\"" + this->label + "\"]\n";
}