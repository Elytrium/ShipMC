#include "GameProfile.hpp"
#include <utility>

namespace Ship {
  GameProfileProperty::GameProfileProperty(std::string  name, std::string value, std::string signature)
    : name(std::move(name)), value(std::move(value)), signature(std::move(signature)) {
  }

  const std::string& GameProfileProperty::GetName() const {
    return name;
  }

  const std::string& GameProfileProperty::GetValue() const {
    return value;
  }

  const std::string& GameProfileProperty::GetSignature() const {
    return signature;
  }

  GameProfile::GameProfile(const UUID& uuid, std::string name, std::vector<GameProfileProperty> properties)
    : uuid(uuid), name(std::move(name)), properties(std::move(properties)) {
  }

  const UUID& GameProfile::GetUuid() const {
    return uuid;
  }

  const std::string& GameProfile::GetName() const {
    return name;
  }

  const std::vector<GameProfileProperty>& GameProfile::GetProperties() const {
    return properties;
  }

  GameProfile* GameProfile::ForOfflinePlayer(const std::string& name) {
    // TODO: game profile for offline player
    return nullptr;
  }
}
