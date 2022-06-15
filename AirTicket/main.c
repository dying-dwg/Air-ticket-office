#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <locale.h>

/* Структура для хранения информации про один рейс */
typedef struct tagAIR
{
    char WhereFrom[25], From[25], Search[25];
    int Transfer, Value;
} AIR;

/* Массив содержащий максимум 30 рейсов */
AIR flight[30];

/* Счётчик заполненных рейсов */
int Number;

/* Функция для сохранения массива в файле */
void Save(void)
{
    // Открытие файла для редактирования и проверка на открытие.
    FILE* F;
    if ((F = fopen("airticket.txt", "wt")) == NULL)
    {
        fprintf(stderr, "Невозможно открыть для записи файл 'airticket.txt'\n");
        return;
    }

    // Запись в файл счётчика заполненных рейсов и основных сведений об рейсах.
    fprintf(F, "%i\n", Number);
    for (int i = 0; i < Number; i++)
        fprintf(F, "%s\n%s\n%i\n%i\n",
            flight[i].WhereFrom,
            flight[i].From,
            flight[i].Transfer,
            flight[i].Value);

    fclose(F);
} /* Конец функции по Сохранению*/


/* Функция для пополнения рейсов */
void Add(void)
{
    // Проверка на возможность добавление новых рейсов.
    if (Number == 29)
    {
        fprintf(stderr, "Невозможно добавить еще один рейс. Освободите место удалив один из рейсов!\n");
        return;
    }
    // Русификация, очистка консоли и добавление нового рейса.
    system("chcp 1251");
    system("cls");
    printf("[Рейс] Введите откуда начинается маршут > ");
    if (scanf == NULL)
        return;
    scanf("%s", flight[Number].WhereFrom);

    printf("[Рейс] Введите где заканчивается маршут > ");
    scanf("%s", flight[Number].From);

    printf("[Рейс] Введите время пересадок (мин) > ");
    scanf("%i", &flight[Number].Transfer);

    printf("[Рейс] Введите цену (руб) > ");
    scanf("%i", &flight[Number].Value);

    printf("\n[Пополнение] Сохранить добавление?\n\n"
        "           [0] : Да\n"
        "[Люб. клавиша] : Нет\n\n"
        "==> ");
    int i = _getch();

    if (i != 48)
    {
        system("cls");
        printf("[Пополнение] Действие отменено!\n");
        return;
    }

    Number++; // После добавления нового рейса - увеличиваем счётчик на 1.

    // Сохраняем и очищаем консоль.
    Save();
    system("cls");
} /* Конец функции Пополнения */


/* Функция для чтения файла в программу*/
void Read(void)
{
    FILE* F;
    // Открытие файла для чтения и проверка на открытие.
    if ((F = fopen("airticket.txt", "rt")) == NULL)
    {
        fprintf(stderr, "Невозможно открыть для чтения файл 'airticket.txt'\n");
        return;
    }

    // Чтение из файла.
    fscanf(F, "%i", &Number);
    for (int i = 0; i < Number; i++)
        fscanf(F, "%s%s%i%i",
            flight[i].WhereFrom,
            flight[i].From,
            &flight[i].Transfer,
            &flight[i].Value);

    fclose(F);
} /* Конец функции Чтения */


/* Функция для вывода всех рейсов */
void Print(void)
{
    printf(" №  Откуда:                   Куда:                     Пересадки (Минут):   Цена (Рублей):\n");
    for (int i = 0; i < Number; i++)
        printf("%2i. %-25s %-25s %-20i %-7i\n", i + 1,
            flight[i].WhereFrom,
            flight[i].From,
            flight[i].Transfer,
            flight[i].Value);

    printf("\n");

} /* Конец функции Вывода */


/* Функция для удаления рейсов */
void Del(void)
{
    Print();
    int i;
    printf("Введите номер удаляемого рейса > ");
    scanf("%d", &i);
    // Проверка на существование рейса.
    if (i < 1 || i > Number)
    {
        system("cls");
        fprintf(stderr, "Рейса с номером %i не существует\n", i);
        return;
    }

    // Ввод номера рейса 'i' равен индексу 'i-1'. Удаление рейса осуществляется путём замены.
    for (i--; i < Number - 1; i++)
        flight[i] = flight[i + 1];

    // Уменьшения счётчика на 1 после удаление однрго рейса. Очистка консоли,сохранение и вывод редактированной базы.
    Number--;
    system("cls");
    Save();
    Print();
} /* Конец функции по Удалению */


/* Функция по редактированию рейсов */
void Edit(void)
{
    Print();

    int i, c = 0;
    printf("Введите номер редактируемого рейса > ");
    scanf("%d", &i);

    if (i < 1 || i > Number)
    {
        system("cls");
        fprintf(stderr, "Рейса с номером %i не существует\n", i);
        return;
    }

    // Русификация, очистка консоли и вывод выбранного рейса для редактирования.
    system("chcp 1251");
    system("cls");

    printf(" №  Откуда:                   Куда:                     Пересадки (Минут):   Цена (Рублей):\n");
    printf("%2i. %-25s %-25s %-20i %-7i\n",
        i,
        flight[i - 1].WhereFrom,
        flight[i - 1].From,
        flight[i - 1].Transfer,
        flight[i - 1].Value);
    // Редактирование определённого элемента в рейсе с помощью меню.
    while ((c < '0' || c > '4'))
    {
        printf("\nРедактирование базы. \nВыберите редактируемый элемент рейса:\n\n"
            "[1] : Откуда начинается маршут.\n"
            "[2] : Где заканчивается маршут.\n"
            "[3] : Время пересадки.\n"
            "[4] : Цена билета.\n\n"
            "[0] : Выйти из меню редактирования.\n\n"
            "==> ");
        c = _getch();
        printf("%c\n", c);
        system("cls");
    }
    // Осуществление редактирование элемента при помощи замены на новый элемент.
    switch (c)
    {
    case '1':
        printf("Введите новые данные: Откуда начинается маршут?\n");
        scanf("%s", flight[i - 1].WhereFrom);
        break;
    case '2':
        printf("Введите новые данные: Где заканчивается маршут?\n");
        scanf("%s", flight[i - 1].From);
        break;
    case '3':
        printf("Введите новые данные: Время пересадки?\n");
        scanf("%i", &flight[i - 1].Transfer);
        break;
    case '4':
        printf("Введите новые данные: Цена билета?\n");
        scanf("%i", &flight[i - 1].Value);
        break;
    }

    // Очистка консоли, сохранение и вывод отредактированной базы.
    system("cls");
    Save();
    Print();
} /* Конец функции по Редактированию */


/* Поиск маршута с наим. временем ожидания*/
void searchTransfer(void)
{
    system("chcp 1251");
    system("cls");

    Print();

    char st[30], num;
    int Number, i = 0, min = 7200;

    FILE* F;
    F = fopen("airticket.txt", "rt");

    fscanf(F, "%i", &Number);

    // Запись в массив для дальнейшего сравнения.
    printf("\n[Рейс] Введите откуда начинается маршут > ");
    scanf("%s", flight[0].Search);

    // Очистка консоли и вывод подходящих по запросу рейсов.
    system("cls");
    printf(" №  Откуда:                   Куда:                     Пересадки (Минут):   Цена (Рублей):\n");
    for (i = 0; i < Number; i++)
    {
        if (strcmp(flight[0].Search, flight[i].WhereFrom) == 0)
        {
            printf("%2i. %-25s %-25s %-20i %-7i\n", i + 1,
                flight[i].WhereFrom,
                flight[i].From,
                flight[i].Transfer,
                flight[i].Value);
        }
    }

    printf("\n[Рейс] Введите где заканчивается маршут > ");
    scanf("%s", flight[1].Search);

    // Поиск наименьшего времени ожидания.
    for (i = 0; i < Number; i++)
    {
        if (strcmp(flight[0].Search, flight[i].WhereFrom) == 0 && strcmp(flight[1].Search, flight[i].From) == 0)
        {
            if (min > flight[i].Transfer)
            {
                min = flight[i].Transfer;
                num = i;
            }
        }
    }
    // Очистка консоли, вывод по произведённому поиску.
    system("cls");
    if (min != 7200) { printf("Маршут №%d имеет наименьшее время ожидания при пересадках (%d минут)!\n", num + 1, min); }
    else { printf("По данному маршуту ничего не найдено!\n"); }

    fclose(F);
} /* Конец функции по Поиску (время ожидания) */


/* Поиск маршута с наим. ценой*/
void searchValue(void)
{
    system("chcp 1251");
    system("cls");

    Print();

    char st[30], num;
    int Number, i = 0, min = 10000;

    FILE* F;
    F = fopen("airticket.txt", "rt");

    fscanf(F, "%i", &Number);

    printf("\n[Рейс] Введите откуда начинается маршут > ");
    scanf("%s", flight[0].Search);

    // Очистка консоли и вывод подходящих по запросу рейсов.
    system("cls");
    printf(" №  Откуда:                   Куда:                     Пересадки (Минут):   Цена (Рублей):\n");
    for (i = 0; i < Number; i++)
    {
        if (strcmp(flight[0].Search, flight[i].WhereFrom) == 0)
        {
            printf("%2i. %-25s %-25s %-20i %-7i\n", i + 1,
                flight[i].WhereFrom,
                flight[i].From,
                flight[i].Transfer,
                flight[i].Value);
        }
    }

    printf("\n[Рейс] Введите где заканчивается маршут > ");
    scanf("%s", flight[1].Search);

    // Поиск наименьшей цены.
    for (i = 0; i < Number; i++)
    {
        if (strcmp(flight[0].Search, flight[i].WhereFrom) == 0 && strcmp(flight[1].Search, flight[i].From) == 0)
        {
            if (min > flight[i].Value)
            {
                min = flight[i].Value;
                num = i;
            }
        }
    }
    // Очистка консоли и вывод по поиску.
    system("cls");
    if (min != 10000) { printf("Маршут №%d имеет наименьшее цену для полёте (%d рублей)!\n", num + 1, min); }
    else { printf("По данному маршуту ничего не найдено!\n"); }

    fclose(F);

} /* Конец функции по Поиску (цена) */


/* Вывод меню и чтение номера выбранного пункта */
int flightu(void)
{
    setlocale(LC_ALL, "Rus");
    Read();
    int c = 0;

    while ((c < '0' || c > '6'))
    {
        printf("База данных 'Авиакасса'\n\n"
            "[1] : Пополнить базу.\n"
            "[2] : Вывести информацию из базы.\n"
            "[3] : Удалить запись из базы.\n"
            "[4] : Редактирование записей в базе.\n"
            "[5] : Подбор маршута с наименьшим временем ожидания при пересадке.\n"
            "[6] : Подбор маршута с наименьшим ценой.\n\n"
            "[0] : Выйти из меню.\n\n"
            "==> ");
        c = _getch();
        printf("%c\n", c);
        system("cls");
    }
    return c;


}


/* Основная функция */
void main(void)
{
    system("mode con cols=95 lines=45");
    int Selection;
    Number = 0;
    while ((Selection = flightu()) != '0')
        switch (Selection)
        {
        case '1':
            Add();
            break;
        case '2':
            Print();
            break;
        case '3':
            Del();
            break;
        case '4':
            Edit();
            break;
        case '5':
            searchTransfer();
            break;
        case '6':
            searchValue();
            break;
        }
}

