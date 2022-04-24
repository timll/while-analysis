#pragma once

class Token
{
public:
  enum class Kind
  {
    Stmt, // dummy token for the parser to throw a syntax error
    Identifier,
    Number,
    Assign,
    // Scope
    Semicolon,
    LeftCurlyBrace,
    RightCurlyBrace,
    LeftParanthesis,
    RightParanthesis,
    EndOfFile,
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

  Token(Token::Kind kind, int line, int col) : kind(kind), line(line), col(col) {}
  ~Token() {}
  Token::Kind getKind();
  int getLine();
  int getCol();
  bool is(Token::Kind kind);

private:
  Token::Kind kind;
  int line;
  int col;
};

class IdentifierToken : public Token
{
public:
  IdentifierToken(char *value, int line, int col) : value(value), Token(Token::Kind::Identifier, line, col) {}
  ~IdentifierToken() {};
  char *getValue();

private:
  char *value;
};

class IntegerToken : public Token
{
public:
  IntegerToken(int value, int line, int col) : value(value), Token(Token::Kind::Identifier, line, col) {}
  int getValue();

private:
  int value;
};