#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
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

    static Errorable<CommandSuggestion> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      const ProtocolVersion* version = holder.GetVersion();
      ProceedErrorable(match, std::string, buffer->ReadString(), InvalidPacketErrorable<>(PACKET_ORDINAL))

      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_13) {
        if (buffer->ReadBoolean()) {
          ProceedErrorable(tooltip, std::string, buffer->ReadString(), InvalidPacketErrorable<>(PACKET_ORDINAL))
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

    static Errorable<CommandSuggestionResponse> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      const ProtocolVersion* version = holder.GetVersion();
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_13) {
        ProceedErrorable(id, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<>(PACKET_ORDINAL))
        ProceedErrorable(start, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<>(PACKET_ORDINAL))
        ProceedErrorable(length, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      }

      uint32_t ProceedErrorable(vectorSize, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<>(PACKET_ORDINAL))
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

    [[nodiscard]] uint32_t GetOrdinal() const override {
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
