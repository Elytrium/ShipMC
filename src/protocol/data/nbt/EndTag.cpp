#include "NBT.hpp"

namespace Ship {
  EndTag::EndTag(const std::string& name) : NBT(name) {
  }

  Errorable<bool> EndTag::Read(ByteBuffer* buffer) {
    return SuccessErrorable<bool>(true);
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
