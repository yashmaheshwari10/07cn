#include <stdio.h>
#include <string.h>

char data[100];     // to store data entered by user
char prepData[400]; // to store data to be transmitted to from sender to receiver

char flag[8] = {'0', '1', '1', '1', '1', '1', '1', '0'};
char esc[6] = {'1', '1', '0', '1', '1'};

int i = 0; // for tracking each bit of data
int j = 0; // for keeping track of prepData

// check function to check if data is flag or esc or none

// checking if data is flag or not
int isFlag(char data[], int i)
{
    int count = 0;
    for (int k = 0; k < 8; k++)
    {
        if (data[i+k] == flag[k])
        {
            count++;
        }
    }
    if (count == 8)
    {
        i += 8;
        return 1;
    }
    return 0;
}
// checking if daa is flag or not
int isEsc(char data[], int i)
{
    int count = 0;
    for (int k = 0; k < 5; k++)
    {
        if (data[i+k] == esc[k])
        {
            count++;
        }
    }
    if (count == 5)
    {
        i += 5;
        return 1;
    }
    return 0;
}

void sender()
{
    // take data from user
    printf("Enter the data :");
    scanf("%s", data);

    i =0;
    j= 0;
    // prepare data to trasmit from users data

    while (i < strlen(data))
    {
        // if there is flag in the data append esc and then flag to prep data
        if (isFlag(data, i) == 1)
        {

            // Appending esc
            for (int k = 0; k < 5; k++)
            {
                prepData[j] = esc[k];
                j++;
            }
            // Appending flag
            for (int k = 0; k < 8; k++)
            {
                prepData[j] = flag[k];
                j++;
            }
        }
        // if there is esc in the data append esc and esc  to prep data
        else if (isEsc(data, i) == 1)
        {
            // append esc esc to prep data

            // Appending esc
            for (int k = 0; k < 5; k++)
            {
                prepData[j] = esc[k];
                j++;
            }
            // Appending esc
            for (int k = 0; k < 5; k++)
            {
                prepData[j] = flag[k];
                j++;
            }
        }
        else
        {
            prepData[j] = data[i];
            i++;
            j++;
        }
    }
    prepData[j] = '\0';
    printf("\nEnterd Data : %s", data);
    printf("\nPrepared Data : %s", prepData);
}
int main()
{
    sender();
    return 0;
}