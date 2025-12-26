#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
int main(int c, char** v) { 
  int p[2], n; 
  char s[10] = "ceva"; 
  pipe(p); 
  n = fork(); 
  if(n == 0) { 
    close(p[0]); 
    printf("înainte\n"); 
    if(c > 2) 
      execlp("grep","grep",v[1],v[2],NULL); 
    strcpy(s, "dup "); 
    write(p[1], s, 6); 
    close(p[1]); 
    exit(0); 
  } 
  close(p[1]); 
  read(p[0], s, 6); 
  close(p[0]); 
  printf("%s\n", s); 
  return 0; 
}

