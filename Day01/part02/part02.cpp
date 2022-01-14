#include <iostream>
#include <fstream>
using namespace std;

template<typename ... Args>
std::string string_format( const std::string& format, Args ... args )
{
    int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
    if( size_s <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
    auto size = static_cast<size_t>( size_s );
    auto buf = std::make_unique<char[]>( size );
    std::snprintf( buf.get(), size, format.c_str(), args ... );
    return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
}

void shift_arr(int values[], int size){
  int temp = values[size-1], temp1;
  for(int i = 0; i < size; i++){
    temp1 = values[i];
    values[i] = temp;
    temp = temp1;
  }
}

int sum_arr(int values[], int size){
  int sum = 0;
  for(int i = 0; i < size; i++){
    sum = sum + values[i];
  }
  return sum;
}

int main() {
  std::ifstream file("/home/input.txt");
  int prev, curr, answer;
  prev = -1;
  bool end;
  int buffer[3];
  std::string line;
  if (file.is_open()) {
    for(int i = 0; i < 2; i++){
      std::getline(file, line);
      buffer[i] = std::stoi(line.c_str());
    }
    while (std::getline(file, line)) {
      //shift the array
      shift_arr(buffer,3);
      //add line to beginning of buffer
      buffer[0] = std::stoi(line.c_str());
      //sum the buffer
      curr = sum_arr(buffer,3);
      //compare buffer sum with prev
      if(prev != -1 && curr > prev) answer++;
      //swap prev/curr
      prev = curr;
    }
    file.close();
  }
  std:cout << string_format("answer: %d", answer) << std::endl;
  return 0;
}