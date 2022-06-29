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
  public:
    explicit LexError(size_t errpos, std::string const& msg)
      : msg(msg)
    {
      this->errpos = errpos;
    }

    char const* what() const noexcept override {
      return (Utils::Format("position=%zu: ", errpos) + msg).c_str();
    }

    std::string msg;
  };

}