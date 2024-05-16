#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N strlen(crc_key)

void sender();
void receiver();
void error();
void crc(char data[]);

// Declerations
char data[50];    // Char Array for data
char crc_key[20]; // Char array for crc key
int data_len;
int i, j;
char chk_val[50]; // Stores the remainder during the CRC function.
int ch;

void crc(char data[])
{
    char remainder[N + 1]; // To store the remainder during CRC calculations.
    for (i = 0; i < N; i++)
        chk_val[i] = data[i];

    i = N;

    do
    {

        if (chk_val[0] == '1')
        {
            // XOR with CRC key.
            for (j = 1; j < N; j++)

                chk_val[j] = ((chk_val[j] == crc_key[j]) ? '0' : '1');
        }

        // Shifting to left
        for (j = 0; j < N - 1; j++)
        {
            chk_val[j] = chk_val[j + 1];
        }
        chk_val[j] = data[i++];
        printf("Remainder%d: %s\n", i - N, chk_val);
    } while (i <= data_len + N - 1);
}

void sender()
{
    printf("\nEnter data : ");
    scanf("%s", data);
    data_len = strlen(data); // Storing the length of initial data.
    printf("\nEnter the crc key: ");
    scanf("%s", crc_key);
    for (i = data_len; i < (data_len + N - 1); i++)
    {
        data[i] = '0';
    }
    data[data_len + N - 1] = '\0';
    printf("\nAppended data with N-1 0s: %s", data);
    printf("\n\n");

    // Performing CRC function
    crc(data);

    printf("\n\nCRC or Check value is : %s", chk_val);
    for (i = data_len; i < data_len + N - 1; i++)
    {
        data[i] = chk_val[i - data_len];
    }

    printf("\nFinal data to be sent : %s", data);
    printf("\n");
}

void receiver()
{
    char receivedData[50];
    strcpy(receivedData, data);
    printf("\nChecking data\n");
    crc(receivedData);
    // Checking weather the final remainder is all '0' or not if '1' found error detected.
    for (int k = 0; k < strlen(crc_key); k++)
    {
        if (chk_val[k] == '1')
        {
            printf("\nError detected. Data corrupted.\n");
            return; // No need to go further just return
        }
    }
    printf("\nData received: %s", receivedData);
}

void error()
{
    int errorPos;
    printf("\nEnter position to add error : ");
    scanf("%d", &errorPos);
    data[errorPos] = (data[errorPos] == '1') ? '0' : '1';
}

int main()
{
    do
    {
        printf("\n\n1) Without error\n2) With error\n3) Exit");
        printf("\nEnter your choice:");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
        {
            sender();
            receiver();
            break;
        }
        case 2:
        {
            sender();
            error();
            receiver();
            break;
        }
        case 3:
        {
            exit(0);
            break;
        }
        default:
        {
            break;
        }
        }
    } while (ch < 4 && ch > 0);
    return 0;
}