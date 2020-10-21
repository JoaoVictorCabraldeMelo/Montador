#include "assembler.h"
#include "preProcessor.h"
#include "Tables.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

void Assembler::run(std::string fileName, std::vector<std::string> Memory, std::vector<DeclaredDirective> Declared)
{
  std::string newFileName;

  Tables *table = new Tables();

  newFileName = changeFileNameToObj(fileName);
  std::ofstream outf{newFileName, std::ofstream::out};

  if (!outf)
  {
    std::cerr << "Não consegui gerar o arquivo OBJ \n";
  }

  std::string maybeAnything;
  int contador_instruction = 0;

  for (int i = 0; i < static_cast<int>(Memory.size()); i++)
  {
    if (Memory[i] == "CONST")
    {
      constSalva direc;
      std::string newLabel = Memory[i - 1];
      newLabel.pop_back();
      direc.label = newLabel;
      direc.param = Memory[i + 1];
      Constantes.push_back(direc);
    }
  }

  for (int i = 0; i < static_cast<int>(Memory.size()); i++)
  {
    if (Memory[i] == "DATA")
    {
      break;
    }
    for (auto &constante : Constantes)
    {
      if (Memory[i] == constante.param)
      {
        Memory[i] = constante.label;
      }
    }
  }

  for (auto &token : Memory)
  {
    if (token.back() == ':')
    {
      if (table->hasSymbol(token) == nullptr)
      {
        Symbol symbol;
        std::string newSymbol = token;
        newSymbol.pop_back();
        symbol.symbol = newSymbol;
        symbol.value = contador_instruction;
        table->SymbolTable.push_back(symbol);
      }
      else
      {
        std::cerr << "Rotulo redefinido" << std::endl;
      }
    }
    else if (table->hasInstruction(token) != nullptr)
    {
      int tamanho = table->hasInstruction(token)->tamanho;
      contador_instruction += tamanho;
    }
    else if (table->hasDirective(token) != nullptr)
    {
      int tamanho = table->hasDirective(token)->tamanho;
      contador_instruction += tamanho;
    }
  }

  for (int i = 0; i < static_cast<int>(Memory.size()); i++)
  {
    if (table->hasSymbol(Memory[i]) != nullptr)
    {
      int value = table->hasSymbol(Memory[i])->value;
      outf << " ";
      outf << value;
    }
    else if (table->hasInstruction(Memory[i]) != nullptr)
    {
      int value = table->hasInstruction(Memory[i])->opcode;
      outf << " ";
      outf << value;
    }
    else if (table->hasDirective(Memory[i]) != nullptr)
    {
      Directive directive = *table->hasDirective(Memory[i]);
      if (directive.name == "SPACE")
      {
        outf << " ";
        outf << "00";
      }
      else if (directive.name == "CONST")
      {
        outf << " ";
        outf << Memory[i + 1];
      }
    }
  }

  delete table;
  outf.close();
};

std::string Assembler::changeFileNameToObj(std::string fileName)
{
  for (int i = 0; i < 3; i++)
  {
    fileName.pop_back();
  }
  fileName.push_back('o');
  fileName.push_back('b');
  fileName.push_back('j');

  return fileName;
}

DeclaredDirective *Assembler::hasDeclared(std::string number, std::vector<DeclaredDirective> Declared)
{
  for (DeclaredDirective &declared : Declared)
  {
    if (declared.param == number)
    {
      return &declared;
    }
  }
  return nullptr;
};

Assembler::Assembler(std::string fileName, std::vector<std::string> Memory, std::vector<DeclaredDirective> Declared)
{
  run(fileName, Memory, Declared);
}
