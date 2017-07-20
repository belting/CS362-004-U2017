#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#define FIRST_CHAR 31
#define NUM_CHARS 96
#define STR_LENGTH 5
#define NULL_CHAR '\0'
#define FIRST_STR_CHAR 'e'
#define NUM_STR_CHARS 16

char randomStringChar()
{
    return FIRST_STR_CHAR + floor((double)rand() / (double)RAND_MAX * NUM_STR_CHARS);
}

char inputChar()
{
    char randomChar = FIRST_CHAR + floor((double)rand() / (double)RAND_MAX * NUM_CHARS);

    if (randomChar == FIRST_CHAR) {
        return NULL_CHAR;
    }
    
    return randomChar;
}

char *inputString()
{
    int i;
    char *str = malloc((STR_LENGTH + 1) * sizeof(char));

    for (i = 0; i < STR_LENGTH; i++) {
        str[i] = randomStringChar();
    }
    
    str[STR_LENGTH] = NULL_CHAR;

    return str;
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

    free(s);
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
