#include "DotGraph.hh"

std::string DotNode::toDot()
{
  return "n" + std::to_string((size_t)this->ptr) + this->suffix + "[label=\"" + this->label + "\"];\n";
}

std::string DotEdge::toDot()
{
  return "n" + std::to_string((size_t)this->from) 
       + "->"
       + "n" + std::to_string((size_t)this->to) 
       + this->to_suffix
       + "[label=\"" + this->label + "\"];\n";
}