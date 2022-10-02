#pragma once

#include "AbstractMinecart.hpp"

namespace Ship {

  class MinecartCommandBlockMetadata : public AbstractMinecartMetadata {
   private:
    std::string command;
    std::string lastOutput = R"({"text":""})";

   public:
    MinecartCommandBlockMetadata() = default;
    ~MinecartCommandBlockMetadata() override = default;

    [[nodiscard]] static uint8_t MaximumEntries(const ProtocolVersion* version) {
      return AbstractMinecartMetadata::MaximumEntries(version) + 2;
    }

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractMinecartMetadata::Read(metadata, version);
      uint8_t currentIndex = AbstractMinecartMetadata::MaximumEntries(version);

      command = metadata->GetString(currentIndex).value_or("");
      lastOutput = metadata->GetString(currentIndex + 1).value_or(R"({"text":""})");
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractMinecartMetadata::Write(metadata, version);
      uint8_t currentIndex = AbstractMinecartMetadata::MaximumEntries(version);

      if (!command.empty()) {
        metadata->Set(currentIndex, new StringMetadataEntry(command));
      }

      if (lastOutput != R"({"text":""})") {
        metadata->Set(currentIndex + 1, new StringMetadataEntry(lastOutput));
      }
    }

    [[nodiscard]] const std::string& GetCommand() const {
      return command;
    }

    void SetCommand(const std::string& value) {
      command = value;
    }

    [[nodiscard]] const std::string& GetLastOutput() const {
      return lastOutput;
    }

    void SetLastOutput(const std::string& value) {
      lastOutput = value;
    }
  };
}