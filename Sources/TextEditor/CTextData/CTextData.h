#pragma once

#include <string>
#include <vector>
#include <CTRPluginFramework.hpp>

/*

  std::vector<std::string> のように使えます。

  std::string は CTextData::Line として実装

*/

namespace CTRPluginFramework {
  class CTextData { 
  public:

    CTextData();

    int open(std::string const& path);

  private:
    File file;
  };
}