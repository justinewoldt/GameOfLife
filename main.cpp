#include <iostream>
#include <string>
#include "GameMaster.cpp"
using namespace std;

main(int argc, char** argv)
{
  GameMaster q;
  q.gameDimensions(q.configChoice());
  q.outputChoice();
  q.gameBoard();
  switch (q.modeChoice())
  {
    case 1:
      q.originalPrint();
      q.classicMode();
      break;
    case 2:
      q.originalPrint();
      q.doughnutMode();
      break;
    default:
      q.originalPrint();
      q.mirrorMode();
      break;
  }



}
