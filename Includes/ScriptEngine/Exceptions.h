#pragma once

#include <stdexcept>
#include <CTRPluginFramework/Utils/Utils.hpp>

namespace CTRPluginFramework::ScriptEngine {

  class CannotOpenFileError : std::exception {
  public:
    char const* what() const noexcept override {
      return "cannot open file";
    }
  };

  class CompileErrorBase : std::exception {
  protected:
    explicit CompileErrorBase(size_t errpos = 0)
      : errpos(errpos)
    {
    }

  public:
    size_t errpos;
  };

  class LexError : CompileErrorBase {
    std::string msg;

  public:
    explicit LexError(size_t errpos, std::string const& msg)
      : msg(msg)
    {
      this->errpos = errpos;
    }

    char const* what() const noexcept override {
      return (Utils::Format("position=%zu: ", errpos) + msg).c_str();
    }
  };

  struct Token;
  struct Node;
  class ParseError : CompileErrorBase {
    std::string msg;

  public:
    ParseError(size_t pos, std::string const& msg);
    ParseError(Token* token, std::string const& msg);
    ParseError(Node* node, std::string const& msg);
    
    char const* what() const noexcept override;
  };

}