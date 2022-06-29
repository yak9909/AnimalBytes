#pragma once

#include <string>

namespace CTRPluginFramework::ScriptEngine {

  struct Token;
  struct Node;

  class Parser {
  public:
    explicit Parser(Token* token);

    Node* factor();
    Node* mul();
    Node* add();
    Node* expr();

    Node* parse();

  private:
    bool check();
    void next();
    bool eat(std::string_view s);
    void expect(std::string_view s);

    Token* token;
    Token* ate;
  };

}