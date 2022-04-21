#include <iostream>
#include <fstream>
#include <iterator>
#include "lexer.hh"

int main(int argc, char *argv[]) {
  if (argc != 2)
    return 1;
  
  std::ifstream fin(argv[1]);
  std::string str(std::istreambuf_iterator<char>(fin), {});
  Lexer *lex = new Lexer(str.c_str());
  lex->scanAll();
  return 0;
}