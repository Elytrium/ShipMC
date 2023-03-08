#pragma once

#include "../../../utils/exceptions/Exception.hpp"
#include "../../../utils/ordinal/OrdinalRegistry.hpp"
#include "../Packet.hpp"
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
    float health;
    uint32_t color;
    uint32_t division;
    uint8_t flags;

   public:
    BossBarAdd(std::string title, float health, uint32_t color, uint32_t division, uint8_t flags)
      : title(std::move(title)), health(health), color(color), division(division), flags(flags) {
    }

    ~BossBarAdd() override = default;

    explicit BossBarAdd(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      title = buffer->ReadString();
      health = buffer->ReadFloat();
      color = buffer->ReadVarInt();
      division = buffer->ReadVarInt();
      flags = buffer->ReadByte();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteString(title);
      buffer->WriteFloat(health);
      buffer->WriteVarInt(color);
      buffer->WriteVarInt(division);
      buffer->WriteByte(flags);
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
    explicit BossBarRemove(const PacketHolder& holder) {
    }

    ~BossBarRemove() override = default;

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
    }

    [[nodiscard]] uint32_t GetAction() const override {
      return 1;
    }
  };

  class BossBarUpdateHealth : public BossBarAction {
   private:
    float health;

   public:
    explicit BossBarUpdateHealth(float health) : health(health) {
    }

    explicit BossBarUpdateHealth(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      health = buffer->ReadFloat();
    }

    ~BossBarUpdateHealth() override = default;

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
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
    explicit BossBarUpdateTitle(std::string title) : title(std::move(title)) {
    }

    explicit BossBarUpdateTitle(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      title = buffer->ReadString();
    }

    ~BossBarUpdateTitle() override = default;

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
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
    uint32_t color;
    uint32_t dividers;

   public:
    BossBarUpdateStyle(uint32_t color, uint32_t dividers) : color(color), dividers(dividers) {
    }

    explicit BossBarUpdateStyle(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      color = buffer->ReadVarInt();
      dividers = buffer->ReadVarInt();
    }

    ~BossBarUpdateStyle() override = default;

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
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
    explicit BossBarUpdateFlags(uint8_t flags) : flags(flags) {
    }

    explicit BossBarUpdateFlags(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      flags = buffer->ReadByte();
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
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

    explicit BossBar(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      uuid = buffer->ReadUUID();
      uint32_t actionId = buffer->ReadVarInt();

      delete action;
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

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteUUID(uuid);
      buffer->WriteVarInt(action->GetAction());
      action->Write(version, buffer);
    }

    uint32_t GetOrdinal() const override {
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
