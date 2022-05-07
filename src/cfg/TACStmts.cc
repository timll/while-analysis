#include "TACStmts.hh"

void TACNormalNode::addPred(TACNode *node)
{
  this->preds.push_back(node);
}

void TACNormalNode::setSucc(TACNode *node)
{
  this->succ = node;
}

std::vector<TACNode *> *TACNormalNode::getPreds()
{
  return &(this->preds);
}

TACNode *TACNormalNode::getSucc()
{
  return this->succ;
}

void TACStructuredBranch::addPred(TACNode *node)
{
  this->preds.push_back(node);
}

void TACStructuredBranch::setTrueSucc(TACNode *node)
{
  this->trueSucc = node;
}

void TACStructuredBranch::setFalseSucc(TACNode *node)
{
  this->falseSucc = node;
}

std::vector<TACNode *> *TACStructuredBranch::getPreds()
{
  return &(this->preds);
}

TACNode *TACStructuredBranch::getTrueSucc()
{
  return this->trueSucc;
}
TACNode *TACStructuredBranch::getFalseSucc()
{
  return this->falseSucc;
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