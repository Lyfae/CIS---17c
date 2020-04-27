/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

//libraries
#include <list>

//user libraries
#include "Player.h"

//constructor
Player::Player(){
    this->setPlayerTotal();
}

//add cards
void Player::addCards(Cards c){
    this->pCards.push_back(c);
}