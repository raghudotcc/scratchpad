#include <array>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
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
#include <shortcut.h>

namespace shortcut {

bool 
Parser::parse_reg_opt(char** argv, int reg_offset) 
{
  std::istringstream curr_arg;
  for (int i = reg_offset; i < m_arg_count; i++) {
    curr_arg.str(argv[i]);
    std::string key, value;
    while (std::getline(std::getline(curr_arg, key, REG_DELIM) >> std::ws, value)) {
      if (key.empty() || value.empty()) {
        return false; 
      }
      m_reg_opts[key] = Util::strip_quotes(value);
    }
  }

  return true;
}

bool
Parser::parse_dereg_opt(char** argv, int dereg_offset)
{
  for (int i = dereg_offset; i < m_arg_count; i++) {
    m_dereg_opts.push_back(argv[i]); 
  }

  return true;
}

bool
Parser::parse_exec_opt(char** argv, int exec_offset)
{
  for (int i = exec_offset; i < m_arg_count; i++) {
    m_exec_opts.push_back(argv[i]);
  }

  return true;
}

void
Parser::help() 
{
  Util::usage();
  std::exit(EXIT_SUCCESS);
}

/*
 * shortcut -r shortcut0="path_to_shortcut" shortcut1="real_command" ...
 * shortcut -d shortcut1 shortcut2 ...
 * shortcut -d *
 * shortcut shortcut0 shortcut3 shortcut4 ...
 * shortcut -h
 * MIN_ARG_COUNT = 2
 * MAX_ARG_COUNT >= 3
 */
Shortcut
Parser::parse(int argc, char** argv)
{
  if (argc < MIN_ARG_COUNT) {
    ErrorHandler::handle(UserError::INVALID_ARG_COUNT); // show error - usage - terminate
  }
  m_arg_count = argc;

  if (strcmp(argv[0],SHORTCUT) && strcmp(argv[0],SHORTCUT_TMP) && strcmp(argv[0], "/home/raghu/Development/shortcut/shortcut")) {
    ErrorHandler::handle(UserError::INVALID_CMD_NAME); // show error - usage - terminate  
  }

  /* Store option type */
  if (!strcmp(argv[1], REGISTER_SHORT) || !strcmp(argv[1], REGISTER_LONG)) {
    m_option = Option::REGISTER;
  } else if (!strcmp(argv[1], DEREGISTER_SHORT) || !strcmp(argv[1], DEREGISTER_LONG)) {
    m_option = Option::DEREGISTER;
  } else if (!strcmp(argv[1], HELP_SHORT) || !strcmp(argv[1], HELP_LONG)) {
    m_option = Option::HELP;   
  } else {
    m_option = Option::EXECUTE;   
  }
  
  const int reg_offset = 2;
  const int dereg_offset = 2;
  const int exec_offset = 1;
  /* Store the shortcuts based on OptionType */
  switch (m_option) {
    case Option::REGISTER: 
      if (parse_reg_opt(argv, reg_offset)) {
        m_shortcut.set_reg_opt(m_reg_opts);
      }
      break;
    case Option::DEREGISTER: 
      if (parse_dereg_opt(argv, dereg_offset)) {
        m_shortcut.set_dereg_opt(m_dereg_opts);  
      }
      break;
    case Option::EXECUTE: 
      if (parse_exec_opt(argv, exec_offset)) {
        m_shortcut.set_exec_opt(m_exec_opts);  
      }
      break;
    case Option::HELP:
    default:
      help();
      break;
  }

  return m_shortcut;
}

bool 
Shortcut::is_dir_shortcut(std::string opt) 
{
  std::ifstream dir_stream(shortcut_conf.c_str());
  std::string line;
  if (dir_stream) {
    while (std::getline(dir_stream, line)) {
      auto alias = line.substr(7, Util::get_nth_occ_idx(line, DELIM, 5) - 7);
      if (alias == opt && Util::starts_with(line, DIR_MNEMONIC)) {
        return true;
      }
    }
  } 

  return false;
}

bool 
Shortcut::is_dir_shortcut(std::vector<std::string> reg_opt)
{ 
  bool cmdStatus = true;
  for (auto opt : reg_opt) {
    if (!is_dir_shortcut(opt)) {
      cmdStatus = false;
      break;
    }
  }
  return cmdStatus;
}


bool 
Shortcut::is_cmd_shortcut(std::string opt) 
{
  std::ifstream cmd_stream(shortcut_conf.c_str());
  std::string line;
  if (cmd_stream) {
    while (std::getline(cmd_stream, line)) {
      auto alias = line.substr(7, Util::get_nth_occ_idx(line, DELIM, 5) - 7);
      if (alias == opt && Util::starts_with(line, CMD_MNEMONIC)) {
        return true;
      }
    }
  } 

  return false;
}

bool 
Shortcut::is_cmd_shortcut(std::vector<std::string> reg_opt)
{ 
  bool cmdStatus = true;
  for (auto opt : reg_opt) {
    if (!is_cmd_shortcut(opt)) {
      cmdStatus = false;
      break;
    }
  }
  return cmdStatus;
}

void
Shortcut::set_reg_opt(std::map<std::string, std::string> reg_opt)
{
  if (reg_opt.empty()) {
    ErrorHandler::handle(UserError::NO_ARGUMENT_PROVIDED);
  }

  std::vector<std::string> reg_opt_vec;
  for (auto& opt : reg_opt) {
    reg_opt_vec.push_back(opt.first);
  }

  if (is_dir_shortcut(reg_opt_vec) || is_cmd_shortcut(reg_opt_vec)) {
    ErrorHandler::handle(UserError::REDUNDANT_SHORTCUT);  
  }

  //check if a directory
  for (auto opt : reg_opt) {
    if (Util::check_if_dir(opt.second)) {
        dir_reg_aliases[opt.first] = opt.second;
    } else {
        cmd_reg_aliases[opt.first] = opt.second;  
    }
  }
}


void 
Shortcut::set_dereg_opt(std::vector<std::string> dereg_opt)
{
  if (dereg_opt.empty()) {
    ErrorHandler::handle(UserError::NO_ARGUMENT_PROVIDED);
  }
  if (!is_dir_shortcut(dereg_opt) && !is_cmd_shortcut(dereg_opt))  {
    ErrorHandler::handle(UserError::INVALID_SHORTCUT);  
  }

  for (auto opt : dereg_opt) {
    dereg_aliases.push_back(opt);
  }
}

void 
Shortcut::set_exec_opt(std::vector<std::string> exec_opt) 
{
  if (exec_opt.empty()) {
    ErrorHandler::handle(UserError::NO_ARGUMENT_PROVIDED);
  }
  if (!is_dir_shortcut(exec_opt) && !is_cmd_shortcut(exec_opt)) {
    ErrorHandler::handle(UserError::INVALID_SHORTCUT);
  }

  for (auto opt : exec_opt) {
    exec_aliases.push_back(opt);
  }
}

Shortcut::operator bool()
{
  if (dir_reg_aliases.empty() || cmd_reg_aliases.empty() || dereg_aliases.empty() && exec_aliases.empty()) {
      return true;
    }

  return false;
}

bool
Shortcut::run_reg()
{
  std::ofstream reg_stream(shortcut_conf, std::ios::app);
  
  if (!reg_stream)
    ErrorHandler::handle(InternalError::IOERROR);

  for (auto& dir_reg_alias : dir_reg_aliases) {
    reg_stream << DIR_MNEMONIC << dir_reg_alias.first << ":" << dir_reg_alias.second << std::endl;
  }
  
  for (auto& cmd_reg_alias : cmd_reg_aliases) {
    reg_stream << CMD_MNEMONIC << cmd_reg_alias.first << ":" << cmd_reg_alias.second << std::endl;
  }

  return true;
}

bool 
Shortcut::run_dereg()
{
  if (dereg_aliases.size() == 1) {
    if (dereg_aliases.back() == SELECT_ALL) {
      std::remove(shortcut_conf.c_str());
      return true;
    }
  } 

  std::ifstream dereg_stream(shortcut_conf);
  std::string line;
  std::vector<std::string> tmp_dereg_aliases;
  while (std::getline(dereg_stream, line)) {
    for (auto& dereg_alias : dereg_aliases) {
      if (line.find(dereg_alias) != 7) {
        tmp_dereg_aliases.push_back(line);
      }
    }
  }
  dereg_stream.close();

  std::ofstream dereg_ostream(shortcut_conf);
  for (auto& tmp_dereg_alias : tmp_dereg_aliases) {
    dereg_ostream << tmp_dereg_alias << "\n";
  }

  return true;
}

void doit(std::string dir_path)
{
  FILE *p;
  // char cmd[34];
  std::cout << dir_path << std::endl;
  auto pid = (long)getppid();
  std::string cmd = "reptyr " + std::to_string(pid) + "; cd " + dir_path;
  //std::string dir_cmd = "call (char)(chdir(\"" + dir_path + "\"))\ndetach\nquit\n";
  // fprintf(p, "%s", dir_cmd.c_str());
  //fclose(p);
  //sprintf(cmd, "gdb -p %d -batch -x /tmp/gdb_cmds", getppid());
  system(cmd.c_str()); 
}

bool 
Shortcut::run_exec() 
{
  std::ifstream exec_stream(shortcut_conf);
  std::string line;

  while (std::getline(exec_stream, line)) {
    if (Util::starts_with(line, DIR_MNEMONIC)) {
      doit(line.substr(Util::get_nth_occ_idx(line, DELIM, 5) + 1, line.size() - 1));  
      // if (res == NPOS)         return false;
      }
     
    
    if (Util::starts_with(line, CMD_MNEMONIC)) {
      std::cout << Util::get_cmd_out(line.substr(Util::get_nth_occ_idx(line, DELIM, 5) + 1, line.size() - 1).c_str()) << std::endl;
      if (Util::get_sta_code() != 0) {
        return false;
      }
    }
  }

  return true;
}

bool
Shortcut::execute() 
{
  bool cmd_status = false;
  if (!dir_reg_aliases.empty() || !cmd_reg_aliases.empty()) {
    cmd_status = run_reg();
  } 
  if (!dereg_aliases.empty()) {
    cmd_status = run_dereg();
  }
  if (!exec_aliases.empty()) {
    cmd_status = run_exec();  
  }
  return cmd_status;
}
}
