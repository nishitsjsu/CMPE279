// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <sys/wait.h>
#include <sys/user.h>
#define PORT 8080 
int main(int argc, char const *argv[]) 
{ 
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    char *hello = "Hello from server"; 
    int pid;
    int uid;
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 

    printf("PID before fork : %d\n", getpid()); // Parent process
    pid = fork(); // Creating child process to handle data coming from the client
    printf("PID after fork : %d\n", pid);
    printf("uid is : %d\n" , getuid());	// Child process
    if(pid == 0){
    	printf("child process %d is created and control is with child now\n", pid);
    	uid = setuid(65534); // set user to "nobody - 65534" user
    	printf("Uid: %d and user id is %d \n", uid, getuid()); // new userid confirmation
    	if(uid == -1){
    		// if setuid() throws error by returning -1 code then terminate the program
    		printf("Error in setting the user to nobody user while dropping privileges\n");
    		exit(EXIT_FAILURE);
    	}
    	valread = read( new_socket , buffer, 1024);
	    printf("%s\n",buffer );  
	    // kill(pid, SIGKILL);
    } else if(pid > 0){
    	sleep(2);
    	printf("control is with parent now\n");
	    send(new_socket , hello , strlen(hello) , 0 ); 
		printf("Hello message sent\n");
    } else{
    	printf("Fork failed\n");
    	exit(EXIT_FAILURE);
    }
    printf(" uid is : %d\n " , getuid());
    return 0; 
} 

