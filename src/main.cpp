#include "../include/array.h"
#include "../include/rectangle.h"
#include "../include/rhombus.h"
#include "../include/trapezoid.h"
#include <iostream>
#include <string>
#include <memory>

int main()
{
    std::cout << "Демонстрация ввода аргуметов фигуры A (прямоугольник с аргументами double) из потока cin:" << std::endl;
    Rectangle<double> A;
    std::cout << "Введите начальные координаты левой нижней точки фигуры A, ширину и высоту (x_0 y_0 width height)" << std::endl;
    std::cin >> A;
    std::cout << "Результат - вывод координат вершин фигуры A (x, y): " << A << std::endl;
    std::cout << std::endl;

    std::cout << "Демонстрация ввода аргументов фигуры B (ромб) через код" << std::endl;
    Rhombus<double> B(Point<double>(1.1, 2.1), 5.0, 3.0);
    std::cout << "Результат работы строки кода ... Rhombus<double> B(Point<double>(1.1, 2.1), 5.0, 3.0); ... : " << B << std::endl;
    std::cout << std::endl;

    std::cout << "Создадим ещё двe фигуры:\nФигуру C (трапеция с аргументами double) и фигуру D (прямоугольник - при помощи конструктора копирования фигуры A)" << std::endl;
    Trapezoid<double> C(Point<double>(3.11, 4.5), 10.0, 5.0);
    Rectangle<double> D(A);
    std::cout << "Результат - координаты вершин фигуры C: " << C << std::endl;
    std::cout << "Результат - координаты вершин фигуры D: " << D << std::endl;
    std::cout << std::endl;

    std::cout << "Вычислим геометрические центры фигур вращения A B C D" << std::endl;
    auto centerA = A.center();
    auto centerB = B.center();
    auto centerC = C.center();
    auto centerD = D.center();
    std::cout << "Результат - координаты центра фигуры A: (" << centerA.get_x() << ", " << centerA.get_y() << ")" << std::endl;
    std::cout << "Результат - координаты центра фигуры B: (" << centerB.get_x() << ", " << centerB.get_y() << ")" << std::endl;
    std::cout << "Результат - координаты центра фигуры C: (" << centerC.get_x() << ", " << centerC.get_y() << ")" << std::endl;
    std::cout << "Результат - координаты центра фигуры D: (" << centerD.get_x() << ", " << centerD.get_y() << ")" << std::endl;
    std::cout << std::endl;

    std::cout << "Вычислим поотдельности площади фигур вращения A B C D, путём неявного приведения к double" << std::endl;
    std::cout << "Результат - площадь фигуры A: " << double(A) << std::endl;
    std::cout << "Результат - площадь фигуры B: " << double(B) << std::endl;
    std::cout << "Результат - площадь фигуры C: " << double(C) << std::endl;
    std::cout << "Результат - площадь фигуры D: " << double(D) << std::endl;
    std::cout << std::endl;

    std::cout << "Продемонстрируем вычисление центра, площадей фигур, а также общую площадь фигур A B C D, которые занесём в массив Data" << std::endl;
    Array<Figure<double>> Data;
    std::shared_ptr<Figure<double>> figA = std::make_shared<Rectangle<double>>(A);
    std::shared_ptr<Figure<double>> figB = std::make_shared<Rhombus<double>>(B);
    std::shared_ptr<Figure<double>> figC = std::make_shared<Trapezoid<double>>(C);
    std::shared_ptr<Figure<double>> figD = std::make_shared<Rectangle<double>>(D);
    Data.add(figA);
    Data.add(figB);
    Data.add(figC);
    Data.add(figD);

    std::cout << "Размер массива Data после занесения фигур A B C D: " << Data.get_size() << std::endl;
    std::cout << "Посмотрим на первый элемент массива (Фигура A) и выведем для неё координаты центра и площадь соответственно: ";
    centerA = Data[0]->center();
    std::cout << "Результат - координаты центра фигуры A как первого элемента массива и площадь фигуры: (" << centerA.get_x() << ", " << centerA.get_y() << "), " << double(*Data[0]) << std::endl;
    std::cout << "Выведем общую площадь фигур массива: " << Data.total_area() << std::endl;
    std::cout << "Удалим первый элемент массива" << std::endl;
    Data.remove(0);
    std::cout << "Длина массива теперь: " << Data.get_size() << std::endl;
    std::cout << std::endl;
    std::cout << "Заметим, что сам элемнет удалился только из массива, но всё равно существует как отдельный объект" << std::endl;
    std::cout << "Координаты фигуры A, удалённой из массива: " << A << std::endl;
    std::cout << std::endl;

    std::cout << "Скопируем массив Data в массив Data_copy при помощи оператора = и сравним их при помощи ==" << std::endl;
    Array<Figure<double>> Data_copy;
    Data_copy = Data;
    std::cout << std::boolalpha;
    std::cout << "Результат работы оператора == : " << (Data_copy == Data) << std::endl;
    return 0;
}
