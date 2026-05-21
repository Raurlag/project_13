#include <iostream>
#include <string>
#include <cmath>

using namespace std;

//БАЗОВЫЙ КЛАСС Figure
class Figure
{
protected:
    string name;
    double area;

    static double totalArea;  //суммарная площадь

public:
    Figure(string name = "Unknown", double area = 0)
    {
        this->name = name;
        this->area = area;
        totalArea += area;  // суммируем площади
    }

    //Виртуальные функции
    virtual void print()   // вывод информации о фигуре
    {
        cout << "Figure: " << name << " Area: " << area << endl;
    }

    virtual string type()  // возвращает тип фигуры
    {
        return "Figure";
    }

    static double getTotalArea()  // возвращает суммарную площадь всех фигур
    {
        return totalArea;
    }

};

double Figure::totalArea = 0; //определение статического члена вне класса



class Rectangle : public Figure //Прямоугольник
{
private:
    double width, height;

public:
    Rectangle(string name, double width, double height)
        : Figure(name, width* height)  // площадь = width * height
    {
        this->width = width;
        this->height = height;
    }

    void print()
    {
        cout << "Прямоугольник: " << name << " Размеры:" << width << "x" << height << " Площадь:" << area << endl;
    }

    string type()
    {
        return "Rectangle";
    }
};



class Triangle : public Figure //Треугольник
{
private:
    double base, height;

public:
    Triangle(string name, double base, double height)
        : Figure(name, 0.5 * base * height)  // площадь = 0.5 * base * height
    {
        this->base = base;
        this->height = height;
    }

    void print()
    {
        cout << "Треугольник: " << name << " Основание:" << base << " Высота:" << height << " Площадь:" << area << endl;
    }

    string type()
    {
        return "Triangle";
    }
};


//ШАБЛОННЫЙ КЛАСС Set
template<typename T>
class Node   ///Базовый элемент для хранения данных в связном списке
{
public:
    T data;          // хранимые данные
    Node* next;      // указатель на следующий узел

    Node(T data, Node* nNode = nullptr)
    {
        this->data = data;
        next = nNode;
    }
};


template<typename T>
class Set   ///множество set
{
private:
    Node<T>* head; //первый узел списка
    int count;   //Кол-во элементов

public:
    Set() //сначала пустое
    {
        head = nullptr;
        count = 0;
    }

    bool isEmpty()  //Проверка пустое ли множество
    {
        return head == nullptr;
    }

    int getSize() const    //Возвращает кол-во элементов
    {
        return count;
    }

    // Проверка принадлежности элемента множеству
    bool contains(const T& value) const
    {
        Node<T>* current = head;
        while (current != nullptr)
        {
            if (current->data == value)
                return true;
            current = current->next;
        }
        return false;
    }

    //ОПЕРАТОРЫ

    // Оператор () - конструктор множества (добавляем элемент, исключая дубликаты)
    Set<T>& operator()(const T& value)
    {
        if (!contains(value)) //Если нет элемента
        {
            if (head == nullptr) //Если список пуст
            {
                head = new Node<T>(value); //Задаем новый элемент
            }
            else
            {
                Node<T>* current = head;
                while (current->next != nullptr)
                {
                    current = current->next;
                }
                current->next = new Node<T>(value);
            }
            count++;
        }
        return *this;
    }

    // Оператор + для добавления элемента
    Set<T>& operator+(const T& value)
    {
        return operator()(value);
    }

    // Оператор + для объединения множеств
    Set<T> operator+(const Set<T>& other) const
    {
        Set<T> result;

        // Добавляем все элементы из текущего множества
        Node<T>* current = head;
        while (current != nullptr)
        {
            result(current->data);
            current = current->next;
        }

        // Добавляем все элементы из другого множества
        current = other.head;
        while (current != nullptr)
        {
            result(current->data);
            current = current->next;
        }

        return result;
    }

    // Оператор <= для проверки на подмножество
    bool operator<=(const Set<T>& other) const
    {
        Node<T>* current = head;
        while (current != nullptr)
        {
            if (!other.contains(current->data))
                return false;
            current = current->next;
        }
        return true;
    }

    void print()
    {
        Node<T>* current = head;
        while (current != nullptr)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};


// Специализация для Figure* (чтобы выводить через print())
template<>
void Set<Figure*>::print()
{
    Node<Figure*>* current = head;

    while (current != nullptr)
    {
        current->data->print();
        current = current->next;
    }
}


//ГЛАВНАЯ ФУНКЦИЯ
int main()
{
    setlocale(LC_ALL, "Russian");

    //ЧАСТЬ B: Демонстрация иерархии фигур
    cout << "B: Иерархия фигур" << endl;

    Rectangle rect1("Rect X", 4, 3);
    Rectangle rect2("Rect Y", 2, 8);
    Triangle tri1("Triangle Z", 10, 5);
    Triangle tri2("Triangle W", 7, 4);

    cout << "\nФигуры" << endl;
    rect1.print();
    rect2.print();
    tri1.print();
    tri2.print();

    cout << "\nСуммарная площадь всех фигур: " << Figure::getTotalArea() << endl;

    //C: Шаблонный класс множества
    cout << "\nC: Шаблонный класс множества" << endl;

    // Множество геометрических фигур
    cout << "\nМножество геометрических фигур" << endl;
    Set<Figure*> figureSet;   //множество указателей на фигуры

    //Добавляем адреса фигур в множество
    figureSet + &rect1;
    figureSet + &rect2;
    figureSet + &tri1;
    figureSet + &tri2;

    figureSet.print();



    // Проверка оператора <= (подмножество)
    Set<Figure*> figureSet2;
    figureSet2 + &rect1;
    figureSet2 + &tri1;

    cout << "\nПроверка подмножества (<=): ";
    cout << "figureSet2 <= figureSet: " << (figureSet2 <= figureSet ? "true" : "false") << endl;

    // Множество действительных чисел
    cout << "\nМножество действительных чисел" << endl;
    Set<double> doubleSet1;
    Set<double> doubleSet2;

    // Используем оператор () для добавления элементов
    doubleSet1(3.14)(2.718)(1.414)(2.718);
    doubleSet2(3.14)(1.618)(2.718);

    cout << "Множество 1: ";
    doubleSet1.print();
    cout << "Множество 2: ";
    doubleSet2.print();

    // Объединение множеств (оператор +)
    Set<double> unionSet = doubleSet1 + doubleSet2;
    cout << "\nОбъединение множеств (doubleSet1 + doubleSet2): ";
    unionSet.print();

    // Проверка подмножества
    cout << "doubleSet1 <= unionSet: " << (doubleSet1 <= unionSet ? "true" : "false") << endl;
    cout << "doubleSet1 <= doubleSet2: " << (doubleSet1 <= doubleSet2 ? "true" : "false") << endl;

    return 0;
}