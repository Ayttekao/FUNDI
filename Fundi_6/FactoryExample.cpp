//
// Created by ayttekao on 4/12/21.
//

#include <iostream>

using std::cout;

class Nature{
public:
    virtual void info() = 0;
    virtual ~Nature()= default; //<-- Виртуальный деструктор
};

class Man:public Nature{
public:
    void info() override{
        cout << "I'm is man!\n"; //<-- Информация на экран для наглядности
    }
};

class Animal:public Nature{
public:
    void info() override{
        cout << "I'm is animal!\n";//<-- Информация на экран для наглядности
    }
};


/*Создаём руководящий класс*/
class Factory{
public:
    virtual Nature* Create() = 0; //Чистая виртуальная функция показывает, что в производстве будет метод Create
    virtual ~Factory()= default;  //Виртуальный деструктор
};


/*Создаём производство*/
class ManFactory:public Factory{
public:
    Nature* Create() override{
        return new Man; //<-- Создаём объект типа "Человек"
    }
};

class AnimalFactory:public Factory{
public:
    Nature* Create() override{
        return new Animal;//<-- Создаём объект типа "Животное"
    }
};
/*Создали производство*/


/*Та самая функция, мозг выносящая*/
Nature* foo(Factory *value){
    return value->Create();
}


////////////////////////////
int main(){
    ManFactory man;         //Переменные для каждого подтипа
    AnimalFactory animal;

    Factory *ptr1 = &man;  //Указатели на объекты нужных типов
    Factory *ptr2 = &animal;

    ///////////////////////////
    Nature *ObjectNature1 = foo(ptr1); //Создали человечка
    Nature *ObjectNature2 = foo(ptr2); //Создали животное

    ObjectNature1->info(); //Вывели информацию. См выше, в методы info дописан вывод на экран.
    ObjectNature2->info();

    delete ObjectNature1, delete ObjectNature2; //Почистили память

}