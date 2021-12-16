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
UCHAR DoubleX(UCHAR *A, UCHAR N, short X);

/// <summary>Функция выводит размер массива и все его элементы в порядке возрастания их индексов</summary>
/// <param name="A">Массив</param>
/// <param name="N">Размерность массива</param>
void PrintArray(UCHAR *A, UCHAR N);

//<summary>Функция наполняет массив случайными числами</summary>
//<param name="A">Массив</param>
//<param name="N">Размерность массива</param>
void RandArray(UCHAR *A, UCHAR N);

int main()
{
   setlocale(LC_ALL, "");

   UCHAR A[Nmax] = { }, N = 0, X = 0;
   time_t t;

   printf_s("Введите целые числа N ([1; %zu]) и целые числа X ([%hi; %hi]): ", Nmax, Rmin, Rmax);
   scanf_s("%hhi %hhi", &N, &X);

   if (N > Nmax) N = Nmax;

   srand((unsigned) time(&t));
   RandArray(A, N);
   PrintArray(A, DoubleX(A, N, 7));

   return 0 * _getch();
}

UCHAR DoubleX(UCHAR *A, UCHAR N, short X)
{
   // s - размер массива A, с учетом добавленных элементов
   UCHAR s = N;
   for (UCHAR i = 0; i < s - 1 && i < Nmax; i++)
   {
      if (A[i] == X)
      {
         UCHAR c = 1, l_in = i;
         for ( ; A[i + c] == X; c++, l_in++);

         for (UCHAR j = s + c - 1; l_in + c < s - 1 && j > l_in; j--) A[j] = A[j - c];

         for (UCHAR k = c; k > 0; k--, i+= 2) A[i + k] = X;

         s = s + c > Nmax ? Nmax : s + c;
      }
   }

   return s;
}
void PrintArray(UCHAR *A, UCHAR N)
{
   printf_s("Размер массива = %hi\nЭлементы массива: ", N);
   for (size_t i = 0; i < N; i++) printf_s("%d ", A[i]);
   printf_s("\n");
}
void RandArray(UCHAR *A, UCHAR N)
{
   for (size_t i = 0; i < N; i++)
   {
      UCHAR r = rand() % Rmax + Rmin;
      if (r % 2) // если так, то генерируем серию чисел случайной длины
      {
         // генерируем число от Lmin до Lmax (длина серии)
         for (short l = rand() % (Lmax + 1 - Lmin) + Lmin; l > 0 && i < N; l--, i++)
            A[i] = r;
         // уменьшаем значение счетчика, так как после генерации серии i пропускает одну позицию
         i--;
      }
      else A[i] = r;
   }
}