#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(){
    int fd[2];
    int ret=pipe(fd);
    //pid_t pid_1,pid_2,wait1;

    if(ret<0){
        perror("pipe");
        return 0;
    }
    //创建进程
    pid_t pid_1=fork();
    if(pid_1<0){
        perror("forkSon1 error");
        return 0;
    }else if(0==pid_1){   //子进程1
        //子进程进行接受
        char buf_read[1024]={0};
        read(fd[0],buf_read,sizeof(buf_read)-1);
        printf("This is processB\n");
        printf("The content is :%s\n",buf_read);
        
    }else{
        pid_t pid_2=fork();
        if(pid_2<0){
            printf("forkSon2 error");
            exit(1);
        }
        if(0==pid_2){    //子进程2
            //子进程进行接受
            char buf_read2[1024]={0};
            read(fd[0],buf_read2,sizeof(buf_read2)-1);
            printf("This is processC\n");
            printf("The content is :%s,too\n",buf_read2);
        }else{
            //父进程发送数据
            char buf_write[]="success!";
            write(fd[1],buf_write,strlen(buf_write));
            wait(NULL);//等待子进程结束
            printf("This is processA\n");//父进程
        }
    }
    return 0;
}










#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
 
int main(){
    int fd[2];
    int ret=pipe(fd);
    if(ret<0){
        perror("pipe");
        return 0;
    }
    pid_t pid=fork();
    if(pid<0){
        perror("fork");
        return 0;
    }else if(pid==0){
        //child
        //子进程进行接受
        close(fd[1]);
        char buf_read[1024]={0};
        read(fd[0],buf_read,sizeof(buf_read)-1);
        printf("The content is :%s\n",buf_read);
    }else{
        //father
        //父进程发送数据
        close(fd[0]);
        char buf_write[]="success!";
        write(fd[1],buf_write,strlen(buf_write));
        wait(NULL);
    }
    return 0;
}




#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include <string.h>
int main(){
pid_t pid_1,pid_2,wait1;
pid_1=fork();
if(pid_1<0){
    printf("fork1 error\n");
    exit(1);
    }
else if(0==pid_1){   //子进程1
    printf("B");
    }
else{
    pid_2=fork();
    if(pid_2<0){
        printf("fork2 error\n");
        exit(1);
    }
    if(0==pid_2){    //子进程2
        printf("C");
    }
    else{
        wait1 = wait(NULL);//等待子进程结束
        printf("A");//父进程
                      //
      }
    }
    return 0;
}
     