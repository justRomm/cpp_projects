/* ��-14 ������� �������
*  ��������� ���������� �������� ������� sin(x)/x
*  ����� ������� � ���������� ��� �������.
*  ��� �������� ������ �������� ��� ����� ���� ���������� �
*  ���������� �������: ������� ��������� -> ����� ��������� -> ���� ��������� -> ������� ���������;
*  � 1 ������� ����� �����. ���������, "-1 1 0.05 0.000001".
*/
#include <iostream>
#include <cmath>
#include <cstdio>
#include <io.h>
#pragma warning( disable : 4996 )
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
struct Data
{
    /* ��������� ��� ��������� �� �������� �����, ���������� ��� ��������� ������� �� ��������
    *  xBegin - ������� ���������
    *  xEnd - ����� ���������
    *  xDelta - ���� ���������
    *  e - ������� ��������� */
    double xBegin;
    double xEnd;
    double xDelta;
    double e;
};
void readData(char[], Data*);
void getData(Data*);
double calcAndOut(Data);
void getFilename(Data*);
void calcAll(Data* data);
void getInput(Data*);
double calc(double, double, double, int&);
//-----------------------------------------------------------------------------------------------------------------------------------------------
void main()
{
    /* �������, �� ������ ����� � ������������ i �������
    *  �������� ������� ��� �������� ������ ����������� ���������� */
    char choice;
    Data data;
    printf("Hello, User!\nThis program is calculating function 'f(x)=sin(x)/x' by expansion it to Taylor power series.\n");
    printf("Do you want to start? \nPrint 'y' if you want, everything else if you want to exit from the program : ");
    cin >> choice;
    while (choice == 'y')
    {
        getData(&data);
        calcAll(&data);
        printf("Do you want to do some more caltulations?\nPrint 'y' if you want, everything else if you want to exit from the program : ");
        cin >> choice;
    }
    printf("\n\nHave a good day!\n\n");
    system("pause");
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void getData(Data* data)
{
    /* ������� ���� � �����������, ����� ���� ��������� ����������
    *  Data* data - ��������� � ����������� */
    printf("If data in a file print '1', else print '0': ");
    char ch;
    cin >> ch;
    while ((ch != '1') && (ch != '0'))
    {
        printf("Print '1', or '0' only: ");
        cin >> ch;
    }
    if (ch == '1')
        getFilename(data);
    else
        getInput(data);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void getFilename(Data* data)
{
    /* ���������� �������, �� ���� � ����������� ����� �����, � ����� ����������
    *  ����������, ��������� ��� ����������.
    *  � ������� ��������� �����, ���������� ������ ������� "readData(name, data)".
    *  � �������, ���� ��������� ����� �� ����, ������� ������� ���� ����, ���
    *  ���������� �������� ��� ������ �����.
    *  Data* data - ��������� ��� ��������� ���������� */
    char filename[256];
    FILE* file;
    printf("Enter filename: ");
    scanf("%s", filename);
    file = fopen(filename, "r");
    if (file)
        readData(filename, data);
    else
    {
        printf("There is no file with this name\n");
        getFilename(data);
    }
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void getInput(Data* data)
{
    /* ������� ���� � ����������� ��� ��� ���������
    *  Data* data - ��������� ��� ��������� ���������� */
    printf("Enter your data (X begin < X end and X delta > 0):\n");
    printf("Enter X begin: ");
    scanf("%lf", &data->xBegin);
    printf("Enter X end: ");
    scanf("%lf", &data->xEnd);
    printf("Enter X delta : ");
    scanf("%lf", &data->xDelta);
    printf("Enter accuracy: ");
    scanf("%lf", &data->e);
    if ((data->xBegin > data->xEnd) || (data->xDelta <= 0)) // �������� �� ���������� �������� �����
    {
        printf("Your data is wrong. Check it and come back please.\n");
        getData(data);
    }
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void readData(char filename[], Data* data)
{
    /* ������� ���� � ����� ����������
    *  �� ������ � ��������� "Data"
    *  char filename[] - ����� �����
    *  Data* data - ��������� ��� ��������� ���������� */
    FILE* file = fopen(filename, "r");
    fscanf(file, "%lf", &data->xBegin);
    fscanf(file, "%lf", &data->xEnd);
    fscanf(file, "%lf", &data->xDelta);
    fscanf(file, "%lf", &data->e);
    if ((data->xBegin > data->xEnd) || (data->xDelta <= 0)) // �������� �� ���������� �������� �����
    {
        printf("Your data is wrong. Check it and come back please.\n");
        getData(data);
    }
    else
        printf("Your input:\nX begin = %f \nX end = %f \nX delta = %f \nAccuracy = %f \n", data->xBegin, data->xEnd, data->xDelta, data->e);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void calcAll(Data* data)
{
    /* �������, �� ��������� ��������� �� �������� �� �����,
    *  ��� �� ����� � � ���� ������� � ������������ ���������.
    *  Data* data - ��������, � ����� �������� ��� ��� ��������� */
    printf("Do you want to save result of calculations?(y/n): ");
    char ch;
    cin >> ch;
    while ((ch != 'y') && (ch != 'n'))
    {
        printf("Please, whrite 'y' or 'n'.\nDo you want to save result of calculations?(y/n): ");
        cin >> ch;
    }
    if (ch == 'y')
    {
        printf("Enter filename, where you want to save the result (with format): ");
        char filename[256];
        cin >> filename;
        if (!access(filename, 0))   // ��������, �� ���� ���� � ������ filename
        {
            printf("Do you want to rename or delete existing file?(r/d): ");
            cin >> ch;
            while ((ch != 'r') && (ch != 'd'))
            {
                printf("Please, write 'r' or 'd': ");
                cin >> ch;
            }   // ����� 'while ((ch != 'r') && (ch != 'd'))'
            if (ch == 'r')
            {
                printf("Enter a new filename: ");
                char newName[256];
                cin >> newName;
                rename(filename, newName);
            }   // ����� ' if (ch == 'r')'
        }   // ����� 'if (!access(filename, 0))'
        FILE* file = fopen(filename, "w");
        printf("===================================================================================================\n");
        printf("| % 8s | % 24s | % 4s | % 24s | % 24s |\n", "x", "series(x)", "n", "f(x)", "Diff");
        printf("===================================================================================================\n");
        fprintf(file, "===================================================================================================\n");
        fprintf(file, "| % 8s | % 24s | % 4s | % 24s | % 24s |\n", "x", "series(x)", "n", "f(x)", "Diff");
        fprintf(file, "===================================================================================================\n");
        for (double x = data->xBegin; x <= data->xEnd; x += data->xDelta)
        {
            int n = 0;
            if (float(abs(x)) == 0) //�����, ��� �������� ��� ��������, �� � = 0 � ������� �� ������������
            {
                printf("| % 8s | % 24s | % 4s | % 24s | % 24s |\n", "0", "---", "---", "---", "---");
                printf("====================================================================================================\n");
                fprintf(file, "| % 8s | % 24s | % 4s | % 24s | % 24s |\n", "0", "---", "---", "---", "---");
                fprintf(file, "====================================================================================================\n");

            }   // ����� 'if (abs(x) <= 1e-6)'
            else
            {
                double res = calc(x, 1, data->e, n);
                double fx = sin(x) / x;
                printf("| % 8.4lf | % 24.10lf | % 4d | % 24.10lf | % 24.10lf |\n", x, res, n, fx, abs(res - fx));
                printf("====================================================================================================\n");
                fprintf(file, "| % 8.4lf | % 24.10lf | % 4d | % 24.10lf | % 24.10lf |\n", x, res, n, fx, abs(res - fx));
                fprintf(file, "====================================================================================================\n");
            }   // ����� 'else' �� 'if (abs(x) <= 1e-6)'

        }   // ����� 'for (double x = data->xBegin; x <= data->xEnd; x += data->xDelta)'
        fclose(file);
    }   // ����� "if (ch == 'y')"
    else
    {
        printf("====================================================================================================\n");
        printf("| % 8s | % 24s | % 4s | % 24s | % 24s |\n", "x", "series(x)", "n", "f(x)", "Diff");
        printf("====================================================================================================\n");
        for (double x = data->xBegin; x <= data->xEnd; x += data->xDelta)
        {
            int n = 0;
            if (float(abs(x)) == 0) //�����, ��� �������� ��� ��������, �� � = 0 � ������� �� ������������
            {
                printf("| % 8s | % 24s | % 4s | % 24s | % 24s |\n", "0", "---", "---", "---", "---");
                printf("====================================================================================================\n");
            }   // ����� 'if (abs(x) <= 1e-6)'
            else {
                double res = calc(x, 1, data->e, n);
                double fx = sin(x) / x;
                printf("| % 8.4lf | % 24.10lf | % 4d | % 24.10lf | % 24.10lf |\n", x, res, n, fx, abs(res - fx));
                printf("====================================================================================================\n");
            }   // ����� 'else' �� 'if (abs(x) <= 1e-6)'
        }   // ����� 'for (double x = data->xBegin; x <= data->xEnd; x += data->xDelta)'
    }   // ����� 'else' �� 'if (ch == 'y')'
}   // ����� "calcAndOut(Data* data)"
//-----------------------------------------------------------------------------------------------------------------------------------------------
double calc(double x, double a, double accuracy, int& n)
{
    /* ���������� �������, �� ��������� ��������� ������� ����� ���������� ���:
    *  x - �������� x
    *  a - ���� ����
    *  accuracy - �������
    *  n - ������� ����� */
    if (abs(a) < accuracy)
        return a;
    n += 1;
    double q = -((x * x) / ((2 * n) * (2 * n + 1)));  // ����������� �������
    return a + calc(x, a * q, accuracy, n);
}