/* 
 * File:   main.cpp
 * Author: scotera
 *
 * Created on May 1, 2014, 5:54 AM
 */
#include <ctime>

#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
using namespace std;

struct character{
    
public :
    int maxHP, maxMP, DEF, ATK, AGI,curHP;
    int maxXP, curXP;
    int level;
    string name;
    string model;
    
    
    void addXP(character&,int);
    void levelUP(character&);
    character(); //default character, initializes with main characters stats
    character(string, string);//custom character must initialize with stats
    void setStats( int, int, int, int, int);
} ;

character::character(){ 
    name = "main character", 
    model = "Model name";
    level = 1;
    maxXP = 20;
    curXP = 0;
    AGI = 5;
    ATK = 15;
    DEF = 10;
    maxHP = 30;
    maxMP = 10;
    curHP = 30;
}

character::character(string id, string sprite){
    name = id; 
    model = sprite;
}

void character::addXP(character &c, int xp){
    c.curXP += xp;
    if(c.curXP >= c.maxXP)
       levelUP(c);
        
}

void character::levelUP(character &c){ 

    c.level += 1;
    c.curXP = 0;
    c.maxXP *= 2;
    c.AGI *= 1.2;
    c.ATK *= 1.2;
    c.DEF *= 1.2;
    c.maxHP += 10;
    c.maxMP += 2;
    c.curHP = maxHP;
}
    
void  character::setStats( int hp, int mp, int def, int atk, int agi){
    AGI=agi;
    ATK=atk;
    DEF=def;
    maxHP=hp;
    maxMP=mp;
    curHP=hp;
    
}

struct weakNPC : public character{
       
weakNPC(string, string );
    
    
} ;
weakNPC::weakNPC(string a, string b){
    character();
    this->setStats(5,5,10,5,5);
    this->name = a;
    this->model = b;
}


struct averageNPC : public character{
    

     string atk1,atk2,atk3;

    averageNPC(string, string );
    
} ;

averageNPC::averageNPC(string a, string b){
    character();
    this->setStats(10,5,10,5,10);
    this->name = a;
    this->model = b;
}

struct strongNPC : public character{
    

     string atk1,atk2,atk3;

    strongNPC(string, string );
    
} ;

strongNPC::strongNPC(string a, string b){
    character();
    this->setStats(20,10,10,15,15);
    this->name = a;
    this->model = b;
}

struct bossNPC : public character{
    bossNPC(string, string );
};

bossNPC::bossNPC(string a, string b){
    character();
    this->setStats(30,20,13,10,12);
    this->name = a;
    this->model = b;
}

struct combat {
    
public:   
    int numTARGETS;
    
    void poisoned(character&);
    int confusedATK(int );
    void setBLIND(character&);
    void unsetBLIND(character&);
    bool checkHIT(int&, int&);
    bool checkCrit(int&, int&);
    void setHp(character&, int);
    combat();
};

combat::combat(){};

void poisoned(character& c){
    c.curHP *= .85;
}

void setBLIND(character& c){
    c.ATK *= .5;
}

void unsetBLIND(character& c){
    c.ATK *= 2;
}

bool combat::checkHIT(int &attack, int &defense){//difference of targets defense from attacker 
    int r = rand() % 21;
    if( r  <= (10 + attack - defense)){
        
        return true;
    }
    return false;
}

void combat::setHp(character &c, int change){//Change needs to be negative value if heal is used
    c.curHP = c.curHP - change;
    if(c.curHP >= c.maxHP)
        c.curHP = c.maxHP;
}

int combat::confusedATK(int targets){//uses number of characters on field to return a value that picks which character to hit
     int r = rand() % targets + 1;   
     return r;
}

bool combat::checkCrit(int &enemAgi, int &pcAgi){//crit chance is the difference in AGI between targets
    int r = rand() % 101;
    if( r  <= (pcAgi - enemAgi)){
        return true;
    }
    return false;
}

struct skills {
    
    bool autoCRIT(character ,character);
    void raiseDEF(character &);
    void endRaiseDEF(character&);
    bool HEAL(character ,character);
    bool AOE(character ,character);
    
};

bool skills::autoCRIT(character hero, character enemy){//halves attack stat to guarentee crit
     combat a;
     hero.ATK *=.6;
     if(a.checkHIT(hero.ATK,enemy.DEF))
         return true;     
  }

void skills::raiseDEF(character &a){
    a.ATK *= 1.6;
    a.DEF *= 2;
}

void skills::endRaiseDEF(character &a){
    a.ATK *= .7;
    a.DEF *= .5;
}

bool isDead(int &curHP){//returns true for hp <= 0
	 if (curHP <= 0){
		curHP=0;
	 return	true;
	 }
         return false;
}




void testKIT(){
    std::srand(std::time(0));
    string a  = "demon";
    string b  = "testChar";
    string e = "rat";
    string f = "testerID";
    combat c;
    skills g;
    weakNPC rat(f,a);
    
    character test;
    character wuss(b,a);
    wuss.setStats(10,5,15,5,9);
  
     
 
    printf("\n===============================================================\n");
  
       
    for(int i = 0; i <3; i++){
    if(g.autoCRIT(test, wuss)){
        int r = rand() % 5;
       
         printf("%d = 2x double damage!\n", r);
          r= r*2.5;
//        c.setHp(wuss, r);
       
        r = 0;
    } 
    }
    
    
    if(isDead(wuss.curHP)){
    printf("%s          is DEAAAAAAAAAAAAAAAAAAAD",wuss.name.c_str());  
    }
    
    poisoned(wuss);poisoned(wuss);poisoned(wuss);
    
    test.addXP(test,10);
    test.addXP(test,14);
    printf("\nHp = %d\nmp = %d\ndef = %d\natk = %d\nagi = %d\n\n", test.maxHP,test.maxMP,test.DEF,test.ATK,test.AGI);
    printf("\nmaxxp = %d\ncurxp = %d\nlevel = %d\ncurhp = %d\n", test.maxXP,test.curXP,test.level,test.curHP); 
 
    
    printf("%s",rat.name.c_str());
    printf("'s current hp is %d. \n", rat.curHP );

    
     printf("\nHpmax = %d\nmp = %d\ndef = %d\natk = %d\nagi = %d\n\n", rat.maxHP,rat.maxMP,rat.DEF,rat.ATK,rat.AGI); 
        g.raiseDEF(rat);  
    printf("\nHpmax = %d\nmp = %d\ndef = %d\natk = %d\nagi = %d\n\n", rat.maxHP,rat.maxMP,rat.DEF,rat.ATK,rat.AGI); 
      g.endRaiseDEF(rat);  
    printf("\nHpmax = %d\nmp = %d\ndef = %d\natk = %d\nagi = %d\n\n", rat.maxHP,rat.maxMP,rat.DEF,rat.ATK,rat.AGI); 
    
    
}

/*
 * 
 */
int main(int argc, char** argv) {
     testKIT();
    return 0;
}
