//
// Created by Jehan on 16/04/2016.
//

#include "LaboPiece.hpp"
#include <math.h>

LaboPiece::LaboPiece(std::string name, int nbLaboPiece, unsigned long long price, bool isBuyable,bool isBought) {
    m_name = name;
    m_nbLaboPiece = nbLaboPiece;
    m_isBought = false;
    m_isBuyable = false;
    m_price = price;
    m_YPS = (unsigned long long) (price * 0.2); //TODO To define
    m_YPSNextLvl = (unsigned long long)ceil((m_YPS + (price * 0.2)));
    m_level = 0;
}


LaboPiece::~LaboPiece() {

}

//TODO To define
void LaboPiece::nextLvl() {
    m_isBought = true;
    if(m_level <= 20){
        m_level++;
        m_price = (unsigned long long) (1.3 * m_price);
        m_YPS = (unsigned long long) (0.2 * m_price);
        m_YPSNextLvl = (unsigned long long) (0.3 * 1.3 * m_price) - m_YPS;
    }
}

unsigned long long LaboPiece::getYPS(){
    return m_YPS;
}

unsigned long long LaboPiece::getYPSNextLvl(){
    return m_YPSNextLvl;
}

void LaboPiece::setBuyable(){
    m_isBuyable = true;
}

bool LaboPiece::isBuyable(){
    return m_isBuyable;
}

unsigned long long LaboPiece::getPrice(){
    return m_price;
}

void LaboPiece::setBought() {
    m_isBought = true;
}
bool LaboPiece::isBought(){
    return m_isBought;
}

int LaboPiece::getLevel(){
    return m_level;
}