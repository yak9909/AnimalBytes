#include <string>
#include <vector>
#include <CTRPluginFramework.hpp>

#include "ScriptEngine/Types/Token.h"
#include "ScriptEngine/Types/Variable.h"
#include "ScriptEngine/Types/TypeInfo.h"
#include "ScriptEngine/Types/Object.h"
#include "ScriptEngine/Types/Node.h"
#include "ScriptEngine/Types/IL.h"

#include "ScriptEngine/Lexer.h"
#include "ScriptEngine/Parser.h"
#include "ScriptEngine/Exceptions.h"
#include "ScriptEngine/ScriptManager.h"

namespace CTRPluginFramework::ScriptEngine {
  std::vector<ScriptData> ScriptManager::data_list;

  static void node_deleter(Node* node) {
    if( node->lhs ) node_deleter(node->lhs);
    if( node->rhs ) node_deleter(node->rhs);

    for( auto&& i : node->list ) {
      if( i ) node_deleter(i);
    }

    delete node;
  }

  void ScriptData::destroy(ScriptData* data) {
    do {
      auto tmp = data->tokens->next;
      delete data->tokens;
      data->tokens = tmp;
    } while( data->tokens );

    node_deleter(data->node);

    delete data;
  }

  void ScriptManager::initialize() {

  }

  void ScriptManager::run_active_scripts(MenuEntry *e) {
    for( auto&& data : data_list ) {
      if( data.built_in ) {
        continue;
      }


    }
  }
  
  void ScriptManager::load_script_file(MenuEntry* e) {

  }

  MenuFolder* ScriptManager::create_folder() {

  }

  ScriptData* ScriptManager::compile(std::string const& path) {
    for( auto&& data : data_list ) {
      if( data.path == path ) {
        return &data;
      }
    }

    File file{ path, File::READ };

    if( !file.IsOpen() ) {
      throw new CannotOpenFileError;
    }

    LineReader reader{ file };
    std::string src;

    for( std::string line; reader(line); ) {
      src += line + '\n';
    }

    if( [&](){for(auto&&c:src){if(c>' ')return 0;}return 1;}() ) {
      return nullptr;
    }

    Lexer lexer{ src };
    auto tokens = lexer.run();
    
    Parser parser{ tokens };
    auto node = parser.parse();
    
    return &data_list.emplace_back(ScriptData{
      .built_in = false,
      .path = path,
      .source = src,
      .tokens = tokens,
      .node = node,
      .oplist = oplist
    });
  }
}