#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
using namespace std;

int16_t fromBinary(const char *s) {
  return (int16_t) strtol(s, NULL, 2);
}

int main() {
  std::ifstream file("/home/input.txt");
  
  if (file.is_open()) {
      std::string line;
      int16_t gamma = 0;
      int16_t epsilon = 0;
      int linecount = 0;
      int bitcounts[12] = {0};
      while (std::getline(file, line)) {
        int16_t inputflags = fromBinary(line.c_str());
        //iterate bitcount arr
        for(int i = 0; i < 12; i++){
            if(inputflags & 1) bitcounts[i]++;
            inputflags = inputflags>>1;
        }
        linecount++;
      }
      //fill gamma with most sig bit per position
      for(int i = 11; i >= 0; i--){
          gamma = gamma<<1;
          epsilon = epsilon<<1;
          int bitcount = bitcounts[i];
          int nulcount = linecount - bitcount;
          if(bitcount > nulcount) gamma = gamma + 1;
          else epsilon = epsilon + 1;
      }
      long long answer = gamma * epsilon;

      printf("GAMMA: %d, EPSILON: %d, ANSWER: %lld\n", gamma, epsilon, answer);
      file.close();
  }
  return 0;
}