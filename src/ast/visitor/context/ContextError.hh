#pragma once
#include <exception>
#include <stdexcept>
#include <stdio.h>
#include "./../../../parser/Token.hh"

class ContextError : public std::exception
{

};

class TypeMismatch : public ContextError
{
public:
  explicit TypeMismatch(Token::Kind type) : type(type) {}

  const char *what() const noexcept;

private:
  Token::Kind type;
};

class VariableRedefined : public ContextError
{
public:
  explicit VariableRedefined(const char *name) : name(name) {}

  const char *what() const noexcept;

private:
  const char *name;
};

class VariableUndefined : public ContextError
{
public:
  explicit VariableUndefined(const char *name) : name(name) {}

  const char *what() const noexcept;

private:
  const char *name;
};
