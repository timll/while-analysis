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
  Lexer *lex = new Lexer(str.c_str());
  Parser *parser = new Parser(lex);
  Program *p;
  try
  {
    p = parser->parse();
  } 
  catch (LexerError &e)
  {
    printf(e.what());
  }
  catch (SyntaxError &e)
  {
    printf(e.what());
  } 

  ASTPrinter printer = ASTPrinter();
  p->accept(&printer);
  printer.dumpToFile("ast.dot");
  return 0;
}
