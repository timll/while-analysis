#include <iostream>
#include <fstream>
#include <iterator>
#include "Lexer.hh"
#include "LexerError.hh"
#include "Program.hh"
#include "Parser.hh"
#include "ASTPrinter.hh"
#include "SyntaxError.hh"

int main(int argc, char *argv[])
{
  if (argc != 2)
    return 1;

  std::ifstream fin(argv[1]);
  std::string str(std::istreambuf_iterator<char>(fin), {});
  #ifdef DEBUG
  Lexer *lex = new Lexer(str.c_str(), true);
  #else
  Lexer *lex = new Lexer(str.c_str());
  #endif
  Parser *parser = new Parser(lex);
  Program *p;
  try
  {
    p = parser->parse();
  } 
  catch (LexerError &e)
  {
    std::cerr << e.what();
    return 1;
  }
  catch (SyntaxError &e)
  {
    std::cerr << e.what();
    return 2;
  }
  ASTPrinter printer = ASTPrinter();
  p->accept(&printer);
  printer.dumpToFile("ast.dot");
  return 0;
}
