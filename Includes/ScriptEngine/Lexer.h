#pragma once

namespace CTRPluginFramework::ScriptEngine {
  struct Token;
  class Lexer {
  public:
    Lexer(std::string const& source);
    
    Token* run();

  private:
    
  };
}