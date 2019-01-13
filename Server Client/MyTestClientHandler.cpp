#include "MyTestClientHandler.h"

void MyTestClientHandler::handleClient(server_side::TCP_client clientSock) {

    std::string currentLine = clientSock.GetLine();

}

MyTestClientHandler::MyTestClientHandler() = default;
