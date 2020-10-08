#include <fstream>
#include <string>
#include <vector>
#include "fileReader.h"
#include "preProcessor.h"

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
  PreProcessor *PreProcessor = new ::PreProcessor(fileName);
  delete PreProcessor;
  return true;
};

bool FileReader::makeObjFile(std::string fileName)
{
  for (int i = 0; i < 3; i++)
  {
    fileName.pop_back();
  }
  fileName.push_back('o');
  fileName.push_back('b');
  fileName.push_back('j');
  std::ofstream outf{fileName, std::ofstream::out};

  if (!outf)
  {
    std::cerr << "Não conseguiu criar arquivo objeto \n";
    return false;
  }

  outf << "Criamos o arquivo objeto \n";
  outf.close();
  return true;
}