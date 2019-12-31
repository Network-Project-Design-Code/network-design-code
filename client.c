#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>
#include <time.h>
#include "iniparser/src/iniparser.h"
#define MAXSZ 200
int port;
char *TheSrvrI;
char serverIp[100];
char *ChngTheUsrIdd;
char *ChngThePaswordId;
char UsrrIdChngt[100];
char PasswordIdChngt[100];
char updateiniString[100];
 char userId[100];
 char pass[100];
            char date[10];
             char user[5];
             char size[5];
             char result[200];
             int len,pos,s=0,l;
             int i;
             

void access_client_ini(char * ini_name);
void update_client_ini(char * ini_name,int TheSelctt);
void auth_client_ini(char * ini_name);
int main()
{
    access_client_ini("client.ini"); 
 int sockfd;

 struct sockaddr_in serverAddress;

 int n,TheAuthhFlggg=1,TheMenuuFlaggg=1,TheMenuuOptn;
 char TheMessage1[MAXSZ];
 char TheMessage2[MAXSZ];
 char TheAuttReslt[100];

    char SndToWhme[MAXSZ];
   char msgSendToWho[MAXSZ];
    char CnfrmSndd[2];
               char drOption[1];
           int drID;
               char CheckkToDltt[2];
               char TheReaddMessage[100];

 sockfd=socket(AF_INET,SOCK_STREAM,0);
 memset(&serverAddress,0,sizeof(serverAddress));
 serverAddress.sin_family=AF_INET;
 serverAddress.sin_addr.s_addr=inet_addr(serverIp);
 serverAddress.sin_port=htons(port);
 connect(sockfd,(struct sockaddr *)&serverAddress,sizeof(serverAddress));

  
 while(1)
 {
         
        
         n=recv(sockfd,TheMessage2,MAXSZ,0);
          if (recv > 0) 
          printf("s: %s\n ",TheMessage2);        

    while(TheAuthhFlggg==1)
    {
    printf("Enter your User ID : ");
    fgets(userId,MAXSZ,stdin);
    if(userId[0]=='#')
    break;
    n=strlen(userId)+1;
    send(sockfd,userId,n,0);
    
    printf("Enter your Password : ");
        fgets(pass,MAXSZ,stdin);
    if(pass[0]=='#')
    break;
    n=strlen(pass)+1;
    send(sockfd,pass,n,0);
    

           n=recv(sockfd,TheMessage2,MAXSZ,0);
           if (recv > 0) 
           strcpy(TheAuttReslt,TheMessage2);
           printf("s : %s\n",TheAuttReslt);
           if(strlen(TheAuttReslt)<40)
           TheAuthhFlggg=-1;

           }
           int TheMenuuFlaggg=1;
            auth_client_ini("client.ini");
            while(TheMenuuFlaggg!=-1)
            {
           printf("Hello %s\nPlease choose your option:\n1)Write Message to User\n2)Change config parameters\n3)Quit\nOption->",userId);
           scanf("%d",&TheMenuuOptn);
          
           if(TheMenuuOptn==1)
              {
        n=1;
    send(sockfd,"2",n,0); 

        printf("Give Target UserId: ");

    scanf("%s",&SndToWhme);

    n=strlen(SndToWhme)+1;
    send(sockfd,SndToWhme,n,0);    

   printf("Please Type Text: ");

    scanf("%s",&msgSendToWho);
    if(msgSendToWho[0]=='#')
    break;
    n=strlen(msgSendToWho)+1;
    send(sockfd,msgSendToWho,n,0);

   printf("Would you like to Send message to %s? (Y/N)",SndToWhme);
 
    scanf(" %s",&CnfrmSndd);
    if(CnfrmSndd[0]=='#')
    break;
    n=strlen(CnfrmSndd)+1;
    send(sockfd,CnfrmSndd,n,0);

       }
       if(TheMenuuOptn==2)
       {
       access_client_ini("client.ini");
          int TheSelctt;
          char checkSelection[2];
         printf("Would you change any following value?\n1)TargetServer : %s\n2)TargetPort : %d\n3)UserID : %s\n4)Passwd : %s\nOption->",serverIp,port,UsrrIdChngt,PasswordIdChngt);
       scanf("%d",&TheSelctt);
       if(TheSelctt==1)
       {
       printf("\nPlease give new TargetServer->");
       scanf("%s",&updateiniString);
       printf("\nDo you want to use this new value? (Y/N))");
       scanf("%s",&checkSelection);
       if(checkSelection[0]=='y'||checkSelection[0]=='Y')
        update_client_ini("client.ini",TheSelctt);
        }
               if(TheSelctt==2)
       {
       printf("\nPlease give new TargetPort ->");
       scanf("%s",&updateiniString);
       printf("\nDo you want to use this new value? (Y/N))");
       scanf("%s",&checkSelection);
       if(checkSelection[0]=='y'||checkSelection[0]=='Y')
        update_client_ini("client.ini",TheSelctt);
        }
        if(TheSelctt==3)
       {
       printf("\nPlease give new UserID  ->");
       scanf("%s",&updateiniString);
       printf("\nDo you want to use this new value? (Y/N))");
       scanf("%s",&checkSelection);
       if(checkSelection[0]=='y'||checkSelection[0]=='Y')
       {
        update_client_ini("client.ini",TheSelctt);
        
        }
        }
                               if(TheSelctt==4)
       {
       printf("\nPlease give new Password  ->");
       scanf("%s",&updateiniString);
       printf("\nDo you want to use this new value? (Y/N))");
       scanf("%s",&checkSelection);
       if(checkSelection[0]=='y'||checkSelection[0]=='Y')
        update_client_ini("client.ini",TheSelctt);
        }
       }
       if(TheMenuuOptn==3)
       {
                                 n=1;
    send(sockfd,"4",n,0); 
              TheMenuuFlaggg=-1;
         printf("\nAu revoir  dear user \n"); 
 }}}
 return 0;
}
void access_client_ini(char * ini_name)
{
     strcpy(serverIp,"");
     strcpy(UsrrIdChngt,"");
     strcpy(PasswordIdChngt,"");
     
    dictionary  *   ini ;
     
    ini = iniparser_load(ini_name);
    if (ini==NULL) {
        fprintf(stderr, "cannot parse file: %s\n", ini_name);
        
    }
    iniparser_dump(ini, stderr);

    port = iniparser_getint(ini, "client:TargetPort", -1);

    TheSrvrI=iniparser_getstring(ini, "client:TargetServer", NULL);
    
    strncpy(serverIp, TheSrvrI,  strlen(TheSrvrI));
 
     ChngTheUsrIdd=iniparser_getstring(ini, "client:UserID", NULL);
    
    strncpy(UsrrIdChngt, ChngTheUsrIdd,  strlen(ChngTheUsrIdd));
    
       ChngThePaswordId=iniparser_getstring(ini, "client:Passwd", NULL);
    
    strncpy(PasswordIdChngt, ChngThePaswordId,  strlen(ChngThePaswordId));
}
void update_client_ini(char * ini_name,int TheSelctt)
{

     
         dictionary  *   ini ;

    ini = iniparser_load(ini_name);
    if (ini==NULL) {
        fprintf(stderr, "cannot parse file: %s\n", ini_name);
        
    }
               FILE *finp = fopen("client.ini", "w");
      fclose(finp);
    if(TheSelctt==1)
    {
iniparser_set(ini,"client:TargetServer",updateiniString);
finp = fopen("client.ini", "w");
iniparser_dump_ini(ini, finp);
fclose(finp);
    }
    if(TheSelctt==2)
    {
iniparser_set(ini,"client:TargetPort",updateiniString);
finp = fopen("client.ini", "w");
iniparser_dump_ini(ini, finp);
fclose(finp);
    }
        if(TheSelctt==3)
    {
iniparser_set(ini,"client:UserID",updateiniString);
finp = fopen("client.ini", "w");
iniparser_dump_ini(ini, finp);
fclose(finp);
    }
        if(TheSelctt==4)
    {
iniparser_set(ini,"client:Passwd",updateiniString);
finp = fopen("client.ini", "w");
iniparser_dump_ini(ini, finp);
fclose(finp);
    }
    	
 
}
void auth_client_ini(char * ini_name)
{

     
         dictionary  *   ini ;

    ini = iniparser_load(ini_name);
    if (ini==NULL) {
        fprintf(stderr, "we cant Paarsse theee Fille: %s\n", ini_name);
        
    }
               FILE *finp = fopen("client.ini", "w");
      fclose(finp);

iniparser_set(ini,"client:UserID",userId);
finp = fopen("client.ini", "w");
iniparser_dump_ini(ini, finp);
fclose(finp);

iniparser_set(ini,"client:Passwd",pass);
finp = fopen("client.ini", "w");
iniparser_dump_ini(ini, finp);
fclose(finp);
}

