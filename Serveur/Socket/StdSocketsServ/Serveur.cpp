#include "Serveur.h"

SOCKET Serveur::sock;
SOCKADDR_IN Serveur::addressInternet;
std::chrono::seconds Serveur::totalProcessTime=std::chrono::seconds(0);
unsigned int Serveur::totalNbProcess=0;
std::mutex Serveur::mutexProcessTime;
Client Serveur::slots[MAX_CLIENTS];
bool Serveur::running=false;
std::mutex Serveur::mutexRunning;

//---------------------------------------------------------------------------------------------------------------------------------//
//                                                       init                                                                      //
//---------------------------------------------------------------------------------------------------------------------------------//
int Serveur::init() {
    Logs::write("-Initialisation socket",LOG_LEVEL_INFO);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == INVALID_SOCKET) {
        Logs::write("Socket error",LOG_LEVEL_ERROR);
        return EXIT_FAILURE;
    }
    Logs::write("Socket Done",LOG_LEVEL_INFO);

    addressInternet.sin_addr.s_addr = inet_addr(IP);
    addressInternet.sin_family = AF_INET;
    addressInternet.sin_port = htons(PORT);
    socklen_t sockAddrInterSize = sizeof(addressInternet);

    if( bind(sock,(SOCKADDR*)&addressInternet,sockAddrInterSize) != 0  ) {
        Logs::write("Bind error",LOG_LEVEL_ERROR);
        return EXIT_FAILURE;
    }
    Logs::write("Bind Done for IP: " + std::string(inet_ntoa(addressInternet.sin_addr)) + " PORT : " + std::to_string(htons(addressInternet.sin_port)),LOG_LEVEL_INFO);

    if(listen(sock, 5) != 0){
        Logs::write("Listen error",LOG_LEVEL_ERROR);
        return EXIT_FAILURE;
    }
    Logs::write("Listen Done",LOG_LEVEL_INFO);

    for(Client & slot: slots) slot.state=STATE_DISCONNECTED;

    mutexRunning.lock();
    running=true;
    mutexRunning.unlock();

    return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------//
//                                                       end                                                                       //
//---------------------------------------------------------------------------------------------------------------------------------//
void Serveur::end() {
    mutexRunning.lock();
    running=false;
    mutexRunning.unlock();

    shutdown(sock, 2);
    for(Client & slot: slots) {
        if(slot.state==STATE_DISCONNECTED) continue;
        slot.processThread.join();
    }
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

    mutexRunning.lock();
    while(running){
        mutexRunning.unlock();
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

        if(slots[freeSlot].processThread.joinable()) {
            Logs::write("Slot " + std::to_string(freeSlot) + " is already processing",LOG_LEVEL_WARNING);
            slots[freeSlot].processThread.join();
            Logs::write("Slot " + std::to_string(freeSlot) + " is done",LOG_LEVEL_VERBOSE);
        }
        slots[freeSlot].processThread=std::thread(Serveur::processLoop,&slots[freeSlot]);
        mutexRunning.lock();
    }
    mutexRunning.unlock();
}

//---------------------------------------------------------------------------------------------------------------------------------//
//                                                 processLoop                                                                     //
//---------------------------------------------------------------------------------------------------------------------------------//
void Serveur::processLoop(Client* slot){
    try{
        Logs::write("Process loop start on slot" + std::to_string(slot->slotNum),LOG_LEVEL_DEBUG);
        // STATE_NEW_CONNECTED:
        slot->state = STATE_RECEIVING_TYPE_DATA;
        Logs::write("Receiving type from client on slot " + std::to_string(slot->slotNum),LOG_LEVEL_VERBOSE);
        if( ! Serveur::getClientDataType(slot) ) return;

        // STATE_RECEIVED_TYPE_DATE:
        slot->state = STATE_SENDING_TYPE_DATA_CONFIRMATION;
        Logs::write("Sending typeConfirm to client on slot " + std::to_string(slot->slotNum),LOG_LEVEL_VERBOSE);
        if( ! Serveur::confirmClientDataType(slot) ) return;

        // STATE_SENT_TYPE_DATA_CONFIRMATION:
        switch (((char*)slot->output)[0]){
            case 1:
                slot->clearOutput<char>();
                Logs::write("Slot " + std::to_string(slot->slotNum) + " choose to send us a picture",LOG_LEVEL_DETAILS);

                //Picture Part ------------------------------------------------------------------------------------------

                slot->state = STATE_RECEIVING_PICTURE_SIZE;
                Logs::write("Slot " + std::to_string(slot->slotNum) + " choose to send us a picture",LOG_LEVEL_VERBOSE);
                if( ! Serveur::getClientPictureSize(slot) ) return;

                Logs::write("Slot " + std::to_string(slot->slotNum) + " picture size : " + std::to_string(((unsigned int*)slot->output)[0]) + " x " + std::to_string(((unsigned int*)slot->output)[1]),LOG_LEVEL_DETAILS);

                if(((unsigned int*)slot->output)[0]*((unsigned int*)slot->output)[1]>MAX_PICTURE_SIZE){
                    Logs::write("Slot " + std::to_string(slot->slotNum) + " picture size is too big",LOG_LEVEL_WARNING);
                    slot->clearOutput<unsigned int>();
                    slot->disconnect();
                    return;
                }

                // STATE_RECEIVED_PICTURE_SIZE:
                slot->state = STATE_SENDING_PICTURE_SIZE_CONFIRMATION;
                Logs::write("Sending pictureSizeConfirm to client on slot " + std::to_string(slot->slotNum),LOG_LEVEL_VERBOSE);
                if( ! Serveur::confirmClientPictureSize(slot) ) return;

                // STATE_SENT_PICTURE_SIZE_CONFIRMATION:
                slot->state = STATE_RECEIVING_PICTURE;
                Logs::write("Receiving picture from client on slot " + std::to_string(slot->slotNum),LOG_LEVEL_VERBOSE);
                if( ! Serveur::getClientPicture(slot) ) return;

                // STATE_RECEIVED_PICTURE:
                slot->state = STATE_SENDING_PICTURE_CONFIRMATION;
                Logs::write("Sending pictureConfirm to client on slot " + std::to_string(slot->slotNum),LOG_LEVEL_VERBOSE);
                if( ! Serveur::confirmClientPicture(slot) ) return;

                // STATE_SENT_TYPE_PICTURE_CONFIRMATION:
                slot->state = STATE_BUILDING_BOARD;
                Logs::write("Building board on slot " + std::to_string(slot->slotNum),LOG_LEVEL_VERBOSE);
                Serveur::buildBoard(slot);

                // STATE_BUILT_BOARD:
                slot->state = STATE_RECEIVING_NB_ROBOTS;
                Logs::write("Receiving nbRobots from client on slot " + std::to_string(slot->slotNum),LOG_LEVEL_VERBOSE);
                if( ! Serveur::getClientNbRobots(slot) ) return;

                Logs::write("Slot " + std::to_string(slot->slotNum) + " nbRobot : " + std::to_string(((Game*)slot->output)->nbRobots),LOG_LEVEL_DEBUG);

                // STATE_RECEIVED_NB_ROBOTS:
                slot->state = STATE_SENDING_NB_ROBOTS_CONFIRMATION;
                Logs::write("Sending nbRobotsConfirm to client on slot " + std::to_string(slot->slotNum),LOG_LEVEL_VERBOSE);
                if( ! Serveur::confirmClientNbRobots(slot) ) return;

                // STATE_SENT_NB_ROBOTS_CONFIRMATION:
                slot->state = STATE_RECEIVING_ROBOTS;
                Logs::write("Receiving robots from client on slot " + std::to_string(slot->slotNum),LOG_LEVEL_VERBOSE);
                if( ! Serveur::getClientRobots(slot) ) return;

                for(int i=0;i<((Game*)slot->output)->nbRobots;++i){
                    Logs::write("Slot " + std::to_string(slot->slotNum) + " robot " + std::to_string(i) + " : " + std::to_string(((Game*)slot->output)->robots[i]),LOG_LEVEL_DEBUG);
                }

                // RECEIVED_ROBOTS:
                slot->state = RECEIVING_TOKEN;
                Logs::write("Receiving token from client on slot " + std::to_string(slot->slotNum),LOG_LEVEL_VERBOSE);
                if( ! Serveur::getClientToken(slot) ) return;
                break;
            case 2:
                slot->clearOutput<char>();
                Logs::write("Slot " + std::to_string(slot->slotNum) + " choose to send us a grid",LOG_LEVEL_DETAILS);

                //Grid Part ------------------------------------------------------------------------------------------

                slot->state = STATE_RECEIVING_GRIP_TYPE;
                Logs::write("Slot " + std::to_string(slot->slotNum) + " choose to send us a grid",LOG_LEVEL_VERBOSE);
                if( ! Serveur::getClientGridType(slot) ) return;

                Logs::write("Slot " + std::to_string(slot->slotNum) + " nbRobot : " + std::to_string(((((char*)slot->output)[0]&2)>>1) + 4) + " mur de travers : " + std::to_string(((char*)slot->output)[0]&1),LOG_LEVEL_DEBUG);

                // STATE_RECEIVED_GRIP_TYPE:
                slot->state = STATE_SENDING_GRIP_TYPE_CONFIRMATION;
                Logs::write("Sending gridTypeConfirm to client on slot " + std::to_string(slot->slotNum),LOG_LEVEL_VERBOSE);
                if( ! Serveur::confirmClientGridType(slot) ) return;

                // STATE_SENT_TYPE_GRIP_TYPE_CONFIRMATION:
                slot->state = STATE_RECEIVING_GRID;
                Logs::write("Receiving grid from client on slot " + std::to_string(slot->slotNum),LOG_LEVEL_VERBOSE);
                if( ! Serveur::getClientGrid(slot) ) return;
                break;

            default:
                Logs::write("Slot " + std::to_string(slot->slotNum) + " send us a wrong choice : " + std::to_string((int)(((char*)slot->output)[0])),LOG_LEVEL_WARNING);
                slot->clearOutput<char>();
                slot->disconnect();
                return;
        }

        // STATE_RECEIVED_GRID OR RECEIVED_TOKEN:
        slot->state = STATE_SENDING_PROCESS_TIME;
        Logs::write("Sending time to client on slot " + std::to_string(slot->slotNum),LOG_LEVEL_VERBOSE);
        if( !Serveur::setProcessTime(slot) ) return;

        // STATE_SENT_TYPE_PROCESS_TIME:
        slot->state = STATE_PREPARING_GRID;
        Logs::write("Preparing grid on slot " + std::to_string(slot->slotNum),LOG_LEVEL_VERBOSE);
        Serveur::prepareGrid(slot);

        // STATE_PREPARED_GRID:
        slot->state = STATE_SOLVING;
        Logs::write("Slot " + std::to_string(slot->slotNum) + " begin to solve",LOG_LEVEL_VERBOSE);
        if( ! Serveur::solving(slot) ) return;

        mutexProcessTime.lock();
        if(totalNbProcess!=0)
            Logs::write("Slot " + std::to_string(slot->slotNum) + " is solved, totalNbProcess : " + std::to_string(totalNbProcess) + " totalProcessTime : " + std::to_string(totalProcessTime.count()) + " time per process : " + std::to_string(totalProcessTime.count()/totalNbProcess),LOG_LEVEL_DETAILS);
        mutexProcessTime.unlock();

        // STATE_SOLVED:
        slot->state = STATE_SENDING_PATH;
        Logs::write("Sending path to client on slot " + std::to_string(slot->slotNum),LOG_LEVEL_VERBOSE);
        if( ! Serveur::sendPath(slot) ) return;

        // STATE_SENT_TYPE_PATH:
        slot->state = STATE_SENDING_GRID;
        Logs::write("Sending grid to client on slot " + std::to_string(slot->slotNum),LOG_LEVEL_VERBOSE);
        if( ! Serveur::sendGrid(slot) ) return;

        // STATE_SENT_GRID:
        Logs::write("Client process on slot " + std::to_string(slot->slotNum) + " is done",LOG_LEVEL_DETAILS);
        shutdown(slot->socket, 2);
        slot->disconnect();
    } catch (const std::exception& e) {
        Logs::write("Error on slot " + std::to_string(slot->slotNum) + " : " + e.what(),LOG_LEVEL_ERROR);
        slot->output= nullptr;
        slot->disconnect();
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
bool Serveur::getClientDataType(Client* slot){
    slot->output=new char[1];
    int result = recv(slot->socket, (char*)slot->output, sizeof(char), 0);
    if(verifySocketOutput<char>(slot,false,result)==EXIT_FAILURE) return false;
    slot->state=STATE_RECEIVED_TYPE_DATE;
    return true;
}
bool Serveur::confirmClientDataType(Client *slot) {
    int result = send(slot->socket, (char*)slot->output, sizeof(char), 0);
    if(verifySocketOutput<char>(slot,true,result)==EXIT_FAILURE) return false;
    slot->state=STATE_SENT_TYPE_DATA_CONFIRMATION;
    return true;
}

//---------------------------------------------------------------------------------------------------------------------------------//
//                                               reception picture                                                                 //
//---------------------------------------------------------------------------------------------------------------------------------//
bool Serveur::getClientPictureSize(Client *slot) {
    slot->output=new unsigned int[2];
    int result = recv(slot->socket, (char*)slot->output, sizeof(unsigned int[2]), 0);
    if(verifySocketOutput<unsigned int>(slot,false,result)==EXIT_FAILURE) return false;
    slot->state=STATE_RECEIVED_PICTURE_SIZE;
    return true;
}
bool Serveur::confirmClientPictureSize(Client *slot) {
    auto* size=static_cast<unsigned int*>(slot->output);
    long confirmSize=static_cast<long>(size[0])*static_cast<long>(size[1])*3;
    int result = send(slot->socket, (char*)&confirmSize, sizeof(long), 0);
    if(verifySocketOutput<unsigned int>(slot,false,result)==EXIT_FAILURE) return false;
    slot->state=STATE_SENT_PICTURE_SIZE_CONFIRMATION;
    return true;
}
bool Serveur::getClientPicture(Client *slot) {
    auto* size=static_cast<unsigned int*>(slot->output);
    slot->output= new char[size[0]*size[1]*3];

    int percent=size[0]/100;
    if(percent==0) percent=1;

    // Picture data reception
    /*for(int i=0;i<size[0];++i){
        for(int j=0;j<size[1];++j){
            char* buff = NULL;
            int result = recv(slot->socket, buff, 3*sizeof(char), 0);
            if(verifySocketOutput<char>(slot,false,result)==EXIT_FAILURE) return false;
            for (int k = 0; k < 3; ++k) {
                memset((char*)slot->output + (i * size[1] * 3 + j * 3 + k), buff[k], 1);
            }
            delete[] buff;
            Logs::write("Data recived" + std::to_string(buff[0]) + " " + std::to_string(buff[1]) + " " + std::to_string(buff[2]), LOG_LEVEL_DEBUG);

            for(int k=0;k<3;++k){
                int result = recv(slot->socket, (char*)slot->output+(i*size[1]*3+j*3+k), sizeof(char), 0);
                if(verifySocketOutput<char>(slot,false,result)==EXIT_FAILURE) return false;
            }
        }
        if(i%percent==0){
            Logs::write("Slot " + std::to_string(slot->slotNum) + " picture received " + std::to_string(i) + "/" + std::to_string(size[0]) + "(" + std::to_string(i*100/size[0]) + "%)",LOG_LEVEL_DEBUG);
        }
    }*/
    //Logs::write("Slot " + std::to_string(slot->slotNum) + " picture received",LOG_LEVEL_DEBUG);

    const int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE] = { 0 };
    auto* picturePath = new std::string();
    *picturePath = PICTURE_PATH;
    *picturePath += "slot" + std::to_string(slot->slotNum) + ".jpg";
    std::ofstream outfile(*picturePath, std::ios::binary);
    if (!outfile) {
        Logs::write("Slot " + std::to_string(slot->slotNum) + " error opening file", LOG_LEVEL_ERROR);
    }
    int bytes_recived;
    while ((bytes_recived = recv(slot->socket, buffer, BUFFER_SIZE, 0)) > 0) {
        outfile.write(buffer, bytes_recived);
        Logs::write("Slot " + std::to_string(slot->slotNum) + " buffer : " + std::to_string(bytes_recived), LOG_LEVEL_DEBUG);
    }
    if (bytes_recived == 0) {
        Logs::write("Slot " + std::to_string(slot->slotNum) + " file recived successfully", LOG_LEVEL_DEBUG);
    }
    else if (bytes_recived == -1) {
        Logs::write("Slot " + std::to_string(slot->slotNum) + " error during reception", LOG_LEVEL_ERROR);
    }

    /*auto* picturePath = new std::string();
    *picturePath=PICTURE_PATH;
    *picturePath+="slot"+std::to_string(slot->slotNum)+".png";
    JPEGBuilder::build((char*)slot->output,(int)(size[0]),(int)(size[1]),*picturePath);
    Logs::write("Slot " + std::to_string(slot->slotNum) + " picture saved at " + *picturePath,LOG_LEVEL_DEBUG);*/

    delete[] size;
    delete[] static_cast<char*>(slot->output);
    slot->output=picturePath;

    auto* picturePathIsolated = new std::string();
    *picturePathIsolated=PICTURE_PATH;
    *picturePathIsolated+="slot"+std::to_string(slot->slotNum)+"_isolated.png";
    if(BoardIsolation::getBoard(*picturePath,*picturePathIsolated)==-1){
        Logs::write("Slot " + std::to_string(slot->slotNum) + " board not isolated",LOG_LEVEL_WARNING);
        slot->clearOutput<std::string>();
        slot->output= nullptr;
        slot->disconnect();
        return false;
    }

    slot->state=STATE_RECEIVED_PICTURE;
    return true;
}
bool Serveur::confirmClientPicture(Client *slot) {
    char confirm=1;
    int result = send(slot->socket, (char*)&confirm, sizeof(char), 0);
    if(verifySocketOutput<std::string>(slot,true,result)==EXIT_FAILURE) return false;
    slot->state=STATE_SENT_TYPE_PICTURE_CONFIRMATION;
    return true;
}
bool Serveur::buildBoard(Client *slot) {
    auto* picturePath = static_cast<std::string*>(slot->output);
    Board board=BoardBuilder::constructBoard(*picturePath,BOARD_PATH);
    Game* game=new Game(4,false,false);
    for(int i=0;i<256;++i){
        game->grid[i]=board.cases[i];
    }
    delete picturePath;
    slot->output=game;
    slot->state=STATE_BUILT_BOARD;
    return true;
}
bool Serveur::getClientNbRobots(Client *slot) {
    int nbRobots=0;
    int result = recv(slot->socket, (char*)&nbRobots, sizeof(int), 0);
    if(verifySocketOutput<Game>(slot,false,result)==EXIT_FAILURE) return false;
    slot->state=STATE_RECEIVED_NB_ROBOTS;
    if(nbRobots<1) {
        Logs::write("Slot " + std::to_string(slot->slotNum) + " nbRobots is too small",LOG_LEVEL_WARNING);
        slot->clearOutput<Game>();
        slot->disconnect();
        return false;
    }
    ((Game*)slot->output)->setNbRobots((int)nbRobots);
    return true;
}
bool Serveur::confirmClientNbRobots(Client *slot) {
    int nbRobots=((Game*)slot->output)->nbRobots;
    int result = send(slot->socket, (char*)&nbRobots, sizeof(int), 0);
    if(verifySocketOutput<Game>(slot,true,result)==EXIT_FAILURE) return false;
    slot->state=STATE_SENT_NB_ROBOTS_CONFIRMATION;
    return true;
}
bool Serveur::getClientRobots(Client *slot) {
    int result = recv(slot->socket, (char*)((Game*)slot->output)->robots, sizeof(unsigned int)*((Game*)slot->output)->nbRobots, 0);
    if(verifySocketOutput<Game>(slot,false,result)==EXIT_FAILURE) return false;
    slot->state=RECEIVED_ROBOTS;
    return true;
}
bool Serveur::getClientToken(Client *slot) {
    int result = recv(slot->socket, (char*)&((Game*)slot->output)->token, sizeof(unsigned int ), 0);
    if(verifySocketOutput<Game>(slot,false,result)==EXIT_FAILURE) return false;
    slot->state=RECEIVED_TOKEN;
    return true;
}
//---------------------------------------------------------------------------------------------------------------------------------//
//                                               reception grid                                                                    //
//---------------------------------------------------------------------------------------------------------------------------------//
bool Serveur::getClientGridType(Client *slot) {
    slot->output=new char[1];
    int result = recv(slot->socket, (char*)slot->output, sizeof(char), 0);
    if(verifySocketOutput<char>(slot,false,result)==EXIT_FAILURE) return false;
    slot->state=STATE_RECEIVED_GRIP_TYPE;
    return true;
}
bool Serveur::confirmClientGridType(Client *slot) {
    int result = send(slot->socket, (char*)slot->output, sizeof(char), 0);
    if(verifySocketOutput<char>(slot,true,result)==EXIT_FAILURE) return false;
    slot->state=STATE_SENT_TYPE_GRIP_TYPE_CONFIRMATION;
    return true;
}
bool Serveur::getClientGrid(Client *slot) {
    char* type=static_cast<char*>(slot->output);
    slot->output=new Game(((type[0]&2)>>1) + 4,type[0]&1,(type[0]&4)>>2);

    int result = recv(slot->socket, (char*)((Game*)slot->output)->grid, sizeof(unsigned int[256]), 0);
    if(verifySocketOutput<Game>(slot,false,result)==EXIT_FAILURE) return false;

    result = recv(slot->socket, (char*)((Game*)slot->output)->robots, sizeof(unsigned int)*((Game*)slot->output)->nbRobots, 0);
    if(verifySocketOutput<Game>(slot,false,result)==EXIT_FAILURE) return false;

    result = recv(slot->socket, (char*)&((Game*)slot->output)->token, sizeof(unsigned int ), 0);
    if(verifySocketOutput<Game>(slot,false,result)==EXIT_FAILURE) return false;

    ((Game*)slot->output)->last=0;

    delete type;
    slot->state=STATE_RECEIVED_GRID;
    return true;
}

bool Serveur::setProcessTime(Client *slot) {
    mutexProcessTime.lock();
    int lastTime;
    if(totalNbProcess==0) lastTime=35;
    else lastTime=static_cast<int>(totalProcessTime.count())/totalNbProcess;
    mutexProcessTime.unlock();
    int result = send(slot->socket, (char*)&lastTime, sizeof(lastTime), 0);
    if(verifySocketOutput<Game>(slot,true,result)==EXIT_FAILURE) return false;
    slot->state=STATE_SENT_TYPE_PROCESS_TIME;
    return true;
}

//---------------------------------------------------------------------------------------------------------------------------------//
//                                               process                                                                           //
//---------------------------------------------------------------------------------------------------------------------------------//
bool Serveur::prepareGrid(Client *slot) {
    ((Game*)slot->output)->prepareGrid();
    slot->state=STATE_PREPARED_GRID;
    return true;
}
bool Serveur::solving(Client *slot) {
    unsigned char* path;
    try{
        path = new unsigned char[32]{0};
    } catch (std::bad_alloc& ba) {
        Logs::write("Bad alloc on slot " + std::to_string(slot->slotNum),LOG_LEVEL_ERROR);
        char flag=2;
        int result = send(slots[0].socket, (char*)&flag, sizeof(char), 0);
        if(verifySocketOutput<Game>(slot,true,result)==EXIT_FAILURE) return false;
        slot->clearOutput<Game>();
        slot->disconnect();
        return false;
    }
    int result;
    try {
        result = Solver::search((Game *) slot->output, path, callbackSolver, &totalProcessTime, &totalNbProcess, &mutexProcessTime);
    } catch (const std::exception& e) {
        Logs::write("Client disconnected on slot " + std::to_string(slot->slotNum),LOG_LEVEL_WARNING);
        slot->clearOutput<Game>();
        slot->disconnect();
        return false;
    }
    if (result==-1) return false;//Client disconnected
    if(result==0){
        Logs::write("No solution found on slot " + std::to_string(slot->slotNum),LOG_LEVEL_WARNING);
        char flag=2;
        result = send(slots[0].socket, (char*)&flag, sizeof(char), 0);
        if(verifySocketOutput<Game>(slot,true,result)==EXIT_FAILURE) return false;
        slot->clearOutput<Game>();
        slot->disconnect();
        return false;
    }
    Logs::write("Solution found on slot " + std::to_string(slot->slotNum),LOG_LEVEL_INFO);
    char flag=3;
    result = send(slots[0].socket, (char*)&flag, sizeof(char), 0);
    if(verifySocketOutput<Game>(slot,true,result)==EXIT_FAILURE) return false;

    ((Game*)slot->output)->path=path;
    slot->state=STATE_SOLVED;
    return true;
}
bool Serveur::callbackSolver(unsigned int max_depth, std::chrono::seconds duration) {
    //if(duration.count()<5) return true;

    char flag=1;
    int result = send(slots[0].socket, (char*)&flag, sizeof(char), 0);
    if(verifySocketOutput<Game>(&slots[0],true,result)==EXIT_FAILURE) return false;
    Logs::write("slot " + std::to_string(slots[0].slotNum) + " flag 1",LOG_LEVEL_DEBUG);

    int message[2]={static_cast<int>(max_depth),static_cast<int>(duration.count())};
    result = send(slots[0].socket, (char*)message, sizeof(int[2]), 0);
    if(verifySocketOutput<Game>(&slots[0],true,result)==EXIT_FAILURE) return false;
    Logs::write("Not solution in depth " + std::to_string(max_depth) + " in " + std::to_string(duration.count()) + "s on slot " + std::to_string(slots[0].slotNum),LOG_LEVEL_DETAILS);

    return true;
}
bool Serveur::sendPath(Client *slot) {
    int result = send(slot->socket,(char*)((Game*)slot->output)->path, sizeof(unsigned char) * 32, 0);
    if(verifySocketOutput<Game>(slot,true,result)==EXIT_FAILURE) return false;

    char confirm;
    result = recv(slot->socket, (char*)&confirm, sizeof(char),MSG_WAITALL);
    if(verifySocketOutput<Game>(slot,false,result)==EXIT_FAILURE) return false;

    slot->state=STATE_SENT_TYPE_PATH;
    return true;
}
bool Serveur::sendGrid(Client *slot) {
    Logs::write("Sending grid to client on slot " + std::to_string(slot->slotNum),LOG_LEVEL_VERBOSE);
    int result = send(slot->socket,(char*)((Game*)slot->output)->grid, sizeof(unsigned int) * 256, 0);
    if(verifySocketOutput<Game>(slot,true,result)==EXIT_FAILURE) return false;

    for(int i=0;i<16;++i)
        Logs::write(std::to_string(((Game*)slot->output)->grid[0+i*16]+((Game*)slot->output)->grid[1+i*16]+((Game*)slot->output)->grid[2+i*16]+((Game*)slot->output)->grid[3+i*16]+((Game*)slot->output)->grid[4+i*16]+((Game*)slot->output)->grid[5+i*16]+((Game*)slot->output)->grid[6+i*16]+((Game*)slot->output)->grid[7+i*16]+((Game*)slot->output)->grid[8+i*16]+((Game*)slot->output)->grid[9+i*16]+((Game*)slot->output)->grid[10+i*16]+((Game*)slot->output)->grid[11+i*16]+((Game*)slot->output)->grid[12+i*16]+((Game*)slot->output)->grid[13+i*16]+((Game*)slot->output)->grid[14+i*16]+((Game*)slot->output)->grid[15+i*16]),LOG_LEVEL_DEBUG);

    char confirm;
    result = recv(slot->socket, (char*)&confirm, sizeof(char),MSG_WAITALL);
    if(verifySocketOutput<Game>(slot,false,result)==EXIT_FAILURE) return false;

    slot->clearOutput<Game>();
    slot->state=STATE_SENT_GRID;
    return true;
}