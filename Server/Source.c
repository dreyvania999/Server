#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#define SIZE_BUFFER 140

int main()
{
    system("chcp 1251 > null");
    LPSTR lpstrPipeName = L"\\\\.\\pipe\\MyPipe"; // им€ канала (такое же, как и на севере)
    HANDLE hNamePipe; 
    BOOL flag_otvet = TRUE;
    char message[SIZE_BUFFER]; 
    DWORD actual_written; // сколько на самом деле было записано байт
    LPWSTR buffer = &message; // строкова€ перемена€, значение которой записываетс€ в канал
    DWORD actual_readen; // сколько на самом деле было прочитано байт
    BOOL isSuccess;
    BOOL SuccessRead;
    while (TRUE)
    {

        hNamePipe = CreateFile( // открываем канал. по аналогии с открытием файла
            lpstrPipeName,
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            0,
            NULL
        );
        DWORD dwMode = PIPE_READMODE_MESSAGE; //переключение в режим чтени€ и обратно
        BOOL isSuccess = SetNamedPipeHandleState( //доступен сервер или нет
            hNamePipe,
            &dwMode,
            NULL,
            NULL
        );
        if (!isSuccess)
        {
            printf("\nсервер не отвечает\n");
            flag_otvet = TRUE;
        }
        else
        {
            //чтение сообщений
            LPSTR message = calloc(SIZE_BUFFER, sizeof(CHAR));
            if (flag_otvet)
            {
                printf("—ообщение: ");
                gets(message);
                WriteFile(hNamePipe, message, SIZE_BUFFER, NULL, NULL);
                flag_otvet = FALSE;
            }
            free(message);

            message = calloc(SIZE_BUFFER, sizeof(CHAR));
            if (ReadFile(hNamePipe, message, SIZE_BUFFER, NULL, NULL))
            {
                printf("—ервер: %s\n", message);
                flag_otvet = TRUE;
            }
            free(message);


            //if (flag_otvet)
            //{
            //    printf("\n¬ведите число дл€ сервера:\n");
            //    gets(message);
            //    buffer = &message;
            //    WriteFile(hNamePipe, buffer, SIZE_BUFFER, &actual_written, NULL); // запись в канал
            //    flag_otvet = FALSE;

            //}
            ////читать с серваера
            //SuccessRead = ReadFile(hNamePipe, buffer, SIZE_BUFFER, &actual_readen, NULL);
            //if (SuccessRead)
            //{
            //    printf("\nќтвет:\n");
            //    printf(buffer);
            //    printf("\n");
            //    flag_otvet = TRUE;
            //}
        }


        Sleep(100);
        CloseHandle(hNamePipe);
    }


}