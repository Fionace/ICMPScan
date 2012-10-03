#include"struct.h"
#include<netinet/in.h>
#include<sys/time.h>
#include <time.h>
//#include"DatePack.h"
extern bool ConstruPack(char*,int); //声明
//extern unsigned short CheckSum(unsigned short,int);
int main(int argc,char** argv)
{
    struct sockaddr_in DestAddr,addr;
    socklen_t Len;
    Len=sizeof(addr);
    //struct IpHeader *ip;
   // struct *IcmpRecv;
    char *Buffer=new char(8);
   //string ipp[4]={"172","17","157","0"};
    unsigned char ipp[4]={172,17,157,0}; //char型默认是有符号的，如果不声明unsigned，则下一步打印的结果是-84.是因为最大能存的正数是127
   // printf("%d\n",ipp[0]);
    int IcmpSocket;
    IcmpSocket=socket(AF_INET,SOCK_RAW,IPPROTO_ICMP);
    if (IcmpSocket==-1)
      {
        printf("Create the icmp socket failed! \n");                
        close(IcmpSocket);
        return -1;
      }
   /*设�超时属性，，如果目标主机不存再火灾关机，由于recvfrom()是阻塞性子的，它会一直等待数据到达，谷为了让程序能再次停止，设置词超时属性*/
   //struct timeval *tv=new timeval();
   struct timeval tv;
 tv.tv_sec=1;
 tv.tv_usec=5000;
  if(setsockopt(IcmpSocket,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv))!=0)//(struct timeval*)
      {
         //int err;
          char *msg=strerror(errno);
          printf("Mesg:%s\n",msg);
        printf("Set Timeout failed! \n");
        close(IcmpSocket);
        return -1;
      }
      printf("11111\n");
   /*构造发送的数据包*/
  ConstruPack(Buffer,2);
    printf("222222\n");
   /*循环给同一子网内的机器发包*/
  int i;
  int send[255];
  int recv[255];
  char RecvBuf[255][1024];
 
  for(i=0;i<255;i++)
 {
    struct IpHeader ip[255], *ipcl;
   ipcl=ip;
   struct IcmpHeader icmprecv[255],*icmpcl;
   icmpcl=icmprecv;
  char *DestIp;
    sprintf(DestIp,"%d.%d.%d.%d",ipp[0],ipp[1],ipp[2],ipp[3]);
    bzero(&DestAddr,sizeof(DestAddr));
    DestAddr.sin_addr.s_addr=inet_addr(DestIp);
    DestAddr.sin_family=AF_INET;
    DestAddr.sin_port=htons(0);
   send[i]=sendto(IcmpSocket,Buffer,sizeof(Buffer),0,(sockaddr*)&DestAddr,sizeof(DestAddr));
   if(send[i]==-1)
      {
          char *msg=strerror(errno);
          printf("Mesg:%s\n",msg);
        printf("Send to %s failed! \n",DestIp);
        close(IcmpSocket);
        return -1;
      }
  recv[i]=recvfrom(IcmpSocket,RecvBuf[i],1024,0,(sockaddr*)&addr,&Len);
  if(recv[i]==-1)
   {
               char *msg=strerror(errno);
          printf("Mesg:%s\n",msg);
        printf("Send to %s failed! \n",DestIp);
       // close(IcmpSocket);
      ipp[3]++;
      ipcl++;
      icmpcl++;
        continue;
    
    }
   else if(!recv[i])
     {printf("Timeout @ %s,it may be down!\n",DestIp);
       //close(IcmpSocket);
         ipp[3]++;
      ipcl++;
      icmpcl++;
        continue;

     }
   else if(recv[i]<sizeof(IcmpHeader)+sizeof(IpHeader))
  {
       printf("Recvived error relay packet @ %s\n",DestIp);
       //close(IcmpSocket);
       ipp[3]++;
       ipcl++;
      icmpcl++;
        continue;
  }
  /*分析得到的应答包*/
   ipcl=(IpHeader*)RecvBuf[i];
   //if((ip[i]->Protocol==IPPROTO_ICMP)&&(ip[i]->SourAddr==inet_addr(DestIp)))
  if((ipcl->Protocol==IPPROTO_ICMP)&&(ipcl->SourAddr==inet_addr(DestIp)))
    {
      icmpcl=(IcmpHeader*)(RecvBuf[i]+sizeof(IpHeader));
      if(icmpcl->Type!=0)
       {
          printf("error type,%d",icmpcl->Type);
         //close(IcmpSocket);
         ipp[3]++;
         ipcl++;
      icmpcl++;
        continue;
       }
      if(icmpcl->Type!=0)
       {
          printf("error type,%d",icmpcl->Type);
        // close(IcmpSocket);
       ipp[3]++;
        ipcl++;
      icmpcl++;
        continue;
       }
     if(icmpcl->ID!=getpid())
       {
          printf("error pid,%d",icmpcl->ID);
         //close(IcmpSocket);
         ipp[3]++;
        ipcl++;
      icmpcl++;
        continue;
       }
     else if((icmpcl->Type==0)&&(icmpcl->ID==getpid()))
      {
         printf("The host %s  is up\n",DestIp);
         ipp[3]++;
          ipcl++;
      icmpcl++;
         continue; 
      }
    }
   else
     {
         printf("so pity~\n");
       //close(IcmpSocket);
         ipp[3]++;
         ipcl++;
      icmpcl++;
        continue;
      }
     
  }
close(IcmpSocket);
 exit(0);
}
