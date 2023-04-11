/* БС-14 Романюк Михайло
*  Реалізація розрахунків значення функції sin(x)/x
*  через розклад у степеневий ряд функції.
*  Для коректної роботи програми дані мають бути розташовані у
*  відповідному порядку: початок інтервалу -> кінець інтервалу -> крок інтервалу -> точність обрахунку;
*  в 1 строчку через пробіл. Наприклад, "-1 1 0.05 0.000001".
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
    /* Структура для зберігання та передачі даних, необхідних для обрахунків фенкції на інтервалі
    *  xBegin - початок інтервалу
    *  xEnd - кінець інтервалу
    *  xDelta - крок інтервалу
    *  e - точність обрахунку */
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
    /* Функція, що починає діалог з користувачем i викликає
    *  необхідні функції для подальшої роботи програмного застосунку */
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
    /* Функція питає в користувача, звідки буде вводитись інформація
    *  Data* data - структура з інформацією */
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
    /* Рекурсивна функція, що бере в користувача назву файлу, в якому зберігається
    *  інформація, необхідна для розрахунків.
    *  У випадку існування файлу, відбувається виклик функції "readData(name, data)".
    *  У випадку, коли вказаного файлу не існує, функція викликає саму себе, щоб
    *  користувач повторно ввів назуву файлу.
    *  Data* data - структура для зберігання інформації */
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
    /* Функція бере в користувача дані для обрахунків
    *  Data* data - структура для зберігання інформації */
    printf("Enter your data (X begin < X end and X delta > 0):\n");
    printf("Enter X begin: ");
    scanf("%lf", &data->xBegin);
    printf("Enter X end: ");
    scanf("%lf", &data->xEnd);
    printf("Enter X delta : ");
    scanf("%lf", &data->xDelta);
    printf("Enter accuracy: ");
    scanf("%lf", &data->e);
    if ((data->xBegin > data->xEnd) || (data->xDelta <= 0)) // перевірка на коректність введених даних
    {
        printf("Your data is wrong. Check it and come back please.\n");
        getData(data);
    }
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void readData(char filename[], Data* data)
{
    /* Функція бере з файлу інформацію
    *  та передає в структуру "Data"
    *  char filename[] - назва файлу
    *  Data* data - структура для зберігання інформації */
    FILE* file = fopen(filename, "r");
    fscanf(file, "%lf", &data->xBegin);
    fscanf(file, "%lf", &data->xEnd);
    fscanf(file, "%lf", &data->xDelta);
    fscanf(file, "%lf", &data->e);
    if ((data->xBegin > data->xEnd) || (data->xDelta <= 0)) // перевірка на коректність введених даних
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
    /* Функція, що проводить обрахунки та виводить на екран,
    *  або на екран і у файл таблицю з результатами обрахунку.
    *  Data* data - аргумент, в якому збережені дані для обрахунків */
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
        if (!access(filename, 0))   // перевірка, чи існує файл з назвою filename
        {
            printf("Do you want to rename or delete existing file?(r/d): ");
            cin >> ch;
            while ((ch != 'r') && (ch != 'd'))
            {
                printf("Please, write 'r' or 'd': ");
                cin >> ch;
            }   // кінець 'while ((ch != 'r') && (ch != 'd'))'
            if (ch == 'r')
            {
                printf("Enter a new filename: ");
                char newName[256];
                cin >> newName;
                rename(filename, newName);
            }   // кінець ' if (ch == 'r')'
        }   // кінець 'if (!access(filename, 0))'
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
            if (float(abs(x)) == 0) //умова, при виконанні якої ввжається, що х = 0 і функція не обраховується
            {
                printf("| % 8s | % 24s | % 4s | % 24s | % 24s |\n", "0", "---", "---", "---", "---");
                printf("====================================================================================================\n");
                fprintf(file, "| % 8s | % 24s | % 4s | % 24s | % 24s |\n", "0", "---", "---", "---", "---");
                fprintf(file, "====================================================================================================\n");

            }   // кінець 'if (abs(x) <= 1e-6)'
            else
            {
                double res = calc(x, 1, data->e, n);
                double fx = sin(x) / x;
                printf("| % 8.4lf | % 24.10lf | % 4d | % 24.10lf | % 24.10lf |\n", x, res, n, fx, abs(res - fx));
                printf("====================================================================================================\n");
                fprintf(file, "| % 8.4lf | % 24.10lf | % 4d | % 24.10lf | % 24.10lf |\n", x, res, n, fx, abs(res - fx));
                fprintf(file, "====================================================================================================\n");
            }   // кінець 'else' від 'if (abs(x) <= 1e-6)'

        }   // кінець 'for (double x = data->xBegin; x <= data->xEnd; x += data->xDelta)'
        fclose(file);
    }   // кінець "if (ch == 'y')"
    else
    {
        printf("====================================================================================================\n");
        printf("| % 8s | % 24s | % 4s | % 24s | % 24s |\n", "x", "series(x)", "n", "f(x)", "Diff");
        printf("====================================================================================================\n");
        for (double x = data->xBegin; x <= data->xEnd; x += data->xDelta)
        {
            int n = 0;
            if (float(abs(x)) == 0) //умова, при виконанні якої ввжається, що х = 0 і функція не обраховується
            {
                printf("| % 8s | % 24s | % 4s | % 24s | % 24s |\n", "0", "---", "---", "---", "---");
                printf("====================================================================================================\n");
            }   // кінець 'if (abs(x) <= 1e-6)'
            else {
                double res = calc(x, 1, data->e, n);
                double fx = sin(x) / x;
                printf("| % 8.4lf | % 24.10lf | % 4d | % 24.10lf | % 24.10lf |\n", x, res, n, fx, abs(res - fx));
                printf("====================================================================================================\n");
            }   // кінець 'else' від 'if (abs(x) <= 1e-6)'
        }   // кінець 'for (double x = data->xBegin; x <= data->xEnd; x += data->xDelta)'
    }   // кінець 'else' від 'if (ch == 'y')'
}   // кінець "calcAndOut(Data* data)"
//-----------------------------------------------------------------------------------------------------------------------------------------------
double calc(double x, double a, double accuracy, int& n)
{
    /* Рекурсивна функція, що проводить обрахунки функції через степеневий ряд:
    *  x - значення x
    *  a - член ряду
    *  accuracy - точність
    *  n - кількість кроків */
    if (abs(a) < accuracy)
        return a;
    n += 1;
    double q = -((x * x) / ((2 * n) * (2 * n + 1)));  // рекурентний множник
    return a + calc(x, a * q, accuracy, n);
}