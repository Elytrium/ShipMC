#pragma once

#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
#include <string>
#include <utility>

namespace Ship {

  class CommandSuggestion {
   private:
    std::string match;
    std::optional<std::string> tooltip;

   public:
    CommandSuggestion(std::string match, std::optional<std::string> tooltip) : match(std::move(match)), tooltip(std::move(tooltip)) {
    }

    explicit CommandSuggestion(std::string match) : match(std::move(match)) {
    }

    CommandSuggestion() : CommandSuggestion("") {
    }

    [[nodiscard]] const std::string& GetMatch() const {
      return match;
    }

    void SetMatch(const std::string& value) {
      match = value;
    }

    [[nodiscard]] const std::optional<std::string>& GetTooltip() const {
      return tooltip;
    }

    void SetTooltip(const std::optional<std::string>& value) {
      tooltip = value;
    }
  };

  class CommandSuggestionResponse : public Packet {
   private:
    uint32_t id;
    uint32_t start;
    uint32_t length;
    std::vector<CommandSuggestion> matches;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    CommandSuggestionResponse(uint32_t id, uint32_t start, uint32_t length, std::vector<CommandSuggestion> matches)
      : id(id), start(start), length(length), matches(std::move(matches)) {
    }

    ~CommandSuggestionResponse() override = default;

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      if (version >= &ProtocolVersion::MINECRAFT_1_13) {
        id = buffer->ReadVarInt();
        start = buffer->ReadVarInt();
        length = buffer->ReadVarInt();
        matches.resize(buffer->ReadVarInt());

        for (CommandSuggestion& match : matches) {
          match.SetMatch(buffer->ReadString());
          if (buffer->ReadBoolean()) {
            match.SetTooltip(buffer->ReadString());
          } else {
            match.SetTooltip(std::nullopt);
          }
        }
      } else {
        matches.resize(buffer->ReadVarInt());

        for (CommandSuggestion& match : matches) {
          match.SetMatch(buffer->ReadString());
          match.SetTooltip(std::nullopt);
        }
      }
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      if (version >= &ProtocolVersion::MINECRAFT_1_13) {
        buffer->WriteVarInt(id);
        buffer->WriteVarInt(start);
        buffer->WriteVarInt(length);
        buffer->WriteVarInt(matches.size());

        for (const CommandSuggestion& match : matches) {
          buffer->WriteString(match.GetMatch());
          buffer->WriteBoolean(match.GetTooltip().has_value());
          if (match.GetTooltip()) {
            buffer->WriteString(match.GetTooltip().value());
          }
        }
      } else {
        buffer->WriteVarInt(matches.size());

        for (const CommandSuggestion& match : matches) {
          buffer->WriteString(match.GetMatch());
        }
      }
    }

    uint32_t GetOrdinal() override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] uint32_t GetId() const {
      return id;
    }

    [[nodiscard]] uint32_t GetStart() const {
      return start;
    }

    [[nodiscard]] uint32_t GetLength() const {
      return length;
    }

    [[nodiscard]] const std::vector<CommandSuggestion>& GetMatches() const {
      return matches;
    }
  };
}
