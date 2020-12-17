/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <string>
#include <unordered_map>

namespace spectral {


template<class resource>
class resource_manager
{
public:
  resource_manager() {
  }


  virtual ~resource_manager() {
    for (auto &Pair : Storage)
    delete Pair.second;
  }


  virtual resource * Get( const std::string &Name ) {
    auto Iterator = Storage.find(Name);
    if (Iterator == Storage.end())
      // Resource not found
      return Storage.insert({Name, new resource(Name)}).first->second;
    return Iterator->second;
  }

protected:
  std::unordered_map<std::string, resource *> Storage;
};


} // End of 'spectral' namespace
