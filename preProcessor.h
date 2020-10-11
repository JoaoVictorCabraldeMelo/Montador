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
  std::vector<std::string> macroDefinition;
  int nro_Argumentos;
  int line_Macro;
};

struct DeclaredDirective
{
  std::string label;
  std::string directive;
  std::string param;
};

class PreProcessor
{
private:
  bool flagSection;
  bool flagEqu;

public:
  std::string changeFileNameExtension(std::string fileName);
  std::vector<DeclaredDirective> DeclaredTable;
  std::vector<MacroNameAndMacroDefinition> MacroTable;
  std::vector<std::string> OnMemory;
  PreProcessor(std::string fileName, bool putOnMemory);
  void run(std::string fileName, bool putOnMemory);
  DeclaredDirective *hasDeclared(std::string Label);
  MacroNameAndMacroDefinition *hasMacro(std::string macroName);
};

#endif