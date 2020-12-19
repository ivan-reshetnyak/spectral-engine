/***************************************************************
 * Copyright (C) 2020
 *    Reshetnyak Ivan
 ***************************************************************/

#pragma once

#include <memory>
#include <string>
#include <unordered_map>

namespace spectral {


template<class tag, class resource>
class resource_manager {
public:
  using ptr = std::shared_ptr<resource>;

  virtual ptr Get( const tag &Tag ) = 0;
  virtual bool Exists( const tag &Tag ) = 0;

protected:
  resource_manager() {
  }


  virtual ~resource_manager() {
  }
};


template<class resource>
class resource_manager<std::string, resource> {
public:
  using ptr = std::shared_ptr<resource>;

  resource_manager() {
  }


  virtual ~resource_manager() {
  }


  virtual ptr Get( const std::string &Name ) {
    auto Iterator = Storage.find(Name);
    if (Iterator == Storage.end())
      // Resource not found
      return Storage.insert({Name, ptr(new resource())}).first->second;
    return Iterator->second;
  }


  virtual bool Exists( const std::string &Name ) {
    return Storage.find(Name) != Storage.end();
  }

protected:
  std::unordered_map<std::string, std::shared_ptr<resource>> Storage;
};


template<class resource>
using resource_manager_named = resource_manager<std::string, resource>;


template<class resource>
class resource_manager<unsigned, resource> {
public:
  resource_manager() {
  }


  virtual ~resource_manager() {
  }


  virtual resource * Get( const unsigned &Index ) {
    if (Exists(Index))
      return Storage[Index];

    std::shared_ptr<resource> NewResource = new resource();
    Storage.push_back(NewResource);
    return NewResource;
  }


  virtual bool Exists( const unsigned &Index ) {
    return Index >= 0 && Index < Storage.size();
  }

protected:
  std::vector<std::shared_ptr<resource>> Storage;
};


template<class resource>
using resource_manager_indexed = resource_manager<int, resource>;


} // End of 'spectral' namespace
