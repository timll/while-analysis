#pragma once
#include <vector>
#include "../parser/Token.hh"

class TACVariable;
class TACExpr;
class TACAtom;

class TACNode
{
public:
  virtual std::string toString() = 0;
  virtual bool isStructuredBranch() = 0;
  void addPred(TACNode *node);
  void addSucc(TACNode *node);
  std::vector<TACNode *> *getPreds();
  std::vector<TACNode *> *getSuccs();

private:
  std::vector<TACNode *> preds;
  std::vector<TACNode *> succs;
};

class TACNormalNode : public TACNode
{
public:
  bool isStructuredBranch() { return false; }
};

class TACStructuredBranch : public TACNode
{
public:
  bool isStructuredBranch() { return true; }
};

class TACAssign : public TACNormalNode
{
public:
  TACAssign(TACVariable *lhs, TACExpr *rhs) : lhs(lhs), rhs(rhs) {}

  std::string toString();

private:
  TACVariable *lhs;
  TACExpr *rhs;
};

class TACSkip : public TACNormalNode
{
public:
  TACSkip() {}

  std::string toString();
};

class TACWhile : public TACStructuredBranch
{
public:
  TACWhile(TACExpr *cond) : cond(cond) {}
  std::string toString();

private:
  TACExpr *cond;
};

class TACIf : public TACStructuredBranch
{
public:
  TACIf(TACExpr *cond) : cond(cond) {}
  std::string toString();

private:
  TACExpr *cond;
};

class TACExpr
{
public:
  virtual std::string toString() = 0;
};

class TACBinOpExpr : public TACExpr
{
public:
  TACBinOpExpr(TACAtom *left, Token::Kind op, TACAtom *right) : left(left), op(op), right(right) {}
  std::string toString();

private:
  TACAtom *left;
  Token::Kind op;
  TACAtom *right;
};

class TACUnOpExpr : public TACExpr
{
public:
  TACUnOpExpr(Token::Kind op, TACAtom *atom) : op(op), atom(atom) {}
  std::string toString();

private:
  Token::Kind op;
  TACAtom *atom;
};

class TACAtom : public TACExpr
{

};

class TACVariable : public TACAtom
{
public:
  TACVariable(const char *name) : name(name) {}
  std::string toString();

private:
  const char *name;
};

class TACNumber : public TACAtom
{
public:
  TACNumber(int value) : value(value) {}
  std::string toString();

private:
  int value;
};

class TACBoolean : public TACAtom
{
public:
  TACBoolean(bool value) : value(value) {}
  std::string toString();

private:
  bool value;
};
