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

int main() {
  std::ifstream file("/home/input.txt");
  int prev, curr, answer;
  prev = -1;
  if (file.is_open()) {
      std::string line;
      while (std::getline(file, line)) {
        curr = std::stoi(line.c_str());
        if(prev != -1 && curr > prev) answer++;
        prev = curr;
      }
      file.close();
  }
  std:cout << string_format("answer: %d", answer) << std::endl;
  return 0;
}