#include <CTRPluginFramework.hpp>
#include "TEImpl.h"

namespace CTRPluginFramework {
  void TextEditorImpl::open_file(std::string const& path, bool create_new) {
    if( create_new ) {
      File::Open(file, path, File::RWC | File::TRUNCATE | File::SYNC);
    }
    else {
      File::Open(file, path, File::RW);
    }

    LineReader reader{ file };
    std::string line;

    data.clear();
    
    while( reader(line) ) {
      data.emplace_back(line);
    }

    if( data.empty() ) {
      data.emplace_back();
    }

    cursor = { 0 };
    file.Flush();
  }

  void TextEditorImpl::save_file(std::string const& path) {
    if( saved ) {
      return;
    }

    File::Open(file, path, File::RWC | File::TRUNCATE | File::SYNC);

    LineWriter writer{ file };

    for( auto it = data.begin(); it < data.end() - 1; it++ ) {
      writer << *it << LineWriter::endl();
    }

    writer << *data.rbegin() << LineWriter::endl();

    file.Flush();

    saved = true;
  }

  void TextEditorImpl::close_file() {
    file.Close();
  }

  bool TextEditorImpl::choice_file(std::string& path) {
    Directory dir{ "/luma/plugins/0004000000086200/" };
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

    if( txtFiles.empty() ) {
      MessageBox("Text file is not found.")();
      return false;
    }

    int index = Keyboard("Choice the file to open.", txtFiles).Open();

    if( index >= 0 ) {
      path = txtFiles[index];

      do {
        Controller::Update();
      } while( Controller::IsKeyDown(Key::A) );

      return true;
    }

    return false;
  }



}