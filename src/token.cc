#include "token.hh"

Token::Token(Token::Kind kind)
{
  this->kind = kind;
}

Token::Kind Token::getKind()
{
  return this->kind;
}

bool Token::is(Token::Kind kind)
{
  return this->kind == kind;
}

IdentifierToken::IdentifierToken(char *value)
    : Token(Token::Kind::Identifier)
{
  this->value = value;
}

char *IdentifierToken::getValue()
{
  return this->value;
}

IntegerToken::IntegerToken(int value)
    : Token(Token::Kind::Number)
{
  this->value = value;
}

int IntegerToken::getValue()
{
  return this->value;
}