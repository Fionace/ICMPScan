#include"struct.h"
using namespace std;
extern unsigned short CheckSum(unsigned short,int);
/*数据包构造函数*/
bool ConstruPack(char *Buffer,int flags)
{
    //Icmppack=new IcmpHeader;
   switch(flags)
     {case 2:
      struct IcmpHeader *icmp;
      icmp=(IcmpHeader*)Buffer;
      icmp->Type=8;
      icmp->Code=0;
      icmp->ID=(unsigned short)getpid();
      icmp->Sequence=htons(1);//填充序列号
      icmp->Checksum=0;
      icmp->Checksum=CheckSum((unsigned short*)Buffer,sizeof(Buffer));
      break;
     
     default:
       //printf("no define!\n");
       break;
     }

}

