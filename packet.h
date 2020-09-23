#ifndef PACKET_H
#define PACKET_H

#include <cstdint>
#include <cstdlib>
#include <limits>
#include <string>
#include <sys/socket.h>

using namespace std;

class Packet
{
  static const int MAX_DATA_SIZE = 500;
  static const int HEADER_SIZE = 12;
  static const int MAX_PACKET_SIZE = MAX_DATA_SIZE+HEADER_SIZE;
  
  static const int DAT_FLAG = 0;
  static const int ACK_FLAG = 1;
  static const int EOT_FLAG = 2;
  
  unsigned int type;
  unsigned int len;
  unsigned int seq;
  
  char data[MAX_DATA_SIZE];
  
  // Packet Constructor
  Packet(int T,int L,int SEQ,char* DATA);
  
  // Constructor for each type of packet
  // data
  Packet* CreateDAT(int L, int SEQ, char* DATA);
  // ack
  Packet* CreateACK(int SEQ);
  // eot
  Packet* CreateEOT(int SEQ);
}