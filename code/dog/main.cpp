#include "dog.h"
int main()
{
    int day=0;
    int ret;
    int _money,_lovepoint;
    Dog d1(3,1000,"dog",'M');
    Cat c1(2,"cat",'F');
    c1.firstsight();
    srand(time(NULL));

    while (1) {
        day ++;
        cout<< "the "<< day <<" day"<<endl;
        ret=rand()%3;
        switch (ret) {
        case 0:
            d1.send_flower(c1);
            break;
        case 1:
            d1.send_gift(c1);
            break;
        case 2:
            d1.angrry_to(c1);
            break;
        }
        _money=d1.get_money();
        _lovepoint=c1.get_lovepoint();
        if(_lovepoint >= 90){
            cout<<"success!"<<endl;
            break;
        }
        if(_money<=0 || _lovepoint<=0){
            cout<<"failed! bey!"<<endl;
            break;
        }

    }
    return 0;
}
