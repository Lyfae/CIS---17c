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

#include "Cards.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
//    
//    int num;
//    cin>>num;
//     
//    switch(num){
//        case 1: 
//            cout<<"Ace";
//            break;
//        case 2: 
//            cout<<"Two";
//            break;
//        case 3:
//            cout<<"Three";
//            break;
//        case 4:
//            cout<<"Four";
//            break;
//        case 5:
//            cout<<"Five";
//            break;
//        case 6:
//            cout<<"Six";
//            break;
//        case 7:
//            cout<<"Seven";
//            break;
//        case 8:
//            cout<<"Eight";
//            break;
//        case 9:
//            cout<<"Nine";
//            break;
//        case 10:
//            cout<<"Ten";
//            break;
//        case 11:
//            cout<<"Jack";
//            break;
//        case 12:
//            cout<<"Queen";
//            break;
//        case 13:
//            cout<<"King";
//        default: 
//            cout<<"Not applicable";
//    }
//            
//    //testing out playing cards
//    string a[52] = 
//    {"\U0001F0A1", "\U0001F0A2", "\U0001F0A3", "\U0001F0A4", "\U0001F0A5"
//   , "\U0001F0A6", "\U0001F0A7", "\U0001F0A8", "\U0001F0A9", "\U0001F0AA", "\U0001F0AB"
//   , "\U0001F0AD", "\U0001F0AE", "\U0001F0B1", "\U0001F0B2", "\U0001F0B3", "\U0001F0B4"
//   , "\U0001F0B5", "\U0001F0B6", "\U0001F0B7", "\U0001F0B8", "\U0001F0B9", "\U0001F0BA"
//   , "\U0001F0BB", "\U0001F0BD", "\U0001F0BE", "\U0001F0C1", "\U0001F0C2", "\U0001F0C3"
//   , "\U0001F0C4", "\U0001F0C5", "\U0001F0C6", "\U0001F0C7", "\U0001F0C8", "\U0001F0C9"
//   , "\U0001F0CA", "\U0001F0CB", "\U0001F0CD", "\U0001F0CE", "\U0001F0D1", "\U0001F0D2"
//   , "\U0001F0D3", "\U0001F0D4", "\U0001F0D5", "\U0001F0D6", "\U0001F0D7", "\U0001F0D8"
//   , "\U0001F0D9", "\U0001F0DA", "\U0001F0DB", "\U0001F0DD", "\U0001F0DE"};
//            
//    for(int i =0; i<52; i++){
//        cout<<a[i]<<endl;
//    } 
    
    for(int i = 0; i< 52; i++){
        Cards c(i);
        c.output();
    }

    

    return 0;
}

