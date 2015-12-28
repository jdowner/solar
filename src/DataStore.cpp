#include "DataStore.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

DataStore::DataStore()
{
}

void DataStore::load(const std::string& filename) {
}

bool DataStore::contains(const std::string& key) const {
  return m_data.end() != m_data.find(key);
}
