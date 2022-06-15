#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <locale.h>

/* ��������� ��� �������� ���������� ��� ���� ���� */
typedef struct tagAIR
{
    char WhereFrom[25], From[25], Search[25];
    int Transfer, Value;
} AIR;

/* ������ ���������� �������� 30 ������ */
AIR flight[30];

/* ������� ����������� ������ */
int Number;

/* ������� ��� ���������� ������� � ����� */
void Save(void)
{
    // �������� ����� ��� �������������� � �������� �� ��������.
    FILE* F;
    if ((F = fopen("airticket.txt", "wt")) == NULL)
    {
        fprintf(stderr, "���������� ������� ��� ������ ���� 'airticket.txt'\n");
        return;
    }

    // ������ � ���� �������� ����������� ������ � �������� �������� �� ������.
    fprintf(F, "%i\n", Number);
    for (int i = 0; i < Number; i++)
        fprintf(F, "%s\n%s\n%i\n%i\n",
            flight[i].WhereFrom,
            flight[i].From,
            flight[i].Transfer,
            flight[i].Value);

    fclose(F);
} /* ����� ������� �� ����������*/


/* ������� ��� ���������� ������ */
void Add(void)
{
    // �������� �� ����������� ���������� ����� ������.
    if (Number == 29)
    {
        fprintf(stderr, "���������� �������� ��� ���� ����. ���������� ����� ������ ���� �� ������!\n");
        return;
    }
    // �����������, ������� ������� � ���������� ������ �����.
    system("chcp 1251");
    system("cls");
    printf("[����] ������� ������ ���������� ������ > ");
    if (scanf == NULL)
        return;
    scanf("%s", flight[Number].WhereFrom);

    printf("[����] ������� ��� ������������� ������ > ");
    scanf("%s", flight[Number].From);

    printf("[����] ������� ����� ��������� (���) > ");
    scanf("%i", &flight[Number].Transfer);

    printf("[����] ������� ���� (���) > ");
    scanf("%i", &flight[Number].Value);

    printf("\n[����������] ��������� ����������?\n\n"
        "           [0] : ��\n"
        "[���. �������] : ���\n\n"
        "==> ");
    int i = _getch();

    if (i != 48)
    {
        system("cls");
        printf("[����������] �������� ��������!\n");
        return;
    }

    Number++; // ����� ���������� ������ ����� - ����������� ������� �� 1.

    // ��������� � ������� �������.
    Save();
    system("cls");
} /* ����� ������� ���������� */


/* ������� ��� ������ ����� � ���������*/
void Read(void)
{
    FILE* F;
    // �������� ����� ��� ������ � �������� �� ��������.
    if ((F = fopen("airticket.txt", "rt")) == NULL)
    {
        fprintf(stderr, "���������� ������� ��� ������ ���� 'airticket.txt'\n");
        return;
    }

    // ������ �� �����.
    fscanf(F, "%i", &Number);
    for (int i = 0; i < Number; i++)
        fscanf(F, "%s%s%i%i",
            flight[i].WhereFrom,
            flight[i].From,
            &flight[i].Transfer,
            &flight[i].Value);

    fclose(F);
} /* ����� ������� ������ */


/* ������� ��� ������ ���� ������ */
void Print(void)
{
    printf(" �  ������:                   ����:                     ��������� (�����):   ���� (������):\n");
    for (int i = 0; i < Number; i++)
        printf("%2i. %-25s %-25s %-20i %-7i\n", i + 1,
            flight[i].WhereFrom,
            flight[i].From,
            flight[i].Transfer,
            flight[i].Value);

    printf("\n");

} /* ����� ������� ������ */


/* ������� ��� �������� ������ */
void Del(void)
{
    Print();
    int i;
    printf("������� ����� ���������� ����� > ");
    scanf("%d", &i);
    // �������� �� ������������� �����.
    if (i < 1 || i > Number)
    {
        system("cls");
        fprintf(stderr, "����� � ������� %i �� ����������\n", i);
        return;
    }

    // ���� ������ ����� 'i' ����� ������� 'i-1'. �������� ����� �������������� ���� ������.
    for (i--; i < Number - 1; i++)
        flight[i] = flight[i + 1];

    // ���������� �������� �� 1 ����� �������� ������ �����. ������� �������,���������� � ����� ��������������� ����.
    Number--;
    system("cls");
    Save();
    Print();
} /* ����� ������� �� �������� */


/* ������� �� �������������� ������ */
void Edit(void)
{
    Print();

    int i, c = 0;
    printf("������� ����� �������������� ����� > ");
    scanf("%d", &i);

    if (i < 1 || i > Number)
    {
        system("cls");
        fprintf(stderr, "����� � ������� %i �� ����������\n", i);
        return;
    }

    // �����������, ������� ������� � ����� ���������� ����� ��� ��������������.
    system("chcp 1251");
    system("cls");

    printf(" �  ������:                   ����:                     ��������� (�����):   ���� (������):\n");
    printf("%2i. %-25s %-25s %-20i %-7i\n",
        i,
        flight[i - 1].WhereFrom,
        flight[i - 1].From,
        flight[i - 1].Transfer,
        flight[i - 1].Value);
    // �������������� ������������ �������� � ����� � ������� ����.
    while ((c < '0' || c > '4'))
    {
        printf("\n�������������� ����. \n�������� ������������� ������� �����:\n\n"
            "[1] : ������ ���������� ������.\n"
            "[2] : ��� ������������� ������.\n"
            "[3] : ����� ���������.\n"
            "[4] : ���� ������.\n\n"
            "[0] : ����� �� ���� ��������������.\n\n"
            "==> ");
        c = _getch();
        printf("%c\n", c);
        system("cls");
    }
    // ������������� �������������� �������� ��� ������ ������ �� ����� �������.
    switch (c)
    {
    case '1':
        printf("������� ����� ������: ������ ���������� ������?\n");
        scanf("%s", flight[i - 1].WhereFrom);
        break;
    case '2':
        printf("������� ����� ������: ��� ������������� ������?\n");
        scanf("%s", flight[i - 1].From);
        break;
    case '3':
        printf("������� ����� ������: ����� ���������?\n");
        scanf("%i", &flight[i - 1].Transfer);
        break;
    case '4':
        printf("������� ����� ������: ���� ������?\n");
        scanf("%i", &flight[i - 1].Value);
        break;
    }

    // ������� �������, ���������� � ����� ����������������� ����.
    system("cls");
    Save();
    Print();
} /* ����� ������� �� �������������� */


/* ����� ������� � ����. �������� ��������*/
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

    // ������ � ������ ��� ����������� ���������.
    printf("\n[����] ������� ������ ���������� ������ > ");
    scanf("%s", flight[0].Search);

    // ������� ������� � ����� ���������� �� ������� ������.
    system("cls");
    printf(" �  ������:                   ����:                     ��������� (�����):   ���� (������):\n");
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

    printf("\n[����] ������� ��� ������������� ������ > ");
    scanf("%s", flight[1].Search);

    // ����� ����������� ������� ��������.
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
    // ������� �������, ����� �� ������������� ������.
    system("cls");
    if (min != 7200) { printf("������ �%d ����� ���������� ����� �������� ��� ���������� (%d �����)!\n", num + 1, min); }
    else { printf("�� ������� ������� ������ �� �������!\n"); }

    fclose(F);
} /* ����� ������� �� ������ (����� ��������) */


/* ����� ������� � ����. �����*/
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

    printf("\n[����] ������� ������ ���������� ������ > ");
    scanf("%s", flight[0].Search);

    // ������� ������� � ����� ���������� �� ������� ������.
    system("cls");
    printf(" �  ������:                   ����:                     ��������� (�����):   ���� (������):\n");
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

    printf("\n[����] ������� ��� ������������� ������ > ");
    scanf("%s", flight[1].Search);

    // ����� ���������� ����.
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
    // ������� ������� � ����� �� ������.
    system("cls");
    if (min != 10000) { printf("������ �%d ����� ���������� ���� ��� ����� (%d ������)!\n", num + 1, min); }
    else { printf("�� ������� ������� ������ �� �������!\n"); }

    fclose(F);

} /* ����� ������� �� ������ (����) */


/* ����� ���� � ������ ������ ���������� ������ */
int flightu(void)
{
    setlocale(LC_ALL, "Rus");
    Read();
    int c = 0;

    while ((c < '0' || c > '6'))
    {
        printf("���� ������ '���������'\n\n"
            "[1] : ��������� ����.\n"
            "[2] : ������� ���������� �� ����.\n"
            "[3] : ������� ������ �� ����.\n"
            "[4] : �������������� ������� � ����.\n"
            "[5] : ������ ������� � ���������� �������� �������� ��� ���������.\n"
            "[6] : ������ ������� � ���������� �����.\n\n"
            "[0] : ����� �� ����.\n\n"
            "==> ");
        c = _getch();
        printf("%c\n", c);
        system("cls");
    }
    return c;


}


/* �������� ������� */
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

