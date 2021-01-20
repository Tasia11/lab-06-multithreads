// Copyright 2020 Osipova Anastasiya anastasiyaosipova2001@gmail.com

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <ctime>
#include <fstream>
#include <iomanip>
#include <mutex>
#include <nlohmann/json.hpp>
#include <sstream>
#include <string>

using json = nlohmann::json;

class JSON {
 public:
  void addHash(const std::string& data, const std::string& hash,
               std::time_t timestamp);
  friend std::ostream& operator<<(std::ostream& out, const JSON& j);

 private:
  mutable std::mutex mut;
  json j_array;
};

#endif // INCLUDE_HEADER_HPP_

using nlohmann::json;

class hashCalc {
 public:
  // hashCalc();
  hashCalc(const size_t& M,
           const std::string& str = "");
  explicit hashCalc(const std::string& str);
  ~hashCalc();
  void countHash();
  void openFilePath();
  void initThreads();
  void initLogs();
  bool directionIsOpen();
  void jsonOut(const int& data, const std::string& hash, const time_t& time);

 private:
  size_t sizeOfThread = boost::thread::hardware_concurrency();
  std::string nameOfReport;
  std::ofstream file_log;
  std::vector<boost::thread> listOfthread;
  json j;
};

#endif  // INCLUDE_HEADER_HPP_
