#include <CTRPluginFramework.hpp>
#include "TextEditor.h"
#include "impl/TEImpl.h"

namespace CTRPluginFramework {
static TextEditor* __g_instance;

TextEditor::TextEditor()
    : impl(new TextEditorImpl)
{
  __g_instance = this;
}

TextEditor::TextEditor(std::string const& path)
    : impl(new TextEditorImpl(path))
{
}

TextEditor::~TextEditor()
{
}

void TextEditor::add_event(EventFuncPointer func)
{
  impl->event_funcs.emplace_back(func);
}

void TextEditor::add_submenu_entry(std::string const& name,
                                   EventFuncPointer func)
{
  impl->submenu_user_entries.emplace_back(name, func);
}

TextEditor::Result TextEditor::open() const
{
  return impl->open();
}

TextEditor* TextEditor::get_instance()
{
  return __g_instance;
}

}  // namespace CTRPluginFramework