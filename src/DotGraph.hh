#pragma once
#include <string>

class DotNode
{
public:
  DotNode(void *ptr, std::string suffix, std::string label) : ptr(ptr), suffix(suffix), label(label) {}
  DotNode(void *ptr, std::string label) : ptr(ptr), suffix(""), label(label) {}
  std::string toDot();

private:
  void *ptr;
  std::string suffix;
  std::string label;
};

class DotEdge
{
public:
  DotEdge(const void *from, const void *to, std::string to_suffix, std::string label) : from(from), to(to), to_suffix(to_suffix), label(label) {}
  DotEdge(const void *from, const void *to, std::string label) : from(from), to(to), to_suffix(""), label(label) {}
  DotEdge(const void *from, const void *to) : from(from), to(to), to_suffix(""), label("") {}
  std::string toDot();

private:
  const void *from;
  const void *to;
  std::string to_suffix;
  std::string label;
};
