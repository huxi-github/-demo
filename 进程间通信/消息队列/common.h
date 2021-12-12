
#ifndef _COMMON_H_
#define _COMMON_H_
#include <string.h>  // strcpy
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>  // read
#include <sys/ipc.h>
#include <sys/msg.h>

#define PATHNAME "./"
#define PROJ_ID  0x666
#define MSGSIZE 1024

#define SERVER_TYPE 1   // 服务端发送消息类型
#define CLIENT_TYPE 2   // 客户端发送消息类型

struct msgbuf          // 消息结构
{
    long mtype;     // 消息类型
    char mtext[MSGSIZE]; // 消息buf
};

int createMsgQueue();  // 创建消息队列
int destroyMsgQueue( int msqid); // 销毁消息队列

int getMsgQueue();     // 获取消息队列

int sendMsg( int msqid, long type,  const char *_sendInfo);   // 发送消息
int recvMsg(int msqid, long type, char buf[]);       // 接收消息

#endif /* _COMMON_H*/
