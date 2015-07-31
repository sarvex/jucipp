#include "singletons.h"

std::unique_ptr<Source::Config> Singleton::Config::source_=std::unique_ptr<Source::Config>(new Source::Config());
std::unique_ptr<Terminal::Config> Singleton::Config::terminal_=std::unique_ptr<Terminal::Config>(new Terminal::Config());
std::unique_ptr<Directories::Config> Singleton::Config::directories_=std::unique_ptr<Directories::Config>(new Directories::Config());

std::unique_ptr<Terminal> Singleton::terminal_=std::unique_ptr<Terminal>();
Terminal *Singleton::terminal() {
  if(!terminal_)
    terminal_=std::unique_ptr<Terminal>(new Terminal());
  return terminal_.get();
}