#include "Tables.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void Tables::makeInstructions()
{

  Instruction add, sub, mult, div, jmp, jmpn, jmpp, jmpz, copy, load, store, input, output, stop;

  add.name = "ADD";
  add.nro_operandos = 1;
  add.opcode = 1;
  add.tamanho = 2;

  sub.name = "SUB";
  sub.nro_operandos = 1;
  sub.opcode = 2;
  sub.tamanho = 2;

  mult.name = "MULT";
  mult.nro_operandos = 1;
  mult.opcode = 3;
  mult.tamanho = 2;

  div.name = "DIV";
  div.nro_operandos = 1;
  div.opcode = 4;
  div.tamanho = 2;

  jmp.name = "JMP";
  jmp.nro_operandos = 1;
  jmp.opcode = 5;
  jmp.tamanho = 2;

  jmpn.name = "JMPN";
  jmpn.nro_operandos = 1;
  jmpn.opcode = 6;
  jmpn.tamanho = 2;

  jmpp.name = "JMPP";
  jmpp.nro_operandos = 1;
  jmpp.opcode = 7;
  jmpp.tamanho = 2;

  jmpz.name = "JMPZ";
  jmpz.nro_operandos = 1;
  jmpz.opcode = 8;
  jmpz.tamanho = 2;

  copy.name = "COPY";
  copy.nro_operandos = 2;
  copy.opcode = 9;
  copy.tamanho = 3;

  load.name = "LOAD";
  load.nro_operandos = 1;
  load.opcode = 10;
  load.tamanho = 2;

  store.name = "STORE";
  store.nro_operandos = 1;
  store.opcode = 11;
  store.tamanho = 2;

  input.name = "INPUT";
  input.nro_operandos = 1;
  input.opcode = 12;
  input.tamanho = 2;

  output.name = "OUTPUT";
  output.nro_operandos = 1;
  output.opcode = 13;
  output.tamanho = 2;

  stop.name = "STOP";
  stop.nro_operandos = 0;
  stop.opcode = 14;
  stop.tamanho = 1;

  InstructionTable.push_back(add);
  InstructionTable.push_back(sub);
  InstructionTable.push_back(mult);
  InstructionTable.push_back(div);
  InstructionTable.push_back(jmp);
  InstructionTable.push_back(jmpn);
  InstructionTable.push_back(jmpp);
  InstructionTable.push_back(jmpz);
  InstructionTable.push_back(copy);
  InstructionTable.push_back(load);
  InstructionTable.push_back(store);
  InstructionTable.push_back(input);
  InstructionTable.push_back(output);
  InstructionTable.push_back(stop);
};

void Tables::makeDirectives()
{
  Directive section, space, cons, equ, equif, macro, endmacro;

  section.name = "SECTION";
  section.nro_operandos = 1;
  section.tamanho = 0;

  space.name = "SPACE";
  space.nro_operandos = 0;
  space.tamanho = 1;

  cons.name = "CONST";
  cons.nro_operandos = 1;
  cons.tamanho = 1;

  equ.name = "EQU";
  equ.nro_operandos = 1;
  equ.tamanho = 0;

  equif.name = "IF";
  equif.nro_operandos = 1;
  equif.tamanho = 0;

  macro.name = "MACRO";
  macro.nro_operandos = 0;
  macro.tamanho = 0;

  endmacro.name = "ENDMACRO";
  endmacro.nro_operandos = 0;
  endmacro.tamanho = 0;

  DirectiveTable.push_back(section);
  DirectiveTable.push_back(space);
  DirectiveTable.push_back(cons);
  DirectiveTable.push_back(equ);
  DirectiveTable.push_back(equif);
  DirectiveTable.push_back(macro);
  DirectiveTable.push_back(endmacro);
};

Tables::Tables()
{
  makeInstructions();
  makeDirectives();
};

Directive *Tables::hasDirective(std::string DirectiveFile)
{
  std::transform(DirectiveFile.begin(), DirectiveFile.end(), DirectiveFile.begin(), ::toupper);
  for (Directive &directive : DirectiveTable)
  {
    if (DirectiveFile == directive.name)
    {
      return &directive;
    }
  }

  return nullptr;
};