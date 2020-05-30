#ifndef DOG_H
#define DOG_H
#include <iostream>
# include <cstring>
using namespace std;

class animal{
protected:
    int age;
    char name[20];
    char sex;
public:
    animal(){}

    animal(int _age,char *_name,char _sex)
    {
        age = a;
        strcpy(name,_name);
        sex = _sex;
    }

    void eat(){
        cout<< name <<" is eatting..."<<endl;
    }

};

class Cat : public animal{
private:
    int lovepoint;
public:
    Cat(int _age,const char* _name,char _sex):animal(age,_name,_sex){
        lovepoint = 0;
    }

    void firstsight(){
        srand(time(NULL));
        lovepoint = rand()%80;
    }

    void change_point(int num){
        lovepoint +=num;
    }
    char * get_name(){
        return name;
    }
    int get_lovepoint(){
        return lovepoint;
    }
};

class Dog : public animal{
private:
    int money;
public:
    Dog(int _age,int _money,const char* _name,char _sex):animal(age,_name,_sex){
        money = _money;
    }

    void send_flower(Cat &c){
        money = money - 50;
        c.change_point(10);
        cout << name <<" is send flower,money:"<< money <<endl;
    }
    void send_gift(Cat &c){
        money = money - 100;
        c.change_point(10);
       cout << name <<" is send gift,money:"<< money <<endl;
    }
    void angrry_to(Cat &c){
        c.change_point(-20);
        cout << name <<" angrry to:"<< c.get_name() <<endl;
    }
    int get_money(){
        return money;
    }

};



#endif // DOG_H
