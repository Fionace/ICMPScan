#include"struct.h"
/*struct IpHeader {
 unsigned char Version_Hlen;//��~V�~C��~U�度�~R~LIp�~I~H�~\��~O�
 unsigned char TOS;//�~\~M�~J�类�~^~KTOS
 unsigned short Length;//�~@��~U�度
 unsigned short Ident;//认��~A
 unsigned short Flags_offset;//�| ~G��~W��~M�~R~L�~A~O移�~G~O
 unsigned char TTL;
 unsigned char Protocol;
 unsigned short Checksum;//�| ���~L�~R~L
 unsigned int SourAddr;
 unsigned int DestAddr;

};
struct IcmpHeader{
 unsigned char Type;//8��~M类�~^~K
 unsigned char Code;//8��~M代�| ~A
 unsigned short Checksum;//�| ���~L�~R~L
 unsigned short ID;//16��~M��~F�~H��~O�
 unsigned short Sequence;//16��~M�~J��~V~G��~O�~H~W�~O�

};*/
 unsigned short CheckSum(unsigned short *buff,int size)
{
    unsigned int cksum=0;
   while(size>1)
       {
         cksum+=*buff++;
         size-=sizeof(unsigned short);
       }
   if(size)   //??��~M�~D~_��~I�~X�计��~W�~N��~O~Wip�~W��~@~Y�~Z~D�| ���~L�~R~LL�~T��~Z~D
    {
       cksum+=*(unsigned short*)(buff);
    }
    cksum=(cksum>>16)+(cksum&0xffff);//��~F��~X16��~M��~N��~N16��~M�~[��~J| 
    cksum+=(cksum>>16);//��~F��~[��~M�~H���~X��~M�~Z~D16��~M��~N��~N16��~M�~F~M�~[��~J| 
   return (unsigned short)(~cksum);
}
