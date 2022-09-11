#include "NBT.hpp"

namespace Ship {

  NBT* NBT::Create(TagType tagType, const std::string& name) {
    switch (tagType) {
      case END: {
        return new EndTag(name);
      }
      case BYTE: {
        return new ByteTag(name);
      }
      case SHORT: {
        return new ShortTag(name);
      }
      case INT: {
        return new IntTag(name);
      }
      case LONG: {
        return new LongTag(name);
      }
      case FLOAT: {
        return new FloatTag(name);
      }
      case DOUBLE: {
        return new DoubleTag(name);
      }
      case BYTE_ARRAY: {
        return new ByteArrayTag(name);
      }
      case STRING: {
        return new StringTag(name);
      }
      case LIST: {
        return new ListTag(name);
      }
      case COMPOUND: {
        return new CompoundTag(name);
      }
      case INT_ARRAY: {
        return new IntArrayTag(name);
      }
      case LONG_ARRAY: {
        return new LongArrayTag(name);
      }
    }
  }
}
