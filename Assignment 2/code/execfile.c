// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 80
int main(int argc, char const *argv[]) 
{   
    int valread;
    char buffer[1024] = {0}; 
    int uid;

    printf("inside exec'd process\n");

    uid = setuid(65534); // set user to "nobody - 65534" user
	printf("Uid: %d and user id is %d \n", uid, getuid()); // new userid confirmation
	if(uid == -1){
		// if setuid() throws error by returning -1 code then terminate the program
		printf("Error in setting the user to nobody user while dropping privileges\n");
		exit(EXIT_FAILURE);
	}

    valread = read( *argv[1] , buffer, 1024);
    printf("%s\n",buffer );  
    return 0; 
} 
