#pragma once

#include "../../../utils/exceptions/Exception.hpp"
#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>
#include <utility>

namespace Ship {

  class BossBarAction : public Serializable {
   public:
    ~BossBarAction() override = default;

    [[nodiscard]] virtual uint32_t GetAction() const = 0;
  };

  class BossBarAdd : public BossBarAction {
   private:
    std::string title; // TODO: Chat components
    float health {};
    uint32_t color {};
    uint32_t division {};
    uint8_t flags {};

   public:
    BossBarAdd() = default;

    BossBarAdd(std::string title, float health, uint32_t color, uint32_t division, uint8_t flags)
      : title(std::move(title)), health(health), color(color), division(division), flags(flags) {
    }

    ~BossBarAdd() override = default;

    static Errorable<BossBarAdd> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(title, std::string, buffer->ReadString(), InvalidPacketErrorable<BossBarAdd>(PACKET_ORDINAL))
      ProceedErrorable(health, float, buffer->ReadFloat(), InvalidPacketErrorable<BossBarAdd>(PACKET_ORDINAL))
      ProceedErrorable(color, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<BossBarAdd>(PACKET_ORDINAL))
      ProceedErrorable(division, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<BossBarAdd>(PACKET_ORDINAL))
      ProceedErrorable(flags, uint8_t, buffer->ReadByte(), InvalidPacketErrorable<BossBarAdd>(PACKET_ORDINAL))
      return SuccessErrorable<BossBarAdd>({title, health, color, division, flags});
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteString(title);
      buffer->WriteFloat(health);
      buffer->WriteVarInt(color);
      buffer->WriteVarInt(division);
      buffer->WriteByte(flags);
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetAction() const override {
      return 0;
    }

    [[nodiscard]] const std::string& GetTitle() const {
      return title;
    }

    [[nodiscard]] float GetHealth() const {
      return health;
    }

    [[nodiscard]] uint32_t GetColor() const {
      return color;
    }

    [[nodiscard]] uint32_t GetDivision() const {
      return division;
    }

    [[nodiscard]] uint8_t GetFlags() const {
      return flags;
    }
  };

  class BossBarRemove : public BossBarAction {
   public:
    static Errorable<BossBarRemove> Instantiate(const PacketHolder& holder) {
    }

    ~BossBarRemove() override = default;

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
    return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetAction() const override {
      return 1;
    }
  };

  class BossBarUpdateHealth : public BossBarAction {
   private:
    float health {};

   public:
    BossBarUpdateHealth() = default;

    explicit BossBarUpdateHealth(float health) : health(health) {
    }

    static Errorable<BossBarUpdateHealth> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(health, float, buffer->ReadFloat(), InvalidPacketErrorable<BossBarUpdateHealth>(PACKET_ORDINAL))
      return SuccessErrorable<BossBarUpdateHealth>(BossBarUpdateHealth(health));
    }

    ~BossBarUpdateHealth() override = default;

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
    return SuccessErrorable<bool>(true);
      buffer->WriteFloat(health);
    }

    [[nodiscard]] uint32_t GetAction() const override {
      return 2;
    }

    [[nodiscard]] float GetHealth() const {
      return health;
    }
  };

  class BossBarUpdateTitle : public BossBarAction {
   private:
    std::string title; // TODO: Chat components

   public:
    BossBarUpdateTitle() = default;

    explicit BossBarUpdateTitle(std::string title) : title(std::move(title)) {
    }

    static Errorable<BossBarUpdateTitle> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(title, std::string, buffer->ReadString(), InvalidPacketErrorable<BossBarUpdateTitle>(PACKET_ORDINAL))
      return SuccessErrorable<BossBarUpdateTitle>(BossBarUpdateTitle(title));
    }

    ~BossBarUpdateTitle() override = default;

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
    return SuccessErrorable<bool>(true);
      buffer->WriteString(title);
    }

    [[nodiscard]] uint32_t GetAction() const override {
      return 3;
    }

    [[nodiscard]] const std::string& GetTitle() const {
      return title;
    }
  };

  class BossBarUpdateStyle : public BossBarAction {
   private:
    uint32_t color {};
    uint32_t dividers {};

   public:
    BossBarUpdateStyle() = default;

    BossBarUpdateStyle(uint32_t color, uint32_t dividers) : color(color), dividers(dividers) {
    }

    static Errorable<BossBarUpdateStyle> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(color, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<BossBarUpdateStyle>(PACKET_ORDINAL))
      ProceedErrorable(dividers, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<BossBarUpdateStyle>(PACKET_ORDINAL))
      return SuccessErrorable<BossBarUpdateStyle>({color, dividers});
    }

    ~BossBarUpdateStyle() override = default;

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
    return SuccessErrorable<bool>(true);
      buffer->WriteVarInt(color);
      buffer->WriteVarInt(dividers);
    }

    [[nodiscard]] uint32_t GetAction() const override {
      return 4;
    }

    [[nodiscard]] uint32_t GetColor() const {
      return color;
    }

    [[nodiscard]] uint32_t GetDividers() const {
      return dividers;
    }
  };

  class BossBarUpdateFlags : public BossBarAction {
   private:
    uint8_t flags;

   public:
    BossBarUpdateFlags() = default;

    explicit BossBarUpdateFlags(uint8_t flags) : flags(flags) {
    }

    static Errorable<BossBarUpdateFlags> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(flags, uint8_t, buffer->ReadByte(), InvalidPacketErrorable<BossBarUpdateFlags>(PACKET_ORDINAL))
      return SuccessErrorable<BossBarUpdateFlags>(BossBarUpdateFlags(flags));
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
    return SuccessErrorable<bool>(true);
      buffer->WriteByte(flags);
    }

    [[nodiscard]] uint32_t GetAction() const override {
      return 5;
    }

    [[nodiscard]] uint8_t GetFlags() const {
      return flags;
    }
  };

  class BossBar : public Packet {
   private:
    UUID uuid;
    BossBarAction* action;

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    BossBar(const UUID& uuid, BossBarAction* action) : uuid(uuid), action(action) {
    }

    static Errorable<BossBar> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(uuid, UUID, buffer->ReadUUID(), InvalidPacketErrorable<>(PACKET_ORDINAL))
      ProceedErrorable(actionId, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<>(PACKET_ORDINAL))

      switch (actionId) {
        case 0:
          action = new BossBarAdd(holder);
          break;

        case 1:
          action = new BossBarRemove(holder);
          break;

        case 2:
          action = new BossBarUpdateHealth(holder);
          break;

        case 3:
          action = new BossBarUpdateTitle(holder);
          break;

        case 4:
          action = new BossBarUpdateStyle(holder);
          break;

        case 5:
          action = new BossBarUpdateFlags(holder);
          break;

        default:
          throw Exception("Unknown boss bar action");
      }
    }

    ~BossBar() override = default;

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
    return SuccessErrorable<bool>(true);
      buffer->WriteUUID(uuid);
      buffer->WriteVarInt(action->GetAction());
      action->Write(version, buffer);
    }

    [[nodiscard]] uint32_t GetOrdinal() const override {
      return PACKET_ORDINAL;
    }

    [[nodiscard]] const UUID& GetUuid() const {
      return uuid;
    }

    [[nodiscard]] BossBarAction* GetAction() const {
      return action;
    }
  };
}
