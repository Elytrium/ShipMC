#pragma once

#include "ShipNet/protocol/Protocol.hpp"
#include <list>
#include <map>
#include <optional>
#include <string>
#include <utility>

namespace Ship {

  enum TagType {
    END = 0,
    BYTE = 1,
    SHORT = 2,
    INT = 3,
    LONG = 4,
    FLOAT = 5,
    DOUBLE = 6,
    BYTE_ARRAY = 7,
    STRING = 8,
    LIST = 9,
    COMPOUND = 10,
    INT_ARRAY = 11,
    LONG_ARRAY = 12
  };

  class NBT {
   private:
    std::string name;

   public:
    static NBT* Create(TagType tagType, const std::string& name);

    NBT() = default;
    explicit NBT(std::string name) : name(std::move(name)) {};

    virtual ~NBT() = default;

    virtual Errorable<bool> Read(ByteBuffer* buffer) {
      return SuccessErrorable<bool>(false);
    };
    virtual void Write(ByteBuffer* buffer) {};
    virtual TagType GetType() = 0;

    virtual uint32_t GetSize() {
      ByteCounter counter;
      Write(&counter);
      return counter.GetWriterIndex();
    }

    std::string GetName() {
      return name;
    }

    void SetName(std::string new_name) {
      name = std::move(new_name);
    }
  };
  CreateInvalidArgumentErrorable(InvalidNBTErrorable, NBT*, "Invalid NBT read");
  CreateInvalidArgumentErrorable(InvalidNBTTagErrorable, bool, "Invalid NBT tag read");

  class EndTag : public NBT {
   public:
    explicit EndTag(const std::string& name);

    void Write(ByteBuffer* buffer) override;
    Errorable<bool> Read(ByteBuffer* buffer) override;
    uint32_t GetSize() override;
    TagType GetType() override;
  };

  class ByteTag : public NBT {
   private:
    uint8_t value {};

   public:
    explicit ByteTag(const std::string& name);
    ByteTag(const std::string& name, uint8_t value);

    void Write(ByteBuffer* buffer) override;
    Errorable<bool> Read(ByteBuffer* buffer) override;
    uint32_t GetSize() override;
    TagType GetType() override;

    [[nodiscard]] uint8_t GetValue() const;
    void SetValue(uint8_t newValue);
  };

  class ShortTag : public NBT {
   private:
    uint16_t value {};

   public:
    explicit ShortTag(const std::string& name);
    ShortTag(const std::string& name, uint16_t value);

    void Write(ByteBuffer* buffer) override;
    Errorable<bool> Read(ByteBuffer* buffer) override;
    uint32_t GetSize() override;
    TagType GetType() override;

    [[nodiscard]] uint16_t GetValue() const;
    void SetValue(uint16_t newValue);
  };

  class IntTag : public NBT {
   private:
    uint32_t value {};

   public:
    explicit IntTag(const std::string& name);
    IntTag(const std::string& name, uint32_t value);

    void Write(ByteBuffer* buffer) override;
    Errorable<bool> Read(ByteBuffer* buffer) override;
    uint32_t GetSize() override;
    TagType GetType() override;

    [[nodiscard]] uint32_t GetValue() const;
    void SetValue(uint32_t newValue);
  };

  class LongTag : public NBT {
   private:
    uint64_t value {};

   public:
    explicit LongTag(const std::string& name);
    LongTag(const std::string& name, uint64_t value);

    void Write(ByteBuffer* buffer) override;
    Errorable<bool> Read(ByteBuffer* buffer) override;
    uint32_t GetSize() override;
    TagType GetType() override;

    [[nodiscard]] uint64_t GetValue() const;
    void SetValue(uint64_t newValue);
  };

  class FloatTag : public NBT {
   private:
    float value {};

   public:
    explicit FloatTag(const std::string& name);
    FloatTag(const std::string& name, float value);

    void Write(ByteBuffer* buffer) override;
    Errorable<bool> Read(ByteBuffer* buffer) override;
    uint32_t GetSize() override;
    TagType GetType() override;

    [[nodiscard]] float GetValue() const;
    void SetValue(float newValue);
  };

  class DoubleTag : public NBT {
   private:
    double value {};

   public:
    explicit DoubleTag(const std::string& name);
    DoubleTag(const std::string& name, double value);

    void Write(ByteBuffer* buffer) override;
    Errorable<bool> Read(ByteBuffer* buffer) override;
    uint32_t GetSize() override;
    TagType GetType() override;

    [[nodiscard]] double GetValue() const;
    void SetValue(double newValue);
  };

  class ByteArrayTag : public NBT {
   private:
    uint8_t* value {};
    uint32_t valueLength {};

   public:
    ~ByteArrayTag() override {
      delete[] value;
    }

    explicit ByteArrayTag(const std::string& name);
    ByteArrayTag(const std::string& name, uint8_t* value, uint32_t valueLength);

    void Write(ByteBuffer* buffer) override;
    Errorable<bool> Read(ByteBuffer* buffer) override;
    uint32_t GetSize() override;
    TagType GetType() override;

    uint8_t* GetValue();
    [[nodiscard]] uint32_t GetValueLength() const;
    void SetValue(uint8_t* newValue, uint32_t newValueLength);
  };

  class StringTag : public NBT {
   private:
    std::string value;

   public:
    ~StringTag() override = default;

    explicit StringTag(const std::string& name);
    StringTag(const std::string& name, std::string value);

    void Write(ByteBuffer* buffer) override;
    Errorable<bool> Read(ByteBuffer* buffer) override;
    uint32_t GetSize() override;
    TagType GetType() override;

    std::string GetValue();
    void SetValue(const std::string& newValue);
  };

  class ListTag : public NBT {
   private:
    std::list<NBT*> list {};

   public:
    ~ListTag() override {
      for (const auto& item : list) {
        delete item;
      }
    }

    explicit ListTag(const std::string& name);
    ListTag(const std::string& name, std::list<NBT*> list);

    void Write(ByteBuffer* buffer) override;
    Errorable<bool> Read(ByteBuffer* buffer) override;
    uint32_t GetSize() override;
    TagType GetType() override;

    std::list<NBT*>& GetList();
  };

  class CompoundTag : public NBT {
   private:
    std::map<std::string, NBT*> map {};

   public:
    ~CompoundTag() override {
      for (const auto& item : map) {
        delete item.second;
      }
    }

    explicit CompoundTag(const std::string& name);
    CompoundTag(const std::string& name, std::map<std::string, NBT*> list);

    void Write(ByteBuffer* buffer) override;
    Errorable<bool> Read(ByteBuffer* buffer) override;
    uint32_t GetSize() override;
    TagType GetType() override;

    bool HasKey(const std::string& name);
    std::optional<NBT*> GetNBT(const std::string& name);
    std::optional<bool> GetBool(const std::string& name);
    std::optional<uint8_t> GetByte(const std::string& name);
    std::optional<uint32_t> GetInt(const std::string& name);
    std::optional<uint64_t> GetLong(const std::string& name);
    std::optional<float> GetFloat(const std::string& name);
    std::optional<double> GetDouble(const std::string& name);
    std::optional<std::string> GetString(const std::string& name);
    void AddNBT(NBT* value);
    void SetNBT(const std::string& name, NBT* value);
  };

  class IntArrayTag : public NBT {
   private:
    uint32_t* value {};
    uint32_t valueLength {};

   public:
    ~IntArrayTag() override {
      delete[] value;
    }

    explicit IntArrayTag(const std::string& name);
    IntArrayTag(const std::string& name, uint32_t* value, uint32_t valueLength);

    void Write(ByteBuffer* buffer) override;
    Errorable<bool> Read(ByteBuffer* buffer) override;
    uint32_t GetSize() override;
    TagType GetType() override;

    uint32_t* GetValue();
    [[nodiscard]] uint32_t GetValueLength() const;
    void SetValue(uint32_t* newValue, uint32_t newValueLength);
  };

  class LongArrayTag : public NBT {
   private:
    uint64_t* value {};
    uint32_t valueLength {};

   public:
    ~LongArrayTag() override {
      delete[] value;
    }

    explicit LongArrayTag(const std::string& name);
    LongArrayTag(const std::string& name, uint64_t* value, uint32_t valueLength);

    void Write(ByteBuffer* buffer) override;
    Errorable<bool> Read(ByteBuffer* buffer) override;
    uint32_t GetSize() override;
    TagType GetType() override;

    uint64_t* GetValue();
    [[nodiscard]] uint32_t GetValueLength() const;
    void SetValue(uint64_t* newValue, uint32_t newValueLength);
  };
}
