//
// Created by Jehan on 16/04/2016.
//

#include <iostream>
#include "Labo.hpp"

Labo::Labo() {

    initLaboPieceVector();

    m_ScientificVector.push_back(new Scientific("Josette", 5, 1));
    m_ScientificVector.push_back(new Scientific("Yvonne", 5, 2));

    m_ptr_stats = new Stats();
    // Year of the first monster at 50
    m_ptr_monster = new Monster(50);
    m_YPS, m_CPS = 0;
    m_YPSBonus, m_CPSBonus = 1;
    m_money = 0;
    m_restartBonus = 1;
    m_year=0;
    m_reputationPointWaiting = 0;
    m_reputationPointOwned = 0;
    m_evolutionLevel = 1;


}

Labo::~Labo() {

}

//TODO Complete LaboPieceList
void Labo::initLaboPieceVector() {
    m_LaboPieceVector.empty();
    m_LaboPieceVector.push_back(new LaboPiece("Clicker", 1, 5, true, false));
    m_LaboPieceVector.push_back(new LaboPiece("2Flasks", 2, 10, false, false));
    m_LaboPieceVector.push_back(new LaboPiece("2TestTubes", 3, 20, false, false));
    m_LaboPieceVector.push_back(new LaboPiece("4TestTubes", 4, 60, false, false));
    m_LaboPieceVector.push_back(new LaboPiece("HeatingMantle", 5, 180, false, false));
    m_LaboPieceVector.push_back(new LaboPiece("HeatingMantleBalloon", 6, 540, false, false));
    m_LaboPieceVector.push_back(new LaboPiece("MagnifyingGlass", 7, 2160, false, false));
    m_LaboPieceVector.push_back(new LaboPiece("Microscope", 8, 8640, false, false));
    m_LaboPieceVector.push_back(new LaboPiece("PinkBurette", 9, 34560, false, false));
    m_LaboPieceVector.push_back(new LaboPiece("PinkFlaks", 10, 138240, false, false));
    m_LaboPieceVector.push_back(new LaboPiece("PurpleBallon", 11, 691200, false, false));
    m_LaboPieceVector.push_back(new LaboPiece("Equipment12", 12, 345600, false, false));
    m_LaboPieceVector.push_back(new LaboPiece("Equipment13", 13, 17280000, false, false));
    m_LaboPieceVector.push_back(new LaboPiece("Equipment14", 14, 86400000, false, false));
    m_LaboPieceVector.push_back(new LaboPiece("Equipment15", 15, 432000000, false, false));
    m_LaboPieceVector.push_back(new LaboPiece("Equipment16", 16, 2592000000, false, false));
    m_LaboPieceVector.push_back(new LaboPiece("Equipment17", 17, 15552000000, false, false));
    m_LaboPieceVector.push_back(new LaboPiece("Equipment18", 18, 93312000000, false, false));
    m_LaboPieceVector.push_back(new LaboPiece("Equipment19", 19, 559872000000, false, false));
    m_LaboPieceVector.push_back(new LaboPiece("Equipment20", 20, 3359232000000, false, false));
}

void Labo::lvlUpLaboPiece(unsigned int id) {
    m_YPS = m_YPS - m_LaboPieceVector.at(id)->getYPS();
    m_LaboPieceVector.at(id)->nextLvl();
    m_YPS = m_YPS + m_LaboPieceVector.at(id)->getYPS();
}

void Labo::lvlUpScientific(unsigned int type) {
    m_LaboPieceVector.at(type)->nextLvl();
    if(type == 1){
        m_CPSBonus = m_CPSBonus + 0.15;
        updateCPS();
    }
    else if(type == 2){
        m_YPSBonus = m_YPSBonus + 0.15;
        updateYPS();
    }
}

//TODO Rajouter bonus scientific
void Labo::updateYPS() {
    m_YPS = 0;
    for(unsigned int i = 1; i < m_LaboPieceVector.size(); i++ ){
        if(m_LaboPieceVector.at(i)->isBought())
            m_YPS = m_YPS + m_LaboPieceVector.at(i)->getYPS();
    }
    m_YPS *= m_YPSBonus;
    m_YPS *= m_restartBonus;
}

void Labo::updateCPS() {
    double percentage = 100;
    m_CPS = (unsigned long long) (percentage * m_LaboPieceVector.at(0)->getYPS());
    for(unsigned int i = 1; i < m_LaboPieceVector.size(); i++ ){
        percentage = percentage - i/2;
        m_CPS = (unsigned long long) (percentage * m_LaboPieceVector.at(i)->getYPS());
    }
    m_CPS *= m_CPSBonus;
    m_CPS *= m_restartBonus;
}


void Labo::restart() {
    m_ptr_stats->setActualMoney(0);
    m_restartBonus *= 1.1;
    m_reputationPointOwned += m_reputationPointWaiting;
    m_reputationPointWaiting;
    m_ptr_stats->incrementActualReputation(m_reputationPointOwned);
    m_ptr_stats->incrementTotalReputation(m_reputationPointOwned);
    initLaboPieceVector();
    updateYPS();
    updateCPS();
    m_YPS, m_CPS = 0;
    if(m_evolutionLevel > m_ptr_stats->getM_nbEvoMax()){
        m_ptr_stats->setNbEvoMax(m_evolutionLevel);
    }
    m_evolutionLevel = 1;
}

void Labo::evolution() {
    unsigned long long moneyGain = 0;
    if(m_evolutionLevel == 5 || m_evolutionLevel == 10 ||
            m_evolutionLevel == 15 || m_evolutionLevel == 20){
        m_reputationPointWaiting += 5 * m_evolutionLevel;
    }
    m_evolutionLevel ++;

    for(unsigned int i = 1; i < m_LaboPieceVector.size(); i++ ){
        if(m_LaboPieceVector.at(i)->isBought())
            moneyGain = m_LaboPieceVector.at(i)->getPrice();
    }
    m_money += moneyGain * 3;
    m_ptr_stats->incrementActualMoney(m_money);
    m_ptr_stats->incrementTotalMoney(m_money);
}

/**
 * Grant (YPS of the last item) / 10 money each sec
 * Upload also the time
 */
void Labo::grant(){

    unsigned long long moneyGain = 0;
    for(unsigned int i = 1; i < m_LaboPieceVector.size()-2; i++ ){
        if(m_LaboPieceVector.at(i)->isBought()){
            moneyGain = m_LaboPieceVector.at(i)->getYPS() / 10;
        }
    }
    m_year += m_YPS;
    m_ptr_stats->incrementSpentTime();
    if(m_year == m_ptr_monster->getAnnee()){
        // TODO : create function to auto-generate year of a monster
        m_ptr_monster->setAnnee(3000);
        m_year = 0;
    }
}

void Labo::click() {
    m_year += m_CPS;
    if(m_year == m_ptr_monster->getAnnee()){
        // TODO : create function to auto-generate year of a monster
        m_ptr_monster->setAnnee(3000);
        m_year = 0;
    }
}
unsigned long long Labo::getM_year(){
    return m_year;
}
void Labo::isPurchasablePiece(){
    for (int i = 0; i < m_LaboPieceVector.size(); ++i) {
        if(m_money >= m_LaboPieceVector.at(i)->getPrice()){
            m_LaboPieceVector.at(i)->setBuyable();
        }
    }
}
