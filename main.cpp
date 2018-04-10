/*
 * main.cpp
 *
 *  Created on: 2016-12-1
 *      Author: fiyang
 */
#include "localMQ.h"
#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

void connectLost()
{
	printf("connection lost!\n");
}

void recv_Cmd(char *msgContent,char *topicName,int topicLen)
{
	printf("recving message on topic: %s,topciLen : %d\n",topicName,topicLen);
	printf("recving message in callback : %s\n", msgContent);
}

int main()
{
	char *AppName = "test1";
	char *userName = "";
	char *passwd = "";
	int port = 1883;
	int beatInterval = 300;
	int connStatus = AccessMQ(AppName,userName,passwd,port,beatInterval,connectLost,recv_Cmd);
	if(connStatus == 0)
	{
		int addSubStatus = addSubTopic("remoteGroup");
		printf("add remote sub topic status : %d\n",addSubStatus);
		int addLocalSubStatus = addSubTopic("localTest1");
		printf("add local sub topic status : %d\n",addLocalSubStatus);

		char *testMsg = "{\"sys_cpuInfo\":\"5.01367%\"}";
		int i=0;
			while(i<30)
			{
				i++;
				if(i == 10)
				{
					int removeStatus = removeSubTopic("remoteGroup");
					printf("remove sub topic status : %d\n",removeStatus);
				}

				if(i == 20)
				{
					int removeStatus = removeSubTopic("localTest1");
					printf("remove local sub topic status : %d\n",removeStatus);
				}

				sendRemoteMsg(testMsg,"App1|App2|App3",10001);
				sendLocalMsg(testMsg,"WIS");

				sleep(5);
			}
			int closeStatus = closeChannel();
			printf("close channel status : %d\n",closeStatus);

	}
	else
	{
		printf("connect return error status : %d \n",connStatus);
	}
	destoryChannel();
	return 0;
}
