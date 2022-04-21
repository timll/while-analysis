#pragma once

class Token
{
public:
  enum class Kind
  {
    Identifier,
    Number,
    Assign,
    // Scope
    LeftCurlyBrace,
    RightCurlyBrace,
    LeftParanthesis,
    RightParanthesis,
    // Keywords
    While,
    If,
    Else,
    Skip,
    // Boolean Exprs
    Not,
    Eq,
    NEq,
    GEq,
    LEq,
    Gt,
    Lt,
    // Arithmetic Exprs
    Add,
    Sub,
    Mul,
    Div
  };

  Token(Token::Kind kind);
  ~Token();
  Token::Kind getKind();
  bool is(Token::Kind kind);

private:
  Token::Kind kind;
};

class IdentifierToken : public Token
{
public:
  IdentifierToken(char *value);
  char *getValue();

private:
  char *value;
};

class IntegerToken : public Token
{
public:
  IntegerToken(int value);
  int getValue();

private:
  int value;
};