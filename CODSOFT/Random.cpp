#include<iostream>
using namespace std;
int main(){
    int rand,guess;
    rand = 40;
    while(true){
        cout << "Guess the number: ";
        cin >> guess;
        if(guess>rand){
            cout << "The number you have guessed is higher than the number\n";
        }
        if(guess<rand){
            cout << "The number you have guessed is lower than the number\n";
        }
        if(guess==rand){
            cout << "Congratulations!  You have guessed the correct number\n";
            break;
        }
    }

}