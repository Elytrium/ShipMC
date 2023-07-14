#pragma once

#include "../../../../lib/ShipNet/src/utils/ordinal/OrdinalRegistry.hpp"
#include <string>
#include <utility>

namespace Ship {

  class BossBarAction : public Serializable {
   public:
    ~BossBarAction() override = default;

    [[nodiscard]] virtual uint32_t GetAction() const = 0;
  };

  template<typename T>
  class InvalidBossBarActionErrorable : public Errorable<T> {
   public:
    static inline const uint32_t TYPE_ORDINAL = OrdinalRegistry::ErrorableTypeRegistry.RegisterOrdinal();

    explicit InvalidBossBarActionErrorable(uint32_t action_id) : Errorable<T>(TYPE_ORDINAL, {}, action_id) {
    }

    void Print(std::ostream o) {
      o << "Invalid boss bar action received, action id: " << this->GetErrorCode();
    }
  };

  class BossBarAdd : public BossBarAction {
   private:
    std::string title; // TODO: Chat components
    float health {};
    uint32_t color {};
    uint32_t division {};
    uint8_t flags {};

   public:
    static inline const uint32_t ACTION_ID = 0;

    BossBarAdd() = default;

    BossBarAdd(std::string title, float health, uint32_t color, uint32_t division, uint8_t flags)
      : title(std::move(title)), health(health), color(color), division(division), flags(flags) {
    }

    ~BossBarAdd() override = default;

    static Errorable<BossBarAdd> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(title, std::string, buffer->ReadString(), InvalidBossBarActionErrorable<BossBarAdd>(ACTION_ID))
      ProceedErrorable(health, float, buffer->ReadFloat(), InvalidBossBarActionErrorable<BossBarAdd>(ACTION_ID))
      ProceedErrorable(color, uint32_t, buffer->ReadVarInt(), InvalidBossBarActionErrorable<BossBarAdd>(ACTION_ID))
      ProceedErrorable(division, uint32_t, buffer->ReadVarInt(), InvalidBossBarActionErrorable<BossBarAdd>(ACTION_ID))
      ProceedErrorable(flags, uint8_t, buffer->ReadByte(), InvalidBossBarActionErrorable<BossBarAdd>(ACTION_ID))
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
      return ACTION_ID;
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
    static inline const uint32_t ACTION_ID = 1;

    static Errorable<BossBarRemove> Instantiate(const PacketHolder& holder) {
      return SuccessErrorable<BossBarRemove>({});
    }

    ~BossBarRemove() override = default;

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetAction() const override {
      return ACTION_ID;
    }
  };

  class BossBarUpdateHealth : public BossBarAction {
   private:
    float health {};

   public:
    static inline const uint32_t ACTION_ID = 2;

    BossBarUpdateHealth() = default;

    explicit BossBarUpdateHealth(float health) : health(health) {
    }

    static Errorable<BossBarUpdateHealth> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(health, float, buffer->ReadFloat(), InvalidBossBarActionErrorable<BossBarUpdateHealth>(ACTION_ID))
      return SuccessErrorable<BossBarUpdateHealth>(BossBarUpdateHealth(health));
    }

    ~BossBarUpdateHealth() override = default;

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteFloat(health);
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetAction() const override {
      return ACTION_ID;
    }

    [[nodiscard]] float GetHealth() const {
      return health;
    }
  };

  class BossBarUpdateTitle : public BossBarAction {
   private:
    std::string title; // TODO: Chat components

   public:
    static inline const uint32_t ACTION_ID = 3;

    BossBarUpdateTitle() = default;

    explicit BossBarUpdateTitle(std::string title) : title(std::move(title)) {
    }

    static Errorable<BossBarUpdateTitle> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(title, std::string, buffer->ReadString(), InvalidBossBarActionErrorable<BossBarUpdateTitle>(ACTION_ID))
      return SuccessErrorable<BossBarUpdateTitle>(BossBarUpdateTitle(title));
    }

    ~BossBarUpdateTitle() override = default;

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteString(title);
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetAction() const override {
      return ACTION_ID;
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
    static inline const uint32_t ACTION_ID = 4;

    BossBarUpdateStyle() = default;

    BossBarUpdateStyle(uint32_t color, uint32_t dividers) : color(color), dividers(dividers) {
    }

    static Errorable<BossBarUpdateStyle> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(color, uint32_t, buffer->ReadVarInt(), InvalidBossBarActionErrorable<BossBarUpdateStyle>(ACTION_ID))
      ProceedErrorable(dividers, uint32_t, buffer->ReadVarInt(), InvalidBossBarActionErrorable<BossBarUpdateStyle>(ACTION_ID))
      return SuccessErrorable<BossBarUpdateStyle>({color, dividers});
    }

    ~BossBarUpdateStyle() override = default;

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteVarInt(color);
      buffer->WriteVarInt(dividers);
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetAction() const override {
      return ACTION_ID;
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
    uint8_t flags{};

   public:
    static inline const uint32_t ACTION_ID = 5;

    BossBarUpdateFlags() = default;

    explicit BossBarUpdateFlags(uint8_t flags) : flags(flags) {
    }

    static Errorable<BossBarUpdateFlags> Instantiate(const PacketHolder& holder) {
      ByteBuffer* buffer = holder.GetCurrentBuffer();
      ProceedErrorable(flags, uint8_t, buffer->ReadByte(), InvalidBossBarActionErrorable<BossBarUpdateFlags>(ACTION_ID))
      return SuccessErrorable<BossBarUpdateFlags>(BossBarUpdateFlags(flags));
    }

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteByte(flags);
      return SuccessErrorable<bool>(true);
    }

    [[nodiscard]] uint32_t GetAction() const override {
      return ACTION_ID;
    }

    [[nodiscard]] uint8_t GetFlags() const {
      return flags;
    }
  };

  class BossBar : public Packet {
   private:
    UUID uuid{};
    BossBarAction* action{};

   public:
    static inline const uint32_t PACKET_ORDINAL = OrdinalRegistry::PacketRegistry.RegisterOrdinal();

    BossBar() = default;
    BossBar(const UUID& uuid, BossBarAction* action) : uuid(uuid), action(action) {
    }

    static Errorable<BossBar> Instantiate(const PacketHolder& holder);

    ~BossBar() override = default;

    Errorable<bool> Write(const ProtocolVersion* version, ByteBuffer* buffer) const override {
      buffer->WriteUUID(uuid);
      buffer->WriteVarInt(action->GetAction());
      action->Write(version, buffer);
      return SuccessErrorable<bool>(true);
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
  CreateInvalidArgumentErrorable(UnknownBossBarActionErrorable, BossBar, "Unknown boss bar action");

  Errorable<BossBar> BossBar::Instantiate(const PacketHolder& holder) {
    ByteBuffer* buffer = holder.GetCurrentBuffer();
    ProceedErrorable(uuid, UUID, buffer->ReadUUID(), InvalidPacketErrorable<BossBar>(PACKET_ORDINAL))
    ProceedErrorable(actionID, uint32_t, buffer->ReadVarInt(), InvalidPacketErrorable<BossBar>(PACKET_ORDINAL))

    switch (actionID) {
      case BossBarAdd::ACTION_ID: {
        ProceedErrorable(action, BossBarAdd, BossBarAdd::Instantiate(holder), InvalidPacketErrorable<BossBar>(PACKET_ORDINAL))
        return SuccessErrorable<BossBar>(BossBar(uuid, &action));
      }
      case BossBarRemove::ACTION_ID: {
        ProceedErrorable(action, BossBarRemove, BossBarRemove::Instantiate(holder), InvalidPacketErrorable<BossBar>(PACKET_ORDINAL))
        return SuccessErrorable<BossBar>(BossBar(uuid, &action));
      }
      case BossBarUpdateHealth::ACTION_ID: {
        ProceedErrorable(action, BossBarUpdateHealth, BossBarUpdateHealth::Instantiate(holder), InvalidPacketErrorable<BossBar>(PACKET_ORDINAL))
        return SuccessErrorable<BossBar>(BossBar(uuid, &action));
      }
      case BossBarUpdateTitle::ACTION_ID: {
        ProceedErrorable(action, BossBarUpdateTitle, BossBarUpdateTitle::Instantiate(holder), InvalidPacketErrorable<BossBar>(PACKET_ORDINAL))
        return SuccessErrorable<BossBar>(BossBar(uuid, &action));
      }
      case BossBarUpdateStyle::ACTION_ID: {
        ProceedErrorable(action, BossBarUpdateStyle, BossBarUpdateStyle::Instantiate(holder), InvalidPacketErrorable<BossBar>(PACKET_ORDINAL))
        return SuccessErrorable<BossBar>(BossBar(uuid, &action));
      }
      case BossBarUpdateFlags::ACTION_ID: {
        ProceedErrorable(action, BossBarUpdateFlags, BossBarUpdateFlags::Instantiate(holder), InvalidPacketErrorable<BossBar>(PACKET_ORDINAL))
        return SuccessErrorable<BossBar>(BossBar(uuid, &action));
      }
      default: {
        return UnknownBossBarActionErrorable(actionID);
      }
    }
  }
}
