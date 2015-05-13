#include "config.h"
#include "logging.h"

MainConfig::MainConfig() :
  keybindings_cfg_(), source_cfg_() {
  INFO("Reading config file");
  boost::property_tree::json_parser::read_json("config.json", cfg_);
  INFO("Config file read");
  GenerateSource();
  GenerateKeybindings();
  GenerateDirectoryFilter();
}

void MainConfig::GenerateSource() {
  INFO("Generating source cfg");
  boost::property_tree::ptree source_json = cfg_.get_child("source");
  boost::property_tree::ptree syntax_json = source_json.get_child("syntax");
  boost::property_tree::ptree colors_json = source_json.get_child("colors");
  for (auto &i : colors_json) {
    source_cfg_.InsertTag(i.first, i.second.get_value<std::string>());
  }
  for (auto &i : syntax_json) {
    source_cfg_.InsertType(i.first, i.second.get_value<std::string>());
  }
  INFO("Source cfg generated");
}

void MainConfig::GenerateKeybindings() {
  INFO("Generating keybindings");
  std::string line;
  std::ifstream menu_xml("menu.xml");
  if (menu_xml.is_open()) {
    while (getline(menu_xml, line)) {
      keybindings_cfg_.AppendXml(line);
    }
    
  }
  boost::property_tree::ptree keys_json = cfg_.get_child("keybindings");
  for (auto &i : keys_json)
    keybindings_cfg_.key_map()[i.first] = i.second.get_value<std::string>();
  INFO("Keybindings generated");
}

void MainConfig::GenerateDirectoryFilter() {
  boost::property_tree::ptree dir_json = cfg_.get_child("directoryfilter");
  boost::property_tree::ptree ignore_json = dir_json.get_child("ignore");
  boost::property_tree::ptree except_json = dir_json.get_child("exceptions");
  for ( auto &i : except_json )
    dir_cfg_.AddException(i.second.get_value<std::string>());
  for ( auto &i : ignore_json )
    dir_cfg_.AddIgnore(i.second.get_value<std::string>());
}

