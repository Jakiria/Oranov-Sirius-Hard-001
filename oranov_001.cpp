#include <iostream>
#include <clocale> //библиотека для установки локали (для вывода кириллицы)
#include <vector> //библиотека для векторов
#include <algorithm> //библиотека для фукнций для работе с векторами (пример: задача 3)
#include <string> //библиотека для функций для работы со строками и переводом переменных других типов в строки (пример: задача 4)

using namespace std;

//перечисление возможных окончаний чисел (для задачи 9)
enum possibleEndings { //перечисление возможных окончаний чисел (для задачи 9)
    zero = 0, one = 1, two = 2, three = 3, four = 4,
    five = 5, six = 6, seven = 7, eight = 8, nine = 9
};

//функция для проверки соответствия числа открывающих скобок числу закрытых (для задачи 2)
bool validParenthesesCheck(string current) { //функция для проверки соответствия числа открывающих скобок числу закрытых (для задачи 2)
    int bracketsCount = 0; //счётчик для проверки корректности пар скобок в строке
    for (char bracket : current) { //проверка осуществляется для символов в строке
        if (bracket == '(') bracketsCount++; // если символ в строке — открывающая скобка, то в счётчик добавить единицу
        else bracketsCount--; //иначе - убрать единицу

        if (bracketsCount < 0) return false; //если счётчик во время проверки станет отрицательным, то нужно немедленно оборвать проверку для текущей строки
    }

    return bracketsCount == 0;
}

//функция для определения нормально структурированных пар скобок (для задачи 2)
void findWellFormedParentheses(int pairNumber, string current) {
    int totalCorrentResults = 0; //счётчик для подсчёта корректных вариаций строки
    
    if (current.length() == pairNumber * 2) { //при наборе нужного числа скобок (в два раза больше, чем число пар), то проверить строку
        if (validParenthesesCheck(current)) { //если она корректная, то она будет выведена в консоль (вместе с отступом на следующую строку)
            cout << current << "\n";
        }
        return; //после чего сразу производится выход из итерации
    }

    //независимо от проверки текущего варианта нужно вызывать функцию с той же строкой дальше (перебор через итерации)
    findWellFormedParentheses(pairNumber, current + "(");
    findWellFormedParentheses(pairNumber, current + ")");
}

//функция для проверки пар скобок в строке (для задачи 4) (подобно функции проверки скобок для задачи 2)
int checkParenthesePairsLeft(int n, string parenthesesString) {
    int maximumLength = 0; //счётчики для символов в самой длинной подстроке корректно записанных скобок из строки и для символов в текщей подстроке
    int currentLength = 0;

    for (int i = 0; i < n; i++) { //основной цикл
        int leftBracketsCount = 0; //счётчики для подсчёта открывающих и закрывающих скобок
        int rightBracketsCount = 0;

        for (int j = i; j < n; j++) { //дополнительный цикл (нужен, чтобы функция обрабатывала строки, в которых сразу же встречается закрывающая скобка)
            if ((char)parenthesesString[j] == '(') leftBracketsCount++; //если символом на позиции i является открывающая скобка, то увеличить счётчик открывающих скобок
            else rightBracketsCount++; // иначе - увеличить счётчик закрывающих скобок
        }

        if (leftBracketsCount == rightBracketsCount) { //если в открывающих и закрывающих скобок поровну, то зафиксировать длину подстроки и проверить её
            currentLength = leftBracketsCount * 2; // запись текущей длины подстроки скобок
            if (currentLength > maximumLength) maximumLength = currentLength; //если она превышает старое значение, то отметить новую наибольшую длину подстроки
        }
    }
    
    return maximumLength;
}

//функция для проверки пар скобок в строке (для задачи 4) (подобно функции проверки скобок для задачи 2)
int checkParenthesePairsRight(int n, string parenthesesString) {
    int maximumLength = 0; //счётчики для символов в самой длинной подстроке корректно записанных скобок из строки и для символов в текщей подстроке
    int currentLength = 0;

    for (int i = n - 1; i >= 0; i--) { //основной цикл
        int leftBracketsCount = 0; //счётчики для подсчёта открывающих и закрывающих скобок
        int rightBracketsCount = 0;

        for (int j = i; j >= 0; j--) { //дополнительный цикл (нужен, чтобы функция обрабатывала строки, в которых сразу же встречается закрывающая скобка)
            if ((char)parenthesesString[j] == ')') rightBracketsCount++; //если символом на позиции i является открывающая скобка, то увеличить счётчик открывающих скобок
            else leftBracketsCount++; // иначе - увеличить счётчик закрывающих скобок
        }

        if (rightBracketsCount == leftBracketsCount) { //если в открывающих и закрывающих скобок поровну, то зафиксировать длину подстроки и проверить её
            currentLength = rightBracketsCount * 2; // запись текущей длины подстроки скобок
            if (currentLength > maximumLength) maximumLength = currentLength; //если она превышает старое значение, то отметить новую наибольшую длину подстроки
        }
    }

    return maximumLength;
}

//функция для определения совпадающих цифр в числах (для задачи 5)
int findRepeatingNumbers(string number, int repeatedDigits) {
    int foundRepeatedbuffer = repeatedDigits; //копирование изначального значения найденных чисел с повторяющимися цифрами (для избежания проблем с подсчётом)

    if (number.length() <= 1) { //если число имеет лишь одну цифру или не имеет их вовсе, то пропустить проверку
        return repeatedDigits = 0;
    }
    else {
        for (int i = 0; i < number.size() - 1; i++) { //цикл для проверки цифр в числе (двойной)
            for (int j = i + 1; j < number.size(); j++) {
                if (number[i] == number[j]) { //если будет совпадение, то отметить это в счётчике и выйти из циклов
                     repeatedDigits++;
                     break;
                }
            }
            if (repeatedDigits > foundRepeatedbuffer) break; //если во время проверки связки i-того числа с j-тым (до замены i-того) число было отмечено как найденное, то вырваться из цикла проверок
        }

        return repeatedDigits; //независимо от результатов проверки вернуть число чисел в повторяющимися цифрами
    }
}

// функция поиска максимального числа в массиве (задача 7)
int findMaxNumber(vector<int> array) {
    int maxFoundNumber = 0; //переменная для записи максимального числа в массиве

    for (int i = 0; i < array.size(); i++) {
        if (array[i] > maxFoundNumber) maxFoundNumber = array[i]; //если число массива больше найденного максимального, то переписать его
    }

    return maxFoundNumber;
}

// функция поиска второго максимального числа в массиве (задача 7)
int findSecondMaxNumber(vector<int> array) {
    int maxFoundNumber = 0; //переменная для записи максимального числа в массиве
    int secondMaxFoundNumber = 0; //второе максимальное число в массиве

    for (int i = 0; i < array.size(); i++) {
        if (array[i] > maxFoundNumber) maxFoundNumber = array[i]; //если число массива больше найденного максимального, то переписать его
    }

    for (int i = 0; i < array.size(); i++) {
        if (array[i] == maxFoundNumber) array[i] = 0; //если число массива больше найденного максимального, то переписать его
        if (array[i] > secondMaxFoundNumber) secondMaxFoundNumber = array[i]; // запись второго максимального числа в массиве по тому же принципу
    }

    for (int i = 0; i < array.size(); i++) { //восстановление нулевого значения до первого максимаьного
        if (array[i] == 0) array[i] = maxFoundNumber;
    }

    return secondMaxFoundNumber;
}

//функция для поиска равности всех чисел в массиве (задача)
bool findLogicalEnd(vector<int> array) {
    int smallestNumber = 1110; //самое малое число в массиве
    int smallestNumberIndex = 10000; //индекс самого малого числа в массиве
    int logicalCount = 0; //счётчик для определения логической остановки (должен быть равен n-1 для завершения работы)
    for (int i = 0; i < array.size(); i++) { //пункт 1: найти самое маленькое число в массиве
        if (array[i] < smallestNumber && array[i] > 0) {
            smallestNumber = array[i];
            smallestNumberIndex = i;
        }
    }

    for (int i = 0; i < array.size(); i++) { //поиск чисел помимо самого маленького, которые равны ему
        if (i == smallestNumberIndex) ;
        else {
            if (array[i] == smallestNumber) logicalCount++;
        }
    }

    if (logicalCount == array.size() - 1) return true; //если таких чисел в массиве ровно n-1, то работа закнчивается
    else return false; //иначе - нет
}

//функция для определения последнего числа в многоступенчатой степени (задача 9)
int findEndingNumber(int base, int power) {
    switch (base) { //логика работы функции: для основ, оканчивающихся на 0/1/5/6, конечное число при возведении в степень всегда равно концу;
                    //для основ 2/3/4/7/8 конечные числа при возведении в степень чередуются через каждые 4 шага; при основе 9 конечное число повторяется каждые 2 шага;
                    //проверяется всё остатком от деления на 8, поскольку это наиболее надёжный вариант;
                    //результат выполнения функции - конечная цифра числа, возведённого в степень
    case (zero):
        return 0;
        break;
    case (one):
        return 1;
        break;
    case (two):
        if (power % 8 == 1 || power % 8 == 5) return 2;
        else if (power % 8 == 2 || power % 8 == 6) return 4;
        else if (power % 8 == 3 || power % 8 == 7) return 8;
        else if (power % 8 == 4 || power % 8 == 0) return 6;
        break;
    case (three):
        if (power % 8 == 1 || power % 8 == 5) return 3;
        else if (power % 8 == 2 || power % 8 == 6) return 9;
        else if (power % 8 == 3 || power % 8 == 7) return 7;
        else if (power % 8 == 4 || power % 8 == 0) return 1;
        break;
    case (four):
        if (power % 2 == 1) return 4;
        else return 6;
        break;
    case (five):
        return 5;
        break;
    case (six):
        return 6;
        break;
    case (seven):
        if (power % 8 == 1 || power % 8 == 5) return 7;
        else if (power % 8 == 2 || power % 8 == 6) return 9;
        else if (power % 8 == 3 || power % 8 == 7) return 3;
        else if (power % 8 == 4 || power % 8 == 0) return 1;
        break;
    case (eight):
        if (power % 8 == 1 || power % 8 == 5) return 8;
        else if (power % 8 == 2 || power % 8 == 6) return 4;
        else if (power % 8 == 3 || power % 8 == 7) return 2;
        else if (power % 8 == 4 || power % 8 == 0) return 6;
        break;
    case (nine):
        if (power % 2 == 1) return 9;
        else return 1;
        break;
    }
}

//функция для запуска отдельных функций для задач
void taskNumberCheck(int taskNumber) {
    if(taskNumber == 1) { //задача 1
        int n = 0; //размер массива

        cout << "Задача 1:\nДан целочисленный массив на n элементов. " <<
                "Найдите элемент, который больше своих соседей в массиве, и выведите его индекс.\n" << 
                "Если таких элементов несколько, то выведите любой из их индексов.\nЭлементы с индексами -1 и n всегда равны -∞.\n" <<
                "Длина массива — от 1 до 1000, значения элемента массива и того, что идёт за ним, не равны.\n\n";

        cout << "Введите размер массива от 1 до 1000";
        cin >> n;
        while (n < 1 || n > 1000) { // для проверки ввода размера массива
            cout << "Ошибка ввода. Попробуйте ещё раз.\n";
            cin >> n;
        }

        int* numbersArray = new int[n]; //массив с числами

        for (int i = 0; i < n; i++) { //заполнение массива значениями от 0 до 100
            numbersArray[i] = rand() % 100;
        }

        for (int i = 0; i < n - 1; i++) { //проверка на повтор числа в массиве со следующим в массиве
            if (numbersArray[i] == numbersArray[i + 1]) {
                if (numbersArray[i] == -100) numbersArray[i] += 10;
                else if (numbersArray[i] == 100) numbersArray[i] -= 10;
                else numbersArray[i] += 1;
            }
        }

        int peakCounter = 0; //счётчик элементов, которые больше своих соседей
        int latestPeak = 0; //значение индекса наиболее позднего элемента, который больше своих соседей

        cout << "Итоговый массив: \n";
        for (int i = 0; i < n; i++) { //вывод массива для перепроверки за алгоритмом поиска потом
            if (i == 0) cout << numbersArray[i] << " | ";
            else if (i % 9 != 0) cout << numbersArray[i] << " | ";
            else cout << numbersArray[i] << "\n";
        }

        cout << "\n";

        for (int i = 0; i < n; i++) { //поиски элементов, которые больше своих соседей
            if (i == 0 && numbersArray[i + 1] < numbersArray[i]) { //условие проверки 1: первое число в массиве
                peakCounter++;
                latestPeak = i;
            }
            else if (i == 999 && numbersArray[i] > numbersArray[i-1]) { //условие проверки 2: последнее число в массиве
                peakCounter++;
                latestPeak = i;
            }
            else if (numbersArray[i] > numbersArray[i - 1] && numbersArray[i] > numbersArray[i + 1]) { //условие проверки 3: для всех остальных элементов массива
                peakCounter++;
                latestPeak = i;
            }
        }

        if (peakCounter != 0) { //если хоть один пик будет найден, то будут выведены общее число пиков и последний из них
            cout << "Всего элементов, которые больше своих соседей: " << peakCounter << "\n";
            cout << "Самый поздний индекс: " << latestPeak << ", значение: " << numbersArray[latestPeak];
        }
        else cout << "Пиковые значения в массиве не найдены."; //иначе — сообщение об их отсутствии
    }
    else if (taskNumber == 2) { //задача 2
        cout << "Задача 2.\nДаны n пар скобок. Напишите функцию, которая выведет все комбинации корректно записанных скобок с заданным числом пар скобок.";

        int n = 0; //число пар открывающих и закрывающих скобок
        int correctResults = 0; //число
        string currentVariant; //строка для текущего в цикле варианта

        cout << "Введите число открывающих и закрывающих скобок n от 1 до 8: ";
        cin >> n; //ввод числа пар открывающих и закрывающих скобок
        while (n < 1 || n > 8) {
            cout << "Введено некорректное число. Введите число от 1 до 8:\n";
            cin >> n;
        }

        cout << "Нормально структурированные пары скобок:\n";
        findWellFormedParentheses(n, currentVariant); //вызов функции для поиска и вывода нормально структурированных пар скобок
    }
    else if (taskNumber == 3) { //задача 3
        cout << "Задача 3.\nДаны два отсортированных целочисленных массива размеров n и m соответственно.\nСлейте их вместе и найдите среднее значение нового массива.\n";
        vector<int> arrayOne, arrayTwo; //массивы для целых чисел
        int n = 0, m = 0; //указатели размеров для массивов

        //ввод размеров массивов
        cout << "Введите значение размера первого массива:\n";
        cin >> n;
        while (n < 0 || n > 1000) {
            cout << "Ошибка ввода. Попробуйте ещё раз.\n";
            cin >> n;
        }
        cout << "Введите значение размера второго массива:\n";
        cin >> m;
        while (m < 0 || m > 1000) {
            cout << "Ошибка ввода. Попробуйте ещё раз.\n";
            cin >> m;
        }

        //присвоение размеров массивам
        arrayOne.resize(n);
        arrayTwo.resize(m);

        //заполнение массивов числами
        for (int i = 0; i < n; i++) arrayOne[i] = rand() % 30;
        for (int i = 0; i < m; i++) arrayTwo[i] = rand() % 30;

        //вывод изначальных массивов
        cout << "Первый массив:\n";
        for (int i = 0; i < arrayOne.size(); i++) cout << arrayOne[i] << " ";
        cout << "\n";
        cout << "Второй массив:\n";
        for (int i = 0; i < arrayTwo.size(); i++) cout << arrayTwo[i] << " ";
        cout << "\n";

        //сортировка массивов (в условии задачи не сказано, что нужно приводить массивы сразу в упорядоченном виде)
        sort(arrayOne.begin(), arrayOne.end());
        sort(arrayTwo.begin(), arrayTwo.end());

        vector<int> mergedArray; //третий массив, для отсортированного
        mergedArray.resize(arrayOne.size() + arrayTwo.size());
        std::merge(arrayOne.begin(), arrayOne.end(), arrayTwo.begin(), arrayTwo.end(), mergedArray.begin()); //слияние массивов в третий, отсортированный

        int numbersSum = 0; //переменная для суммы чисел итогового массива
        for (int i = 0; i < mergedArray.size(); i++) numbersSum += mergedArray[i]; //получение суммы чисел итогового массива

        double arraysMedian = (double)numbersSum / mergedArray.size(); // получение среднего значения элементов итогового массива

        for (int nums : mergedArray) cout << nums << " "; //вывод отсортированного массива
        cout << "\nСреднее значение элементов массивов: " << arraysMedian;

    }
    else if (taskNumber == 4) { //задача 4
        cout << "Задача 4.\nДана строка, состоящая только из символов '(' И ')'.\nНайдите и выведите длинную длиннейшей подстроки с корректно собранными скобками.\n";
        string parenthesesString; //строка для хранения записанных скобок
        int maximumSequence = 0; //переменная для хранения максимальной последовательности корректно собранных скобок
        
        cout << "Введите строку из открывающих и закрывающих скобок: ";
        cin >> parenthesesString; //ввод строки

        if (parenthesesString.size() <= 1) return; // если строка пустая или имеет всего один символ, то длина подстроки составит 0
        else { //иначе - проверять
            int n = parenthesesString.size(); //получение размера строки
            maximumSequence = checkParenthesePairsLeft(n, parenthesesString); //вызов функции для расчёта длины подстроки (ориентируясь на левую часть)

            if (maximumSequence == 0) maximumSequence = checkParenthesePairsRight(n, parenthesesString); //если результат не получился, то провести расчёт, опираясь на правую часть

            cout << "Длина наибольшей подстроки: " << maximumSequence;
        }
    }
    else if (taskNumber == 5) { //задача 5
        cout << "Задача 5.\nДано число n от диапазона [1; n]. Найдите число чисел в диапазоне от 1 до n включительно," <<
            "в которых есть хотя бы одна повторяющаяся цифра.\nПримеры: 11, 22, 101, 1000 и т.д.\n";
        
        int n = 0; //верхняя граница диапазона для работы
        int repeatedDigitsTotalNumber = 0; //переменная для записи числа чисел с повторяющимися цифрами

        cout << "Введите значение верхней границы n:\n";
        cin >> n; //ввод значения для n
        while (n < 1 || n > 1000000000) {
            cout << "Введено некорректное значение. Попробуйте ещё раз.\n";
            cin >> n;
        }

        for (int i = 1; i <= n; i++) { //цикл для инициализации проверки всех чисел от единицы до введённого включительно
            string charNumber = std::to_string(i);
            repeatedDigitsTotalNumber = findRepeatingNumbers(charNumber, repeatedDigitsTotalNumber);
        }

        cout << "Итого чисел с повторяющимися цифрами: " << repeatedDigitsTotalNumber; //вывод результата работы функции для поиска чисел с повторяющимися цифрами
    }
    else if (taskNumber == 6) { //задача 6
        cout << "Задача не реализована.";
    }
    else if (taskNumber == 7) { //задача 7
        cout << "Задача 7.\nДан массив положительных целых чисел, которые нужно обработать по следующему правилу: если X[i] > X[j], то их X[i] вычитается X[j].\n" <<
                "Когда подобные преобразования более невозможны, выведите сумму элементов получившегося массива.";

        vector<int> numbersArray; //массив для чисел задачи
        int n = 0; //размерность массива
        int maxNumber = 0; //максимальное число в массиве
        int secondMaxNumber = 0; //второе по величине число в массиве
        int maxNumberIndex = 0; //индекс самого большого числа в массиве
        int secondMaxNumberIndex = 0; //индекс второго большого числа в массиве
        int stepCount = 0; //счётчик для числа шагов в работе с массивом
        int numbersSum = 0; //переменная для суммы всех элементов в итоге

        cout << "Введите размерность массива n: ";
        cin >> n; //ввод размерности массива n
        
        numbersArray.resize(n); //назначение размерности для самого массива

        for (int i = 0; i < n; i++) numbersArray[i] = rand() % 1000; //предел значений: от 0 до 1000

        cout << "Рабочий массив:\n";
        for (int number : numbersArray) cout << number << "|";
        cout << "\n";

        while (!findLogicalEnd(numbersArray)) { //пока все числа не сведутся к одному минимальнейшему в ходе работы, вести расчёты
            stepCount++;
            maxNumber = findMaxNumber(numbersArray); //извлечение самых больших чисел массива
            secondMaxNumber = findSecondMaxNumber(numbersArray);
            for (int i = 0; i < numbersArray.size(); i++) { //найти индексы нужных элементов, используя их значения
                if (numbersArray[i] == maxNumber) maxNumberIndex = i;
                if (numbersArray[i] == secondMaxNumber) secondMaxNumberIndex = i;
            }
            numbersArray[maxNumberIndex] -= numbersArray[secondMaxNumberIndex]; //расчёт нового значения для максимального

            cout << "Шаг " << stepCount << ": "; // вывод массива после каждого шага
            for (int i = 0; i < numbersArray.size(); i++) {
                cout << numbersArray[i] << " | ";
            }
            cout << "\n";
        }

        for (int i = 0; i < numbersArray.size(); i++) { //расчёт и вывод суммы элементов массива в итоге
            numbersSum += numbersArray[i];
        }

        cout << "Минимальнейшая сумма элементов массива: " << numbersSum;
    }
    else if (taskNumber == 8) { //задача 8
        cout << "Задача не реализована.";
    }
    else if (taskNumber == 9) { //задача 9
        cout << "Задача 9.\nДля некоторого массива [x1, x2, x3, ..., xn] вычислите последнюю цифру в результате выражения x1 ^ (x2 ^ (x3 ^ (... ^ xn))).";

        vector<int> equationNumbers; //массив с числами для многоступенчатой степени (первое число - всегда основа степени)
        int n; //размерность массива чисел
        int endingNumber = 0; //переменная для хранения последних цифр чисел, возведённых в степень

        cout << "Введите размерность массива n: ";
        cin >> n; //ввод размера массива

        equationNumbers.resize(n); //назначение размера массиву
        for (int i = 0; i < n; i++) {
            equationNumbers[i] = rand() % (9 - 1 + 1) + 1; //задаваемые числа: от 1 до 9
            cout << equationNumbers[i] << " | "; //и параллельный вывод массива в консоль
        }

        for (int i = n - 2; i >= 0; i--) { //разбор многоступенчатой степени до основания
            endingNumber = findEndingNumber(equationNumbers[i], equationNumbers[i + 1]);
        }

        cout << "\nИтоговое конечное число после возведения в степени: " << endingNumber; //вывод результата
    }
    else if (taskNumber == 10) { //задача 10
        cout << "Задача не реализована.";
    }
    else cout << "Введено некорректное число."; //число за пределами [1; 10]
}

int main() {
    int task = 0;
    std::setlocale(LC_ALL, "Russian"); //установка локали на русский язык
    cout << "Введите номер сложной задачи от 1 до 10:\n";
    cin >> task; //ввод номера сложной задачи
    while (task < 1 || task > 10) { //проверка ввода (если допущена ошибка - вводить число, пока оно не будет в промежутке [1; 10]
        cout << "Введено некорректное число. Введите число от 1 до 10: ";
        cin >> task;
    }

    taskNumberCheck(task); //обращение к функции для выбора определённый задачи

    return 0;
}