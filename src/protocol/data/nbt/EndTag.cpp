#include "NBT.hpp"

namespace Ship {
  EndTag::EndTag(const std::string& name) : NBT(name) {
  }

  void EndTag::Read(ByteBuffer* buffer) {
  }

  void EndTag::Write(ByteBuffer* buffer) {
  }

  uint32_t EndTag::GetSize() {
    return 0;
  }

  TagType EndTag::GetType() {
    return TagType::END;
  }
}
