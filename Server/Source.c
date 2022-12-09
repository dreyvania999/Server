#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#define SIZE_BUFFER 140

int main()
{
    //сервер создает канал
    system("chcp 1251 > null");
    HANDLE hNamePipe; //объявление дескриптора канала
    LPSTR lpstPipeName = L"\\\\.\\pipe\\MyPipe"; // переменная, содержащая имя канала   
    LPWSTR buffer = (CHAR*)calloc(SIZE_BUFFER, sizeof(CHAR)); // строковая перменная, в которую будут считаны даные
    char message[SIZE_BUFFER]; // массив симвролов
    BOOL Connected;
    DWORD actual_readen; // сколько на самом деле было прочитано байт
    //читать из канала
    LPWSTR b = (CHAR*)calloc(SIZE_BUFFER, sizeof(CHAR));
    LPWSTR zero = (CHAR*)calloc(SIZE_BUFFER, sizeof(CHAR));
    while (TRUE)
    {
        HANDLE hNamePipe = CreateNamedPipe( // создание канала
            lpstPipeName, // имя канала - путь
            // и принимает и отправляет
            PIPE_ACCESS_DUPLEX, // режм доступа к каналу (односторонний/двусторонний)
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, // режим работы канала: передавать сообщения| читать собщения | ждать
            PIPE_UNLIMITED_INSTANCES, // количест во водящих соединений в каналу, в данном случае неогр.
            SIZE_BUFFER, // объем буфера для чтения (байт)
            SIZE_BUFFER, // объем буфера для записи (байт)
            INFINITE, // максимальное время ожидания сообщения - ждать до конца
            NULL // указатель на структуру безопасности
        );
        Connected = ConnectNamedPipe(hNamePipe, NULL); // установка с оединения клиента с каналом
        if (Connected) // если клиент подключился
        {
            printf("\nКлиент успешно подключен\n");

            if (ReadFile(hNamePipe, buffer, SIZE_BUFFER, &actual_readen, NULL))
            {
                // обмен сообщениями
                printf("\nКлиент пишет: ");
                printf(buffer);

                printf("\nСообщение: ");
                gets(message);
                buffer = &message;
                WriteFile(hNamePipe, buffer, SIZE_BUFFER, &actual_readen, NULL);

                // возведение в квадрат
                //printf("\nКлиент пишет: \n");
                //printf(buffer);// вывод на экран прочитанного сообщения
                //printf("\n");
                //float a = atof(buffer);// преобразует строку в значение типа double
                //float aa = a * a; // в квадрат
                //sprintf(message, "%g", aa); // вывод
                //zero = L"0";
                //sprintf(b, "%s", buffer);
                //if (aa == 0 && strcmp(b, zero) != 0)
                //{
                //    sprintf(message, "Не корректно введены данные");
                //}
                //buffer = &message;
                //WriteFile(hNamePipe, buffer, SIZE_BUFFER, &actual_readen, NULL);
            }


        }
        else
        {
            printf("\nКлиент отключился от сервера\n");
        }
        CloseHandle(hNamePipe); // закрываем канал

    }
}