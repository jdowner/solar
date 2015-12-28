#ifndef DATASTORE_H
#define DATASTORE_H

#include <string>
#include <sstream>
#include <stdexcept>
#include <map>


/**
 *
 */
class DataStore
{
  public:
    DataStore();

    void load(const std::string& filename);
    bool contains(const std::string& key) const;

    template <typename T>
    void set(const std::string& key, const T& value) {
      std::stringstream oss;
      oss << value;
      m_data[key] = oss.str();
    }

    template <typename T>
    T get(const std::string& key) const {
      auto result = m_data.find(key);
      if(result == m_data.end()) {
        std::stringstream msg;
        msg << "datastore does not contain requested key: " << key;
        throw std::runtime_error(msg.str());
      }

      T value;
      std::istringstream iss(result->second);
      iss >> value;
      return value;
    }

  private:
    std::map<std::string, std::string> m_data;
};

#endif // DATASTORE_H

