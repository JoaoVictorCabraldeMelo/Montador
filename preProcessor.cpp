#include "preProcessor.h"
#include "Tables.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include <cmath>

void PreProcessor::run(std::string fileName)
{
  Tables *table = new Tables();

  std::string newFileName = fileName;

  flagSection = false;
  flagEqu = false;

  newFileName = changeFileNameExtension(newFileName);

  std::ofstream outf{newFileName, std::ofstream::out};

  std::ifstream inf{fileName};

  if (!inf)
  {
    std::cerr << "Não consegui achar o arquivo para Pre Processar \n";
  }

  std::string maybeSection;

  std::string maybeDirective, directive, param, symbol;

  //Pega todas as suas diretivas e coloca em um rotulo e parametro
  while (inf >> symbol)
  {
    if (table->hasDirective(symbol) != nullptr)
    {
      Directive directiveWithoutLabel;
      directiveWithoutLabel = *table->hasDirective(symbol);
      if (directiveWithoutLabel.name == "SECTION")
      {
        flagSection = true;
      }
      else if (directiveWithoutLabel.name == "IF")
      {
        if (flagEqu)
        {
          inf >> param;
          if (hasDeclared(param) == nullptr)
          {
            std::cerr << "IF sem EQU correspondente" << std::endl;
            exit(-1);
          }
        }
        else
        {
          std ::cerr << "IF sem EQU por favor declare um EQU" << std::endl;
          exit(-1);
        }
      }
    }
    else if (symbol.back() == ':')
    {
      inf >> maybeDirective;
      if (table->hasDirective(maybeDirective) != nullptr)
      {
        DeclaredDirective declared;
        declared.directive = table->hasDirective(maybeDirective)->name;
        if (declared.directive == "CONST" || declared.directive == "EQU")
        {
          if (declared.directive == "EQU")
          {
            flagEqu = true;
          }
          if (declared.directive == "EQU" && flagSection)
          {
            std::cerr << "EQU dentro de SECTION por favor retire o EQU para fora do SECTION" << std::endl;
            exit(-1);
          }
          inf >> param;
          int newParamInt = stoi(param);
          std::string transformParam = std::to_string(newParamInt);
          if (param != transformParam)
          {
            std::cerr << "CONST com argumento não decimal" << std::endl;
            exit(-1);
          }
          symbol.pop_back();
          declared.label = symbol;
          declared.param = param;
          DeclaredTable.push_back(declared);
        }
        else if (declared.directive == "SPACE")
        {
          symbol.pop_back();
          declared.label = symbol;
          declared.param = "SPACE";
          DeclaredTable.push_back(declared);
        }
        else if (declared.directive == "MACRO")
        {
          symbol.pop_back();
          declared.label = symbol;
          declared.param = "MACRO";
          DeclaredTable.push_back(declared);
          MacroNameAndMacroDefinition macro;
          int counter = 0;
          macro.macroName = symbol;
          inf >> param;
          if (table->hasDirective(param) == nullptr && table->hasInstruction(param) == nullptr && param.back() != ':')
          {
            counter++;
            macro.macroDefinition.push_back(param);
          }
          else
          {
            macro.macroDefinition.push_back(param);
          }
          macro.nro_Argumentos = counter;

          while (param != "ENDMACRO")
          {
            inf >> param;
            macro.macroDefinition.push_back(param);
          }
          MacroTable.push_back(macro);
        }
      }
      else if (table->hasInstruction(maybeDirective) != nullptr)
      {
        DeclaredDirective declared;
        declared.directive = table->hasInstruction(maybeDirective)->name;
        symbol.pop_back();
        declared.label = symbol;
        declared.param = declared.directive;
        DeclaredTable.push_back(declared);
      }
    }
  }

  inf.clear();
  inf.seekg(0, std::ios::beg);

  std::string maybeLabel, maybeAnything;

  while (inf >> maybeAnything)
  {
    if (maybeAnything.back() == ':')
    {
      std::string maybeLabelEQU = maybeAnything;
      std::string maybeMacro = maybeAnything;
      maybeMacro.pop_back();
      if (hasMacro(maybeMacro) != nullptr)
      {
        inf >> maybeAnything;
        while (maybeAnything != "ENDMACRO")
        {
          inf >> maybeAnything;
        }
        inf >> maybeAnything;
      }
      maybeLabelEQU.pop_back();
      DeclaredDirective maybeEqu = *hasDeclared(maybeLabelEQU);
      if (maybeEqu.directive == "EQU")
      {
        inf >> maybeAnything;
        inf >> maybeAnything;
      }
      else
      {
        outf << maybeAnything;
        outf << " ";
      }
    }
    else if (table->hasDirective(maybeAnything) != nullptr)
    {
      std::string param, maybeAnythingIF;
      Directive directive = *table->hasDirective(maybeAnything);

      if (directive.name == "IF")
      {
        inf >> param;
        if (hasDeclared(param) != nullptr)
        {
          DeclaredDirective preProcessorIf = *hasDeclared(param);
          if (preProcessorIf.param == "0")
          {
            inf >> maybeAnythingIF;
            if (maybeAnythingIF.back() == ':')
            {
              inf >> maybeAnythingIF;
              if (table->hasDirective(maybeAnythingIF) != nullptr)
              {
                Directive diretiva = *table->hasDirective(maybeAnythingIF);
                for (int i = 1; i <= diretiva.nro_operandos; i++)
                {
                  inf >> param;
                }
              }
              else if (table->hasInstruction(maybeAnythingIF) != nullptr)
              {
                Instruction instruction = *table->hasInstruction(maybeAnythingIF);
                for (int i = 0; i < instruction.nro_operandos; i++)
                {
                  inf >> param;
                }
              }
            }
            else if (table->hasDirective(maybeAnythingIF) != nullptr)
            {
              Directive diretiva = *table->hasDirective(maybeAnythingIF);
              for (int i = 1; i <= diretiva.nro_operandos; i++)
              {
                inf >> param;
              }
            }
            else if (table->hasInstruction(maybeAnythingIF) != nullptr)
            {
              Instruction instruction = *table->hasInstruction(maybeAnythingIF);
              for (int i = 0; i < instruction.nro_operandos; i++)
              {
                inf >> param;
              }
            }
          }
        }
      }
      else
      {
        outf << maybeAnything;
        for (int i = 1; i <= directive.nro_operandos; i++)
        {
          outf << " ";
          inf >> param;
          if (hasDeclared(param) != nullptr)
          {
            DeclaredDirective declared = *hasDeclared(param);
            if (declared.param == "SPACE" || declared.param == "MACRO")
            {
              outf << declared.label;
            }
            else
            {
              outf << declared.param;
            }
          }
          else
          {
            outf << param;
          }
        }
        outf << std::endl;
      }
    }
    else if (table->hasInstruction(maybeAnything) != nullptr)
    {
      std::string param;
      Instruction instruction = *table->hasInstruction(maybeAnything);
      outf << maybeAnything;
      for (int i = 1; i <= instruction.nro_operandos; i++)
      {
        outf << " ";
        inf >> param;
        if (param.back() == ',')
        {
          param.pop_back();
        }
        if (hasDeclared(param) != nullptr)
        {
          DeclaredDirective declared = *hasDeclared(param);
          if (declared.param == "SPACE" || declared.param == "MACRO")
          {
            outf << declared.label;
          }
          else if (instruction.name == "JMP" || instruction.name == "JMPN" || instruction.name == "JMPP" || instruction.name == "JMPZ")
          {
            outf << declared.label;
          }
          else
          {
            outf << declared.param;
          }
        }
        else
        {
          outf << param;
        }
      }
      outf << std::endl;
    }
    else if (hasMacro(maybeAnything) != nullptr)
    {
      MacroNameAndMacroDefinition macro = *hasMacro(maybeAnything);
      std::vector<std::string> params;
      int i = 0;
      if (macro.nro_Argumentos > 0)
      {
        while (macro.nro_Argumentos > i)
        {
          inf >> maybeAnything;
          params.push_back(maybeAnything);
          i++;
        }
        int contadorDoParametro = 0;
        for (auto &param : params)
        {
          for (int i = 0; i < static_cast<int>(macro.macroDefinition.size()); i++)
          {
            if (macro.macroDefinition[i] == macro.macroDefinition[contadorDoParametro])
            {
              macro.macroDefinition[i] = param;
            }
          }
          contadorDoParametro++;
        }
      }
      for (int i = 0; i < static_cast<int>(macro.macroDefinition.size()); i++)
      {
        if (macro.macroDefinition[i].back() == ':')
        {
          outf << macro.macroDefinition[i];
        }
        else if (table->hasDirective(macro.macroDefinition[i]) != nullptr)
        {
          Directive declared = *table->hasDirective(macro.macroDefinition[i]);
          for (int j = i; j < i + declared.nro_operandos; j++)
          {
            if (hasDeclared(macro.macroDefinition[i]) != nullptr)
            {
              DeclaredDirective declared = *hasDeclared(macro.macroDefinition[i]);
              if (declared.param == "SPACE" || declared.param == "MACRO")
              {
                outf << declared.label;
              }
            }
            else
            {
              outf << macro.macroDefinition[j];
              if (j != i + declared.nro_operandos - 1)
              {
                outf << " ";
              }
            }
          }
          outf << std::endl;
        }
        else if (table->hasInstruction(macro.macroDefinition[i]) != nullptr)
        {
          Instruction instruction = *table->hasInstruction(macro.macroDefinition[i]);
          for (int j = i; j < i + instruction.nro_operandos; j++)
          {
            if (hasDeclared(macro.macroDefinition[j]) != nullptr)
            {
              DeclaredDirective declared = *hasDeclared(param);
              if (declared.param == "SPACE" || declared.param == "MACRO")
              {
                outf << declared.label;
              }
              else if (instruction.name == "JMP" || instruction.name == "JMPN" || instruction.name == "JMPP" || instruction.name == "JMPZ")
              {
                outf << declared.label;
              }
            }
            else
            {
              outf << macro.macroDefinition[j];
              if (j != i + instruction.nro_operandos - 1)
              {
                outf << " ";
              }
            }
          }
          outf << std::endl;
        }
      }
    }
  }

  if (!outf)
  {
    std::cerr << "Não conseguiu criar arquivo pre processado \n";
  }

  inf.close();
  outf.close();

  delete table;
};

std::string PreProcessor::changeFileNameExtension(std::string fileName)
{
  for (int i = 0; i < 3; i++)
  {
    fileName.pop_back();
  }
  fileName.push_back('p');
  fileName.push_back('r');
  fileName.push_back('e');

  return fileName;
};

DeclaredDirective *PreProcessor::hasDeclared(std::string label)
{
  std::transform(label.begin(), label.end(), label.begin(), ::toupper);
  for (DeclaredDirective &declared : DeclaredTable)
  {
    if (declared.label == label)
    {
      return &declared;
    }
  }
  return nullptr;
};
MacroNameAndMacroDefinition *PreProcessor::hasMacro(std::string macroName)
{
  std::transform(macroName.begin(), macroName.end(), macroName.begin(), ::toupper);
  for (MacroNameAndMacroDefinition &macro : MacroTable)
  {
    if (macro.macroName == macroName)
    {
      return &macro;
    }
  }
  return nullptr;
}

PreProcessor::PreProcessor(std::string fileName)
{
  run(fileName);
};
