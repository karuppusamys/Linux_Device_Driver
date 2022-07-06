#include <stdio.h>  
#include <unistd.h>

int main()  
 {  
      pid_t pid;  
      printf("Parent\n");  
      pid = vfork();  
      if(pid==0)  
      {  
          printf("Child\n");  
      }  
      return 0;  
}
