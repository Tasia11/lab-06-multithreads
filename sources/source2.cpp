// Copyright 2020 Osipova Anastasiya anastasiyaosipova2001@gmail.com
#include <picosha2.h>

#include <Declarations.hpp>
#include <header.hpp>
#include <atomic>
#include <csignal>
#include <cstdlib>
#include <ctime>
#include <thread>

std::atomic<bool> continueProcess = true;
std::atomic<bool> makeJSON = false;

void stopProcess(int param) {
  if (param == SIGINT) {
    continueProcess = false;
  }
}

void hashConfig(JSON& j) {
  while (continueProcess) {
    std::string genstring = std::to_string(std::rand());
    std::string hash = picosha2::hash256_hex_string(genstring);
    std::time_t timestamp(std::time(nullptr));
    std::string lastChar = hash.substr(hash.size() - kEndCharSize);

    if (lastChar == kEndChar) {
      BOOST_LOG_TRIVIAL(info) << "0000 founded in hash '" << hash
                              << "' of string '" << genstring << "'";
      if (makeJSON) {
        j.addHash(genstring, hash, timestamp);
      }
    } else {
      BOOST_LOG_TRIVIAL(trace)
        << "Hash '" << hash << "' get from string'" << genstring << "'";
    }
  }
}
void findHash(const int& argc, char* argv[]){
  unsigned int numberOfThreads;
  std::string json_path;
  std::srand(time(nullptr));
  // Проверка числа потоков
  switch (argc) {
    case 1:
      numberOfThreads = std::thread::hardware_concurrency();
      break;
    case 2:
      numberOfThreads = std::atoi(argv[1]);
      if (numberOfThreads == 0 ||
          numberOfThreads > std::thread::hardware_concurrency()) {
        throw std::out_of_range(" Invalid number of threads!!!");
      }
      break;
    case 3:
      numberOfThreads = std::atoi(argv[1]);
      if (numberOfThreads == 0 ||
          numberOfThreads > std::thread::hardware_concurrency()) {
        throw std::out_of_range(" Invalid number of threads!!!");
      }
      json_path = argv[2];
      makeJSON = true;
      break;
    default:
      throw std::out_of_range("Invalid number of arguments!!!");
  }
  init();
  // Добавление распространенных атрибутов в лог
  boost::log::add_common_attributes();
  std::vector<std::thread> threads;
  JSON json_obj;
  //Задает емкость контейнера по крайней мере, size. Новая память выделяется при
  //необходимости.
  threads.reserve(numberOfThreads);
  // Обработка сигналов терминала
  std::signal(SIGINT, stopProcess);
  // Запуск потоков

  for (size_t i = 0; i < numberOfThreads; i++) {
    threads.emplace_back(hashConfig, std::ref(json_obj));
  }
  for (auto& thread : threads) {
    thread.join();
  }
  if (makeJSON) {
    std::ofstream fout{json_path};
    fout << json_obj;
  }
}
//int main(int argc, char* argv[]) {
// findHash(argc,argv);
 // return 0;
//}

