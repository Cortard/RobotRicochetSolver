#include "Serveur.h"

SOCKET Serveur::sock;
SOCKADDR_IN Serveur::addressInternet;
std::chrono::seconds Serveur::lastProcessTime=std::chrono::seconds(35);
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

    addressInternet.sin_addr.s_addr = inet_addr(IP);
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
[[noreturn]] void Serveur::acceptLoop() {
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
[[noreturn]] void Serveur::processLoop(){
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
                        slot.clearOutput<char>();
                        slot.state = STATE_RECEIVING_PICTURE_SIZE;
                        Logs::write("Slot " + std::to_string(i) + " choose to send us a picture",LOG_LEVEL_VERBOSE);
                        std::thread(Serveur::getClientPictureSize, &slot).detach();
                    } else {
                        slot.clearOutput<char>();
                        slot.state = STATE_RECEIVING_GRIP_TYPE;
                        Logs::write("Slot " + std::to_string(i) + " choose to send us a grid",LOG_LEVEL_VERBOSE);
                        std::thread(Serveur::getClientGridType, &slot).detach();
                    }
                    break;
                //Picture Part ------------------------------------------------------------------------------------------
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
                //Grid Part ------------------------------------------------------------------------------------------
                case STATE_RECEIVED_GRIP_TYPE:
                    slot.state = STATE_SENDING_GRIP_TYPE_CONFIRMATION;
                    Logs::write("Sending gridTypeConfirm to client on slot " + std::to_string(i),LOG_LEVEL_VERBOSE);
                    std::thread(Serveur::confirmClientGridType, &slot).detach();
                    break;
                case STATE_SENT_TYPE_GRIP_TYPE_CONFIRMATION:
                    slot.state = STATE_RECEIVING_GRID;
                    Logs::write("Receiving grid from client on slot " + std::to_string(i),LOG_LEVEL_VERBOSE);
                    std::thread(Serveur::getClientGrid, &slot).detach();
                    break;
                case STATE_RECEIVED_GRID:
                    slot.state = STATE_SENDING_GRID_CONFIRMATION;
                    Logs::write("Sending gridConfirm to client on slot " + std::to_string(i),LOG_LEVEL_VERBOSE);
                    std::thread(Serveur::confirmClientGrid, &slot).detach();
                    break;
                case STATE_SENT_TYPE_GRID_CONFIRMATION:
                    slot.state = STATE_SOLVING;
                    Logs::write("Slot " + std::to_string(i) + " begin to solve",LOG_LEVEL_VERBOSE);
                    std::thread(Serveur::solving, &slot).detach();
                    break;
                //Process Part ------------------------------------------------------------------------------------------
                case STATE_SOLVED:
                    slot.state = STATE_SENDING_PATH;
                    Logs::write("Sending path to client on slot " + std::to_string(i),LOG_LEVEL_VERBOSE);
                    std::thread(Serveur::sendPath, &slot).detach();
                    break;
                case STATE_SENT_TYPE_PATH:
                    Logs::write("Client process on slot " + std::to_string(i) + " is done",LOG_LEVEL_VERBOSE);
                    shutdown(slot.socket, 2);
                    slot.disconnect();
                    break;

                case STATE_Process1:
                default:
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
    int result = recv(slot->socket, (char*)slot->output, sizeof(char), 0);
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
    int result = recv(slot->socket, (char*)slot->output, sizeof(unsigned int[2]), 0);
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
    int result = recv(slot->socket, (char*)slot->output, sizeof(char)*size[0]*size[1]*3, 0);
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

//---------------------------------------------------------------------------------------------------------------------------------//
//                                               reception grid                                                                    //
//---------------------------------------------------------------------------------------------------------------------------------//
void Serveur::getClientGridType(Client *slot) {
    slot->output=new char[1];
    int result = recv(slot->socket, (char*)slot->output, sizeof(char), 0);
    if(verifySocketOutput<char>(slot,false,result)==EXIT_FAILURE) return;
    slot->state=STATE_RECEIVED_GRIP_TYPE;
}
void Serveur::confirmClientGridType(Client *slot) {
    int result = send(slot->socket, (char*)slot->output, sizeof(char), 0);
    if(verifySocketOutput<char>(slot,true,result)==EXIT_FAILURE) return;
    slot->state=STATE_SENT_TYPE_GRIP_TYPE_CONFIRMATION;
}
void Serveur::getClientGrid(Client *slot) {
    char* type=static_cast<char*>(slot->output);
    slot->output=new Game();

    int result = recv(slot->socket, (char*)((Game*)slot->output)->grid, sizeof(unsigned int[256]), 0);
    if(verifySocketOutput<Game>(slot,false,result)==EXIT_FAILURE) return;

    result = recv(slot->socket, (char*)((Game*)slot->output)->robots, sizeof(unsigned int[4]), 0);
    if(verifySocketOutput<Game>(slot,false,result)==EXIT_FAILURE) return;

    result = recv(slot->socket, (char*)&((Game*)slot->output)->token, sizeof(unsigned int ), 0);
    if(verifySocketOutput<Game>(slot,false,result)==EXIT_FAILURE) return;



    ((Game*)slot->output)->last=0;

    delete type;
    slot->state=STATE_RECEIVED_GRID;
}

void Serveur::confirmClientGrid(Client *slot) {
    int lastTime=static_cast<int>(lastProcessTime.count());
    int result = send(slot->socket, (char*)&lastTime, sizeof(lastTime), 0);
    if(verifySocketOutput<Game>(slot,true,result)==EXIT_FAILURE) return;
    slot->state=STATE_SENT_TYPE_GRID_CONFIRMATION;
}

//---------------------------------------------------------------------------------------------------------------------------------//
//                                               process                                                                           //
//---------------------------------------------------------------------------------------------------------------------------------//
void Serveur::solving(Client *slot) {
    unsigned char* path;
    try{
        path = new unsigned char[32]{0};
    } catch (std::bad_alloc& ba) {
        Logs::write("Bad alloc on slot " + std::to_string(slot->slotNum),LOG_LEVEL_ERROR);
        char flag=2;
        int result = send(slots[0].socket, (char*)&flag, sizeof(char), 0);
        if(verifySocketOutput<Game>(slot,true,result)==EXIT_FAILURE) return;
        slot->clearOutput<Game>();
        slot->disconnect();
        return;
    }
    ((Game*)slot->output)->displayGame();
    int result=0;
    try {
        result = Solver::search((Game*)slot->output, path, callbackSolver);
    } catch (const std::exception& e) {
        Logs::write("Client disconnected on slot " + std::to_string(slot->slotNum),LOG_LEVEL_WARNING);
        slot->clearOutput<Game>();
        slot->disconnect();
        return;
    }
    if (result==-1) return;//Client disconnected
    if(result==0){
        Logs::write("No solution found on slot " + std::to_string(slot->slotNum),LOG_LEVEL_WARNING);
        char flag=2;
        result = send(slots[0].socket, (char*)&flag, sizeof(char), 0);
        if(verifySocketOutput<Game>(slot,true,result)==EXIT_FAILURE) return;
        slot->clearOutput<Game>();
        slot->disconnect();
        return;
    }
    Logs::write("Solution found on slot " + std::to_string(slot->slotNum),LOG_LEVEL_INFO);
    char flag=3;
    result = send(slots[0].socket, (char*)&flag, sizeof(char), 0);
    if(verifySocketOutput<Game>(slot,true,result)==EXIT_FAILURE) return;

    slot->clearOutput<Game>();
    slot->output=path;
    slot->state=STATE_SOLVED;
}
bool Serveur::callbackSolver(unsigned int max_depth, std::chrono::seconds duration) {
    if(duration.count()<5) return true;

    char flag=1;
    int result = send(slots[0].socket, (char*)&flag, sizeof(char), 0);
    if(verifySocketOutput<Game>(&slots[0],true,result)==EXIT_FAILURE) return false;

    int message[2]={static_cast<int>(max_depth),static_cast<int>(duration.count())};
    result = send(slots[0].socket, (char*)message, sizeof(int[2]), 0);
    if(verifySocketOutput<Game>(&slots[0],true,result)==EXIT_FAILURE) return false;
    Logs::write("Not solution in depth " + std::to_string(max_depth) + " in " + std::to_string(duration.count()) + "s on slot " + std::to_string(slots[0].slotNum),LOG_LEVEL_DETAILS);

    return true;
}
void Serveur::sendPath(Client *slot) {
    int result = send(slot->socket,(char*)slot->output, sizeof(unsigned char) * 32, 0);
    if(verifySocketOutput<unsigned char>(slot,true,result)==EXIT_FAILURE) return;
    char confirm;
    result = recv(slot->socket, (char*)&confirm, sizeof(char),MSG_WAITALL);
    if(verifySocketOutput<unsigned char>(slot,false,result)==EXIT_FAILURE) return;

    slot->clearOutput<unsigned char>();
    slot->state=STATE_SENT_TYPE_PATH;
}