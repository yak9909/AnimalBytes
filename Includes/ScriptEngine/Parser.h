#pragma once

#include <string>

namespace CTRPluginFramework::ScriptEngine {

  struct Token;
  struct Node;

  class Parser {
  public:
    explicit Parser(Token* token);

    Node* parse();

  private:
    bool check();
    void next();
    bool eat(std::string_view s);
    void expect(std::string_view s);
  };

}