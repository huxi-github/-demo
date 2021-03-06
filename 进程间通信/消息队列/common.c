#include "common.h"


int commMsg(int msgflag)
{
    // 生成IPC 关键字
    key_t _k = ftok(PATHNAME, PROJ_ID);
    int msqid = msgget(_k, msgflag); // 获取消息队列ID
    if(msqid < 0)
    {
        perror("msgget");
        return -2;
    }
    return msqid;

}


int createMsgQueue()  // 创建消息队列
{
    return commMsg(IPC_CREAT|IPC_EXCL|0666);
}

int destroyMsgQueue( int msqid) // 销毁消息队列
{
    int _ret = msgctl(msqid, IPC_RMID, 0);
    if(_ret < 0)
    {
        perror("msgctl");
        return -1;
    }
    return 0;
}

int getMsgQueue()     // 获取消息队列
{
    return commMsg(IPC_CREAT);
}

int sendMsg( int msqid, long type,  const char *_sendInfo)         // 发送消息
{
    struct msgbuf msg;
    msg.mtype = type;
    strcpy(msg.mtext, _sendInfo);

    int _snd = msgsnd(msqid, &msg, sizeof(msg.mtext), 0);
    if( _snd < 0)
    {
        perror("msgsnd");
        return -1;
    }
    return 0;
}

int recvMsg(int msqid, long type, char buf[])          // 接收消息
{
    struct msgbuf msg;
    int _rcv = msgrcv(msqid, &msg, sizeof(msg.mtext), type, 0);
    if( _rcv < 0)
    {
        perror("msgrcv");
        return -1;

    }
    strcpy(buf, msg.mtext);
    return 0;
}