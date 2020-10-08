#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <fstream>
#include <vector>
#include <vector>
#include <string>
#include <utility>

struct MacroNameAndMacroDefinition
{
  std::string macroName;
  std::string macroDefinition;
  int nro_Argumentos;
  int line_Macro;
};

struct DeclaredDirective {
  std::string label;
  std::string directive;
  std::string param;
};

class PreProcessor
{
private:
  std::string changeFileNameExtension(std::string fileName);

public:
  std::vector<DeclaredDirective> DeclaredTable;
  std::vector<MacroNameAndMacroDefinition> MacroTable;
  PreProcessor(std::string fileName);
  void run(std::string fileName);
};

#endif