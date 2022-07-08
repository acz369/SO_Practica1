#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include "clientBridge.h"

void write_struct(int fd, unsigned long command, struct complex_struct * struct_address){
    if (ioctl(fd, command, struct_address) == -1){
        perror("Write message error at ioctl");
    }
}

void write_message(int fd, unsigned long command, char * message){
    if (ioctl(fd, command, message) == -1){
        perror("Write message error at ioctl");
    }
}

void read_message(int fd, unsigned long command, char * message){
    if(ioctl(fd, command, message) == -1){
	perror("Read message error at ioctl");
    }
}

void read_message_param(int fd, unsigned long command, int * value){
    if(ioctl(fd, command, value) == -1){
        perror("Read message param error at ioctl");
    }else{
        printf("Copy the messsage from the kernel\n");
    }
}

void write_int(int fd, unsigned long command, int * value){
    if (ioctl(fd, command, value) == -1){
        perror("Write int error at ioctl");
    }
}

void read_int(int fd, unsigned long command, int * value){
    if(ioctl(fd, command, value) == -1){
        perror("Read int error at ioctl");
    }else{
        printf("Copy the int from the kernel\n");
    }
}

int send_empty_command(int fd, unsigned long command){
    int returned_value = ioctl(fd, command);
    if(returned_value == -1){
       perror("Send command error at ioctl");
    }else{
	return returned_value;
        printf("Command OK to the kernel\n");
    }
}

void write_several_messages(int fd){
    write_message(fd, BRIDGE_W_S, "Message 01");
    write_message(fd, BRIDGE_W_S, "Message 02");
    write_message(fd, BRIDGE_W_S, "Message 03");
}

//void read_all_messages(int fd){
//	char message[100];
//	while( send_empty_command(fd, BRIDGE_STATE_S) > 0){
//	    read_message(fd, BRIDGE_R_S, message);
//	    printf("Message: %s\n", message);
//	}
//}

void read_all_messages(int fd, unsigned long command_r, unsigned long command_state){
	char message[100];
	while(send_empty_command(fd, command_state) > 0){
	    read_message(fd, command_r, message);
	    printf("Message: %s\n", message);
	}
}

//1. Read file lines and display them in reverse order.
/*void reverse_order(int fd, char filepath_arg){
    char filepath[] = filepath_arg;
    char line[100];
    FILE *fp; //fp: file pointer
    
    send_empty_command(fd, BRIDGE_CREATE_S);
    
    fp = fopen(filepath, "r");
    
    if(fp == NULL) {
    	printf("Can not open %s\n", filepath);
    	exit(1);
    }
    while (fgets(line, sizeof(line), fp)) {
    	write_message(fd, BRIDGE_W_S, line);
    	printf("%s", line);
    }
    
    read_all_messages(fd, BRIDGE_R_S, BRIDGE_STATE_S);
    
    fclose(fp);
    };*/
// End 1

int main(int argc, char *argv[]){

    const char *file_name = "/dev/bridge"; //used by ioctl
    int fd;

    fd = open(file_name, O_RDWR);
    if (fd == -1){
        perror("Bridge ioctl file open");
        return 2;
    }

    //char message[] = "mensajeEspecifico";
    //int value = 10;

//Ask for an option
	int n, option;

	    do
	    {
		printf( "\n   1. Read file lines and display them in reverse order.");
		printf( "\n   2. Randomly shuffles the lines of a file.");
		printf( "\n   3. Analyze a C source code file and verifies that parentheses and braces are balanced.");
		printf( "\n   4. Queue with priorities that handles three levels: high, medium and low." );
		printf( "\n   5. Completely destroys a linked list." );
		printf( "\n   6. Invert the order of the nodes of a list." );
		printf( "\n   7. Concatenate two lists." );
		printf( "\n   8. Cotates a list N times to the right." );
		printf( "\n   9. Removes identical values from a list." );
		printf( "\n   10. Returns the largest value in a list." );
		printf( "\n   11. Exit." );
		
		do
		{
		    printf( "\n   Enter your option (1-11): ");
		    scanf( "%d", &option );

		} while ( option < 1 || option > 11 );

		switch (option)
		{
		    case 1: 
		            char filepath[100];
		            
		            printf("Enter your file's path: ");
		            scanf("%s", filepath);
		            
		            char line[100];
			    FILE *fp; //fp: file pointer
			    
			    send_empty_command(fd, BRIDGE_CREATE_S);
			    
			    fp = fopen(filepath, "r");
			    
			    if(fp == NULL) {
			    	printf("Can not open %s\n", filepath);
			    	exit(1);
			    }
			    while (fgets(line, sizeof(line), fp)) {
			    	write_message(fd, BRIDGE_W_S, line);
			    	printf("%s", line);
			    }
			    
			    read_all_messages(fd, BRIDGE_R_S, BRIDGE_STATE_S);
			    
			    fclose(fp);
		            break;

		    case 2: printf( "\n   Introduzca un n%cmero entero: ", 163 );
		            /*scanf( "%d", &n );
		            printf( "\n   La mitad de %d es %f\n\n", n, ( float ) n / 2 );*/
		            break;

		    case 3: printf( "\n   Introduzca un n%cmero entero: ", 163 );
		            /*scanf( "%d", &n );
		            printf( "\n   El cuadrado de %d es %d\n\n", n, ( int ) pow( n, 2 ) );*/
		 }

	    } while ( option != 11 );

	    return 0;
    

    //send_empty_command(fd, BRIDGE_CREATE_Q);                    //Create a queue
    //write_message(fd, BRIDGE_W_HIGH_PRIOR_Q, message);		//Send message with high priority
    //write_message(fd, BRIDGE_W_MIDDLE_PRIOR_Q, message);	//Send message with middle priority
    //write_message(fd, BRIDGE_W_LOW_PRIOR_Q, message);		//Send message with low priority
    //read_message(fd, BRIDGE_R_HIGH_PRIOR_Q, message);		//Read a message with high priority
    //read_message(fd, BRIDGE_R_MIDDLE_PRIOR_Q, message);		//Read a message with middle priority
    //read_message(fd, BRIDGE_R_LOW_PRIOR_Q, message);		//Read a message with low priority
    //send_empty_command(fd, BRIDGE_STATE_Q);			//Get an int indicating the state of the queue
    //send_empty_command(fd, BRIDGE_DESTROY_Q);			//Destroy a queue completely releasing memory (IMPORTANT!!)

    //send_empty_command(fd, BRIDGE_CREATE_S);                   	//Create a stack
    //write_message(fd, BRIDGE_W_S, "Message WS");		//Write a message in the stack
    //read_message(fd, BRIDGE_R_S, message);			//Read a message from the stack
    //send_empty_command(fd, BRIDGE_STATE_S);			//Get an int indicating the statte of the stack
    //send_empty_command(fd, BRIDGE_DESTROY_S);			//Destroy a stack completely releasing the memory (IMPORTANT!!)

    //send_empty_command(fd, BRIDGE_CREATE_L);                    //Create a list
    //write_message(fd, BRIDGE_W_L, message);			//Write a message in the last position of a list
    //read_message(fd, BRIDGE_R_L, message);			//Read a message of the last position of a list
    //send_empty_command(fd, BRIDGE_INVERT_L);			//Invert the order of the elements of a list
    //write_int(fd, BRIDGE_ROTATE_L, &value);			//Rotate a list value position to the right
    //send_empty_command(fd, BRIDGE_CLEAN_L);			//Eliminate repeated elements in a list
    //read_message(fd, BRIDGE_GREATER_VAL_L, message);		//Find the greater value of a list of strings
    //printf("Value obtained: %s\n", message);
    //send_empty_command(fd, BRIDGE_END_L);			//End a list (to be able to create another list) (Module limited to at most three list)
    //send_empty_command(fd, BRIDGE_CONCAT_L);			//Concatenate two previous list in a third new one
    //send_empty_command(fd, BRIDGE_STATE_L);			//Get an int indicating the state of a list
    //send_empty_command(fd, BRIDGE_DESTROY_L);			//Destroy all the list of the module releasing memory (IMPORTANT!!)
    
    //struct complex_struct tmp;
    //strcpy((tmp.messages)[0],"Complex struct message 1");
    //strcpy((tmp.messages)[1], "Complex struct message 2");
    //strcpy((tmp.messages)[2], "Complex struct message 3");
    //tmp.value = 3;
    //write_struct(fd, BRIDGE_W_CS, &tmp);
    //write_several_messages(fd);
    //read_all_messages(fd, BRIDGE_R_S, BRIDGE_STATE_S);
    
    
    close (fd);
    return 0;
}
