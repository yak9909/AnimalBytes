#pragma once

namespace CTRPluginFramework::ScriptEngine {

  struct Token;
  struct Node;
  struct ILOperator;
  struct ScriptData {
    std::string path;
    std::string source;
    Token* tokens;
    Node* node;
    std::vector<ILOperator> oplist;
  };

  class ScriptManager {
  public:

    static ScriptData const* compile(std::string const& path);

  private:
    static std::vector<ScriptData> data_list;

  };

}