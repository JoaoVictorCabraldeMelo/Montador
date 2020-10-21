#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <string>
#include <vector>
#include "preProcessor.h"

struct constSalva {
  std::string label;
  std::string param;
};

class Assembler
{
public:
  std::vector<constSalva> Constantes;
  Assembler(std::string fileName, std::vector<std::string> Memory, std::vector<DeclaredDirective> declared);
  void run(std::string fileName, std::vector<std::string> Memory, std::vector<DeclaredDirective> declared);
  std::string changeFileNameToObj(std::string fileName);

  DeclaredDirective* hasDeclared(std::string label, std::vector<DeclaredDirective> declared);
};

#endif