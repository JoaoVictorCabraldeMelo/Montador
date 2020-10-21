#include <fstream>
#include <string>
#include <vector>

#include "fileReader.h"
#include "preProcessor.h"
#include "assembler.h"

FileReader::FileReader(std::string fileName, std::vector<std::string> flags)
{

  for (std::string flag : flags)
  {
    if (flag == "-p")
    {
      makePreFile(fileName);
    }
    if (flag == "-o")
    {
      makeObjFile(fileName);
    }
  }
};

bool FileReader::makePreFile(std::string fileName)
{
  PreProcessor *PreProcessor = new ::PreProcessor(fileName, false);
  delete PreProcessor;
  return true;
};

bool FileReader::makeObjFile(std::string fileName)
{
  PreProcessor *PreProcessor = new ::PreProcessor(fileName, true);

  std::string newFileName = PreProcessor->changeFileNameExtension(fileName);

  std::vector<std::string> Memory = PreProcessor->OnMemory;

  Assembler *Assembler = new ::Assembler(fileName, Memory, PreProcessor->DeclaredTable);

  delete Assembler;
  delete PreProcessor;
  return true;
}