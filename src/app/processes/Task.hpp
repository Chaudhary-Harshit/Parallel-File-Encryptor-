// Passing by Lvalue Reference (&): Allows a function to modify the original
// variable or object, avoiding copies but still providing access to the
// original data.
/*Passing by Rvalue Reference (&&): Enables move semantics, allowing functions
 to take advantage of temporary objects or to "steal" resources from an
 object, making the operation more efficient by avoiding unnecessary copying.*/

#ifndef TASK_HPP
#define TASK_HPP

#include "../fileHandling/IO.hpp"
#include <sstream>
#include <stdexcept>
#include <string>


/*By using std::move, the constructor takes ownership of the stream object,
transferring its resources (like file handles) from the input stream parameter
to the f_stream member variable. After the move, stream is left in a valid but
unspecified state (essentially "empty").*/

enum class Action { ENCRYPT, DECRYPT };

struct Task {
  std::string file_path;
  std::fstream f_stream;
  Action action;

  Task(std::fstream &&stream, Action act, std::string file_path)
      : f_stream(std::move(stream)), action(act), file_path(file_path) {}

  std::string to_String() {
    std::ostringstream oss;
    oss << file_path << ","
        << (action == Action::ENCRYPT ? "ENCRYPT" : "DECRYPT");

    // test.txt ENCRYPT f_stream
    //  return "test.txt,ENCRYPT"

    return oss.str();
  }

  static Task fromString(const std::string &taskData) {
    std::istringstream iss(taskData);

    std::string filePath;
    std::string actionstr;

    if (std::getline(iss, filePath, ',') && std::getline(iss, actionstr)) {
      Action action =
          (actionstr == "ENCRYPT" ? Action::ENCRYPT : Action::DECRYPT);

      IO io(filePath);

      std::fstream f_stream = std::move(io.getFileStream());

      if (f_stream.is_open()) {
        return Task(std::move(f_stream), action, filePath);
      } else {
        throw std::runtime_error("Failed to open file: " + filePath);
      }
    } else {
      throw std::runtime_error("Invalid Task Data format");
    }
  }
};

#endif