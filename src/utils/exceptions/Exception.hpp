#pragma once

#include <cstdint>
#include <string>
#include <utility>

namespace Ship {

  class Exception : public std::exception {
   protected:
    std::string text;

   public:
    explicit Exception(std::string text) : text(std::move(text)) {
    }

    std::string GetText() {
      return this->text;
    }

    [[nodiscard]] const char* what() const noexcept override {
      return this->text.c_str();
    }
  };
}
