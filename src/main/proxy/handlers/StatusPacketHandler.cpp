#include "../../../network/Connection.hpp"
#include "../../../protocol/packets/status/StatusResponse.hpp"
#include "ProxyPacketHandler.hpp"

namespace Ship {
  void StatusPacketHandler::Init() {
    SetPacketCallback(StatusPacketHandler, StatusRequest, OnStatusRequest);
    SetPacketCallback(StatusPacketHandler, StatusPing, OnStatusPing);
  }

  inline bool StatusPacketHandler::OnStatusRequest(Connection* connection, StatusRequest* statusRequest) {
    connection->WriteAndFlush(new StatusResponse(R"({"players":{"max": 4444,"online":    0,"sample":[{"id":"00000000-0000-0000-0000-000000000009","name":"ShipMC Test"}]},"description":{"extra":[{"color":"red","text":"| "},{"bold":true,"color":"dark_purple","text":"Elytrium "},{"color":"red","text":"| "},{"color":"gold","text":"ShipMC Test"},{"text":"\n . "},{"color":"gray","text":"1.12.2 - 1.19.3"},{"text":" . "},{"color":"gray","text":"https://elytrium.net/discord/"}],"text":" "},"version":{"name":"Elytrium","protocol":       47},"favicon":""})"), true);
    return true;
  }

  inline bool StatusPacketHandler::OnStatusPing(Connection* connection, StatusPing* statusPing) {
    connection->WriteAndFlush(new StatusPing(statusPing->GetId()), true);
    connection->GetReadWriteCloser()->Close();
    return true;
  }
} // Ship