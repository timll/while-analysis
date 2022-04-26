#pragma once
#include <string>

class DotNode
{
public:
  DotNode(void *ptr, std::string label) : ptr(ptr), label(label) {}
  std::string toDot();

private:
  void *ptr;
  std::string label;
};

class DotEdge
{
public:
  DotEdge(const void *from, const void *to) : from(from), to(to), label("") {}
  DotEdge(const void *from, const void *to, std::string label) : from(from), to(to), label(label) {}
  std::string toDot();

private:
  const void *from;
  const void *to;
  std::string label;
};
