
#undef UNICODE

#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#define  _WINSOCK_DEPRECATED_NO_WARNINGS

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>





// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")


/*
* #define MAXPENDING 5
#define RCVBUFSIZE 1024
typedef struct playerinfo {
    SOCKET client;
    int id;
}PlayerInfo;

typedef struct sessioninfo {
    int id;
    char name;
    str serverip;
    int serverport;
}SessionInfo;


list<PlayerInfo> players;
list<SessionInfo> sessions;
int playercount = 0;

int sessioncount = 0;
*/


// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#define ZW_PORT "8888"
#define WELCOME_MESAAGE "Welcome to ZW MATHMAKING\n"
#define EXE_MESAAGE "ZW MATHMAKING OPEN "

#define PlayersPerLobby 2

#define ServerWaiting 1
#define ServerReady 2
#define ServerOn 3

#define ServerGo "GameServerReady"
#define servertowait "GameServerWaiting"
#define waitingforplayerMessage "WAITING FOR PLAYERS"

#define ReceiveIpGameServer "IPGameServerInfo"
#define serverJoindedMessage "playerjoined"

struct ClientInfo {
    int clientID;
    SOCKET socket;
    char name[DEFAULT_BUFLEN];
    char pass[DEFAULT_BUFLEN];
    char config[DEFAULT_BUFLEN];
    char message[DEFAULT_BUFLEN];
    int state;// 0 is off, 1 is on, 2 is looking for game, 3 in game
    int recevingInfo; // 0 is off, 1 is on
    char* clientIp;
}Clients[DEFAULT_BUFLEN], tempClient;


struct ServerInfo {
    int serverID;
    SOCKET socket;
    char ip[DEFAULT_BUFLEN];
    char port[DEFAULT_BUFLEN];
   // char config[DEFAULT_BUFLEN];
    int idOfPlayers[PlayersPerLobby];
    int playersOn;
    int state; //1 is waiting players, 2 is ready, 3 open to connect
}Servers[DEFAULT_BUFLEN];

struct SessionInfo {
    int id;
    char name[DEFAULT_BUFLEN];
    char serverIP[DEFAULT_BUFLEN];
    int serverPort;
};



struct C1_C2 {
    int Client1;
    int Client2;
}CIndexs;

int DoneCommand =0;
int ClientConnected = 0;
int ServersConnected = 0;
int UsersOn = 0;
int ServersOn = 0;
int ServerState = 1;

int isAcceptingClients = 1;



char tempIp[DEFAULT_BUFLEN];
int Sender = 0;
int Receiver = 0;


SOCKET ListenSocket = INVALID_SOCKET;
//struct Client_Info Clients[10];

#pragma region ServerCommands
void PrintClientes() {

    int y = 0;

    printf("number of clients %d \n", ClientConnected);

    for (y; y < ClientConnected; y++) {

        printf("////////Client %d //////////// \n", y);
        printf(" Name: %s \n  ", Clients[y].name);
        //printf(" Pass: %s \n", Clients[y].pass);
        printf(" ID: %d \n ", Clients[y].clientID);

        int h = 0;
        if (Clients[y].socket == INVALID_SOCKET) {
            h = -1;
        }
        else if (Clients[y].socket == NULL) {
            h = -2;
        }
        else {
            h = 1;
        }

        switch (h)
        {
        case 1:
            printf(" Socket: valid\n");
            break;
        case -1:
            printf(" Socket: invalid\n");
            break;
        case -2:
            printf(" Socket: null\n");
            break;
        default:
            break;
        }


        printf("gameConfig: %s \n Player is: ", Clients[y].config);
        switch (Clients[y].state)
        {
        case 1:
            printf("Online\n");
            break;
        case 2:
            printf("Looking for game\n");
            break;
        case 3:
            printf("In Game\n");
            break;
        default:
            break;
        }

    }

}


void PrintServers() {

    int y = 0;

    printf("number of servers online %d \n", ServersConnected);

    for (y; y < ServersConnected; y++) {

        printf("////////server %d //////////// \n", y);
        printf("IP : %s:%s\n", Servers[y].ip,Servers[y].port);
        printf("ID : %d\n", Servers[y].serverID);
        switch (Servers[y].state)
        {
        case 0: 
            printf("no players reserved here");
                break;
        case 1:
            printf(waitingforplayerMessage);
            break;
        case 2:
            printf(ServerGo);
        default:
            break;
        }

        printf("Clients in this server\n");
        for (int j = 0; j < Servers[y].playersOn; j++) {

            printf("cLIENT with id %d in server", Servers[y].idOfPlayers[j]);

        }



    }




}

void CommandLines(void* arguments) {

    char comand[DEFAULT_BUFLEN] = ".x";
    while (ServerState)
    {   
        if (DoneCommand == 0) {
            DoneCommand = 1;
            printf("Input MM Server Command\n");
            gets(comand);
        }
      
        if (strcmp(comand, "PC") == 0) {
            PrintClientes();
            DoneCommand = 0;
        }
        if (strcmp(comand, "PS") == 0) {
            PrintServers();
            DoneCommand = 0;
        }
        if (strcmp(comand, "OFF") == 0) {
            printf("CloseServer");
            ServerState = 0;
        }

    }
}
#pragma endregion 







void InformClientOfServerofState(void* in) {
    int ID = (int*)in;
    char msgSender[DEFAULT_BUFLEN];
    int snd = 0;
    printf("sending info of server to clients connected: '%s' \n", Servers[ID].ip);
  


    if (Servers[ID].state == ServerWaiting) {

        for (int j = 0; j < Servers[ID].playersOn; j++) {

            printf("cLIENT with id %d in server", Servers[ID].idOfPlayers[j]);

        }
        printf("Server is Waiting for more players\n");
        //_itoa(Clients[indexSender].Sent, msgSender, 10);
        //sprintf_s((char*)&msgSender, DEFAULT_BUFLEN, "Game Server number %d is waiting to go", Servers[ID].serverID);
            //Clients[index].message);
       // sprintf_s((char*)&msgSender, DEFAULT_BUFLEN, "Game Server number %s is waiting to go", Servers[ID].serverID);
        sprintf_s((char*)&msgSender, DEFAULT_BUFLEN, servertowait);
        snd = send(Servers[ID].socket, msgSender, sizeof(msgSender), 0);
        if (snd > 0) {

            for (int j = 0; j < Servers[ID].playersOn; j++) {
                int tempCid = Servers[ID].idOfPlayers[j];
                if (Clients[tempCid].socket != INVALID_SOCKET) {

                    printf(" try notifiy client '%s'\n", Clients[tempCid].name);

                    snd = send(Clients[tempCid].socket, msgSender, sizeof(msgSender), 0);
                    if (snd > 0) {
                        //CLIENT NOTIFIED OF SERVER STATE
                        // printf(" client %s notified\n", Clients[Servers[ID].idOfPlayers[j]].name);



                        Clients[tempCid].recevingInfo = 0;
                        if (Servers[ID].state == ServerReady) {

                            Clients[tempCid].state = 3;
                            printf("Client  '%s' is in game\n", Clients[tempCid].name);
                        }
                    }
                }
            }


        }
    }
    else if (Servers[ID].state == ServerReady) {
        printf("Server is ready for game\n");
        sprintf_s((char*)&msgSender, DEFAULT_BUFLEN, ServerGo);
        snd = send(Servers[ID].socket, msgSender, sizeof(msgSender), 0);
        if (snd > 0) {

            for (int j = 0; j < Servers[ID].playersOn; j++) {

                if (Clients[Servers[ID].idOfPlayers[j]].socket != INVALID_SOCKET) {

                    printf(" try notifiy client %s\n", Clients[Servers[ID].idOfPlayers[j]].name);

                    snd = send(Clients[Servers[ID].idOfPlayers[j]].socket, msgSender, sizeof(msgSender), 0);
                    if (snd > 0) {
                        //CLIENT NOTIFIED OF SERVER STATE
                        // printf(" client %s notified\n", Clients[Servers[ID].idOfPlayers[j]].name);



                        Clients[Servers[ID].idOfPlayers[j]].recevingInfo = 0;
                        if (Servers[ID].state == ServerReady) {

                            Clients[Servers[ID].idOfPlayers[j]].state = 3;
                            printf("%s is in game\n", Clients[Servers[ID].idOfPlayers[j]].name);
                        }
                    }
                }
            }


        }
    }
}
    // Server update 
    /* snd = send(Servers[ID].socket, msgSender, sizeof(msgSender), 0);
    if (snd > 0) {

        for (int j = 0; j < Servers[ID].playersOn; j++) {

            if (Clients[Servers[ID].idOfPlayers[j]].socket != INVALID_SOCKET) {

                printf(" client %s notified\n", Clients[Servers[ID].idOfPlayers[j]].name);

                snd = send(Clients[Servers[ID].idOfPlayers[j]].socket, msgSender, sizeof(msgSender), 0);
                if (snd > 0) {
                    //CLIENT NOTIFIED OF SERVER STATE
                    // printf(" client %s notified\n", Clients[Servers[ID].idOfPlayers[j]].name);
                    


                    Clients[Servers[ID].idOfPlayers[j]].recevingInfo = 0;
                    if (Servers[ID].state == ServerReady) {

                        Clients[Servers[ID].idOfPlayers[j]].state = 3;
                        printf("%s is in game\n", Clients[Servers[ID].idOfPlayers[j]].name);
                    }
                }
            }
        }


    }
    */
   







void HandleServerSocket(void* socket) {

    SOCKET ServerSocket = (SOCKET)socket;
    int iRes = 0;
    char msgbuf[DEFAULT_BUFLEN];
    int sid = ServersConnected;
    ServersConnected++;

    Servers[sid].serverID = sid;
    Servers[sid].socket = ServerSocket;
    Servers[sid].state = 0;
    Servers[sid].playersOn = 0;
    memcpy(Servers[sid].ip, tempIp,sizeof(tempIp));




    printf("Waiting game Server Port :");

    iRes = recv(ServerSocket, msgbuf, sizeof(msgbuf), 0);
    if (iRes > 0)
    {

        int  s = sizeof(msgbuf) / sizeof(char);
        char init[DEFAULT_BUFLEN];
        strcpy(init, msgbuf, s);
        //printf("init is %s \n", init);
        int count = 0;
        for (int j = 0; j < 100; j++) {
            if (init[j] == '.') {
                j = 10000;
            }
            else {
                count++;
            }
        }
        msgbuf[count] = '\0';

        //printf(" %s .ok \n", msgbuf);
        memcpy(Servers[sid].port, msgbuf, sizeof(msgbuf));
        printf("Server Registered with %s:%s\n", Servers[sid].ip,Servers[sid].port);
        isAcceptingClients = 0;
    }
   
    _endthread();

}



#pragma region ClientHandle
void HandleClientSocketConnect(void* socket) {

    //client connected
    SOCKET ClientSocket = (SOCKET)socket;
    int iRes = 0;
    char msgbuf[DEFAULT_BUFLEN];
    char passbuf[DEFAULT_BUFLEN];
    int id = ClientConnected;
 
    iRes = recv(ClientSocket, msgbuf, sizeof(msgbuf), 0);
    if (iRes > 0) {
        //printf("Name of client: %s\n", recvbuf);
       // int  s = sizeof(recvbuf) / sizeof(char);
        //printf("init is %s \n", init);
        int count = 0;
        int j = 0;
        for (j; j < 100; j++) {
            if (msgbuf[j] == '.') {
                j = 100;
            }
            else {
                count++;
            }
        }
        msgbuf[count] = '\0';
        // received name from client

        
        //printf("Name of client: %s\n waiting password", msgbuf);

        iRes = recv(ClientSocket, passbuf, sizeof(passbuf), 0);
        if (iRes > 0) {
            //printf("Pass of client: %s\n", passbuf);
            int countP = 0;
            int Pj = 0;
            for (Pj; Pj < 100; j++) {
                if (passbuf[Pj] == '.') {
                    Pj = 100;
                }
                else {
                    countP++;
                }
            }
            isAcceptingClients = 0;
            passbuf[countP] = '\0';
           // printf("Pass size of  client: %d\n", sizeof(passbuf));
            memcpy(Clients[id].pass, passbuf, sizeof(passbuf));
            printf("Pass of client: %s\n", Clients[id].pass);
            memcpy(Clients[id].name, msgbuf, sizeof(msgbuf));
            Clients[id].state = 1;
            Clients[id].recevingInfo = 0;
            Clients[id].clientID = id;
            Clients[id].socket = ClientSocket;
            UsersOn++;
            ClientConnected++; 
          
            printf("Clietn Set!");
         
            
        }
        else
        {
            printf("Pass ofClient not HERE");
            isAcceptingClients = 0;
        }

    }
    else {
        isAcceptingClients = 0;
    }


    /*
    iRes = send(Clients[id].socket, WELCOME_MESAAGE, sizeof(WELCOME_MESAAGE), 0);
    if (iRes > 0) {
        // set client state to online

    }
    */


}
/*
*   iRes = recv(Clients[id].socket, msgbuf, sizeof(msgbuf),0);

if(iRes>0)
{
    // received name from client
    printf("Name of client: %s\n", msgbuf);
    memcpy(Clients[id].name, msgbuf,sizeof(msgbuf));

    //receive client Configurations
    iRes = recv(Clients[id].socket, msgbuf, sizeof(msgbuf), 0);
    if (iRes > 0)
    {
        // received client config
        printf("Configs of client: %s\n", msgbuf);
        memcpy(Clients[id].config, msgbuf, sizeof(msgbuf));

        iRes = send(Clients[id].socket, WELCOME_MESAAGE, sizeof(WELCOME_MESAAGE), 0);
        if (iRes > 0) {
            ClientConnected++;
            // set client state to online
            Clients[id].state = 1;
            Clients[id].recevingInfo = 0;
            //_beginthread(ReceiveClientMessage, 0, (void*)id);
            UsersOn++;
        }


    }
}
*/
// receive name from client






#pragma endregion

#pragma region DiogoCodeCHECKOUTLATER
/*
*
*
* codigo DIogo
struct MsgBase
{
    int type :
    int length :
};

struct MsgLogin
{
    int type:
    int length:
    char name[256];
    char pass[256];
};

MsgLogin lmsessage:
send(so, &lmessage, sizeof(MsgLogin));
MsgBase base;
recv(so, &base, sizeof(base));
if (base.type == 1)
{
    MsgLogin login;
    memcpy(&login, &base, sizeof(MsgBase));
    recv(so, ((char*)&login) + sizeof(MsgBase), sizeof(masgLogin) - sizeof(MsgBase));
}*/

#pragma endregion



#pragma region AcceptSockets
//ACCEPT CLIENT THREAD 
void AcceptSockets(void* socketToListen) {

    SOCKADDR_IN clientIn = { 0 };
    SOCKET TempSocket;
    SOCKET listenSocket = (SOCKET)socketToListen;
    int iResult = 0;
    char recvbuf[DEFAULT_BUFLEN];
    int addrsize = sizeof(clientIn);



    printf("AcceptingSockets : \n");
    // Accept a client socket
    TempSocket = accept(listenSocket, (struct sockaddr*)&clientIn, &addrsize);
    if (TempSocket == INVALID_SOCKET) {
        printf("s45: accept failed with error: %d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    else {
        
        char* ip = inet_ntoa(clientIn.sin_addr);
        strcpy(tempIp, ip);
        

        printf(" Connected! from IP: %s\n", tempIp);


        //Clients[ClientConnected].socket = TempSocket;

        iResult = recv(TempSocket, recvbuf, sizeof(recvbuf), 0);
        if (iResult > 0) {
         
            int  s = sizeof(recvbuf) / sizeof(char);
            char init[DEFAULT_BUFLEN];
            strcpy(init, recvbuf, s);
            //printf("init is %s \n", init);
            int count = 0;
            for (int j = 0; j < 100; j++) {
                if (init[j] == '.') {
                    j = 10000;
                }
                else {
                    count++;
                }
            }
            recvbuf[count] = '\0';
            printf("%s  is  ", recvbuf);

            if (strcmp(recvbuf, "/client") == 0) {
                printf("Client\n");
                //handle Client thread

                int iRes = 0;
                char msgbuf[DEFAULT_BUFLEN];
                char passbuf[DEFAULT_BUFLEN];
                int id = ClientConnected;

                iRes = recv(TempSocket, msgbuf, sizeof(msgbuf), 0);
                if (iRes > 0) {
                    //printf("Name of client: %s\n", recvbuf);
                   // int  s = sizeof(recvbuf) / sizeof(char);
                    //printf("init is %s \n", init);
                  
                    // received name from client

                   // printf("Name of client: %s\n waiting password", msgbuf);


                    iRes = recv(TempSocket, passbuf, sizeof(passbuf), 0);
                    if (iRes > 0) {
                        //printf("Pass of client: %s\n", passbuf);
                        int countP = 0;
                        int Pj = 0;
                        for (Pj; Pj < 100; Pj++) {
                            if (passbuf[Pj] == '.') {
                                Pj = 100;
                            }
                            else {
                                countP++;
                            }
                        }

                        int count = 0;
                        int j = 0;
                        for (j; j < 100; j++) {
                            if (msgbuf[j] == '.') {
                                j = 100;
                            }
                            else {
                                count++;
                            }
                        }
                        msgbuf[count] = '\0';

                        passbuf[countP] = '\0';
                        memcpy(Clients[id].name, msgbuf, sizeof(msgbuf));
                      
                        memcpy(Clients[id].pass, passbuf, sizeof(passbuf));
                          printf("name of  client: %s\n", Clients[id].name);
                        printf("Pass of client: %s\n", Clients[id].pass);
                      
                        Clients[id].state = 1;
                        Clients[id].recevingInfo = 0;
                        Clients[id].clientID = id;
                        Clients[id].socket = TempSocket;
                        UsersOn++;
                        ClientConnected++;

                        printf("Client Set!");
                        isAcceptingClients = 0;

                        //_endthread();

                    }
                    else
                    {
                        printf("Pass ofClient not HERE");
                        isAcceptingClients = 0;
                    }

                }
                else {
                    isAcceptingClients = 0;
                }
            
            }




            if (strcmp(recvbuf, "/gameserver") == 0) {
                printf("Server\n");
                //handle server thread
               
                _beginthread(HandleServerSocket, 0, (void*)TempSocket);
            }


        }
        else
        {
            isAcceptingClients = 0;
        }
        // _endthread();


    }
}

#pragma endregion






int IsCommand(char in[]) {

    int commando = 0;
    char check1 = in[0];
    if (check1 == '/') {
        commando = 1;
    }
    return commando;
}


int GetCommandToDo(char msg[]) {

    int commando = 0;

    if (strcmp("/ClientmessageSent", msg) == 0) {
        printf("hello Client\n");
    }


    if (strcmp("/setName", msg) == 0) {
        commando = 22;
    }

    if (strcmp("/SaveConfig", msg) == 0) {
        commando = 33;
    }


    if (strcmp("/join", msg) == 0) {
        commando = 1;
    }

    if (strcmp("/cancel", msg) == 0) {
        commando = 2;
    }

    if (strcmp("/exit", msg) == 0) {
        commando = -1;
    }
    return commando;
}

int AvailableServer() {
    int servedID = -1;
    int i = 0;


    for (i; i < ServersConnected; i++) {

        if ((Servers[i].state == ServerWaiting) && (Servers[i].playersOn < PlayersPerLobby)) {
            printf("Server to join found with %d players on \n", Servers[i].playersOn);
            servedID = Servers[i].serverID;
            i = 513;
            return servedID;
        }
        else {

            if (Servers[i].state == 0) {
                printf("Server to join found with 0 players at %s\n", Servers[i].ip);
                servedID = Servers[i].serverID;
                Servers[i].state = ServerWaiting;
                i = 513;
                return servedID;
            }
        }
    }
    /*if (serverID == -1) {

        int sid = ServersConnected;
        ServersConnected++;

        Servers[sid].serverID = sid;
        Servers[sid].socket = ServerSocket;
        Servers[sid].state = 0;
        Servers[sid].playersOn = 0;

    }
    */







    return servedID;
}



#pragma region Handle Client Commands
void HandleClientMessageTh(void* in) {
    int index = (int*)in;

    tempClient = Clients[index];
    char msgReceiver[DEFAULT_BUFLEN];
    int snd = 0;
    int commandToDo = GetCommandToDo(Clients[index].message);
    int serverID;

    switch (commandToDo)
    {
        //player sent /join 
#pragma region /join
    case 1: //layer tries //join// get avilable server
        serverID = AvailableServer();
        Clients[index].state = 2;

        printf("%s joinded server at %s\n", Clients[index].name, Servers[serverID].ip);
        Servers[serverID].idOfPlayers[Servers[serverID].playersOn++] = Clients[index].clientID;
        printf("id of player joinded %d\n", Servers[serverID].idOfPlayers[Servers[serverID].playersOn]);
        

        snd = send(Clients[index].socket, "IP", sizeof("IP"), 0);
        if (snd > 0) {
            //inform server ip to join client connected to set server
            char str[DEFAULT_BUFLEN];
            printf("player knows command of receive IP");
            sprintf_s((char*)&str, DEFAULT_BUFLEN, "%s:%s", Servers[serverID].ip, Servers[serverID].port);
            //send 
               
            printf(" ip to send to client %s\n", str);

            snd = send(Clients[index].socket, str, sizeof(str), 0);
            if (snd > 0) {
                // send to sever info that someone joinned
                snd = send(Servers[serverID].socket, serverJoindedMessage, sizeof(serverJoindedMessage), 0);
                if (snd > 0) {
                    // send info of client to GameServer
                    snd = send(Servers[serverID].socket, Clients[index].config, sizeof(Clients[index].config), 0);
                    if (snd > 0) {
                        //Servers[serverID].playersOn++;
                        if (Servers[serverID].playersOn == PlayersPerLobby) {
                            // game can start
                            Servers[serverID].state = ServerReady;
                            _beginthread(InformClientOfServerofState, 0, serverID);
                        }
                        else {
                            //server needs more player

                            _beginthread(InformClientOfServerofState, 0, serverID);

                        }
                    }


                }




            }
        }

        break;
        // send player info of game server
#pragma endregion



    case -1:

        //disconnectplayer

        break;

    case 22:
        snd = send(Clients[index].socket, "SendName", sizeof("SendName"), 0);
        if (snd > 0) {
            // Sleep(100);
             //if something is received
            snd = recv(Clients[index].socket, msgReceiver, sizeof(msgReceiver), 0);
            if (snd > 0) {
                int  s = sizeof(msgReceiver) / sizeof(char);
                char init[DEFAULT_BUFLEN];
                strcpy(init, msgReceiver, s);
                //printf("init is %s \n", init);
                int count = 0;
                for (int j = 0; j < 100; j++) {
                    if (init[j] == '.') {
                        j = 10000;
                    }
                    else {
                        count++;
                    }
                }

                msgReceiver[count] = '\0';
                // received name from client
                printf("Name of client: %s\n", msgReceiver);
                memcpy(Clients[index].name, msgReceiver, sizeof(msgReceiver));
                Clients[index].recevingInfo = 0;
                // Clients[index].
            }

        }
        break;

        // parsing player configuration
        // Code in Unreal
        //result = "W" + Int(WarriorID) + ";A" +Int(Ability1ID) + ";B" + Int(Ability2ID) + ";C" + Int(Ability2ID) + ";";
    case 33:

        snd = recv(Clients[index].socket, msgReceiver, sizeof(msgReceiver), 0);
        if (snd > 0) {
            int  s = sizeof(msgReceiver) / sizeof(char);
            char init[DEFAULT_BUFLEN];
            strcpy(init, msgReceiver, s);
            //printf("init is %s \n", init);
            int count = 0;
            for (int j = 0; j < 100; j++) {
                if (init[j] == '.') {
                    j = 10000;
                }
                else {
                    count++;
                }
            }

            msgReceiver[count] = '\0';
            // received name from client
            printf("Config of client: %s\n", msgReceiver);
            memcpy(Clients[index].config, msgReceiver, sizeof(msgReceiver));




            Clients[index].recevingInfo = 0;
            // Clients[index].
        }


        break;

    default:
        Clients[index].recevingInfo = 0;
        break;
    }

    _endthread();
}
#pragma endregion




#pragma region ReceiveMessageThread

void ReceiveClientMessage(void* Info) {

    int index = (int*)Info;


    tempClient = Clients[index];
    char msgReceiver[DEFAULT_BUFLEN];
    char msg[DEFAULT_BUFLEN];

    int res = 0;
    //printf("Waiting for messages from  %s \n", tempClient.name);
    //printf("waiting for %s to send message\n", Clients[index].name);
    if (Clients[index].socket != INVALID_SOCKET) {

        // Message Recieved from Client
        res = recv(Clients[index].socket, msgReceiver, sizeof(msgReceiver), 0);
        if (res > 0)
        {
            //printf("client number %d sent %s \n", Clients[index].clientID, msgReceiver);
           // printf("client number %d sent %s \n", Clients[index].clientID, msgReceiver);
            /**/

            int  s = sizeof(msgReceiver) / sizeof(char);
            char init[DEFAULT_BUFLEN];
            strcpy(init, msgReceiver, s);
            //printf("init is %s \n", init);
            int count = 0;
            for (int j = 0; j < 100; j++) {
                if (init[j] == '.') {
                    j = 10000;
                }
                else {
                    count++;
                }
            }

            msgReceiver[count] = '\0';

            printf("client number %d sent %s \n", Clients[index].clientID, msgReceiver);

            strcpy(msg, msgReceiver);


            //if is a servercommand?
            if (IsCommand(msgReceiver) == 1) {
                printf("is a comman! \n");
                memcpy(Clients[index].message, msgReceiver, sizeof(msgReceiver));
                //printf("%s\n",Clients[index].message);
                _beginthread(HandleClientMessageTh, 0, (void*)index);
                //Clients[index].recevingInfo = 0;

            }
            else {
                Clients[index].recevingInfo = 0;
                //printf(" : ignored\n");
            }


        }
        else if (res == 0) {
            //  printf("nothing received\n ");
              //Reset receive Client Message
            Clients[index].recevingInfo = 0;
        }
        else {
            printf("s181: recv failed with error: %d\n", WSAGetLastError());
            closesocket(Clients[index].socket);
            WSACleanup();

        }
    }
    _endthread();
}

#pragma endregion


#pragma region MatchMakingLoop
void MMServer() {

    // looping for accepting clients
    if (isAcceptingClients == 0) {
        isAcceptingClients = 1;
        _beginthread(AcceptSockets, 0, (void*)ListenSocket);
    }

    /*
    *  if (DoneCommand == 0) {
        DoneCommand = 1;
        _beginthread(CommandLines, 0, (void*)ServerState);
    }
    */
   

    if (UsersOn > 0) {
        //for all clients connected // loop clients via servers
        for (int i = 0; i < ClientConnected; i++) {
            if (Clients[i].socket != INVALID_SOCKET) {

                if (Clients[i].state != 3) {
                    //ifnot listening to client
                    if (Clients[i].recevingInfo == 0) {
                        Clients[i].recevingInfo = 1; // listen on for client i
                        printf("Waiting to get message from client number %d \n", Clients[i].clientID);
                        _beginthread(ReceiveClientMessage, 0, (void*)Clients[i].clientID);
                    }
                    /*   if (Clients[i].hastoSend == 1) {
                        Clients[i].hastoSend = 0;
                        // printf("Sender: %d try to send ' %s ' from ' %s ' to all\n", Sender++, Clients[i].message, Clients[i].name);
                        _beginthread(SendClientMessageMulticast, 0, (void*)i);
                    }
                    */
                }



            }
        }
    }


}
#pragma endregion


int __cdecl main(int argc, char** argv)
{


    WSADATA wsaData;
    int iResult;

    SOCKET ClientSocket[2];
    SOCKET TempSocket = INVALID_SOCKET;




    int numberOfClients = 0;
    struct addrinfo* result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    char portLabel[DEFAULT_BUFLEN];



    if (argc != 1) {
        printf("usage: %s \n", argv[0]);
        return 1;
    }

    printf("%s on port '%s' ", EXE_MESAAGE, ZW_PORT);
#pragma region ServerSetup
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    //set matchmakin port of Ziniax Warriors
    strcpy(portLabel, ZW_PORT);

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, portLabel, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for the server to listen for client connections.
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP Listen socket
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

#pragma endregion

    // recieve clients 
    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }


    // do process of commandlines
    
    _beginthread(CommandLines, 0, (void*)ServerState);
    _beginthread(AcceptSockets, 0, (void*)ListenSocket);

    while (ServerState != -1) // if not off, do sever loop
    {
        MMServer();//MMServer loop
    }



#pragma region CloseServer
    // No longer need server socket
    closesocket(ListenSocket);

    for (int i = 0; i < ClientConnected; i++) {
        iResult = shutdown(Clients[i].socket, SD_SEND);
        if (iResult == SOCKET_ERROR) {
            printf("shutdown failed with error: %d\n", WSAGetLastError());
            closesocket(Clients[i].socket);
            WSACleanup();
            return 1;
        }
    }
    // shutdown the connection since we're done

    // cleanup
    closesocket(ClientSocket);
    WSACleanup();

    return 0;
#pragma endregion
}


