// Copyright 2020 Osipova Anastasiya anastasiyaosipova2001@gmail.com

#include "hashCalc.hpp"

int main(int, char*[]){
  hashCalc A("/Users/mishadolbnin/lab-06-multithreads/map.json");
  A.initLogs();
  A.initThreads();
  return 0;
}
