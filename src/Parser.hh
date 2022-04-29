#pragma once
#include "Lexer.hh"
#include "Program.hh"
#include "Stmt.hh"
#include "Expr.hh"

class Parser
{
public:
  Parser(Lexer *lexer) : curr(0), lexer(lexer) {}
  Program* parse();

private:
  void accept(Token::Kind kind);
  void acceptIt();
  Expr *parseExpression();
  Expr *parseCompare();
  Expr *parseAddSub();
  Expr *parseMulDiv();
  Expr *parseUnaryMinus();
  Expr *parseRest();
  Variable *parseVariable();
  Number *parseNumber();
  Stmt *parseStmt();
  DeclarationStmt *parseDeclStmt();
  AssignStmt *parseAssignStmt();
  IfStmt *parseIfStmt();
  WhileStmt *parseWhileStmt();
  CompoundStmt *parseCompoundStmt();

  int curr;
  Token *currentToken;
  Lexer *lexer;
};