#include	<sys/socket.h>
#include	<netinet/in.h>
#include  <arpa/inet.h>
#include 	<netinet/in.h>
#include 	<stdio.h>
#include	<string.h>
#include  <unistd.h>
#define MAX_SIZE 2048
#define 	BUFFSIZE	4096
void parse(char*);

int main(int argc, char *argv[]) {
  char req[MAX_SIZE]="";

  if(argc<4){
    printf("Not Enough Arguments\n");
    return 1;
  }
  sprintf(req, "GET /en/flights_schedule/arrivals?type=arrivals&from_city=&date=%s&flight_number=%s%%20%s&airline= HTTP/1.0\r\nHost: www.qaiairport.com\r\n\r\n", argv[1], argv[2],argv[3]);

  int	sockfd, n;				// socfd is the socket descriptor (similar to a file descriptor)
  char	recvline[BUFFSIZE + 1];	// array of characters to hold the response from the server
  struct 	sockaddr_in servaddr;	// a structure variable to hold the server IP address & port #

  sockfd = socket(AF_INET, SOCK_STREAM, 0);	// Create a socket. AF_INET means an Internet socket. SOCK_STREAM means we will use TCP.

  if (sockfd < 0) {		// if socket creation is successful sockfd must be >= 0
    perror("cannot create socket");	// if unsuccessful print an error message, and
    return 1;				// exit unsuccessfully
  }

  memset(&servaddr, 0, sizeof(servaddr)); // Clearing the address structure
  servaddr.sin_family = AF_INET;			// Setting the address family to Internet (IP address)
  servaddr.sin_port   = htons(80);		// filling in the port # (daytime server)
  servaddr.sin_addr.s_addr = inet_addr("188.165.221.35"); // filling in the server IP address

  if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {		// establish the connection to server
    perror("cannot connect to server");	// if connection fails print error message, and
    return 1;				// quit unsucessfully
  }
  write(sockfd, req, strlen(req));
  FILE *response=fopen("page.html","w");
  while ( (n = read(sockfd, recvline, BUFFSIZE)) > 0) {	// read from socket into the buffer (char array)
    recvline[n] = 0;	// explicitly terminating the char array with null
    fprintf(response,recvline);	// print the reply on the standard output
  }
  if (n < 0) {
    printf("cannot read from server");	// In case of error, print error message
  }
  close(sockfd);		// close the socket
  fclose(response);

  response=fopen("page.html","r");
  if(response==NULL){
    perror("File not found");
    return 1;
  }
  char inp[MAX_SIZE+1];
  fgets(inp,MAX_SIZE,response);
  while(strstr(inp,"class=\"odd\"")==NULL){
    fgets(inp,MAX_SIZE,response);
  }
  parse(inp);
  fclose(response);

  return 0;
}

void parse(char * line){
  //(Number,City,Scheduled),Estimated,Gate,Status
  //puts(line);
  char out[MAX_SIZE];
  char* Number;
  char* City;
  char* Scheduled;
  char* tokens[5];
  int i=0,j=0;
  char * token =strtok(line,"<>");
  while(token!=NULL){

    if((i)%3==0&&i<10){
      tokens[j]=token;
      j++;
  }
    i++;
    token =strtok(NULL,"<>");
  }
  token=strtok(tokens[3]," ");
  sprintf(out,"Flight %s arriving from %s is expected to arrive on %s at %s\0",tokens[1],tokens[2],token,strtok(NULL," "));
  puts(out);

}
