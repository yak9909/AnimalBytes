#pragma once

#include <string>
#include <vector>

/*

  std::vector<std::string> のように使えます。


*/

namespace CTRPluginFramework {
  class CTextData { 
  public:
    struct Line {
      
      void setchar(size_t index, char ch);
      char operator[] (size_t index);

      std::string to_str();

    private:
      File* file;
      size_t pos, len;

      void reset();
      Line() { }
    };

    CTextData();
    ~CTextData();

    int open(std::string const& path);

    Line* operator[] (size_t index);

    void clear();

  private:
    File file;
    std::vector<size_t> linepos_list;
  };
}