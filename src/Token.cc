#include "Token.hh"

Token::Kind Token::getKind()
{
  return this->kind;
}

int Token::getLine()
{
  return this->line;
}

int Token::getCol()
{
  return this->col;
}

bool Token::is(Token::Kind kind)
{
  return this->kind == kind;
}

bool Token::isType()
{
  return this->kind == Token::Kind::Int || this->kind == Token::Kind::Bool;
}

std::string Token::toString(Token::Kind kind)
{
  return Token::strings[kind];
}

char *IdentifierToken::getValue()
{
  return this->value;
}

int IntegerToken::getValue()
{
  return this->value;
}