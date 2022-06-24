#include <CTRPluginFramework.hpp>
#include "TextEditor.h"
#include "TextEditorImpl.h"

namespace CTRPluginFramework {
  TextEditorImpl::TextEditorImpl() {
  }

  TextEditorImpl::TextEditorImpl(std::string const& path) {
    File::Open(file, path);
  }

  void TextEditorImpl::open() {
    bool paused = Process::IsPaused();

    if( !paused ) {
      Process::Pause();
    }

    while( 1 ) {
      
    }

    if( !paused ) {
      Process::Play();
    }
  }
}