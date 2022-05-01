#include <set>
#include "Parser.hh"
#include "Program.hh"
#include "Stmt.hh"
#include "Expr.hh"
#include "SyntaxError.hh"

Program *Parser::parse()
{
  Program *p = new Program();
  this->currentToken = lexer->getNextToken();
  while (!currentToken->is(Token::Kind::EndOfFile))
  {
    p->addStmt(parseStmt());
  }
  return p;
}

void Parser::accept(Token::Kind kind)
{
  if (!this->currentToken->is(kind))
    throw SyntaxError(kind, this->currentToken);
  acceptIt();
}

void Parser::acceptIt()
{
  this->currentToken = lexer->getNextToken();
}

Expr *Parser::parseExpression()
{
  return parseCompare();
}

Expr *Parser::parseCompare()
{
  std::set<Token::Kind> comparators = {
      Token::Kind::Lt, Token::Kind::LEq,
      Token::Kind::Eq, Token::Kind::NEq,
      Token::Kind::Gt, Token::Kind::GEq};

  Expr *lhs = parseAddSub();
  while (comparators.find(this->currentToken->getKind()) != comparators.end())
  {
    Token *tok = this->currentToken;
    acceptIt();
    Expr *rhs = parseAddSub();
    lhs = new CompareExpr(lhs, tok->getKind(), rhs);
  }
  return lhs;
}

Expr *Parser::parseAddSub()
{
  Expr *lhs = parseMulDiv();
  while (this->currentToken->is(Token::Kind::Add) || this->currentToken->is(Token::Kind::Sub))
  {
    Token *tok = this->currentToken;
    acceptIt();
    Expr *rhs = parseMulDiv();
    lhs = new ArithmeticExpr(lhs, tok->getKind(), rhs);
  }
  return lhs;
}

Expr *Parser::parseMulDiv()
{
  Expr *lhs = parseUnaryMinus();
  while (this->currentToken->is(Token::Kind::Mul) || this->currentToken->is(Token::Kind::Div))
  {
    Token *tok = this->currentToken;
    acceptIt();
    Expr *rhs = parseUnaryMinus();
    lhs = new ArithmeticExpr(lhs, tok->getKind(), rhs);
  }
  return lhs;
}

Expr *Parser::parseUnaryMinus()
{
  if (currentToken->is(Token::Kind::Sub))
  {
    acceptIt();
    Expr *expr = parseRest();
    return new UnOpExpr(Token::Kind::Sub, expr);
  }
  return parseRest();
}

Expr *Parser::parseRest()
{
  if (currentToken->is(Token::Kind::Identifier))
    return parseVariable();
  else if (currentToken->is(Token::Kind::Number))
    return parseNumber();
  else if (currentToken->is(Token::Kind::LeftParanthesis))
  {
    acceptIt();
    Expr *expr = parseExpression();
    accept(Token::Kind::RightParanthesis);
    return expr;
  }
  throw SyntaxError(Token::Kind::Identifier, currentToken);
}

Variable *Parser::parseVariable()
{
  Token *tok = this->currentToken;
  accept(Token::Kind::Identifier);
  Variable *var = new Variable(((IdentifierToken *)tok)->getValue());
  return var;
}

Number *Parser::parseNumber()
{
  Token *tok = this->currentToken;
  accept(Token::Kind::Number);
  Number *num = new Number(((IntegerToken *)tok)->getValue());
  return num;
}

Stmt *Parser::parseStmt()
{
  if (this->currentToken->isType())
    return parseDeclStmt();
  else if (this->currentToken->is(Token::Kind::Identifier))
    return parseAssignStmt();
  else if (this->currentToken->is(Token::Kind::Skip))
  {
    accept(Token::Kind::Skip);
    accept(Token::Kind::Semicolon);
    return new SkipStmt();
  }
  else if (this->currentToken->is(Token::Kind::If))
    return parseIfStmt();
  else if (this->currentToken->is(Token::Kind::While))
    return parseWhileStmt();

  throw SyntaxError(Token::Kind::Stmt, this->currentToken);
}

DeclarationStmt *Parser::parseDeclStmt()
{
  Token::Kind type = this->currentToken->getKind();
  acceptIt();
  Variable *lhs = parseVariable();
  accept(Token::Kind::Assign);
  Expr *rhs = parseExpression();
  DeclarationStmt *decl = new DeclarationStmt(type, lhs, rhs);
  accept(Token::Kind::Semicolon);
  return decl;
}

AssignStmt *Parser::parseAssignStmt()
{
  Variable *lhs = parseVariable();
  accept(Token::Kind::Assign);
  Expr *rhs = parseExpression();
  AssignStmt *assign = new AssignStmt(lhs, rhs);
  accept(Token::Kind::Semicolon);
  return assign;
}

IfStmt *Parser::parseIfStmt()
{
  accept(Token::Kind::If);
  accept(Token::Kind::LeftParanthesis);

  Expr *cond = parseExpression();
  accept(Token::Kind::RightParanthesis);
  CompoundStmt *body = parseCompoundStmt();

  IfStmt *ifstmt = NULL;
  if (this->currentToken->is(Token::Kind::Else))
  {
    acceptIt();
    CompoundStmt *elseBody = parseCompoundStmt();
    ifstmt = new IfStmt(cond, body, elseBody);
  }
  else
  {
    ifstmt = new IfStmt(cond, body);
  }
  return ifstmt;
}

WhileStmt *Parser::parseWhileStmt()
{
  accept(Token::Kind::While);
  accept(Token::Kind::LeftParanthesis);
  Expr *cond = parseExpression();
  accept(Token::Kind::RightParanthesis);
  CompoundStmt *cstmt = parseCompoundStmt();

  WhileStmt *whilestmt = new WhileStmt(cond, cstmt);
  return whilestmt;
}

CompoundStmt *Parser::parseCompoundStmt()
{
  accept(Token::Kind::LeftCurlyBrace);
  CompoundStmt *cstmt = new CompoundStmt();
  while (!(this->currentToken->is(Token::Kind::RightCurlyBrace)))
  {
    Stmt *stmt = parseStmt();
    cstmt->addStmt(stmt);
  }
  accept(Token::Kind::RightCurlyBrace);
  return cstmt;
}
