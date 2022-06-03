#pragma once

#include <memory>
#include <CTRPluginFramework.hpp>

#define Alert Logger::alert(__FILE__,__LINE__)

namespace CTRPluginFramework {
  class Logger {
    static inline Logger* instance;

    File file;
    std::unique_ptr<LineWriter> writer;

  public:
    Logger(std::string const& path) {
      File::Open(file, path, File::RWC | File::TRUNCATE);

      writer.reset(new LineWriter(file));

      instance = this;
    }

    template <class ... Args>
    static void write(char const* fmt, Args const& ... args) {
      (*instance->writer) << Utils::Format(fmt, args...) << "\n";
      flush();
    }

    static void alert(char const* file, int line) {
      write("\tAlert %s:%d\n", file, line);
    }

    static void flush() {
      instance->file.Flush();
    }
  };
}