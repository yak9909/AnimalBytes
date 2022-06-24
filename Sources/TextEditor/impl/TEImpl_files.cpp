#include <CTRPluginFramework.hpp>
#include "TEImpl.h"

namespace CTRPluginFramework {
  void TextEditorImpl::open_file(std::string const& path, bool create_new) {
    if( create_new ) {
      
    }
    else {

    }
  }

  void TextEditorImpl::save_file(std::string const& path) {
    if( saved ) {
      return;
    }

    File::Open(file, path, File::WRITE | File::CREATE | File::TRUNCATE);

    LineWriter writer{ file };

    for( auto&& line : data ) {
      writer << line << LineWriter::endl();
    }

    file.Flush();

    saved = true;
  }

  void TextEditorImpl::close_file() {
    file.Close();
  }

  bool TextEditorImpl::choice_file(std::string& path) {
    Directory dir{ "" };
    std::vector<std::string> txtFiles;

    dir.ListFiles(txtFiles, ".txt");

    for( u32 i = 0; i < txtFiles.size(); ) {
      if( txtFiles[i].find(".txt") != txtFiles[i].length() - 4 ) {
        txtFiles.erase(txtFiles.begin() + i);
      }
      else {
        i++;
      }
    }

    int index = Keyboard("Choice the file to open.", txtFiles).Open();

    if( index >= 0 ) {
      path = txtFiles[index];
      return true;
    }

    return false;
  }



}