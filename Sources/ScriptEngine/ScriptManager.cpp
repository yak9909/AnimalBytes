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
#include "ScriptEngine/Evaluater.h"
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

      if( data.activated ) {

      }
    }
  }
  
  void ScriptManager::load_script_file(MenuEntry* e) {

  }

  MenuFolder* ScriptManager::create_folder() {
    auto folder = new MenuFolder("Scripts");

    folder->Append(new MenuEntry("run active scripts", run_active_scripts));

    folder->Append(new MenuEntry("test", nullptr, [](MenuEntry*e){
        
      File file{ "test.txt", File::READ };

      if( !file.IsOpen() ) {
        return;
      }

      LineReader reader{ file };
      std::string src;

      for( std::string line; reader(line); ) {
        src += line + '\n';
      }

      if( [&](){for(auto&&c:src){if(c>' ')return 0;}return 1;}() ) {
        return;
      }

      Lexer lexer{ src };
      auto tokens = lexer.run();

      std::vector<std::string> X;
      for(auto p=tokens;p->kind!=TOK_END;p=p->next){
        X.emplace_back(p->str);
      }

      (Keyboard(X)).Open();

      do {
        auto tmp = tokens->next;
        delete tokens;
        tokens = tmp;
      } while( tokens );
      
    }));

    return folder;
  }

  ScriptData* ScriptManager::compile(std::string const& path) {
    for( auto&& data : data_list ) {
      if( data.path == path ) {
        return &data;
      }
    }

    try {
      File file{ path, File::READ };

      if( !file.IsOpen() ) {
        throw CannotOpenFileError();
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
        .activated = false,
        .path = path,
        .source = src,
        .tokens = tokens,
        .node = node,
        .oplist = { }
        //.oplist = oplist
      });
    }
    catch( CannotOpenFileError const& e ) {
      
    }
    catch( std::exception const& e ) {
      OSD::SwapBuffers();
      (MessageBox(std::string("unhandled exception has been occurred, please tell developer: \n") + e.what()))();
      OSD::SwapBuffers();
    }

    return nullptr;
  }
}