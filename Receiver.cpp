#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "packet.h"

int main(int argc, char* argv[]) 
{ 
  bool gbn;
  string src_file_name = argv[2];
  int seq_num = 0;
  int packet_total = 0;
  
  if(argv[1] == 0)
  {
    gbn = true;
  }
  else if(argv[1] == 1)
  {
    gbn = false;
  }
  else
  {
    cerr << "Invalid Protocol Selector!\n" << endl;
    return 1;
  }
  
  int temp_seq = -1;
  
  
  if(gbn)
  {
    while(1)
    {
      packet* tempac = recv_pac();
      if(tempac->type == Packet::EOT_FLAG)
      {
        packet* EOT_conf = CreateEOT(tempac->seq);
        send_ack(EOT_conf);
        return 1;
      }
      else
      {
        if(temp_seq+1 == tempac->seq)
        {
          packet* ACK_conf = CreateACK(temp_seq+1);
          send_ack(ACK_conf);
          ++temp_seq;
        }
        else
        {
          packet* ACK_conf = CreateACK(temp_seq);
          send_ack(ACK_conf);
        }
      }
    }
  }
  else
  {
    return 1;
  }
  cout << "Not normal return" << endl;
  return 1;
}