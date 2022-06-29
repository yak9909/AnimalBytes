#pragma once

#include <string>

namespace CTRPluginFramework::ScriptEngine {

  struct Token;
  struct Node;

  class Parser {
  public:
    explicit Parser(Token* token);
    ~Parser();

    Node* factor();
    Node* mul();
    Node* add();
    Node* expr();

    Node* parse();

    static Parser* get_instance();

  private:
    bool check();
    void next();
    bool eat(std::string_view s);
    void expect(std::string_view s);
    void expect_ident();
    Node* expect_typename();

    Token* token;
    Token* ate;
    std::vector<Node*> _allocated_nodes;

    friend Node;
  };

}