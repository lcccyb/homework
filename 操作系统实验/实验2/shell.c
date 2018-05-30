#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINE 80
#define BUFFER_SIZE 50

 /* 每次输入的命令规定不超过80个字符 */
/* * setup() 用于读入下一行输入的命令，并将它分成没有空格的命令和参数存于数组args[]中，
 * 用NULL作为数组结束的标志 
 */

int pos = 0; // 下一个指令存放的下标
char* history[10][MAX_LINE/2+1]; // 存放历史记录
int CommandLength[10] = {0}; // 标识指令的长度

/*
 * setup() 用于读入下一行输入的命令，并将它分成没有空格的命令和参数存于数组args[]中，
 * 用NULL作为数组结束的标志 
 */
void setup(char inputBuffer[], char *args[], int *background) {
    int length; /* 命令的字符数目 */
    int i;      /* 循环变量 */
    int start;  /* 命令的第一个字符位置 */
    int ct;     /* 下一个参数存入args[]的位置 */

    ct = 0;

    /* 读入命令行字符，存入inputBuffer */
    length = read(STDIN_FILENO, inputBuffer, MAX_LINE);

    start = -1;

    /* 输入ctrl+d，结束shell程序 */
    if(length == 0) {
        exit(0);
    }

    else if(length < 0) {
        perror("error reading the command");
        /* 出错时用错误码-1结束shell */
        exit(-1);
    }

    else {
        /* 检查inputBuffer中的每一个字符 */
        for(i = 0; i < length; i++) {
            switch(inputBuffer[i]) {

                case ' ':
                case '\t':  /* 字符为分割参数的空格或制表符(tab)'\t'*/
                    if(start != -1) {
                        args[ct] = &inputBuffer[start];
                        ct++;
                    }
                    inputBuffer[i] = '\0';   /* 设置 C string 的结束符 */
                    start = -1;
                    break;
                
                case '\n':        /* 命令行结束 */
                    if(start != -1) {
                        args[ct] = &inputBuffer[start];
                        ct++;
                    }
                    inputBuffer[i] = '\0';
                    args[ct] = NULL;  /* 命令及参数结束 */
                    break;

                default:  /* 其他字符 */
                    if(start == -1) {
                        start = i;
                    }
                    if (inputBuffer[i] == '&'){  
		                *background  = 1;          /*置命令在后台运行*/
                        inputBuffer[i] = '\0';
		            }
            }
        }
    }
    args[ct] = NULL;    
}

int main(void) {
    char inputBuffer[MAX_LINE]; /* 这个缓存用来存放输入的命令*/
    int background;             /* ==1时，表示在后台运行命令，即在命令后加上'&' */
    char *args[MAX_LINE/2+1];/* 命令最多40个参数 */
    
    while (1) {            /* 程序在setup中正常结束*/
	    background = 0;
 	    printf("COMMAND->"); //输出提示符，没有换行，仅将字符串送入输出缓存
        fflush(stdout);                              //若要输出输出缓存内容用fflush(stdout);头文件stdio.h

        setup(inputBuffer, args, &background);       /* 获取下一个输入的命令 */

	/* 这一步要做:
	 (1) 用fork()产生一个子进程
	 (2) 子进程将调用execvp()执行命令,即 execvp(args[0],args);
	 (3) 如果 background == 0, 父进程将等待子进程结束, 即if(background==0) wait(0);
	       否则，将回到函数setup()中等待新命令输入.
	*/  

        pid_t pid;
        pid = fork();
        //创建子进程失败
        if (pid < 0) {
            fprintf(stderr, "Fork Failed");
            exit(-1);
        }
        //子进程调用execvp()执行命令
        else if (pid == 0) {
            execvp(args[0], args);
        }
        //父进程等待子进程结束
        else if (background == 0) {
            wait(0);
        }
    }
}