//12, 12, 12, 20, 14, 5, 2, 9, 1, 1, 12, 12, 10, 14, 13, 7


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


void DoubleX(UCHAR *A, UCHAR &N, const short X);
void PrintArray(UCHAR *A, UCHAR N);
void RandArray(UCHAR *A, UCHAR N);

int main()
{
   setlocale(0, "");

   UCHAR A[Nmax] = { }, N = 0, X = 0;
   time_t t;

   printf_s("Введите целые числа N ([1; %zu]) и целые числа X ([%hi; %hi]): ", Nmax, Rmin, Rmax);
   scanf_s("%hhi %hhi", &N, &X);

   if (N > Nmax) N = Nmax;

   srand((UINT) time(&t));
   RandArray(A, N);
   DoubleX(A, N, X);
   PrintArray(A, N);

   return 0 * _getch();
}

/// <summary>Функция дублирует в целочисленном массиве элементы, равные целому числу X</summary>
/// <param name="A">Массив</param>
/// <param name="N">Размер передаваемого массива</param>
/// <param name="X">Повторяемое число</param>
void DoubleX(UCHAR *A, UCHAR &N, const short X)
{
   for (UCHAR i = 0; i < N - 1; i++)
   {
      if (A[i] == X)
      {
         UCHAR c = 1; // c - количество повторений X.
         for ( ; A[i + c] == X; c++); // Вычисляем длину серии из повторений X.
         
         for (UCHAR j = N + c - 1; i + 2 * c < Nmax && j > i + 2 * c - 1; j--) // Смещаем массив вправо, с учетом границ массива и выявленной длиной серии X.
            A[j] = A[j - c];

         for (UCHAR k = c; k > 0; k--, i += 2)
            A[i + k] = X; // Дублируем элементы серии.

         N = N + c > Nmax ? Nmax : N + c; // Задаем размер массива.
      }
   }
}
/// <summary>Функция выводит размер массива и все его элементы в порядке возрастания их индексов</summary>
/// <param name="A">Массив</param>
/// <param name="N">Размерность массива</param>
void PrintArray(UCHAR *A, UCHAR N)
{
   printf_s("Размер массива = %hi\nЭлементы массива: ", N);
   for (size_t i = 0; i < N; i++) 
      printf_s("%d ", A[i]);
   printf_s("\n");
}
//<summary>Функция наполняет массив случайными числами</summary>
//<param name="A">Массив</param>
//<param name="N">Размерность массива</param>
void RandArray(UCHAR *A, UCHAR N)
{
   for (size_t i = 0; i < N; i++)
   {
      UCHAR r = rand() % Rmax + Rmin; // Случайное число [Rmin; Rmax], используемое для заполенения массива А.
      if (r % 2)
      {
         for (short l = rand() % (Lmax + 1 - Lmin) + Lmin; l > 0 && i < N; l--, i++) // Генерируем серию из чисел r длиной [Lmin; Lmax].
            A[i] = r;
         
         i--; // Уменьшаем значение счетчика, так как после генерации серии i пропускает одну позицию.
      }
      else A[i] = r;
   }
}