#include <unistd.h>
#include <sys/wait.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>

const int READ = 0, WRITE = 1;

int main(int argc , char *argv[]) {

   int pipefd[2];

   if (pipe(pipefd)  == -1) {
      std::cerr << "Error creating pipe\n";
      return 1;
   }
   int pid2 = -1, pid1 = -1;
   pid1 = fork();
   if (pid1 == 0) {
      close (pipefd[READ]);
      dup2(pipefd[WRITE], WRITE);
      //execlp("ls", "ls", "-l", nullptr);
      execlp("ls", "ls", "-l", 0);
   }
   else {
       pid2 = fork();
       if (pid2 == 0) {
           close(pipefd[WRITE]);
           dup2(pipefd[READ], READ);
           //execlp("wc", "wc", "-l", nullptr);
           execlp("wc", "wc", "-l", 0); 
      }
   }
   //waitpid(pid1, nullptr, 0);
     waitpid(pid1, 0, 0);

   close(pipefd[WRITE]);
   //waitpid(pid2, nullptr, 0);
   waitpid(pid1, 0, 0); 
   return 0;
}
