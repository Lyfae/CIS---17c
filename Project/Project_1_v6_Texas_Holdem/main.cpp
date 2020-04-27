/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: serva
 *
 * Created on April 21, 2020, 11:49 AM
 */

#include <cstdlib>
#include <iostream>

#include "Dealer.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    //declare variables
    int players;
    
    //Poker...
    cout<<"Welcome to the game of Texas Hold'em!"<<endl;
    cout<<"How many players do we have today?"<<endl;
    cin>>players;
    while(players <=1){
        cout<<"Please enter a number greater than 1"<<endl;
        cin>>players;
    }
    //start the game
    Dealer game(players);
    
    
    
    

    return 0;
}

