#include <iostream>
#include <string>
using namespace std;

class GameMaster
{
  public:

    GameMaster();
    ~GameMaster();
    int configChoice();
    int modeChoice();
    void outputChoice();
    void gameDimensions(int choice);
    void gameBoard();
    void classicMode();
    void doughnutMode();
    void mirrorMode();
    void originalPrint();


};
