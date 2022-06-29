#pragma once

namespace CTRPluginFramework {
  class MenuEntry;
  class MenuFolder;
}

namespace CTRPluginFramework::ScriptEngine {

  struct Token;
  struct Node;
  struct Object;
  struct ILOperator;

  struct ScriptData {
    bool built_in;
    bool activated;
    std::string path;
    std::string source;
    Token* tokens;
    Node* node;
    std::vector<ILOperator> oplist;

    Object* execute();
    static void destroy(ScriptData* data);
  };

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