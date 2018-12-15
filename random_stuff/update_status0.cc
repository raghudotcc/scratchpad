#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <fstream>
#include <cstring>
#include <chrono>
#include <cstdlib>
#include <cctype>

std::string generateFileName()
{
  auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
  return std::string("tmp.") + 
    std::to_string(std::chrono::duration_cast<std::chrono::seconds>(now).count()) + 
    ".status";

}

bool createStatusFile(std::string fileName)
{
  std::ofstream tmpStatusFile(fileName, std::ios::out);
  // Add comments
  tmpStatusFile << "**************************************************************************************************\n";
  tmpStatusFile << "*        Advice to follow:                                                                       *\n";
  tmpStatusFile << "*        -----------------                                                                       *\n";
  tmpStatusFile << "* 1. Please do not nest items. PmWiki does not support nested entries.                           *\n";
  tmpStatusFile << "* 2. You don't have to specify you name, we will fetch it for you.                               *\n";
  tmpStatusFile << "* 3. You don't have to specify line number like (1. something), but its okay even if you specify.*\n";
  tmpStatusFile << "* 4. We don't check for abominated itemizer like \" 1 . \" or \"*\" or \">\" etc.                *\n";
  tmpStatusFile << "**************************************************************************************************\n";
  tmpStatusFile << "               WRITE BELOW THIS POINT. THIS IS MY MARKER TO FETCH YOUR ITEMS/ LIST  \n";
  tmpStatusFile << " " << std::endl;
  return tmpStatusFile.good();
}

void 
printPmWikiStatus(std::string inputFileName)
{
  std::ifstream ifs(inputFileName);
  // snip till /*-----*/
  std::string line;
  std::stringstream statusContent;
  int statusContentFlag = false;
  int itemCount = 0;
  while (std::getline(ifs, line)) {
    if (statusContentFlag == true) {
      if (!line.empty()) {
        ++itemCount;
        std::string itemizer = std::to_string(itemCount) + ".";
        bool alphaState = false;
        int itemPos = 0;
        if ((itemPos = line.find(itemizer)) != std::string::npos) {
          for (auto it = line.begin(); it != line.begin() + itemPos; it++) {
            if (isalpha(*it)) {
              alphaState = true;
              break;
            }
          }
          if (alphaState == true) {
            statusContent << "# " << line << "\n"; 
          } else {
            // strip it and place hash
            line.replace(0, itemPos + 3, "# ");
            statusContent << line << "\n";
          }
        } else {
          statusContent << "# " << line << "\n"; 
        }
      }
    }
    auto pos = line.find("WRITE BELOW THIS POINT");
    if (pos != std::string::npos) {
      statusContentFlag = true;
    }
  }
  
  // if created, change permissions
  std::cout << "\n";
  std::cout << "!@@" << __DATE__ << "@@" << std::endl;
  std::cout << "----\n";
  std::cout << statusContent.str() << "\n\n";

}

void 
copyRegularStatus(std::string inputFileName, std::string outputFileName) 
{
  std::ifstream ifs(inputFileName);
  // snip till /*-----*/
  std::string line;
  std::stringstream statusContent;
  int statusContentFlag = false;
  int itemCount = 0;
  while (std::getline(ifs, line)) {
    if (statusContentFlag == true) {
      if (!line.empty()) {
        ++itemCount;
        std::string itemizer = std::to_string(itemCount) + ".";
        bool alphaState = false;
        int itemPos = 0;
        if ((itemPos = line.find(itemizer)) != std::string::npos) {
          for (auto it = line.begin(); it != line.begin() + itemPos; it++) {
            if (isalpha(*it)) {
              alphaState = true;
              break;
            }
          }
          if (alphaState == true) {
            statusContent << itemCount << ". " << line << "\n"; 
          } else {
            statusContent << line << "\n";
          }
        } else {
          statusContent << itemCount << ". " << line << "\n"; 
        }
      }
    }
    auto pos = line.find("WRITE BELOW THIS POINT");
    if (pos != std::string::npos) {
      statusContentFlag = true;
    }
  }
  
  // if created, change permissions
  std::ofstream ofs(outputFileName, std::ios::app);
  std::string username = getenv("USER");
  std::transform(username.begin(), username.end(), username.begin(), [](unsigned char c){ return std::tolower(c); });
  username[0] = std::toupper(username[0]);
  ofs << username << "\n";
  ofs << "------------------\n";
  ofs << statusContent.str() << "\n\n";
}

enum class ErrCode {
  INCORRECT_COMMAND_NAME,
  INVALID_ARG_COUNT
};

/* up filename */
int 
main(int argc, char** argv)
{
  auto usage = []() -> void { std::cout << "Usage: up <filename>\n"; };
  auto handleError = [](ErrCode errCode) -> void 
    { std::string errMsg;
      switch(errCode) {
        case ErrCode::INCORRECT_COMMAND_NAME: errMsg = "Error: Incorrect Command Name."; break;
        case ErrCode::INVALID_ARG_COUNT: errMsg = "Error: Invalid Arg Count"; break;
      }
      std::cout << errMsg << std::endl;
      std::exit(EXIT_FAILURE);
    };

  if (strcmp(argv[0], "./up") != 0)  { usage(); handleError(ErrCode::INCORRECT_COMMAND_NAME); }
  if (argc < 2) { usage(); handleError(ErrCode::INVALID_ARG_COUNT); }
  
  std::string fileName = generateFileName();  
  std::string cmd = "vim " + fileName;
  
  if (createStatusFile(fileName))
    system(cmd.c_str());

  copyRegularStatus(fileName, std::string(argv[1]));
  printPmWikiStatus(fileName);
  
  std::remove(fileName.c_str());
  return 0;
}
