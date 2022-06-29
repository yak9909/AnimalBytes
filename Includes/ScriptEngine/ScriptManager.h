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

    static void destroy(ScriptData* data);
  };

  class MenuEntry;
  class MenuFolder;
  class ScriptManager {
  public:

    static void initialize();

    static void run_active_scripts(MenuEntry *e);
    static void load_script_file(MenuEntry* e);

    static MenuFolder* create_folder();

    static ScriptData* compile(std::string const& path);

  private:
    static std::vector<ScriptData> data_list;

  };

}