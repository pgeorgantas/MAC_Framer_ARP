#include <stdio.h>
#include <string.h>

typedef unsigned char byte;
#define mac_data_size 100
void Send_MAC_frm(byte mac[]);
void send_ARP_req(byte ip[]);

//Variables Declaration
int i, found=0;
byte line[25],ipSrc[4],dot,MACDst[7],ipDest[4],tmpIP[4],msg[]="Hello";
FILE *fr;

void main()
{
	printf("ARP Exercise\n\n");
	printf("Input the Source IP address: ");
	scanf("%d.%d.%d.%d",&ipDest[0],&ipDest[1],&ipDest[2],&ipDest[3]);
	
	fr=fopen("arp.txt","rt"); //rt=Read Text
	if (fr==NULL) 
	{
		printf("ARP table does not exist. Continuing without it...\n");
		printf("Creating MAC Frame with ARP Request...");
		send_ARP_req(ipDest);
	}
	else
	{
		while(fgets(line,80,fr)!=NULL)
		{
			sscanf(line,"%d %c %d %c %d %c %d ",&tmpIP[0],&dot,&tmpIP[1],&dot,&tmpIP[2],&dot,&tmpIP[3]);
			if (tmpIP[0] >= 0 && tmpIP[0] < 256 &&
				tmpIP[1] >= 0 && tmpIP[1] < 256 &&
				tmpIP[2] >= 0 && tmpIP[2] < 256 &&
				tmpIP[3] >= 0 && tmpIP[4] < 256)
					if (tmpIP[0]==ipDest[0] &&
						tmpIP[1]==ipDest[1] &&
						tmpIP[2]==ipDest[2] &&
						tmpIP[3]==ipDest[3])
						{
							found=1;
							printf("%c %c %c %c %c\n",MACDst[0],MACDst[1],MACDst[2],MACDst[3],MACDst[4],MACDst[5]);
						}
		}
		fclose(fr);
		if(found)
		{
			printf("IP exists in the ARP table with MAC %s...\nCreating MAC Frame with message...",MACDst);
			Send_MAC_frm(MACDst);
		}
		else
		{
			printf("IP does not exist in the ARP table...\nCreating MAC Frame with ARP Request...");
			send_ARP_req(ipDest);
		}
			
	}	
}
void Send_MAC_frm(byte mac[])
{
	int i;
	byte pkt[mac_data_size];
	pkt[0]=mac[0];		//Destination Address
	pkt[1]=mac[1];
	pkt[2]=mac[2];
	pkt[4]=mac[3];
	pkt[5]=mac[4];
	pkt[6]=mac[5];
	pkt[7]=1;			//Source Address
	pkt[8]=1;
	pkt[9]=1;
	pkt[10]=1;
	pkt[11]=1;
	pkt[12]=1;
	pkt[13]=8;			//Type 0x0800h
	pkt[14]=0;
	for(i=0;i<strlen(msg);i++)	//Controls Dynamic size of the message
		pkt[15+i]=msg[i];
	pkt[16+i]=0;		//FCS
	pkt[17+i]=0;
	pkt[18+i]=0;
	pkt[19+i]=0;
	for(i=0;i<19+strlen(msg);i++)
		if (i%16==0)
			printf("\n%0x",pkt[i]);
		else
			printf("%0x",pkt[i]);
}
void send_ARP_req(byte ip[])
{
	int i;
	byte pkt[100];
	pkt[0]=0;		//Destination Address
	pkt[1]=0;
	pkt[2]=0;
	pkt[4]=0;
	pkt[5]=0;
	pkt[6]=0;
	pkt[7]=1;		//Source Address
	pkt[8]=1;
	pkt[9]=1;
	pkt[10]=1;
	pkt[11]=1;
	pkt[12]=1;
	pkt[13]=8;		//Type 0x0800h
	pkt[14]=0;
	pkt[15]=0;		//Hardware type
	pkt[16]=0;
	pkt[17]=0;		//Protocol type
	pkt[18]=0;
	pkt[19]=0;		//Hardware Length
	pkt[20]=0;		//Protocol Length
	pkt[21]=0;		//Operation
	pkt[22]=1;
	pkt[23]=1;		//Sender MAC
	pkt[24]=1;
	pkt[25]=1;
	pkt[26]=1;
	pkt[27]=1;
	pkt[28]=1;
	pkt[29]=2;		//Sender IP
	pkt[30]=2;
	pkt[31]=2;
	pkt[32]=2;
	pkt[33]=0;		//Target MAC (Not filled as a Request)
	pkt[34]=0;
	pkt[35]=0;
	pkt[36]=0;
	pkt[37]=0;
	pkt[38]=0;
	pkt[39]=ip[0];	//Target IP (Requesting its MAC)
	pkt[40]=ip[1];
	pkt[41]=ip[2];
	pkt[42]=ip[3];
	pkt[43]=0;		//FCS
	pkt[44]=0;
	pkt[45]=0;
	pkt[46]=0;
	for(i=0;i<=46;i++)
		if (i%16==0)
			printf("\n%0x",pkt[i]);
		else
			printf("%0x",pkt[i]);
}