#include <iostream>
#include <fstream>
#include <iterator>
#include "Lexer.hh"
#include "LexerError.hh"
#include "Parser.hh"
#include "SyntaxError.hh"

int main(int argc, char *argv[]) {
  if (argc != 2)
    return 1;
  
  std::ifstream fin(argv[1]);
  std::string str(std::istreambuf_iterator<char>(fin), {});
  Lexer *lex = new Lexer(str.c_str());
  try {
    lex->scanAll();
  } catch (LexerError &e) {
    printf(e.what());
  }
  try {
    Parser *parser = new Parser(lex);
    parser->parse();
  } catch (SyntaxError &e) {
    printf(e.what());
  }
  return 1;
}