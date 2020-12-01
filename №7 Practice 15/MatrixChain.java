package com.company;

public class MatrixChain {
    /*
     * Выведет минимальное количество операций для вычисления произведения матриц
     * В ходе выполнения задачи операции умножения разбиватются на подзадачи: рассматриваем все операции умножения и записываем их результаты:
     * Например как здесь. Имеем три матрицы: A1, A2, A3, произведение которых можно получить двумя способами:
     * (A1A2)A3 и A1(A2A3). Программа сделает следующее: Сначала найдет результаты умножения A1 и A2, A2 и A3.
     * Потом (A1A2)A3 и A1(A2A3) и из них выведет минимальный результат.
     * O(N^3) время
     */
    public static int multiplyOrder(int[] input) {
        int length = input.length - 1; // Получаем количество матриц
        int[][] alreadyFound = new int[length][length]; //Создаем и инициализиурем массив, который хранит результаты уже выполненныч операций

        for (int i = 0; i < length; ++i) {
            alreadyFound[i][i] = 0;
        }

        for (int operations = 1; operations < length; ++operations) { //Данный цикл - количество операции
            for (int firstMatrix = 0; firstMatrix < length - operations; ++firstMatrix) { //Данный цикл - перебор матриц по индексам(первый множитель)
                int secondMatrix = firstMatrix + operations; //Индекс второй матрицы(множителя)
                alreadyFound[firstMatrix][secondMatrix] = Integer.MAX_VALUE; //Изначально результат умножения ставим максимальным
                for (int util = firstMatrix; util < secondMatrix; ++util) { //Данный цикл - смена указателй на уже выполненные операции(нужен, т.к. результаты подоперации требуются для вычисления количества операции с данными матрицами)
                    alreadyFound[firstMatrix][secondMatrix] = Math.min(alreadyFound[firstMatrix][secondMatrix], //Записываем в результат либо то что есть
                            alreadyFound[firstMatrix][util] + alreadyFound[util + 1][secondMatrix] + input[firstMatrix] * input[util + 1] * input[secondMatrix + 1]);//либо сумму подоперации с обеими матрицами и количество операций для умножения данных матриц
                }
            }
        }
        return alreadyFound[0][length - 1];
    }

    public static void main(String[] args) {
        int[] test = { 10, 100, 5, 50 };
        System.out.println(MatrixChain.multiplyOrder(test));
    }
}