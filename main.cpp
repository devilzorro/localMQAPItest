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

string cmdContent;

void connectLost()
{
	printf("connection lost!\n");
}

void recv_Cmd(char *msgContent,char *topicName,int topicLen)
{
	printf("recving message on topic: %s,topciLen : %d\n",topicName,topicLen);
	printf("recving message in callback : %s\n", msgContent);
//	if(topicName == "WISpad")
//	{
		cmdContent = msgContent;
//	}
}

int main()
{
	cmdContent = "";
	int sendStatus = 0;
	char *AppName = "test1";
	char *userName = "";
	char *passwd = "";
	int port = 1883;
	int beatInterval = 300;
	int connStatus = AccessMQ(AppName,userName,passwd,port,beatInterval,connectLost,recv_Cmd);
	if(connStatus == 0)
	{
		int addSubStatus = addSubTopic("WISpad");
		printf("add WISpad topic status : %d\n",addSubStatus);
//		int addLocalSubStatus = addSubTopic("localTest1");
//		printf("add local sub topic status : %d\n",addLocalSubStatus);
		int addLoginStatus = addSubTopic("woLogin");
		printf("add local subTopic woLogin status: %d\n",addLoginStatus);

		char *testMsg = "{\"sys_cpuInfo\":\"5.01367%\"}";
		int i=0;
//			while(i<30)
//			{
//				i++;
//				if(i == 10)
//				{
//					int removeStatus = removeSubTopic("remoteGroup");
//					printf("remove sub topic status : %d\n",removeStatus);
//				}
//
//				if(i == 20)
//				{
//					int removeStatus = removeSubTopic("localTest1");
//					printf("remove local sub topic status : %d\n",removeStatus);
//				}

//				sendRemoteMsg(testMsg,"App1|App2|App3",10001);
		while(sendStatus == 0)
		{
			printf("cmd content:%s\n",cmdContent.c_str());
			if(cmdContent == "requestWisList")
			{
				string woTest = "{\"equSerialNo\": \"T001\",\"data_job\": [{\"time_StartPlan\": \"2017-07-24 09:44:57\",\"time_EndPlan\": \"2017-07-25 09:44:57\",\"jobDispatchRealStartTime\": \"2017-07-24 09:44:57\",\"jobDispatchProjectCount\": 30,\"jobDispatchRealFinishCount\": 0,\"jobDispatchNo\": \"2456\",\"processNo\": \"03\",\"partNo\": \"TS001\",\"status\": \"1\",\"data_technology\": [{\"uniqueID\": \"111\",\"documentName\": \"TS001\",\"type\": \"1\",\"path\": \"www.baidu.com/id=1?\"}, {\"uniqueID\": \"111\",\"documentName\": \"TS001\",\"type\": \"2\",\"path\": \"www.baidu.com/id=1?\"}],\"data_relatedJob\": [{\"relatedJobNo\": \"03\",\"status\": \"1\"}]}]}";

				sendLocalMsg(woTest.c_str(),"WISpad");
				sendStatus = 1;
			}
			sleep(5);
		}

//			}
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
