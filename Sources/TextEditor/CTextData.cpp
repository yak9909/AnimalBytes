#include <CTRPluginFramework.hpp>
#include "CTextData.h"

namespace CTRPluginFramework {

  void CTextData::Line::setchar(size_t index, char ch) {
    reset();

    file->Seek(pos + index, File::SET);

    // todo 挿入されるかどうか確認
    file->Write(&ch, sizeof(char));

  }

  char CTextData::Line::operator[] (size_t index) {
    reset();

    char ch;
    file->Seek(pos + index, File::SET);
    file->Read(&ch, sizeof(char));

    return ch;
  }

  std::string CTextData::Line::to_str() {
    std::string ret;

    reset();

    ret.resize(len + 1);
    file->Read(ret.data(), len);

    return ret;
  }

  void CTextData::Line::reset() {
    file->Seek(pos, File::SET);
  }

  CTextData::CTextData()
  {
  }

  CTextData::~CTextData() {
    if( file.IsOpen() ) {
      file.Flush();
    }
  }

  int CTextData::open(std::string const& path) {
    int res = File::Open(file, path);

    if( res != 0 ) {
      return res;
    }

    if( linepos_list.size() ) {
      linepos_list.clear();
    }



    return 0;
  }

  CTextData::Line* CTextData::operator[] (size_t index) {
    size_t pos = linepos_list[index];

    
  }

  void CTextData::clear() {
    if( file.IsOpen() ) {
      file.Close();
    }
  }


}