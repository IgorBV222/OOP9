#include <iostream>
#include <utility>
#include <string>
#include <map>
#include <tuple> //кортеж
#include <vector>
#include <unordered_map>


//НАСЛЕДОВАНИЕ ШАБЛОННЫХ КЛАССОВ
template <class T>
class Shape {
public:
    Shape(T width, T height): _width(width), _height(height){
        std::cout << "Constructor Shape()" << std::endl;
    }
   
    T calculateSquare() {
        return _width * _height;
    }

private:
    T _width;
    T _height;
};

//наследуем
template <class T>
class Square : public Shape<T> {
public:// публичное наследование - публичные методы родителя останутся публичными и у наследника
    Square(T width, T height ) : 
        Shape<T>(width, height), //вызвали конструктор родителя
        _width(width){
        std::cout << "Constructor Square()" << std::endl;
    }
    
    T calculateSquare() {
        return _width * _width;
    }

private:
    T _width;
};

//Пачки параметров и сверстки -Вариабелбные шаблоны классов
//template <typename ... T>
//auto sum_all(T ... args) {return (args + ...);} - сумма всех аргументов начиная с последнего
//void print_all (T ... args) {(std::cout << ...<< args) << std::endl;} - вывод всех
template <typename ... Types> // void func(Types ... args) - можно использовать в функции
class MyClass {
public:
    void print_all(Types ... args) {
        std::cout << sizeof ... (args) << std::endl;
        (std::cout << ... << args) << std::endl;
    }
};

//самый часто встречающийся элемент
class DataManager {
public:
    int mostSearchedKey() {
        std::unordered_map<int, int> keyAmount;
        for (size_t i = 0; i < _keys.size(); i++) {
            const auto& [it, isInserted] = keyAmount.insert({ _keys[i], 1 });
            if (!isInserted) {
                auto value = it->second; // обращение к 2-му элементу пары
                value++;
                keyAmount[_keys[i]] = value; // принудительно вставляет value ; <1, 2>;;;; <2, 1>
                //_keys[1]=2
            }
        }
        std::pair<int, int> key_biggestValue = { 0,0 };
        for (std::unordered_map <int, int>::const_iterator it = keyAmount.begin(); it != keyAmount.end(); it++) {
            if (key_biggestValue.second < it->second) {
                key_biggestValue = std::make_pair(it->first, it->second);
            }
        }
        return key_biggestValue.first;
    }
private:
    std::vector<int> _keys = { 1, 1, 2, 2, 2, 4, 6, 2, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2 };
};



//НАСЛЕДОВАНИЕ ШАБЛОННЫХ КЛАССОВ
int main()
{
    //самый часто встречающийся элемент
    /*DataManager dm;
    std::cout << dm.mostSearchedKey() << std::endl;
    std::cout << "==================================\n";*/


    //НАСЛЕДОВАНИЕ ШАБЛОННЫХ КЛАССОВ
    Square<int> s(5, 4);
    std::cout << s.calculateSquare() << std::endl; // собственная функция наследника
    std::cout << s.Shape<int>::calculateSquare() << std::endl; //функция от родителя

    //Пачки параметров и сверстки

    MyClass <int, double, float, std::string> args;
    int x = 1;
    double y = 3.14;
    float z = 2.5f;
    std::string str = "Hy!";    
    args.print_all(x, y, z, str);
    
}


