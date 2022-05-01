#pragma once
#include <vector>
#include <string>

class Token
{
public:
  enum Kind
  {
    Default, // used to identify the default value
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
    // Types
    Int,
    Bool,
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
  bool isType();

  static std::string toString(Token::Kind kind);

private:
  Token::Kind kind;
  int line;
  int col;
  static const inline std::vector<std::string> strings = {
      "Default",
      "Stmt",
      "Identifier",
      "Number",
      "AssignStmt",
      // Scope
      ";",
      "{",
      "}",
      "(",
      ")",
      "EOF",
      // Keywords
      "While",
      "If",
      "Else",
      "Skip",
      // Types
      "int",
      "bool",
      // Boolean Exprs
      "!",
      "==",
      "!=",
      ">=",
      "<=",
      ">",
      "<",
      // Arithmetic Exprs
      "+",
      "-",
      "*",
      "/"};
};

class IdentifierToken : public Token
{
public:
  IdentifierToken(char *value, int line, int col) : Token(Token::Kind::Identifier, line, col), value(value) {}
  ~IdentifierToken(){};
  char *getValue();

private:
  char *value;
};

class IntegerToken : public Token
{
public:
  IntegerToken(int value, int line, int col) : Token(Token::Kind::Number, line, col), value(value) {}
  int getValue();

private:
  int value;
};