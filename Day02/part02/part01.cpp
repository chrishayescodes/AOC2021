#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
using namespace std;


int main() {
  std::ifstream file("/home/input.txt");
  int horz;
  int depth;
  int aim;
  if (file.is_open()) {
      std::string line;
      while (std::getline(file, line)) {
        
        char* cmd = const_cast<char*>(line.c_str());
        char* dir = strtok(cmd," ");
        int amt = std::stoi(strtok(NULL," "));
        if(strcmp(dir, "forward") == 0) { 
          horz = horz + amt;
          depth = depth + (aim * amt);
        }
        if(strcmp(dir, "down") == 0) { aim = aim + amt; }
        if(strcmp(dir, "up") == 0) { aim = aim - amt; }
        printf("DIR: %s, AMT: %d CURR horz: %d, depth: %d\n", dir, amt, horz, depth);
     }
      printf("ANSWER horz: %d, depth: %d\n", horz, depth);
      int final;
      final = depth * horz;
      printf("FINAL ANSWER: %d", final);
      file.close();
  }
  return 0;
}