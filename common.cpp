#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "packet.h"

const string rc_file = "recvInfo";
const string sd_file = "channelInfo";

int socS = socket(AF_INET,SOCK_DGRAM,0);
int socB = socket(AF_INET,SOCK_DGRAM,0);
int socC = socket(AF_INET,SOCK_DGRAM,0);
int socR = socket(AF_INET,SOCK_DGRAM,0);

void send_pac(packet* pac_send)
{
  ifstream addrFile(sd_file);
  
  int dest_host,dest_port;
  addrFile >> dest_host;
  addrFile >> dest_port;
  
  
  
  addrFile.close();
}

packet* recv_pac()
{
  
}

void send_ack(packet* ack_send)
{
  ifstream addrFile(rc_file);
  
  int dest_host,dest_port;
  addrFile >> dest_host;
  addrFile >> dest_port;
  
  addrFile.close();
}

packet* read_ack()
{
  
}