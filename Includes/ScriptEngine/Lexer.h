#pragma once

namespace CTRPluginFramework::ScriptEngine {
  struct Token;
  class Lexer {
  public:
    Lexer(std::string const& source);
    
    Token* run();

  private:
    bool check();
    char peek();
    bool match(std::string_view s);
    void pass_space();

    std::string const& source;
    size_t position;
  };
}