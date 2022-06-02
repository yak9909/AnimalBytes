#pragma once

namespace CTRPluginFramework::Cheats {
  class FolderBase {
  public:
    virtual FolderBase* create() = 0;
    virtual MenuFolder* make_folder() = 0;

  protected:
    FolderBase();
    
  };
}