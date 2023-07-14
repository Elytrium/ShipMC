#pragma once

#include "ShipNet/protocol/data/uuid/UUID.hpp"
#include <string>
#include <vector>

namespace Ship {
  class GameProfileProperty {
   private:
    std::string name;
    std::string value;
    std::string signature;

   public:
    explicit GameProfileProperty(std::string  name, std::string value, std::string signature);

    [[nodiscard]] const std::string& GetName() const;
    [[nodiscard]] const std::string& GetValue() const;
    [[nodiscard]] const std::string& GetSignature() const;
  };

  class GameProfile {
   private:
    UUID uuid;
    std::string name;
    std::vector<GameProfileProperty> properties;

   public:
    explicit GameProfile(const UUID& uuid, std::string name, std::vector<GameProfileProperty> properties);
    static GameProfile* ForOfflinePlayer(const std::string& basicString);

    [[nodiscard]] const UUID& GetUuid() const;
    [[nodiscard]] const std::string& GetName() const;
    [[nodiscard]] const std::vector<GameProfileProperty>& GetProperties() const;
  };
}