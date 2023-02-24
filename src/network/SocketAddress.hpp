#pragma once

#include <cstdint>
#include <string>
#include <utility>

namespace Ship {
  class SocketAddress {
   private:
    std::string hostname;
    uint16_t port;

   public:
    SocketAddress(std::string hostname, uint16_t port) : hostname(std::move(hostname)), port(port) {}

    [[nodiscard]] std::string GetHostname() const {
      return hostname;
    }

    [[nodiscard]] uint16_t GetPort() const {
      return port;
    }
  };
} // Ship
