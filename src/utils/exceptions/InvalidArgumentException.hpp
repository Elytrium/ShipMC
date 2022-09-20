#pragma once

#include <cstdint>
#include <string>
#include <utility>

namespace Ship {

  class InvalidArgumentException : public std::exception {
   private:
    std::string text;
    uint32_t argument;
    const char** check = new const char*[1];

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
      this->check[0] = (this->text + std::to_string(argument)).c_str();
      return *this->check;
    }
  };
}
