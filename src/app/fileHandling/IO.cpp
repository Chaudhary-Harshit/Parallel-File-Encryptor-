#include "IO.hpp"
#include <iostream>

IO::IO(const std::string &file_path) {
  file_stream.open(file_path, std::ios::in | std::ios::out | std::ios::binary);

  if (!file_stream.is_open()) {
    std::cout << "Unable to open the file: " << file_path << std::endl;
  }
}

/*move transfers ownership by copying the resource pointer from the original
object to the new object, and then nullifying the original pointer which is
handled within the move constructor or move assignment operator....std::move(),
the object is cast to an rvalue reference (T&&), which is a temporary object*/

std::fstream IO::getFileStream() { return std::move(file_stream); }

IO::~IO() {
  if (file_stream.is_open()) {
    file_stream.close();
  }
}