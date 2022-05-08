#include "TACStmts.hh"

void TACNode::addPred(TACNode *node)
{
  this->preds.push_back(node);
}

void TACNode::addSucc(TACNode *node)
{
  this->succs.push_back(node);
}

std::vector<TACNode *> *TACNode::getPreds()
{
  return &(this->preds);
}

std::vector<TACNode *> *TACNode::getSuccs()
{
  return &(this->succs);
}

std::string TACAssign::toString()
{
  return lhs->toString() + " = " + rhs->toString();
}

std::string TACSkip::toString()
{
  return "Skip";
}

std::string TACWhile::toString()
{
  return "while (" + cond->toString() + ")";
}

std::string TACIf::toString()
{
  return "if (" + cond->toString() + ")";
}

std::string TACBinOpExpr::toString()
{
  return left->toString() + Token::toString(op) + right->toString();
}

std::string TACUnOpExpr::toString()
{
  return Token::toString(op) + atom->toString();
}

std::string TACVariable::toString()
{
  return std::string(name);
}

std::string TACNumber::toString()
{
  return std::to_string(value);
}

std::string TACBoolean::toString()
{
  if (value)
    return "true";
  return "false";
}