/*
Jane The Dragon Slayer

Protagonist Name: Jane Damselindistress

Plot:
Recieve letter from the king
Prompt: "Do you open it?"
summoning you to the castle
Prompt: "Do you go?"
(ASCII Castle art)
Ordered to go kill the local dragon who is stealing from the treasury
Prompt: "Do you accept the challenge?"

Dungeon

Floor 1 and 2

Each "round" will consist of a movement and something happening from the encounter table
0-4: Straight line forward is the only option (no other movement option, no other actions on turn)
5-10: fork in the road (left or right, no effect on gameplay)
11-12: Item appears from the random item table.
    0:Sword (allows you to damage monsters)
    1:Bunny (makes noises sometimes, cute graphic)
    2:Map (Increases odds of finding keys, indicates dragon is on the 3rd basement)
    3:Shiny rock (no effect)
13-14: Encounter from random encounter table
    0-3:Ogre (low int, high perception, medium health)
    4-5:Slime (zero int, low perception, low health, subdevision)
    6:Nymph (resets health)
    7:Sphinx (high int, max perception, infinate health, riddle (trivia))
15: stair case
16: (only if user has bunny) Bunny gives you a plant

Floor 3
0-2: Straight line
3:Intersection with locked door
4: Key found

Combat mechanics

Any hit does 1 health
Player has 4 health
Attacking can hit or miss, player accuracy is 70%
Other options in an encounter are talk, sneak, or flee

Ogre: 3 health, 40% accuracy, 30% sneak success rate, 75% flee succsess rate,
70% talk success rate with right path

Slime: 1 health, 1 subdevision (becomes 2 more slime), 30% accuracy,
85% sneak succsees rate, 90% flee success rate, 0% talk success

Sphinks: Riddle only, wrong answer costs 1hp.
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <string>
using namespace std;

class player {
public:
  int health = 4;
  int roll;
  bool hasSword = true; //reset this to false once game enviornment created
  bool hasMap = false;
  bool hasBunny = false;
};

class bruteMonster {
public:
  int health;
  int roll;
  float accuracy; //ability to hit (roll a d100, and if it is less than this value it hits, the player has an accuracy of 70)
  float perception; //ability to notice player sneaking (rolls a d100 and if it is less, they will prevent the player from sneaking)
  float follow; //tendancy to follow player who flees (rolls a d100 and if its less it will prevent the player from fleeing)
  bool attack() {
    roll = rand() % 100 + 1;
    if (roll<accuracy){
      cout << "You get hit with a club and take one damage."  << endl;
      return true;
    }
    else{
      cout << "You manage to escape the monster's swing" << endl;
      return false;
     }
  }
  bool sneak() {
    roll = rand() % 100 + 1;
    if (roll<perception){
      return true;
    }
    else{
      return false;
    }
  }
  bool flee(){
    roll = rand() % 100 + 1;
    if (roll<follow){
      return true;
    }
    else{
      return false;
    }
  }
};

class Sphinx {
public:
  int health = 1;
  string answer;
  bool ask(){
  int roll = rand() % 4;
  cout << "You see a large sphinx. ";
  if (roll == 1) {
    cout << "What is the ph of water? ";
    cin >> answer;
  if (answer == "7") {
    cout << "Correct, you have passed my test. " << endl;
    health = health - 1;
  }
  else {
    cout << "You feel a sharp pain in your head, and take one damage. " << endl;
    return false;
  }
}
  else if (roll == 2) {
    cout << "What part of the atom has no electric charge? ";
    cin >> answer;
  if (answer == "neutron") {
    cout << "Correct, you have passed my test. " << endl;
    health = health - 1;
  }
  else {
    cout << "You feel a sharp pain in your head, and take one damage. " << endl;
    return false;
  }
}
  else if (roll == 3) {
    cout << "What is the dirivative of 8x^2 ";
    cin >> answer;
    if (answer == "16x") {
    cout << "Correct, you have passed my test. " << endl;
    health = health - 1;
  }
  else {
    cout << "You feel a sharp pain in your head, and take one damage. " << endl;
    return false;
  }
}
  else if (roll == 4) {
    cout << "What year was the very first model of the iPhone released? ";
    cin >> answer;
    if (answer == "2007") {
    cout << "Correct, you have passed my test. " << endl;
    health = health - 1;
    }
    else {
    cout << "You feel a sharp pain in your head, and take one damage. " << endl;
    return false;
  }
  }
}
};

class stackMap{ //based on the stack code from the exam
public:
string stack[100];
int top= -1;
string tiles [4] = {"path", "fork", "encounter", "item"};
int isempty() {
    return top < 0;
}

int isfull() {
    return top == 100;
}

void push(string value) {
    if (isfull()) {
        printf("Stack is full.\n");
    } else {
        top++;
        stack[top] = value;
    }
}
void pop() {
    if (isempty()) {
        printf("Stack is empty.\n");
    } else  {
        top--;
    }
}
string forward() {
  push(tiles[rand() % 4]);
  return stack[top];
}

string backwards(){
  while(stack[top]!="fork"){
    pop();
  }
  return stack[top];
}
string stairs(){ //no longer used
  while(isempty()!=true){
    pop();
  }
  return forward();
}
};

int encounter(int playerHealth, bool hasSword){
  string userInput;
  string currentMonster;
  int roll;
  int healSlot = 2;
  bool endBattle = false;
  string monsters [4] = {"sphinx", "ogre", "cyclopse", "nymph"};
  currentMonster = monsters[rand() % 4];
  if (currentMonster == "ogre" || currentMonster == "cyclopse") {
    cout << "a " << currentMonster << " appears." << endl;
    bruteMonster enemy;
    if (currentMonster == "ogre"){
      enemy.health=2;
      enemy.accuracy=45;
      enemy.follow=35;
      enemy.perception=60;
    }
    else if (currentMonster == "cyclopse") {
      enemy.health=4;
      enemy.accuracy=25;
      enemy.follow=70;
      enemy.perception=30;
  }
  while(playerHealth > 0 && enemy.health > 0 && endBattle == false) {
    if (enemy.attack() == true) {
      playerHealth = playerHealth - 1;
      cout << "You now have " << playerHealth << " health" << endl;
    }
     cout << "Would you like to (a)ttack, (f)lee, (s)neak or (h)eal: " << endl;
     cin >> userInput;
     if (userInput == "a"){
       if (hasSword == true){
         roll = rand() % 100 + 1;
         if (roll<70){
           enemy.health = enemy.health - 1;
           cout << "you hit it with your sword reducing it to " << enemy.health << " health." << endl;
         }
         else{
           cout << "you swing your sword, but it narrowly misses" << endl;
         }
     }
        if (hasSword == false){
          cout << "You attempt to punch your foe, but they don't flinch" << endl;
        }
     }
     else if (userInput == "f") {
       if (enemy.flee() == false) {
         //move back function
         cout << "You managed run away to the nearest fork in the path. " << endl;
         endBattle=true;
         return 100+playerHealth;
       }
       else{
         cout << "Your foe has blocked the exit" << endl;
       }
     }
     else if (userInput == "s") {
       if (enemy.sneak() == true) {
         cout << "You were able to sneak past the monster. " << endl;
         endBattle=true;
       }
       else{
         cout << "The monster noticed you and blocked your escape." << endl;
     }
   }
     else if (userInput == "h"){
       if (healSlot > 0) {
         playerHealth = playerHealth + 1;
         healSlot = healSlot - 1;
         cout << "You now have " << playerHealth << " health and enough supplies to heal " << healSlot << " more times." << endl;
     }
      else {
        cout << "You are out of medical supplies" << endl;
      }
   }
  }
  return playerHealth;
}
else if (currentMonster == "nymph"){
  playerHealth = 4;
  cout << "you encounter a nymph, who has fully restored your health" << endl;
  return playerHealth;
}
else if (currentMonster == "sphinx"){
  Sphinx sphinx;
  while(playerHealth > 0 && sphinx.health > 0){
    if (sphinx.ask()==false){
      playerHealth=playerHealth-1;
    }
  }
  return playerHealth;
}
}

int enviornmentHandeler(string currentTile, int playerHealth, bool hasSword, bool hasMap, bool hasBunny){
    if(currentTile == "path"){
      cout << "You walk through a tight walkway. ";
      return 5;
    }
    if(currentTile == "fork"){
    char LorR;
    cout << "You come up to a fork in the pathway, would you like to go left or right? ";
    cin >> LorR;
    return 6;
}
  if(currentTile == "encounter"){
      return encounter(playerHealth, hasSword);
    }

//  if(currentTile == "stairs"){
//    cout << "You found stairs and decend a layer deeper into the dungeon. ";
//    return 7; }

  if(currentTile == "item"){
    cout << "You see something in the dirt: ";
    string items [3] = {"sword", "map", "bunny"};
    string foundItem = items[rand() % 3];
    cout << "you found a " << foundItem <<endl;
    if(foundItem == "sword") {return 8;}
    if(foundItem == "map") {return 9;}
    if(foundItem == "bunny") {return 10;}
  }
}

int main() {
  srand(time(0));
  player jane;
  stackMap map;
  int output;
  string currentTile;
  currentTile=map.forward();
  cout << "Jane... Wake up, you hear in a familiar voice. \nAs you wake up though you remember you are alone. You have been for 6 days now. \nThere is little hope for escape from the dungeon, your only remaining goal is to survive. \n";
  while (jane.health > 0){
    output=enviornmentHandeler(currentTile, jane.health, jane.hasSword, jane.hasMap, jane.hasBunny);
    if(output<5) {
      jane.health=output;
      currentTile = map.tiles[rand() % 4];
      map.push(currentTile);
    }
  //  if(output==7){
  //    currentTile = map.stairs();

    else if(output==8){
      jane.hasSword=true;
      currentTile = map.tiles[rand() % 4];
      map.push(currentTile);
    }
    else if(output==9){
      jane.hasMap=true;
      currentTile = map.tiles[rand() % 4];
      map.push(currentTile);
    }
    else if(output = 10){
      jane.hasBunny=true;
      currentTile = map.tiles[rand() % 4];
      map.push(currentTile);
    }
    else if (output>100){
      jane.health = output-100;
      currentTile = map.backwards();
    }
  }
  cout << jane.health << " health, you died :(";
  return 0;
}
