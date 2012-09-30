#ifndef STRUCT
#define STRUCT
#include  <stdlib.h>
#include <unistd.h>
#include "sys/socket.h"
#include "errno.h"
#include "netdb.h"
#include "string.h"
#include "arpa/inet.h"
#include "stdio.h"
#include "iostream"
#include <unistd.h>
#include <fcntl.h>
#include "fstream"
#include"pcap.h"
using namespace std;

#define IPPack 1
#define ICMPPack 2
struct IpHeader {
 unsigned char Version_Hlen;//首部长度和Ip版本号
 unsigned char TOS;//服务类型TOS
 unsigned short Length;//总长度
 unsigned short Ident;//认证
 unsigned short Flags_offset;//标志位和偏移量
 unsigned char TTL;
 unsigned char Protocol;
 unsigned short Checksum;//校验和
 unsigned int SourAddr;
 unsigned int DestAddr;

};
 struct IcmpHeader{
 unsigned char Type;//8位类型
 unsigned char Code;//8位代码
 unsigned short Checksum;//校验和
 unsigned short ID;//16位识别号
 unsigned short Sequence;//16位报文序列号
 
};
/*计算校验和函数*/
 unsigned short CheckSum(unsigned short *buff,int size);
#endif
