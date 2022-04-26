#include <cctype>
#include <stdlib.h>
#include "Lexer.hh"
#include "Token.hh"
#include "LexerError.hh"

Lexer::Lexer(const char *pSource)
{
  this->pSource = pSource;
}

Token *Lexer::getNextToken()
{
  size_t old_size = this->deque.size();
  if (old_size > 2)
  {
    delete this->deque.front();
    this->deque.erase(deque.begin());
    old_size = 2;
  }
  while (this->deque.size() == old_size)
    scan();
  return this->deque.back();
}

char Lexer::consume()
{
  return *(pSource++);
}

void Lexer::consumeDigit(char c)
{
  char *buffer = new char[13];
  buffer[0] = c;
  int i = 1;
  while (isdigit(peek()))
  {
    if (i >= 13)
    {
      // too large integer constant
      throw new LexerError(line, col, c);
      break;
    }
    c = consume();
    buffer[i++] = c;
    col++;
  }
  buffer[i] = '\0';
  int val = atoi(buffer);
  addToken(new IntegerToken(val, line, col));
}

void Lexer::consumeIdentifierOrKeyword(char c)
{
  char *buffer = new char[17];
  buffer[0] = c;
  int i = 1;
  while (isalpha(peek()))
  {
    if (i >= 17)
    {
      // too long identifier
      throw new LexerError(line, col, c);
    }
    c = consume();
    buffer[i++] = c;
    col++;
  }
  buffer[i] = '\0';
  auto find = keywords.find(std::string(buffer));
  if (find == keywords.end())
  {
    // no keyword
    addToken(new IdentifierToken(buffer, line, col));
  }
  else
  {
    // keyword
    addToken(new Token(find->second, line, col));
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
  this->deque.push_back(token);
}

void Lexer::scan()
{
  char c = consume();
  switch (c)
  {
  case ';':
    addToken(new Token(Token::Kind::Semicolon, line, col));
    break;
  case '(':
    addToken(new Token(Token::Kind::LeftParanthesis, line, col));
    break;
  case ')':
    addToken(new Token(Token::Kind::RightParanthesis, line, col));
    break;
  case '{':
    addToken(new Token(Token::Kind::LeftCurlyBrace, line, col));
    break;
  case '}':
    addToken(new Token(Token::Kind::RightCurlyBrace, line, col));
    break;
  case '+':
    addToken(new Token(Token::Kind::Add, line, col));
    break;
  case '-':
    addToken(new Token(Token::Kind::Sub, line, col));
    break;
  case '*':
    addToken(new Token(Token::Kind::Mul, line, col));
    break;
  case '/':
    addToken(new Token(Token::Kind::Div, line, col));
    break;
  case '=':
    addToken(match('=') ? new Token(Token::Kind::Eq, line, col) : new Token(Token::Kind::Assign, line, col));
    break;
  case '!':
    addToken(match('=') ? new Token(Token::Kind::NEq, line, col) : new Token(Token::Kind::Not, line, col));
    break;
  case '<':
    addToken(match('=') ? new Token(Token::Kind::LEq, line, col) : new Token(Token::Kind::Lt, line, col));
    break;
  case '>':
    addToken(match('=') ? new Token(Token::Kind::GEq, line, col) : new Token(Token::Kind::Gt, line, col));
    break;
  case '\n':
    line++;
    col = 1;
    break;
  case ' ':
  case '\t':
  case '\r':
    break;
  case '\0':
    addToken(new Token(Token::Kind::EndOfFile, line, col));
    break;
  default:
    if (isdigit(c))
    {
      consumeDigit(c);
    }
    else if (isalpha(c))
    {
      consumeIdentifierOrKeyword(c);
    }
    else
    {
      // unexpected token
      throw new LexerError(line, col, c);
    }
    break;
  }
  col += 1;
}
