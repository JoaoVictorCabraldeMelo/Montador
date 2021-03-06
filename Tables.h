#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <vector>

struct Instruction
{
  std::string name;
  int opcode;
  int nro_operandos;
  int tamanho;
};

struct Directive
{
  std::string name;
  int nro_operandos;
  int tamanho;
};

struct Symbol
{
  std::string symbol;
  int value;
};

class Tables
{
private:
  void makeInstructions();
  void makeDirectives();

public:
  Tables();

  std::vector<Instruction> InstructionTable;
  std::vector<Directive> DirectiveTable;
  std::vector<Symbol> SymbolTable;

  Directive *hasDirective(std::string Directive);
  Instruction *hasInstruction(std::string Instruction);
  Symbol *hasSymbol(std::string Symbol);
  
};

#endif