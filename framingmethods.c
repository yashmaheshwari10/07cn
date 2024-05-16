// // 1)  IMPLEMENT FOLLOWING FRAMING METHODS
// // 1. BYTE COUNT
// // Code:
// #include <stdio.h>
// #include <string.h>
// #define S 20

// int data2[S];

// void sender()
// {
//     int data1[S];
//     int data;
//     int data_len = 0, i = 0;
//     int last_digit;
//     printf("Enter Data:");
//     scanf("%d", &data);

//     while (data != 0)
//     {
//         last_digit = data % 10;
//         data = data / 10;
//         data1[i++] = last_digit;
//         data_len++;
//     }
//     data2[0] = data_len + 1;
//     int k = 1;
//     for (int i = data_len - 1; i >= 0; i--)
//     {
//         data2[k++] = data1[i];
//     }

//     printf("Enter sender's data:");
//     for (int i = 0; i < data_len + 1; i++)
//     {
//         printf("%d", data2[i]);
//     }
//     printf("\n");
// }

// void receiver(int data[])
// {
//     char rev_data[S];
//     int data_sz = data[0];
//     int j = 0;
//     for (int i = 1; i < data_sz; i++)
//     {
//         rev_data[j++] = data[i];
//     }
//     printf("Original received data: ");
//     for (int i = 0; i < data_sz - 1; i++)
//     {
//         printf("%d", rev_data[i]);
//     }
//     printf("\n");
// }
// int main()
// {
//     sender();
//     receiver(data2);
// }

// 2. FLAG BYTE WITH BYTE STUFFING
//     Code :
// flag bytes with byte stuffing Framing Method
#include <stdio.h>
#include <string.h>
#define S 100

char flag[] = {'0', '1', '1', '1', '1', '1', '1', '0'};
char esc[] = {'0', '0', '0', '1', '1', '0', '1', '1'};

void reciever(char data[])
{
    char res[S];
    int count = 0, count1 = 0, j = 0, k = 0, l = 0, p = 0;
    while (1)
    {
        int isFlag = 0, isEsc = 0;
        for (int i = 0; i < 8; i++)
        {
            if (data[j + i] == flag[i])
            {
                isFlag = 1;
            }
            else
            {
                isFlag = 0;
                break;
            }
        }
        for (int m = 0; m < 8; m++)
        {
            if (data[j + m] == esc[m])
            {
                isEsc = 1;
            }
            else
            {
                isEsc = 0;
                break;
            }
        }
        if (isFlag == 1 && count1 == 0)
        {
            count++;
            l++;
        }
        else if (isEsc == 1 && count1 == 0)
        {

            count1++;
            l++;
        }
        else
        {
            for (int i = 0; i < 8; i++)
            {
                res[p++] = data[j + i];
            }
            count1 = 0;
        }
        j += 8;
        if (count == 2)
        {
            break;
        }
    }
    res[strlen(data) - l * 8] = '\0';
    printf("Original Data is %s", res);
}

int main()
{
    char data[S];
    char data1[S];
    char data2[S];

    printf("Enter Data:");
    scanf("%s", data);
    data[strlen(data)] = '\0';

    // covert bits to bytes by appending leading zero's
    int c_bytes;
    if (strlen(data) % 8 == 0)
    {
        c_bytes = strlen(data) / 8;
        for (int i = 0; i < c_bytes * 8; i++)
        {
            data1[i] = data[i];
        }
        data1[c_bytes * 8] = '\0';
    }
    else
    {
        c_bytes = (strlen(data) / 8) + 1;
        for (int i = 0; i < (c_bytes * 8) - strlen(data); i++)
        {

            data1[i] = '0';
        }
        int j = 0;
        for (int i = (c_bytes * 8) - strlen(data); i < c_bytes * 8; i++)
        {
            data1[i] = data[j++];
        }
        data1[c_bytes * 8] = '\0';
    }
    printf("Data is of %d bytes.\n", c_bytes);
    printf("Data Converted in Bytes format: %s\n", data1);

    // append esc if data bits are equal to flag or esc key
    int j = 0, k = 0, count1 = 0;
    int count = c_bytes;
    while (1)
    {
        int isFlag = 1, isEsc = 1;
        for (int i = 0; i < 8; i++)
        {
            if (data1[j + i] != flag[i])
            {
                isFlag = 0;
                break;
            }
        }

        for (int m = 0; m < 8; m++)
        {
            if (data1[j + m] != esc[m])
            {
                isEsc = 0;
                break;
            }
        }
        if (isFlag == 1 || isEsc == 1)
        {
            count1++;
            for (int i = 0; i < 8; i++)
            {
                data2[k++] = esc[i];
            }
        }
        for (int l = 0; l < 8; l++)
        {
            data2[k++] = data1[j++];
        }
        count--;
        if (count == 0)
        {
            break;
        }
    }
    data2[strlen(data1) + count1 * 8] = '\0';
    printf("Data after inserting Esc key if data having flag or Esc byte: %s\n", data2);

    // create final data by appending flag at both ends
    for (int i = 0; i < 8; i++)
    {
        data1[i] = flag[i];
    }
    for (int i = 0; i < strlen(data2); i++)
    {
        data1[8 + i] = data2[i];
    }
    for (int i = 0; i < 8; i++)
    {
        data1[8 + strlen(data2) + i] = flag[i];
    }
    data1[16 + strlen(data2)] = '\0';
    printf("Final data to be sent: %s\n", data1);

    reciever(data1);
    return 0;
}

// // 3. FLAG BYTE WITH BIT STUFFING
// //     Code :
// #include <stdio.h>
// #include <string.h>

// char flag[] = {'0', '1', '1', '1', '1', '1', '1', '0'};
// #define s 50

// void receiver(char data[])
// {
//     char res[s];
//     int z, j, k = 0;
//     int count = 0;
//     for (int i = 0; i < strlen(data); i++)
//     {
//         count = 0;
//         if (data[i] == '0')
//         {
//             count++;
//             for (j = i + 1; j < i + 8; j++)
//             {
//                 if (data[j] == '1')
//                 {
//                     count++;
//                 }
//                 else
//                 {
//                     break;
//                 }
//             }
//         }
//         if (count == 7)
//         {
//             i = j;
//         }
//         else
//         {
//             res[k++] = data[i];
//         }
//     }
//     res[strlen(data) - 16] = '\0';
//     printf("Data after Flag bytes dropped by reciever: %s\n", res);
//     k = 0;
//     int count1 = 0;
//     for (int i = 0; i < strlen(res); i++)
//     {
//         count = 0;

//         if (res[i] == '0')
//         {
//             data[k++] = res[i];
//             for (int j = i + 1; j < i + 7; j++)
//             {
//                 if (res[j] == '1')
//                 {
//                     data[k++] = res[j];
//                     count++;
//                 }
//                 else
//                 {
//                     break;
//                 }
//             }
//         }

//         if (count == 5)
//         {
//             i = j;
//             count1++;
//         }
//         else
//         {
//             data[k++] = res[i];
//         }
//     }
//     data[strlen(res) - count1] = '\0';
//     printf("Orignal Data recieved: %s\n", data);
// }

// int main()
// {
//     char data[s];
//     char data1[s];
//     printf("Enter the data: ");
//     scanf("%s", &data);
//     data[strlen(data)] = '\0';

//     // after zero --continous five 1's stuff zero.
//     int count = 0;
//     int count1 = 0;
//     int k = 0;
//     for (int i = 0; i < strlen(data); i++)
//     {

//         data1[k++] = data[i];
//         if (data[i] == '0')
//         {
//             count = 0;
//             for (int j = i + 1; j < i + 6; j++)
//             {
//                 data1[k++] = data[j];
//                 if (data[j] == '1')
//                 {
//                     count++;
//                     if (count == 5)
//                     {
//                         count1++;
//                         data1[k++] = '0';
//                     }
//                 }
//                 else
//                 {
//                     i = j;
//                     break;
//                 }
//                 i = j;
//             }
//         }
//     }
//     data1[strlen(data) + count1] = '\0';
//     printf("Data after stuffing 0's: %s \n", data1);

//     // flag.
//     for (int i = 0; i < strlen(data1) + 16; i++)
//     {
//         if (i < 8)
//         {
//             data[i] = flag[i];
//         }
//         else if (i > strlen(data1) + 7)
//         {
//             data[i] = flag[i - strlen(data1) - 8];
//         }
//         else
//         {
//             data[i] = data1[i - 8];
//         }
//     }

//     data[strlen(data1) + 16] = '\0';
//     printf("Final Data to be sent: %s\n", data);

//     receiver(data);
// }