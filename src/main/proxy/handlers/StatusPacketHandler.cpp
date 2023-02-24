#include "../../../network/Connection.hpp"
#include "../../../protocol/packets/status/StatusResponse.hpp"
#include "ProxyPacketHandler.hpp"

namespace Ship {
  void StatusPacketHandler::Init() {
    SetPacketCallback(StatusPacketHandler, StatusRequest, OnStatusRequest);
    SetPacketCallback(StatusPacketHandler, StatusPing, OnStatusPing);
  }

  inline bool StatusPacketHandler::OnStatusRequest(Connection* connection, StatusRequest* statusRequest) {
    connection->WriteAndFlush(new StatusResponse("{}"), true); // TODO: It doesn't work well =( It duplicates packets many times. Not sure why. Possibly the packet registry is broken.
    return true;
  }

  inline bool StatusPacketHandler::OnStatusPing(Connection* connection, StatusPing* statusPing) {
    connection->WriteAndFlush(new StatusPing(statusPing->GetId()), true);
    connection->GetReadWriteCloser()->Close();
    return true;
  }
} // Ship