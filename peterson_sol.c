#include<pthread.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
//function for process 1
void* func1(void *fd);

//function for porcess 2
void* func2(void *fd);
int flag[2];
int turn=0;

int main()
{   
    //char for process 1 in file
	char buff[20] = "hello world";
	//char for process 2 in file
	char buff1[20] = "HELLO WORLD";
	
	//open file 
	int rd = open("abd.txt",O_CREAT | O_WRONLY);
	//rd returns -1 when there is an error.
	if(rd == -1){
		printf("AN ERROR OCCURED \n");
	}
	
	int *fd;
	fd = &rd;
	
	//pthread created for two different process.
    pthread_t t1,t2;
    pthread_create(&t1,NULL,func1,(void *)fd);
    pthread_create(&t2,NULL,func2,(void *)fd);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

}

//defination of process1
void *func1(void *fd)
{
    int i=0;
    while(i<2)
    {   
    	//peterson solution concept
        flag[0]=1;
        turn=1;
        while(flag[1]==1 && turn==1);
        
        //critical Section starts
		int sd = &fd;
		//write in the file.
      	write(sd,"hello world \n",20);
      	//write on the screen (File Descriptor = 1 is used to write).
      	write(1,"hello world \n",20);
      	//critical section
      	
        flag[0]=0;
        i++;
    }
}
void *func2(void *fd)
{
    int i=0;
    while(i<2)
    {
    	//peterson solution concept
        flag[1]=1;
        turn=0;
        while(flag[0]==1 && turn==0);
       	
		//critical section   
		int sd = &fd;
		//write into the file.
       	write(sd,"HELLO WORLD \n",20);
       	//write on the screen (File Descriptor = 1 is used to write)
       	write(1,"HELLO WORLD \n",20);
       	//critical section ends
       	
        flag[1]=0;
        i++;
    }
}
