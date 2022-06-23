#include <CTRPluginFramework.hpp>
#include "TextEditor.h"
#include "TEImpl.h"
#include "../Hotkeys.h"

namespace CTRPluginFramework {
  int TextEditorImpl::open() {
    bool paused = Process::IsPaused();

    if( !paused ) {
      Process::Pause();
    }

    while( 1 ) {
      Controller::Update();


    }

    if( !paused ) {
      Process::Play();
    }

    return 0;
  }

  void TextEditorImpl::update() {

  }

}