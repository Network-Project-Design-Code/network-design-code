 
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "iniparser/src/iniparser.h" 
#include <time.h>
#include <dirent.h> 
#define DEFAULT_BUFLEN 512
  void make_user_folder();
void access_server_ini(char * ini_name);
void do_job(int fd);
 int port;
 char *TheSrvrMessage; 
 char serverM[100];
  char TheAuthhErr[100];
 int   TheCrrcttAut=0;
  int authentication_processing(char * ini_nam);
  char *user; 
  char userId[5];
  char *pass; 
  char userPass[100];
                  char TheUsrNd[5];
                 char toWhichUser[10];
                 char TheMessageThatWillBeStrd[100];
                 char CnfrmSndd[2];
                              
             
            


int main()
{
int server, client;
struct sockaddr_in local_addr;
struct sockaddr_in remote_addr;
int length,fd,rcnt,OV;
pid_t pid;
 access_server_ini("server.ini"); 
if ((server = socket( AF_INET, SOCK_STREAM, 0)) < 0 ) { 
    perror("Can't create socket!");
    return(1);
}
strcpy(TheAuthhErr,"Error");
memset( &local_addr, 0, sizeof(local_addr) );
memset( &remote_addr, 0, sizeof(remote_addr) );

local_addr.sin_family = AF_INET;
local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
local_addr.sin_port = htons(port);

OV = 1;
setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &OV, sizeof OV);

if ( bind( server, (struct sockaddr *)&local_addr, sizeof(local_addr) ) < 0 )
{
    perror("Bind error");
    return(1);
}

if ( listen( server, SOMAXCONN ) < 0 ) {
        perror("listen");
        exit(1);
}

printf("Concurrent  socket server now starting on port %d\n",port);
printf("Wait for connection\n");

while(1) {  
    length = sizeof remote_addr;
    if ((fd = accept(server, (struct sockaddr *)&remote_addr, \
          &length)) == -1) {
          perror("Accept Problem!");
          continue;
    }

    printf("Server: got connection from %s\n", \
            inet_ntoa(remote_addr.sin_addr));
    if ((pid=fork()) == 0) {
        close(server);
        do_job(fd);
        char userIdd[100];
        strncpy(userIdd,userId,strlen(userId)-1);
        printf("%s End his/her connection Successfully  \n",userIdd);
        close(fd);
        exit(0);
}}
close(server);

}
void do_job(int fd) {
int length,rcnt,n,TheAuthhFlggg=-1;;
char recvbuf[DEFAULT_BUFLEN],bmsg[DEFAULT_BUFLEN];
int  recvbuflen = DEFAULT_BUFLEN;

    do {
   
       
         
         n=strlen(serverM)+1;
       send( fd, serverM, n, 0 );
           
            while(TheAuthhFlggg==-1)
            {
       
          
         n = recv(fd, recvbuf, recvbuflen, 0);
        if (recv > 0) 
          strcpy(userId, recvbuf); 
            printf("UserId: %s\n", userId);
     
      n = recv(fd, recvbuf, recvbuflen, 0);
        if (recv > 0) 
        strcpy(userPass, recvbuf); 
               printf("UserPass: %s\n", userPass);
      
            
        if (rcnt == 0)
            printf("Connection closing...\n");
  
       
        int authnictionResult=authentication_processing("server.ini");
        if(authnictionResult==-1)
        {
 
      
         printf("\nError in Authnication \n");
  
         strcpy(TheAuthhErr,"-ERR Either UserID or Password is wrong.");
         n=strlen(TheAuthhErr)+1;
         send( fd, TheAuthhErr, n, 0 );
          TheAuthhFlggg=-1;
         TheCrrcttAut=-1;
     
        

        }
        else{
         printf("\nCorrect in Authnication \n");
         make_user_folder();
         strcpy(TheAuthhErr,"+OK UserID and password okay go ahead");
         n=strlen(TheAuthhErr)+1;
         send( fd, TheAuthhErr, n, 0 );
            TheAuthhFlggg=0;
                TheCrrcttAut=1;

            }
printf("\n  TheCrrcttAut=%d\n",  TheCrrcttAut);
                            
                                        FILE *auth_attemp;
         auth_attemp=fopen("Authentication_Attempts.txt", "a");
            if(  TheCrrcttAut==1)
            {

          fprintf(auth_attemp, "\n");
   fprintf(auth_attemp, "\n+GOOD attempt to authenticate from UserId=%s , Password=%s \n",userId,userPass);
   fclose(auth_attemp);
            }
        if(  TheCrrcttAut==-1)
            {

           fprintf(auth_attemp, "\n");
   fprintf(auth_attemp, "\n-Bad attempt to authenticate from UserId=%s , Password=%s \n",userId,userPass);
   fclose(auth_attemp);
            }
            }
           
                while(TheUsrNd[0]!='3'){
     
                  n = recv(fd, recvbuf, recvbuflen, 0);
                 if (recv > 0) 
                 {
                 TheUsrNd[0]=recvbuf[0];
                 }
            
                 if (recv > 0) 
                 {
                 TheUsrNd[0]=recvbuf[0];
                 }

            if(TheUsrNd[0]=='1')
              {
            
                 
              
                 char TheStrdPt[300]="data/home/20168450/server/";
                 strncat(TheStrdPt,userId,strlen(userId)-1);
           
        if (recv > 0) 
          strcpy(toWhichUser, recvbuf); 
            printf("toWhichUser: %s\n", toWhichUser);
      
          char textSize[100];
      n = recv(fd, recvbuf, recvbuflen, 0);
        if (recv > 0) 
        {
        strcpy(TheMessageThatWillBeStrd, recvbuf); 
               printf("TheMessageThatWillBeStrd: %s\n", TheMessageThatWillBeStrd);
             sprintf(textSize, "%d",n);
             }
                     n = recv(fd, recvbuf, recvbuflen, 0);
                     
        if (recv > 0) 
        strcpy(CnfrmSndd, recvbuf); 
               printf("confirmSend: %s\n", CnfrmSndd);
              TheUsrNd[0]='9';
                  if((strncmp(CnfrmSndd, "y", 1)==0)||(strncmp(CnfrmSndd, "Y", 1)==0)){
                  
char TheStrdPt[300]="data/home/20168450/server/";
char timeStamp[100];
sprintf(timeStamp, "%d", (int)time(NULL));
strncat(TheStrdPt,toWhichUser,strlen(userId)-1);
strcat(TheStrdPt,"/");
                      printf("Timestamp: %s\n",timeStamp);
                     strcat(TheStrdPt,timeStamp);
                     strcat(TheStrdPt,"_");
                    strncat(TheStrdPt,userId,strlen(userId)-1);
                    strcat(TheStrdPt,"_");
                    strcat(TheStrdPt,textSize);
                    printf("\n%s\n",TheStrdPt);
                     FILE *storeMsg;
                    storeMsg=fopen(strcat(TheStrdPt,".msg"), "w");
                     fprintf(storeMsg,"%s \n",TheMessageThatWillBeStrd);
                     fflush(storeMsg);
                   printf("\n%s\n",TheStrdPt);
                        }

              }
                         
               if(TheUsrNd[0]=='3')
              {
            rcnt=-1;
           TheUsrNd[0]='3';
            }
              }
            
    } while (rcnt > 0);
}

void access_server_ini(char * ini_name)
{
    dictionary  *   ini ;


    ini = iniparser_load(ini_name);
    if (ini==NULL) {
        fprintf(stderr, "cannot parse file: %s\n", ini_name);
        
    }
    iniparser_dump(ini, stderr);

    port = iniparser_getint(ini, "server:ListenPort", -1);
    printf("%d this is \n", port);
   TheSrvrMessage=iniparser_getstring(ini, "server:ServerMsg", NULL);
    strncpy(TheSrvrMessage, TheSrvrMessage,  strlen(TheSrvrMessage));
    printf("server msg:  %s\n",TheSrvrMessage);
        
}

int authentication_processing(char * ini_nam){
      dictionary  *   ini ;
        char tempPass[100];
 
    ini = iniparser_load(ini_nam);
    if (ini==NULL) {
        fprintf(stderr, "cannot parse file: %s\n", ini_nam);
        
    }
    iniparser_dump(ini, stderr);
   

      int id = atoi(userId);


   if(id==10000)
   {

    pass=iniparser_getstring(ini,"users:10000","no");
    printf("\npass= %s",pass);
    strcpy(tempPass, pass);
        printf("\nuserId*= %s",userId);
        printf("\ntempPass*= %s",tempPass);
         
   }
    if(id==10001)
   {
    pass=iniparser_getstring(ini,"users:10001","no");
    printf("\npass= %s",pass);
    strcpy(tempPass, pass);
        printf("\nuserId*= %s",userId);
        printf("\ntempPass*= %s",tempPass);
   }
         if(id==10002)
   {
    pass=iniparser_getstring(ini,"users:10002","no");
    printf("\npass= %s",pass);
    strcpy(tempPass, pass);
        printf("\nuserId*= %s",userId);
        printf("\ntempPass*= %s\n",tempPass);
   }
          printf("\n **tempPass= %d \n**userPass= %d\n",strlen(tempPass),strlen(userPass));
    if((strlen(tempPass)+1)!=strlen(userPass)){
                            return -1;
                            }
        int i;
    for(i=0;i<strlen(tempPass);i++){
     if((tempPass[i]!=userPass[i])){
         return -1;
         }
         }
         
     return 0;
                             }
void make_user_folder(){
       int id;
     if(id=10000){
   char* userDir="mkdir -p data/home/20168450/server/10000";
   system(userDir);
   }
       if(id=10001){
   char* userDir="mkdir -p data/home/20168450/server/10001";
   system(userDir);
   }
     if(id=10002){
   char* userDir="mkdir -p data/home/20168450/server/10002";
   system(userDir);
   }
                      }
