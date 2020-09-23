#include "packet.h"

using namespace std;

class Packet
{ 
  Packet(int T,int L,int SEQ,char* DATA)
  {
    type = T;
    len = L;
    seq = SEQ;
    memcpy(data,DATA,len);
  }
  
  Packet* CreateDAT(int L, int SEQ, char* DATA)
  {
    return new Packet(DAT_FLAG,L,SEQ,DATA); 
  }
  
  Packet* CreateACK(int SEQ)
  {
    return new Packet(ACK_FLAG,0,SEQ,"");
  }
  
  Packet* CreateEOT(int SEQ)
  {
    return new Packet(EOT_FLAG,0,SEQ,""); 
  }
}