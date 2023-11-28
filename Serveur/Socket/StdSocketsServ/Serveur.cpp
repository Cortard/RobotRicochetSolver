#include "Serveur.h"

SOCKET Serveur::sock;
SOCKADDR_IN Serveur::addressInternet;
Client Serveur::slots[MAX_CLIENTS];

//---------------------------------------------------------------------------------------------------------------------------------//
//                                                       init                                                                      //
//---------------------------------------------------------------------------------------------------------------------------------//
int Serveur::init() {
    Logs::write("Initialisation socket",LOG_LEVEL_INFO);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == INVALID_SOCKET) {
        Logs::write("Socket error",LOG_LEVEL_ERROR);
        return EXIT_FAILURE;
    }
    Logs::write("Socket Done",LOG_LEVEL_DETAILS);

    addressInternet.sin_addr.s_addr = inet_addr(IP);//htonl(INADDR_ANY)
    addressInternet.sin_family = AF_INET;
    addressInternet.sin_port = htons(PORT);
    socklen_t sockAddrInterSize = sizeof(addressInternet);

    if( bind(sock,(SOCKADDR*)&addressInternet,sockAddrInterSize) != 0  ) {
        Logs::write("Bind error",LOG_LEVEL_ERROR);
        return EXIT_FAILURE;
    }
    Logs::write("Bind Done for IP: " + std::string(inet_ntoa(addressInternet.sin_addr)) + " PORT : " + std::to_string(htons(addressInternet.sin_port)),LOG_LEVEL_DETAILS);

    if(listen(sock, 5) != 0){
        Logs::write("Listen error",LOG_LEVEL_ERROR);
        return EXIT_FAILURE;
    }
    Logs::write("Listen Done",LOG_LEVEL_DETAILS);

    for(Client & slot: slots) slot.state=STATE_DISCONNECTED;

    return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------//
//                                                       end                                                                       //
//---------------------------------------------------------------------------------------------------------------------------------//
void Serveur::end() {
    shutdown(sock, 2);
    closesocket(sock);
    Logs::write("Close socket",LOG_LEVEL_INFO);
}

//---------------------------------------------------------------------------------------------------------------------------------//
//                                                 acceptLoop                                                                      //
//---------------------------------------------------------------------------------------------------------------------------------//
void Serveur::acceptLoop() {
    Logs::write("Accept loop start",LOG_LEVEL_INFO);

    SOCKADDR_IN sockAddrClient;
    socklen_t sockAddrClientSize=sizeof(SOCKADDR_IN);

    while(true){
        SOCKET newClientSock=accept(sock, (SOCKADDR*)&sockAddrClient, &sockAddrClientSize);
        if( newClientSock == SOCKET_ERROR ) {
            continue;
        }
        Logs::write("Client accepted IP" + std::string(inet_ntoa(sockAddrClient.sin_addr)) + " PORT : " + std::to_string(htons(sockAddrClient.sin_port)),LOG_LEVEL_DETAILS);

        int freeSlot=foundEmptySlot();
        if(freeSlot==MAX_CLIENTS){
            Logs::write("Max client reached",LOG_LEVEL_WARNING);
            continue;
        }
        slots[freeSlot].connect(newClientSock);
        Logs::write("Client added on slot " + std::to_string(freeSlot),LOG_LEVEL_VERBOSE);
    }
}

//---------------------------------------------------------------------------------------------------------------------------------//
//                                                 processLoop                                                                     //
//---------------------------------------------------------------------------------------------------------------------------------//
void Serveur::processLoop(){
    Logs::write("Process loop start",LOG_LEVEL_INFO);
    while (true) {
        for (int i=0;i<MAX_CLIENTS; ++i) {
            Client& slot = slots[i];
            int state = slot.state;
            if(state%2) continue;// if state is odd, the slot is processing or disconnected
            switch (state) {
                case STATE_DISCONNECTED:
                    break;
                case STATE_NEW_CONNECTED:
                    slot.state = STATE_RECEIVING_TYPE_DATA;
                    Logs::write("Receiving type from client on slot " + std::to_string(i),LOG_LEVEL_VERBOSE);
                    std::thread(Serveur::getClientDataType, &slot).detach();
                    break;
                case STATE_RECEIVED_TYPE_DATE:
                    slot.state = STATE_SENDING_TYPE_DATA_CONFIRMATION;
                    Logs::write("Sending typeConfirm to client on slot " + std::to_string(i),LOG_LEVEL_VERBOSE);
                    std::thread(Serveur::confirmClientDataType, &slot).detach();
                    break;
                case STATE_SENT_TYPE_DATA_CONFIRMATION:
                    if(((char*)slot.output)[0]==0){
                        slot.state = STATE_RECEIVING_PICTURE_SIZE;
                        slot.clearOutput<char>();
                        Logs::write("Slot " + std::to_string(i) + " choose to send us a picture",LOG_LEVEL_VERBOSE);
                        std::thread(Serveur::getClientPictureSize, &slot).detach();
                    } else {
                        slot.state = STATE_RECEIVING_GRIP_TYPE;
                        slot.clearOutput<char>();
                        Logs::write("Slot " + std::to_string(i) + " choose to send us a grid",LOG_LEVEL_VERBOSE);
                        //TODO
                    }
                    break;

                case STATE_RECEIVED_PICTURE_SIZE:
                    slot.state = STATE_SENDING_PICTURE_SIZE_CONFIRMATION;
                    Logs::write("Sending pictureSizeConfirm to client on slot " + std::to_string(i),LOG_LEVEL_VERBOSE);
                    std::thread(Serveur::confirmClientPictureSize, &slot).detach();
                    break;
                case STATE_SENT_PICTURE_SIZE_CONFIRMATION:
                    slot.state = STATE_RECEIVING_PICTURE;
                    Logs::write("Receiving picture from client on slot " + std::to_string(i),LOG_LEVEL_VERBOSE);
                    std::thread(Serveur::getClientPicture, &slot).detach();
                    break;
                case STATE_RECEIVED_PICTURE:
                    slot.state = STATE_SENDING_PICTURE_CONFIRMATION;
                    Logs::write("Sending pictureConfirm to client on slot " + std::to_string(i),LOG_LEVEL_VERBOSE);
                    std::thread(Serveur::confirmClientPicture, &slot).detach();
                    break;
                case STATE_SENT_TYPE_PICTURE_CONFIRMATION:
                    slot.state = STATE_Process1;
                    slot.clearOutput<char>();
                    Logs::write("Slot " + std::to_string(i) + " is ready to process",LOG_LEVEL_VERBOSE);
                    //TODO
                    break;

                case STATE_Process1:
                    Logs::write("Client process on slot " + std::to_string(i) + " is done",LOG_LEVEL_VERBOSE);
                    shutdown(slot.socket, 2);
                    slot.output= nullptr;
                    slot.disconnect();
                    break;
            }
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------------------//
//                                            acceptLoop tools                                                                     //
//---------------------------------------------------------------------------------------------------------------------------------//
int Serveur::foundEmptySlot()
{
    int i=0;
    while(i<MAX_CLIENTS && slots[i].state!=STATE_DISCONNECTED){
        ++i;
    }
    return i;
}

//---------------------------------------------------------------------------------------------------------------------------------//
//                                           processLoop tools                                                                     //
//---------------------------------------------------------------------------------------------------------------------------------//
template <typename T>
int Serveur::verifySocketOutput(Client *slot, bool send, int result) {
    switch (result) {
        case SOCKET_ERROR:
            if(send) Logs::write("Error when send for slot "+std::to_string(slot->slotNum)+" on state "+std::to_string(slots[slot->slotNum].state), LOG_LEVEL_ERROR);
            else Logs::write("Error when receive for slot "+std::to_string(slot->slotNum)+" on state "+std::to_string(slots[slot->slotNum].state), LOG_LEVEL_ERROR);
            slot->clearOutput<T>();
            slot->disconnect();
            return EXIT_FAILURE;
        case 0:
            Logs::write("Client disconnected for slot "+std::to_string(slot->slotNum)+" on state "+std::to_string(slots[slot->slotNum].state), LOG_LEVEL_WARNING);
            slot->clearOutput<T>();
            slot->disconnect();
            return EXIT_FAILURE;
        default:
            break;
    }
    return EXIT_SUCCESS;
}

//---------------------------------------------------------------------------------------------------------------------------------//
//                                        reception type of Client input                                                           //
//---------------------------------------------------------------------------------------------------------------------------------//
void Serveur::getClientDataType(Client* slot){
    slot->output=new char[1];
    int result = recv(slot->socket, (char*)slot->output, sizeof(char), MSG_WAITALL);
    if(verifySocketOutput<char>(slot,false,result)==EXIT_FAILURE) return;
    slot->state=STATE_RECEIVED_TYPE_DATE;
}
void Serveur::confirmClientDataType(Client *slot) {
    int result = send(slot->socket, (char*)slot->output, sizeof(char), 0);
    if(verifySocketOutput<char>(slot,true,result)==EXIT_FAILURE) return;
    slot->state=STATE_SENT_TYPE_DATA_CONFIRMATION;
}

//---------------------------------------------------------------------------------------------------------------------------------//
//                                               reception picture                                                                 //
//---------------------------------------------------------------------------------------------------------------------------------//
void Serveur::getClientPictureSize(Client *slot) {
    slot->output=new unsigned int[2];
    int result = recv(slot->socket, (char*)slot->output, sizeof(unsigned int[2]), MSG_WAITALL);
    if(verifySocketOutput<unsigned int>(slot,false,result)==EXIT_FAILURE) return;
    slot->state=STATE_RECEIVED_PICTURE_SIZE;
}
void Serveur::confirmClientPictureSize(Client *slot) {
    auto* size=static_cast<unsigned int*>(slot->output);
    long confirmSize=static_cast<long>(size[0])*static_cast<long>(size[1])*3;
    int result = send(slot->socket, (char*)&confirmSize, sizeof(long), 0);
    if(verifySocketOutput<unsigned int>(slot,false,result)==EXIT_FAILURE) return;
    slot->state=STATE_SENT_PICTURE_SIZE_CONFIRMATION;
}
void Serveur::getClientPicture(Client *slot) {
    auto* size=static_cast<unsigned int*>(slot->output);
    slot->output=new char[size[0]*size[1]*3];
    int result = recv(slot->socket, (char*)slot->output, sizeof(char)*size[0]*size[1]*3, MSG_WAITALL);
    if(verifySocketOutput<char>(slot,false,result)==EXIT_FAILURE) return;
    //TODO put real picture object in slot->output
    delete[] size;
    slot->state=STATE_RECEIVED_PICTURE;
}
void Serveur::confirmClientPicture(Client *slot) {
    char confirm=0;
    int result = send(slot->socket, (char*)&confirm, sizeof(char), 0);
    if(verifySocketOutput<char>(slot,true,result)==EXIT_FAILURE) return;
    //TODO change char for type of picture on the previous line
    slot->state=STATE_SENT_TYPE_PICTURE_CONFIRMATION;
}
