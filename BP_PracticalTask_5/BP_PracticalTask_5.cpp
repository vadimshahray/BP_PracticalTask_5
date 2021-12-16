#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <locale.h>
#include <windows.h>

/// <summary>Максимальное случайное число</summary>
const short Rmax = 20;
/// <summary>Минимальное случайное число</summary>
const short Rmin = 1;
/// <summary>Максимальный размер серии одинаковых чисел</summary>
const short Lmax = 7;
/// <summary>Минимальный размер серии одинаковых чисел</summary>
const short Lmin = 2;
/// <summary>Максимальная размерность массива</summary>
const size_t Nmax = 16;

/// <summary>Функция дублирует в целочисленном массиве элементы, равные целому числу X</summary>
/// <param name="A">Массив</param>
/// <param name="N">Размер передаваемого массива</param>
/// <param name="X">Повторяемое число</param>
/// <returns>Размерность массива после его обработки</returns>
UCHAR DoubleX(short* A, UCHAR N, short X);

/// <summary>Функция выводит размер массива и все его элементы в порядке возрастания их индексов</summary>
/// <param name="A">Массив</param>
/// <param name="N">Размерность массива</param>
void PrintArray(short* A, UCHAR N);

//<summary>Функция наполняет массив случайными числами</summary>
//<param name="A">Массив</param>
//<param name="N">Размерность массива</param>
void RandArray(short* A, UCHAR N);

int main()
{
   setlocale(LC_ALL, "");

   short A[Nmax] = { }, X = 0;
   UCHAR N = 0;
   time_t t;

   printf_s("Введите целые числа N ([1; %zu]) и целые числа X ([%hi; %hi]): ", Nmax, Rmin, Rmax);
   scanf_s("%hhi %hi", &N, &X);

   if (N > Nmax) N = Nmax;

   srand((unsigned)time(&t));
   RandArray(A, N);
   PrintArray(A, DoubleX(A, N, X));

   return 0 * _getch();
}

UCHAR DoubleX(short* A, UCHAR N, short X)
{
   // a - кол-во новых элементов
   UCHAR a = 0;

   for (short i = 0; i < N + a - 1 && i < Nmax; i++)
   {
      if (A[i] == X)
      {
         // d - количество дополнительных элементов при серии
         short d = 0;
         for (; A[i + d + 1] == X; d++);

         // перемещаем "хвост" массива вправо на 1 позицию
         // Если текущее кол-во элементов массива больше допустимого, то j = Nmax - 1 (максимальное допустимое значение), иначе j = N + a (последний элемент в массиве)
         for (UCHAR j = N + a < Nmax - 1 ? N + a : Nmax - 1; j > i + d; j--)
            A[j] = A[j - 1 - d];

         // Дублируем
         for (; d >= 0; d--)
         {
            A[i + d + 1] = A[i];
            i += 2;
            a++;
         }
      }
   }

   return N + a < Nmax ? N + a : Nmax;
}
void PrintArray(short* A, UCHAR N)
{
   printf_s("Размер массива = %hi\nЭлементы массива: ", N);
   for (size_t i = 0; i < N; i++) printf_s("%d ", A[i]);
   printf_s("\n");
}
void RandArray(short* A, UCHAR N)
{
   for (size_t i = 0; i < N; i++)
   {
      short r = rand() % Rmax + Rmin;
      if (r % 2) // если так, то генерируем серию чисел случайной длины
      {
         // генерируем число от Lmin до Lmax (длина серии)
         for (short l = rand() % Lmax + Lmin; l > 0 && i < N; l--, i++)
            A[i] = r;
         // уменьшаем значение счетчика, так как после генерации серии i пропускает одну позицию
         i--;
      }
      else A[i] = r;
   }
}