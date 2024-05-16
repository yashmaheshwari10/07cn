#include <stdio.h>
#include <string.h>

char flag[] = {'0', '1', '1', '1', '1', '1', '1', '0'};
#define s 50

void receiver(char data[])
{
    char res[s];
    int z, j, k = 0;
    int count = 0;
    for (int i = 0; i < strlen(data); i++)
    {
        count = 0;
        if (data[i] == '0')
        {
            count++;
            for (j = i + 1; j < i + 8; j++)
            {
                if (data[j] == '1')
                {
                    count++;
                }
                else
                {
                    break;
                }
            }
        }
        if (count == 7)
        {
            i = j;
        }
        else
        {
            res[k++] = data[i];
        }
    }
    res[strlen(data) - 16] = '\0';
    printf("Data after Flag bytes dropped by reciever: %s\n", res);
    k = 0;
    int count1 = 0;
    for (int i = 0; i < strlen(res); i++)
    {
        count = 0;

        if (res[i] == '0')
        {
            data[k++] = res[i];
            for (int j = i + 1; j < i + 7; j++)
            {
                if (res[j] == '1')
                {
                    data[k++] = res[j];
                    count++;
                }
                else
                {
                    break;
                }
            }
        }

        if (count == 5)
        {
            i = j;
            count1++;
        }
        else
        {
            data[k++] = res[i];
        }
    }
    data[strlen(res) - count1] = '\0';
    printf("Orignal Data recieved: %s\n", data);
}

int main()
{
    char data[s];
    char data1[s];
    printf("Enter the data: ");
    scanf("%s", &data);
    data[strlen(data)] = '\0';

    // after zero --continous five 1's stuff zero.
    int count = 0;
    int count1 = 0;
    int k = 0;
    for (int i = 0; i < strlen(data); i++)
    {

        data1[k++] = data[i];
        if (data[i] == '0')
        {
            count = 0;
            for (int j = i + 1; j < i + 6; j++)
            {
                data1[k++] = data[j];
                if (data[j] == '1')
                {
                    count++;
                    if (count == 5)
                    {
                        count1++;
                        data1[k++] = '0';
                    }
                }
                else
                {
                    i = j;
                    break;
                }
                i = j;
            }
        }
    }
    data1[strlen(data) + count1] = '\0';
    printf("Data after stuffing 0's: %s \n", data1);

    // flag.
    for (int i = 0; i < strlen(data1) + 16; i++)
    {
        if (i < 8)
        {
            data[i] = flag[i];
        }
        else if (i > strlen(data1) + 7)
        {
            data[i] = flag[i - strlen(data1) - 8];
        }
        else
        {
            data[i] = data1[i - 8];
        }
    }

    data[strlen(data1) + 16] = '\0';
    printf("Final Data to be sent: %s\n", data);

    receiver(data);
}
