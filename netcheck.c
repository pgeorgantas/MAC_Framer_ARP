/*
Εργαστηριακή Άσκηση 1
Γεωργαντάς Φίλιππος
40266
*/
#include <stdio.h>

//Definitions
typedef unsigned char byte;
void result(short x);

main()
{
    byte ipB[4];
    byte ipA[4];
    char dot;
    printf("Input IP address of PC A: \n");
    scanf("%d.%d.%d.%d",&ipA[0], &ipA[1], &ipA[2], &ipA[3]);
    printf("Input IP address of PC B: \n");
    scanf("%d.%d.%d.%d",&ipB[0], &ipB[1], &ipB[2], &ipB[3]);
        // if Class A
    if ((ipA[0]>=0) && (ipA[0]<128) && (ipB[0]>=0) && (ipB[0]<128))
        if (ipA[0] == ipB[0] && (ipA[3]>0) && (ipB[3]>0))
            result(1);
        else
            result(0);
	    // if Class B
    else if ((ipA[0]>=128) && (ipA[0]<192) && (ipB[0]>=128) && (ipB[0]<192))
        if ((ipA[0] == ipB[0]) && (ipA[1] == ipB[1]) && (ipA[3]>0) && (ipB[3]>0))
            result(1);
        else
            result(0);
        // if Class C
    else if ((ipA[0]>=192) && (ipA[0]<225) && (ipB[0]>=192) && (ipB[0]<225))
        if ((ipA[0] == ipB[0]) && (ipA[1] == ipB[1]) && (ipA[2] == ipB[2]) && (ipA[3]>0) && (ipB[3]>0))
            result(1);
        else
            result(0);
        // if other class or wrong input
    else
        result(0);
}
void result(short x)
{
	if (x==0)
        printf("Communication not supported.\n");
    else
        printf("Communication supported.\n");
}
    