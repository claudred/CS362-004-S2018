#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
  char char_array[]={'r', 'e', 's', 't','a','x', '[', '(', '{', ' ', '}', ')', ']'};
  int totalSize=sizeof(char_array);
  int rand_index=rand() % (totalSize);
  return char_array[rand_index];
}

char *inputString()
{
  int rand_string_size=6;
  char rand_string[rand_string_size];
  int i;
  for (i=0; i<rand_string_size-1; i++)
  {
    rand_string[i]=inputChar();
  }
  rand_string[rand_string_size-1]='\0';
  char *returnme=rand_string;
  return returnme;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}

