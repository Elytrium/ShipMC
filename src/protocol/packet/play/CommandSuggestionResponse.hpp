#pragma once


#include <string>
#include <utility>

namespace Ship {

  class CommandSuggestion : Serializable {
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

    explicit CommandSuggestion(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      const ProtocolVersion* version = holder.GetVersion();
      match = buffer->ReadString();

      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_13) {
        if (buffer->ReadBoolean()) {
          tooltip = buffer->ReadString();
        } else {
          tooltip = std::nullopt;
        }
      } else {
        tooltip = std::nullopt;
      }
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteString(match);
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_13) {
        buffer->WriteBoolean(tooltip.has_value());
        if (tooltip) {
          buffer->WriteString(tooltip.value());
        }
      }
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

    explicit CommandSuggestionResponse(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      const ProtocolVersion* version = holder.GetVersion();
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_13) {
        id = buffer->ReadVarInt();
        start = buffer->ReadVarInt();
        length = buffer->ReadVarInt();
      }

      uint32_t vectorSize = buffer->ReadVarInt();
      for (int i = 0; i < vectorSize; ++i) {
        matches.emplace_back(holder);
      }
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_13) {
        buffer->WriteVarInt(id);
        buffer->WriteVarInt(start);
        buffer->WriteVarInt(length);
        buffer->WriteVarInt(matches.size());
      } else {
        buffer->WriteVarInt(matches.size());
      }

      for (const CommandSuggestion& match : matches) {
        match.Write(version, buffer);
      }
    }

    uint32_t GetOrdinal() const override {
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
