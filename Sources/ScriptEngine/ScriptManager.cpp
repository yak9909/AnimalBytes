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
#include "ScriptEngine/ScriptManager.h"

namespace CTRPluginFramework::ScriptEngine {
  std::vector<ScriptData> ScriptManager::data_list;

  ScriptData const* ScriptManager::compile(std::string const& path) {
    for( auto&& data : data_list ) {
      if( data.path == path ) {
        return &data;
      }
    }

    File file{ path, File::READ };

    if( !file.IsOpen() ) {
      return nullptr;
    }

    LineReader reader{ file };
    std::string src;

    for( std::string line; reader(line); ) {
      src += line + '\n';
    }

    Lexer lexer{ src };
    auto tokens = lexer.run();
    
    
    return &data_list.emplace_back(ScriptData{
      .path = path,
      .source = src,
      .tokens = tokens,
      .node = node,
      .oplist = oplist
    });
  }
}