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

    virtual char const* what() const noexcept = 0;
  };

  class ConstructionFailureBase : std::exception {
  protected:
    explicit ConstructionFailureBase(char const* name)
      : typename(name)
    {
    }

  public:
    char const* typename;

    virtual char const* what() const noexcept = 0;
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

  class FailedToConstructNode : ConstructionFailureBase {
  public:
    explicit FailedToConstructNode(Node* node)
      : node(node)
    {
    }

    char const* what() const noexcept override {
      return Utils::Format("failed to construct node: %p", node).c_str();
    }

    Node* node;
  };

}