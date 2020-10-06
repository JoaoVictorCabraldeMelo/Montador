#ifndef FILEREADER_H
#define FILEREADER_H

#include <iostream>
#include <string>
#include <vector>

class FileReader
{
public:
  FileReader(std::string fileName, std::vector<std::string> flags);
  bool makePreFile(std::string filename);
  bool makeObjFile(std::string filename);
};

#endif