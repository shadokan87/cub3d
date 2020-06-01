#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *test(char *str)
{
    char *return_value;
    int i;
    int y;

    i = 0;
    y = 0;
    if (!(return_value = malloc(sizeof(char) * strlen(str))))
        return (0);
    while (str[i])
    {
        if (!(str[i] && str[i] == ' ' && str[i - 1] == ' '))
       {
        return_value[y] = str[i];
        y++;
       }
       i++;
    }
   printf("%s", return_value);
    return (return_value);
}

int main(void)
{
    char *str = strdup("test    test                   test                                                                              ");
    str = test(str);
   //printf("%s", str);
}