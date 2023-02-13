#pragma once

#include <cstdint>
#include <string>
#include <utility>

namespace Ship {

  class InvalidArgumentException : public std::exception {
   private:
    std::string text;
    uint32_t argument;
    std::string* check = new std::string[1];

   public:
    InvalidArgumentException(std::string text, uint32_t argument) : text(std::move(text)), argument(argument) {
    }

    ~InvalidArgumentException() override {
      delete[] check;
    }

    std::string GetText() {
      return this->text;
    }

    [[nodiscard]] uint32_t GetArgument() const {
      return this->argument;
    }

    [[nodiscard]] const char* what() const noexcept override {
      *this->check = this->text + std::to_string(argument);
      return this->check->c_str();
    }
  };
}
