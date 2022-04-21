#include <cctype>
#include <stdlib.h>
#include "lexer.hh"
#include "token.hh"
#include "lexerexception.hh"

Lexer::Lexer(const char *pSource)
{
  this->pSource = pSource;
}

void Lexer::scanAll()
{
  while (*pSource != '\0')
    scan();
}

char Lexer::consume()
{
  return *(pSource++);
}

void Lexer::consumeDigit(char c)
{
  char buffer[13];
  buffer[0] = c;
  int i = 1;
  while (isdigit(peek()))
  {
    if (i >= 13)
    {
      // too large integer constant
      throw new LexerException(line, col, c);
      break;
    }
    c = consume();
    buffer[i++] = c;
    col++;
  }
  buffer[i] = '\0';
  int val = atoi(buffer);
}

void Lexer::consumeIdentifierOrKeyword(char c)
{
  char buffer[17];
  buffer[0] = c;
  int i = 1;
  while (isalpha(peek()))
  {
    if (i >= 17)
    {
      // too long identifier
      throw new LexerException(line, col, c);
    }
    c = consume();
    buffer[i++] = c;
    col++;
  }
  buffer[i] = '\0';
  auto find = keywords.find(buffer);
  if (find == keywords.end())
  {
    // no keyword
    addToken(new IdentifierToken(buffer));
  }
  else
  {
    // keyword
    addToken(new Token(find->second));
  }
}

char Lexer::peek()
{
  return *pSource;
}

bool Lexer::match(char expected)
{
  if (*pSource == '\0' || *pSource != expected)
    return false;
  pSource++;
  return true;
}

void Lexer::addToken(Token *token)
{
  this->tokens.push_back(token);
}

void Lexer::scan()
{
  char c = consume();
  switch (c)
  {
  case '(':
    addToken(new Token(Token::Kind::LeftParanthesis));
    break;
  case ')':
    addToken(new Token(Token::Kind::RightParanthesis));
    break;
  case '{':
    addToken(new Token(Token::Kind::LeftCurlyBrace));
    break;
  case '}':
    addToken(new Token(Token::Kind::RightCurlyBrace));
    break;
  case '+':
    addToken(new Token(Token::Kind::Add));
    break;
  case '-':
    addToken(new Token(Token::Kind::Sub));
    break;
  case '*':
    addToken(new Token(Token::Kind::Mul));
    break;
  case '/':
    addToken(new Token(Token::Kind::Div));
    break;
  case '=':
    addToken(match('=') ? new Token(Token::Kind::Eq) : new Token(Token::Kind::Assign));
    break;
  case '!':
    addToken(match('=') ? new Token(Token::Kind::NEq) : new Token(Token::Kind::Not));
    break;
  case '<':
    addToken(match('=') ? new Token(Token::Kind::LEq) : new Token(Token::Kind::Lt));
    break;
  case '>':
    addToken(match('=') ? new Token(Token::Kind::GEq) : new Token(Token::Kind::Gt));
    break;
  case '\n':
    line++;
    col = 1;
    break;
  case ' ':
  case '\t':
  case '\r':
    break;
  default:
    if (isdigit(c)) {
      consumeDigit(c);
    } else if (isalpha(c)) {
      consumeIdentifierOrKeyword(c);
    } else {
      // unexpected token
      throw new LexerException(line, col, c);
    }
    break;
  }
  col += 1;
}
