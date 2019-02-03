#include <shortcut.h>

int main(int argc, char** argv)
{
  shortcut::Parser parser;
  shortcut::Shortcut result = parser.parse(argc, argv);
  if (result) 
  {
    result.execute();
  }
  
  return 0;
}
