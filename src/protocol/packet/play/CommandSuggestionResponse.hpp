#pragma once

#include "ShipNet/utils/ordinal/OrdinalRegistry.hpp"
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

    static Errorable<CommandSuggestion> Instantiate(const PacketHolder& holder);

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteString(match);
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_13) {
        buffer->WriteBoolean(tooltip.has_value());
        if (tooltip) {
          buffer->WriteString(tooltip.value());
        }
      }
      return SuccessErrorable<bool>(true);
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

  CreateInvalidArgumentErrorable(InvalidCommandSuggestionErrorable, CommandSuggestion, "Invalid CommandSuggestion read");

  Errorable<CommandSuggestion> CommandSuggestion::Instantiate(const PacketHolder& holder) {
    ByteBuffer* buffer = holder.GetCurrentBuffer();
    const ProtocolVersion* version = holder.GetVersion();
    ProceedErrorable(match, std::string, buffer->ReadString(), InvalidCommandSuggestionErrorable(buffer->GetReadableBytes()))

    std::optional<std::string> tooltip;
    if (version >= &MinecraftProtocolVersion::MINECRAFT_1_13) {
      ProceedErrorable(hasTooltip, bool, buffer->ReadBoolean(), InvalidCommandSuggestionErrorable(buffer->GetReadableBytes()))
      if (hasTooltip) {
        SetFromErrorable(tooltip, std::string, buffer->ReadString(), InvalidCommandSuggestionErrorable(buffer->GetReadableBytes()))
      } else {
        tooltip = std::nullopt;
      }
    } else {
      tooltip = std::nullopt;
    }

    return SuccessErrorable<CommandSuggestion>(CommandSuggestion(match, tooltip));
  }

  class CommandSuggestionResponse : public Packet {
   private:
    uint32_t id{};
    uint32_t start{};
    uint32_t length{};
    std::vector<CommandSuggestion> matches;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    CommandSuggestionResponse() = default;
    CommandSuggestionResponse(uint32_t id, uint32_t start, uint32_t length, std::vector<CommandSuggestion> matches)
      : id(id), start(start), length(length), matches(std::move(matches)) {
    }

    ~CommandSuggestionResponse() override = default;

    static Errorable<CommandSuggestionResponse> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      const ProtocolVersion* version = holder.GetVersion();
      uint32_t id, start, length;
      if (version >= &MinecraftProtocolVersion::MINECRAFT_1_13) {
        SetFromErrorable(id, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<CommandSuggestionResponse>(PACKET_ORDINAL))
        SetFromErrorable(start, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<CommandSuggestionResponse>(PACKET_ORDINAL))
        SetFromErrorable(length, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<CommandSuggestionResponse>(PACKET_ORDINAL))
      }

      ProceedErrorable(vectorSize, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<CommandSuggestionResponse>(PACKET_ORDINAL))
      std::vector<CommandSuggestion> matches;
      for (int i = 0; i < vectorSize; ++i) {
        ProceedErrorable(match, CommandSuggestion, CommandSuggestion::Instantiate(holder), InvalidPacketErrorable<CommandSuggestionResponse>(PACKET_ORDINAL))
        matches.push_back(match);
      }

      return SuccessErrorable<CommandSuggestionResponse>(CommandSuggestionResponse(id, start, length, matches));
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
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
      return SuccessErrorable<bool>(true);
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
