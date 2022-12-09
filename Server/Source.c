#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#define SIZE_BUFFER 140
BOOL checkClient(LPSTR str)
{
    for (size_t i = 0; *(str + i) != '\0'; i++)
    {
        if (*(str + i) < '0' || *(str + i) > '9')
        {
            return FALSE;
        }
    }

    return TRUE;
}

int main()
{
    //������ ������� �����
    system("chcp 1251 > null");
    HANDLE hPipe; //���������� ����������� ������
    LPSTR lpstPipeName = L"\\\\.\\pipe\\MyPipe"; // ����������, ���������� ��� ������   
    LPWSTR buffer = (CHAR*)calloc(SIZE_BUFFER, sizeof(CHAR)); // ��������� ���������, � ������� ����� ������� �����
    char message[SIZE_BUFFER]; // ������ ���������
    BOOL Connected;
    DWORD actual_readen; // ������� �� ����� ���� ���� ��������� ����
    //������ �� ������
    LPWSTR b = (CHAR*)calloc(SIZE_BUFFER, sizeof(CHAR));
    LPWSTR zero = (CHAR*)calloc(SIZE_BUFFER, sizeof(CHAR));
    while (TRUE)
    {
        HANDLE hPipe = CreateNamedPipe( // �������� ������
            lpstPipeName, // ��� ������ - ����
            // � ��������� � ����������
            PIPE_ACCESS_DUPLEX, // ���� ������� � ������ (�������������/������������)
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, // ����� ������ ������: ���������� ���������| ������ �������� | �����
            PIPE_UNLIMITED_INSTANCES, // �������� �� ������� ���������� � ������, � ������ ������ �����.
            SIZE_BUFFER, // ����� ������ ��� ������ (����)
            SIZE_BUFFER, // ����� ������ ��� ������ (����)
            INFINITE, // ������������ ����� �������� ��������� - ����� �� �����
            NULL // ��������� �� ��������� ������������
        );
        Connected = ConnectNamedPipe(hPipe, NULL); // ��������� � ��������� ������� � �������
        if (Connected) // ���� ������ �����������
        {
            printf("\n������ ������� ���������\n");

            if (ReadFile(hPipe, buffer, SIZE_BUFFER, &actual_readen, NULL))
            {
                //// ����� �����������
                //printf("\n������ �����: ");
                //printf(buffer);

                //printf("\n���������: ");
                //gets(message);
                //buffer = &message;
                //WriteFile(hPipe, buffer, SIZE_BUFFER, &actual_readen, NULL);

                // ���������� � �������
                printf("\n������ �����: \n");
                printf(buffer);// ����� �� ����� ������������ ���������
                printf("\n");
                 
                if (checkClient(buffer))
                {
                    int number = atoi(buffer);
                    sprintf(message, "%d", number * number);
                    buffer = &message;
                    WriteFile(hPipe, buffer, SIZE_BUFFER, NULL, NULL);
                }
                else
                {
                    WriteFile(hPipe, "����� ������� �����������", SIZE_BUFFER, &actual_readen, NULL);
                }
             
            }


        }
        else
        {
            printf("\n������ ���������� �� �������\n");
        }
        CloseHandle(hPipe); // ��������� �����

    }
}