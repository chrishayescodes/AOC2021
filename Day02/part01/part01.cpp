#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
using namespace std;


int main() {
  std::ifstream file("/home/input.txt");
  int horz;
  int depth;
  if (file.is_open()) {
      std::string line;
      while (std::getline(file, line)) {
        
        char* cmd = const_cast<char*>(line.c_str());
        char* dir = strtok(cmd," ");
        int amt = std::stoi(strtok(NULL," "));
        if(strcmp(dir, "forward") == 0) { horz = horz + amt; }
        if(strcmp(dir, "down") == 0) { depth = depth + amt; }
        if(strcmp(dir, "up") == 0) { depth = depth - amt; }
        printf("DIR: %s, AMT: %d CURR horz: %d, depth: %d\n", dir, amt, horz, depth);
     }
      printf("ANSWER horz: %d, depth: %d\n", horz, depth);
      file.close();
  }
  return 0;
}