#pragma once

#include "AbstractVillager.hpp"

namespace Ship {

  class WanderingTraderMetadata : public AbstractVillagerMetadata {
   public:
    WanderingTraderMetadata() = default;
    ~WanderingTraderMetadata() override = default;

    void Read(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractVillagerMetadata::Read(metadata, version);
    }

    void Write(Metadata* metadata, const ProtocolVersion* version) override {
      AbstractVillagerMetadata::Write(metadata, version);
    }
  };
}