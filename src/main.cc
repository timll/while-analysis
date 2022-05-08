#include <iostream>
#include <fstream>
#include <iterator>
#include "parser/Lexer.hh"
#include "parser/LexerError.hh"
#include "parser/Parser.hh"
#include "parser/SyntaxError.hh"
#include "ast/ASTNodes.hh"
#include "ast/visitor/ASTVisitor.hh"
#include "ast/visitor/printer/ASTPrinter.hh"
#include "ast/visitor/context/ContextAnalysis.hh"
#include "ast/visitor/context/ContextError.hh"
#include "ast/visitor/ast2tac/AST2TAC.hh"
#include "cfg/CFG.hh"

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

  ContextAnalysis context = ContextAnalysis();
  try
  {
    p->accept(&context);
  }
  catch (ContextError &e)
  {
    std::cerr << e.what();
    return 2;
  }

  ASTPrinter printer = ASTPrinter();
  p->accept(&printer);
  printer.dumpToFile("ast.dot");

  // AST2TAC a2t = AST2TAC();
  // p->accept(&a2t);

  CFG cfg = CFG(p);
  cfg.printCode();
  cfg.dumpToFile("cfg.dot");
  return 0;
}
