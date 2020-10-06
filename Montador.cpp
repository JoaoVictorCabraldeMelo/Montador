#include <iostream>
#include <string>
#include <vector>
#include "fileReader.h"
#include "string.h"

int main(int argc, char *argv[])
{
  std::vector<std::string> flags;
  std::string fileName;

  if (argc < 3)
  {
    std::cerr << "Argumentos menores que os necessários defina o pre processamento com a flag -p ou executavel com a flag -o e arquivo a ser traduzido\n";
    exit(-1);
  }

  for (int i = 0; i < argc; i++)
  {
    if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "-o") == 0)
    {
      flags.push_back(argv[i]);
    }
    else
    {
      fileName = argv[i];
    }
  }
  FileReader *Reader = new FileReader(fileName, flags);
  delete Reader;
  return 0;
}