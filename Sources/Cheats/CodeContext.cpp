#include <CTRPluginFramework.hpp>
#include "Cheats/CodeContext.h"

namespace CTRPluginFramework::Cheats {
  static CodeContext* g_cdctx_instance;

  CodeContext* CodeContext::get_instance() {
    static_assert(
      sizeof(CodeContext) < 0x1000,
      "Size of CodeContext is too big to place to 0x838000, must less than 0x1000."
    );

    return reinterpret_cast<CodeContext*>(0x838000);

    // if( !g_cdctx_instance ) {
    //   g_cdctx_instance = new CodeContext;
    // }

    // return g_cdctx_instance;
  }

  CodeContext::CodeContext() {
    
  }
}