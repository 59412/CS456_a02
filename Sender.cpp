#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "packet.h"
#include "common.cpp"

using namespace std;

static const int GBN_FLAG = 0;
static const int SR_FLAG = 1;
static const int WINDOW_SIZE = 10;

void GoBackN(vector<packet*> PacQ, int timout,int start_index)
{
  if(start_index == PacQ.size() - 2) return;
  
  int temp_index = start_index;
  int pac_len = 0;

  // send
  while(PacS.size()<WINDOW_SIZE && temp_index < pacQ.size()-1)
  {
    send_pac(PacQ[temp_index]);
    ++temp_index;
    ++pac_len;
  }
  
  vector<int>ack_vec (pac_len,0);
  // receive and check for each
  while(1)
  {
    packet* ack_pack =  read_ack();
    int ack_num = ack_pack->seq;
    
    if(ack_vec[ack_num] == 0)
    {
      ack_vec[ack_num] = 1;
    }
    if(timeout)
    {
      break;
    }
  }
  
  // resend if necessary
  int no_ack = -1;
  for(int i = 0; i < pac_len; i++)
  {
    if(ack_vec[i] != 1)
    {
      no_ack = i;
      break;
    }
  }
  
  if(no_ack == -1)
  {
    GoBackN(PacQ,timeout,temp_index);
  }
  else
  {
    GoBackN(PacQ,timeout,i+start_index);
  }
}

void SelectRep(vector<packet*> PacQ, int timout,int start_index, vector<int>* ack_vec, int* winS)
{
  if(start_index == PacQ.size() - 1) return;
  
  // send
  //send_pac(PacQ[start_index]);
  
  // wait
  // resend if necessary
}

int main(int argc, char* argv[]) 
{
  bool gbn;
  string dest_host;
  string dest_port;
  int timeout = argv[2];
  string src_file_name = argv[3];
  int seq_num = 0;
  int packet_total = 0;
  
  vector<packet*> PacQueu;
  
  // Select Protocol
  if(argc != 2)
  {
    cerr << "Sender: Invalid number of arguments!\n" << endl;
    return 1;
  }
  
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
  
  // Get target file
  ifstream sourceFile(src_file_name);
  
  char file_buffer[Packet::MAX_DATA_SIZE];
  while(!(sourceFile.eof()))
  {
    sourceFile.read(buffer,Packet::MAX_DATA_SIZE);
    Packet* curr_pack = Packet::CreateDAT(transferFile.gcount(),seq_num,buffer);
    PacQueu.push_back(curr_pack);
    
    ++seq_num;
    seq_num = seq_num % 256;
    ++packet_total;
  }
  
  sourceFile.close();
  
  curr_pack = Packet::CreateEOT(seq_num);
  PacQueu.push_back();
  ++packet_total;
  
  // ************************* GBN or SR
  if(gbn)
  {
    GoBackN(PacQueu,timeout,0);
  }
  else
  {
    
  }
  
  send_pac(PacQueu[packet_total - 1]);
  if(recv_pac->type == Packet::EOT_FLAG)
  {
    cout << "EOT confirmation received" << endl;
  }
  // ************************* GBN or SR finished
  
  // deletion
  for(int i = 0; i < packet_total; i++)
  {
    free((PacQueu[i])->data);
    free(PacQueu[i]);
  }
  return 1;
}