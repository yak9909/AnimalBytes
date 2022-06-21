#include <CTRPluginFramework.hpp>
#include "Cheats/CodeContext.h"

namespace CTRPluginFramework::Cheats {
  static CodeContext* g_cdctx_instance;

  CodeContext* CodeContext::get_instance() {
    if( !g_cdctx_instance ) {
      g_cdctx_instance = new CodeContext;
    }

    return g_cdctx_instance;
  }

  CodeContext::CodeContext() {
    
  }
}