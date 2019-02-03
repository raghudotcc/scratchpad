#ifndef SHORTCUT_H
#define SHORTCUT_H
#include <array>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>
#define NPOS -1

namespace shortcut {

using byte = char;

class Shortcut {
public:
 void set_reg_opt(std::map<std::string, std::string> reg_opt); 
 void set_dereg_opt(std::vector<std::string> dereg_opt);
 void set_exec_opt(std::vector<std::string> exec_opt);
 bool execute();

 // Result shouldn't be empty
 operator bool();
      
private:
  std::map<std::string, std::string> dir_reg_aliases; // check the shortcut.dir before adding here
  std::map<std::string, std::string> cmd_reg_aliases; // check the shortcut.cmd before adding here
  std::vector<std::string> dereg_aliases; // add only if found in the maps or the files
  std::vector<std::string> exec_aliases; // add only if found in the maps or the files
  bool run_reg();
  bool run_dereg();
  bool run_exec();

  bool is_dir_shortcut(std::vector<std::string> reg_opt);
  bool is_dir_shortcut(std::string reg_opt);

  bool is_cmd_shortcut(std::vector<std::string> reg_opt);
  bool is_cmd_shortcut(std::string reg_opt);
  
  int get_expansion_idx(const std::string& str,const std::string& pat, int occurrence);
  const std::string shortcut_conf = "shortcut.conf";
  const std::string DIR_MNEMONIC = "::dir::";
  const std::string CMD_MNEMONIC = "::cmd::";
  const std::string SELECT_ALL = "*";
  const std::string DELIM = ":";
};

class Util {
public:
  static std::string 
  strip_quotes(std::string str)
  {
    const char quote = '"';
    if (str.front() == quote && str.back() == quote) {
      str.erase(0, 1);
      str.erase(str.size() - 1);
    }

    return str;
  }

  static bool
  check_if_dir(std::string str)
  {
    struct stat statbuf;
    bool is_dir = false;
    if (stat(str.c_str(), &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
    {
      is_dir = true;  
    }

    return is_dir;
  }

  static bool
  starts_with(std::string main_str, std::string sub_str)
  {
    auto pos = main_str.find(sub_str);
    if (pos == 0) 
      return true;
    
    return false;
  }

  /* Return cmd output if any */
  static std::string 
  get_cmd_out(std::string cmd)
  {
    // std::string suppress_stderr = " 2> /dev/null"; /* suppress stderr */
    // cmd += suppress_stderr; /* append to cmd */
    std::array<byte, 128> buff;
    std::string res;
    std::shared_ptr<FILE> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe)
      throw std::runtime_error("popen failed !");
    while (!feof(pipe.get())) {
      if (fgets(buff.data(), 128, pipe.get()) !=  nullptr)
        res += buff.data(); /* does not take into account stderr output */
    }
    return res;
  }

  /* Return command status code */
  static int 
  get_sta_code()
  {
    return std::stoi(get_cmd_out("echo $?"));
  }


  static int
  get_nth_occ_idx(const std::string& str,
                  const std::string& pat,
                  int occurrence) {
     std::string::size_type i = str.find(pat);
     std::string::size_type adv = 1;

     int j;
     for (j = 1; j < occurrence && i != std::string::npos; ++j) {
        i = str.find(pat, i+adv);
     }

     if (j == occurrence)
       return i;
     else
       return NPOS;
  }


  static void
  usage() 
  {
    std::cout << "Usage: shortcut [OPTION] [ALIAS]...\n";  
    std::cout << "       example: shortcut -r <alias_0=\"path_to_directory\"> \
 <alias_1=\"command\">\n";
    std::cout << "       shortcut -d <alias0> <alias1> ...\n";
    std::cout << "       shortcut <alias0> <alias1> ..." << std::endl;
  }

};


enum class UserError {
  INVALID_ARG_COUNT,
  INVALID_CMD_NAME,
  REDUNDANT_SHORTCUT,
  INVALID_SHORTCUT,
  NO_ARGUMENT_PROVIDED,
};

enum class InternalError {
 IOERROR, 
};

class ErrorHandler {
public:
  static void
  handle(UserError&& user_error) 
  {
    std::string error_msg;
    switch(user_error) {
      case UserError::INVALID_ARG_COUNT: error_msg= "Error: Invalid Argument Count.\n"; break;
      case UserError::INVALID_CMD_NAME: error_msg= "Error: Invalid Command Name.\n"; break;
      case UserError::REDUNDANT_SHORTCUT: error_msg= "Error: Shortcut already present.\n"; break;
      case UserError::INVALID_SHORTCUT: error_msg= "Error: Invalid Shortcut.\n"; break;
      case UserError::NO_ARGUMENT_PROVIDED: error_msg= "Error: Please provide atleast one shortcut\n"; break;
    }

    std::cout << error_msg; 
    Util::usage();
    std::exit(EXIT_FAILURE);
  }

  static void 
  handle(InternalError&& internal_error) 
  {
    std::string error_msg;
    switch(internal_error) {
      case InternalError::IOERROR: error_msg= "Error: Could not register shortcut due to some internal i/o error.\n"; break;
    }

    std::cout << error_msg; 
    Util::usage();
    std::exit(EXIT_FAILURE);
     
  }
};

enum class Option {
  REGISTER,
  DEREGISTER,
  EXECUTE,
  HELP,
};

class Parser {
public:
  Parser() = default;
  Shortcut parse(int argc, char** argv);
private:
  bool parse_reg_opt(char** argv, int reg_offset);
  bool parse_dereg_opt(char** argv, int dereg_offset);
  bool parse_exec_opt(char** argv, int exec_offset);

 void help();

  const uint8_t MIN_ARG_COUNT = 2;
  const char* REGISTER_SHORT = "-r";
  const char* REGISTER_LONG = "--register";
  const char* DEREGISTER_SHORT = "-d";
  const char* DEREGISTER_LONG = "--deregister";
  const char* SHORTCUT = "shortcut";
  const char* SHORTCUT_TMP = "./shortcut";
  const char* HELP_SHORT = "-h";
  const char* HELP_LONG = "--h";
  const char REG_DELIM = '='; 
  unsigned int m_arg_count;
 
  /* Reason for this design decision is 
     to allow multiple types of options in a
     single command in future */
  std::map<std::string, std::string> m_reg_opts;
  std::vector<std::string> m_dereg_opts;
  std::vector<std::string> m_exec_opts;
  Shortcut m_shortcut;
  Option m_option;
};

}

#endif // SHORTCUT_H
