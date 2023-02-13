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

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteString(title);
      buffer->WriteFloat(health);
      buffer->WriteVarInt(color);
      buffer->WriteVarInt(division);
      buffer->WriteByte(flags);
    }

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      title = buffer->ReadString();
      health = buffer->ReadFloat();
      color = buffer->ReadVarInt();
      division = buffer->ReadVarInt();
      flags = buffer->ReadByte();
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
    ~BossBarRemove() override = default;

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
    }

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
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

    ~BossBarUpdateHealth() override = default;

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteFloat(health);
    }

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      health = buffer->ReadFloat();
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

    ~BossBarUpdateTitle() override = default;

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteString(title);
    }

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      title = buffer->ReadString();
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

    ~BossBarUpdateStyle() override = default;

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteVarInt(color);
      buffer->WriteVarInt(dividers);
    }

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      color = buffer->ReadVarInt();
      dividers = buffer->ReadVarInt();
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

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteByte(flags);
    }

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      flags = buffer->ReadByte();
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

    ~BossBar() override {
      delete action;
    }

    void Read(const ProtocolVersion* version, ByteBuffer* buffer) override {
      uuid = buffer->ReadUUID();
      uint32_t actionId = buffer->ReadVarInt();

      delete action;
      switch (actionId) {
        case 0:
          action = new BossBarAdd({}, 0, 0, 0, 0);
          break;

        case 1:
          action = new BossBarRemove();
          break;

        case 2:
          action = new BossBarUpdateHealth(0);
          break;

        case 3:
          action = new BossBarUpdateTitle({});
          break;

        case 4:
          action = new BossBarUpdateStyle(0, 0);
          break;

        case 5:
          action = new BossBarUpdateFlags(0);
          break;

        default:
          throw Exception("Unknown boss bar action");
      }

      action->Read(version, buffer);
    }

    void Write(const ProtocolVersion* version, ByteBuffer* buffer) override {
      buffer->WriteUUID(uuid);
      buffer->WriteVarInt(action->GetAction());
      action->Write(version, buffer);
    }

    uint32_t GetOrdinal() override {
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
