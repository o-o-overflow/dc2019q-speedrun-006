#include <sys/mman.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 1

char clean[] = "\x48\x31\xed\x48\x31\xe4\x48\x31\xc0\x48\x31\xdb\x48\x31\xc9\x48\x31\xd2\x48\x31\xf6\x48\x31\xff\x4d\x31\xc0\x4d\x31\xc9\x4d\x31\xd2\x4d\x31\xdb\x4d\x31\xe4\x4d\x31\xed\x4d\x31\xf6\x4d\x31\xff";

typedef struct challenge {
   char mytime[48];
   char first[5];
   char after_first;
   char second[4];
   char after_second;
   char third[9];
   char after_third;
   char fourth[8];
   char after_fourth;
} challenge;

challenge say_hello()
{
   printf("How good are you around the corners?\n");
}

void shellcode_it(char* buf, unsigned int size)
{

   challenge chall;

   // Set up the challenge from their buf
   memcpy(chall.first, buf, 5);
   memcpy(chall.second, buf+5, 4);
   memcpy(chall.third, buf+9, 9);
   memcpy(chall.fourth, buf+18, 8);

   // put our things in
   chall.after_first = 0xcc;
   chall.after_second = 0xcc;
   chall.after_third = 0xcc;
   chall.after_fourth = 0xcc;

   // put the cleanup code in
   memcpy(chall.mytime, clean, 48);
   
   void *ptr = mmap(0, sizeof(challenge), PROT_EXEC | PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0);
   void (*shell)();
   memcpy(ptr, &chall, sizeof(challenge));

   // Set an alarm
   if (!DEBUG)
   {
	  alarm(5);
   }

   shell = (void (*)()) ptr;
   shell();

   return;
}

void get_that_shellcode()
{
   char buf[27];
   int num;
   printf("Send me your ride\n");
   num = read(0, buf, 26);
   buf[26] = '\0';

   if (num != 26)
   {
	  printf("You ain't ready.\n");
	  return;
   }
   if (strlen(buf) != 26)
   {
	  printf("You're not up to code.\n");
	  return;
   }

   shellcode_it(buf, 26);
}


int main(int argc, char** argv)
{
   setvbuf(stdout, NULL, _IONBF, 0);

   say_hello();
   get_that_shellcode();
}
