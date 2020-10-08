#include "preProcessor.h"
#include "Tables.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void PreProcessor::run(std::string fileName)
{
  Tables *table = new Tables();

  std::string newFileName = fileName;

  newFileName = changeFileNameExtension(newFileName);

  std::ofstream outf{newFileName, std::ofstream::out};

  std::ifstream inf{fileName};

  if (!inf)
  {
    std::cerr << "Não consegui achar o arquivo para Pre Processar \n";
  }

  while (inf)
  {
    std::string maybeDirective, directive, param;
    inf >> maybeDirective;
    if (table->hasDirective(maybeDirective) != nullptr)
    {
      directive = table->hasDirective(maybeDirective)->name;

      if (directive == "CONST")
      {
        inf >> param;
        try
        {
          std::stoi(param);
        }
        catch (const std::invalid_argument &ia)
        {
          std::cerr << "Não pode usar CONST com valor não decimal: " << ia.what() << std::endl;
        }
      }
      else if (directive == "EQU")
      {
        std::cout << "Diretiva EQU\n";
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
}

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
}

PreProcessor::PreProcessor(std::string fileName)
{
  run(fileName);
}
