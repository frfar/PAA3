#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <cerrno>
#include <sys/types.h>
#include <string.h>
using namespace std;

//changes made
char state;
int cya;

void dispVersion(){
	cout << "The current version is 1.2\n";
}
// This is the number that will hold our inputs that will be coming into the system command line.
int numb = 500;
string bash = "FarzinGO> ";


void didi(char** argg, char** TheFile) {
  
  int numberofD;    
  char v;  
   int lolo;   
  pid_t pid;
   int descriptor[2];
  pipe(descriptor);

  if (fork() == 0) {
   
    numberofD = open(TheFile[0], O_RDWR | O_CREAT, 0666);

    dup2(descriptor[0], 0);

    close(descriptor[1]);
	
    while ((lolo = read(0, &v, 1)) > 0){
      write(numberofD, &v, 1); 
	//cout << "it works\n";
	}

    execlp("echo", "echo", NULL);

  } else if ((pid = fork()) == 0) {
    dup2(descriptor[1], 1);

    close(descriptor[0]);

    execvp(argg[0], argg);
    perror("the execution didn't go through");

  } else {
	waitpid(pid, NULL, 0);
	
	
	
    close(descriptor[0]);
    close(descriptor[1]);
  }
}


int aa(char **argv) {
  char *cstr;
  string arg;
  int cya = 0;

  while ((cin >> arg)  ){

    cstr = new char[arg.size()+1];
    strcpy(cstr, arg.c_str());
    argv[cya] = cstr;

    cya++;

    if (cin.get() == '\n')
		break;
  }

  argv[cya] = NULL;

  return cya;
}

void multiTask(char** argii, char** argiii) {
  int descriptors[2]; 
  pipe(descriptors);
  pid_t pid;
int j = fork();
pid =j;
  if (fork() == 0) {
    dup2(descriptors[0], 0);

    close(descriptors[1]);

    execvp(argiii[0], argiii);
    perror("The execution didn't go through");

  } else if ((pid= fork())==0) {
    dup2(descriptors[1], 1);

    close(descriptors[0]);

    execvp(argii[0], argii);
    perror("The execution didn't go through");

  } else
    waitpid(pid, NULL, 0);
}

void pipingIt(char** argOne, char** argTwo){
           int descriptors[2];
           pipe(descriptors);
			pid_t pidOne, pidTwo;

           // child process #1
           if ((pidOne = fork()) == 0) {
                dup2(descriptors[1], 1);
		close(descriptors[0]);
		close(descriptors[1]);
                execvp(argOne[0], argOne);
                perror("execution failed");

                // child process #2
                } else if ((pidTwo = fork()) == 0) {
                  dup2(descriptors[0], 0);

                  close(descriptors[1]);
                  execvp(argTwo[0], argTwo);
                  perror("execution failed failed");


            } else {
    	close(descriptors[1]);

    	waitpid(pidOne, NULL, 0);
	waitpid(pidTwo, NULL, 0);
    	
		}
}

char figureArgs(char** argv, int cya, char** argg, char** arggg) {
  int p = 0;
char res;

  for (int x=0; x<cya; x++) {
   
    if (strcmp(argv[x], "|") == 0) {
      res = 'p';
      p = x;

    } else if (strcmp(argv[x], ">>") == 0) {
      res = 'r';
      p = x;
    }else if (strcmp(argv[x], ">") == 0) {
      res = 'r';
      p = x;
    }else if (strcmp(argv[x], "<") == 0) {
      res = 'r';
      p = x;
    }else if (strcmp(argv[x], ";") == 0) {
      res = 's';
      p = x;


    }
  }

  if ((res == 'p') || (res == 'r') || (res == 's')) {

    for (int x=0; x<p; x++)
      argg[x] = argv[x];

    int keepTrack = 0;
    for (int x=p+1; x<cya; x++) {
      arggg[keepTrack] = argv[x];
      keepTrack++;
    }

   argg[p] = NULL;
    arggg[keepTrack] = NULL;
  }

  return res;
}


void RunIt(char** argv) {
  pid_t pid;

  pid = fork();

  if (pid < 0)
    perror("Error (pid < 0)");

  else if (pid == 0) {
  
    execvp(argv[0], argv);
    perror("execvp error");

  } else
    waitpid(pid, NULL, 0); 
}


int main() {
  dispVersion();
	char *argv[numb], *argg11[numb], *arggg22[numb];
  while (1==1) {
    cout << bash;

    cya = aa(argv);

    state = figureArgs(argv, cya, argg11, arggg22);

    if (state == 'p')          
      pipingIt(argg11, arggg22);
    else if (state == 'r') 
      didi(argg11, arggg22);
    else
      RunIt(argv);              

    for (int x=0; x<cya; x++)
      argv[x] = NULL;
  }

 
  return 0;
}
