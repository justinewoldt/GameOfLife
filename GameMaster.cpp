#include "GameMaster.h"
#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
using namespace std;

  int gameRows;
  int gameColumns;
  float gameDensity;
  int figChoice;
  int speedChoice; // 1 for pause, 2 for enter, 3 for file print
  string printFile; // file path to print
  string filePath;
  char** MyGameBoard;
  int generationCount = 1;
  ofstream outFile;

  GameMaster::GameMaster()
  {


  }
  GameMaster::~GameMaster()
  {

  }
  int GameMaster::configChoice()
  {
    string destination; // local variable
    cout << "Type random for a random assignment and file for a file path:" << endl; // prompt user for type of gameBoard
    cin >> destination;
    for(int i = 0; i < destination.size(); i++) // account for capitals
    {
      destination[i] = tolower(destination[i]);
    }

    if (destination == "random") // if statement to return proper number
    {
      figChoice = 1; // stored for future use
      return 1;
    }
    else
    {
      figChoice = 0; // stored for future use
      return 0;
    }

  }
  int GameMaster::modeChoice()
  {
    string destination; // temp variable
    cout << "Choose your mode(classic, doughnut, or mirror):";
    cin >> destination;
    for(int i = 0; i < destination.size(); i++) // account for capitals
    {
      destination[i] = tolower(destination[i]);
    }
    if (destination == "classic") // if statement to return proper number
    {
      return 1;
    }
    else if(destination == "doughnut")
    {
      return 2;
    }
    else
    {
      return 3;
    }
  }
  void GameMaster::outputChoice()
  {
    string destination; // temp variable
    cout << "Choose your speed(pause, enter, or file):";
    cin >> destination;
    for(int i = 0; i < destination.size(); i++) // account for capitals
    {
      destination[i] = tolower(destination[i]);
    }
    if (destination == "pause") // if statement to return proper number
    {
      speedChoice = 1; // store for output
    }
    else if(destination == "enter")
    {
      speedChoice = 2;
    }
    else
    {
      speedChoice = 3;
      cout << "Please print your output file path:";
      cin >> printFile; // store file output path
    }
  }
  void GameMaster::gameDimensions(int configChoice)
  {
    string tempString;
    if(configChoice == 1) // only when user chooses random
    {
      cout << "Constructing you world..." << endl;
      cout << "Number of rows: ";
      cin >> tempString;
      gameRows = stoi(tempString); // convert dimensions from string to integer
      cout << "Number of columns: ";
      cin >> tempString;
      gameColumns = stoi(tempString);
      cout << "World Density: ";
      cin >> tempString;
      gameDensity = stod(tempString);
    }
    else
    {
      cout << "Please print the file path: ";
      cin >> filePath; // store filepath to open
      cout << filePath << endl;
      string line;
      ifstream myFile;
      myFile.open(filePath); // open file path
      int i = 1; // want to read first and second line only
      while(getline(myFile, line))
      {
        if(i == 1)
        {
          gameRows = stoi(line);
        }
        else if(i == 2)
        {
          gameColumns = stoi(line);
        }
        else
        {
          break;
        }
        i++;
      }
      myFile.close(); // close file
    }
  }



  void GameMaster::gameBoard()
  {
      srand(time(NULL)); // each random number now different
      MyGameBoard = new char* [gameRows]; // add pointer of rows
      for(int i = 0; i < gameRows; i++)
      {
        MyGameBoard[i] = new char[gameColumns]; // add columns to game grid
        for(int j = 0; j < gameColumns; j++)
        {
          MyGameBoard[i][j] = '-'; // fill game grid with default options
        }
      }
      if (figChoice == 1) // random choice
      {
        for(int i = 0; i < gameRows; i++)
        {
          for(int j = 0; j < gameColumns; j++)
          {
            double randomNumber = (double)rand() / (double)RAND_MAX; // create random number
            if(randomNumber <= gameDensity) // calculate chances of X via the density inputted by user, fill board
            {
              MyGameBoard[i][j] = 'X';
            }
            else
            {
              MyGameBoard[i][j] = '-';
            }
          }
        }
      }
      else
      {
        string line; // temp variable
        ifstream myFile; // create file stream
        myFile.open(filePath); // open file to read
        int lineNumber = 0;
        int gameNumber = 0;
        while(getline(myFile, line)) // run through file line by line
        {
          if(lineNumber > 1)
          {
            for(int i = 0; i < line.length(); i++)
            {
              MyGameBoard[gameNumber][i] = line[i]; // read each line and create game board
            }
            gameNumber++;
          }
          lineNumber++;
        }
        myFile.close(); // close file
      }
    }
  void GameMaster::mirrorMode()
  {
    char tempArr[gameRows][gameColumns]; // create temporary array
    bool flow = true; // variable to stop loop
    while(flow)
    {
      for(int i = 0; i < gameRows; i++)
      {
        for(int j = 0; j < gameColumns; j++)
        {
          int x = 0; // add up all x's per element in array
          if(i == 0)
          {
              if(j == 0) // 0,0 ONLY
              {
                if(MyGameBoard[i+1][j] == 'X')
                {
                  x += 2;
                }
                if(MyGameBoard[i+1][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i][j+1] == 'X')
                {
                  x += 2;
                }
                if(MyGameBoard[i][j] == 'X')
                {
                  x += 3;
                }
              }
              else if(j == gameColumns-1) // 0, LAST COLUMN
              {
                if(MyGameBoard[i][j-1] == 'X')
                {
                  x += 2;
                }
                if(MyGameBoard[i+1][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j] == 'X')
                {
                  x += 2;
                }
                if(MyGameBoard[i][j] == 'X')
                {
                  x += 3;
                }
              }
              else // 0,1 0,2 0,3 0,4
              {
                if(MyGameBoard[i][j-1] == 'X')
                {
                  x += 2;
                }
                if(MyGameBoard[i+1][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i][j+1] == 'X')
                {
                  x += 2;
                }
                if(MyGameBoard[i][j] == 'X')
                {
                  x++;
                }
              }
            }
            else if(i == gameRows - 1)
            {

              if(j == 0) // LAST ROW, COLUMN 0
              {
                if(MyGameBoard[i-1][j] == 'X')
                {
                  x += 2;
                }
                if(MyGameBoard[i-1][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i][j+1] == 'X')
                {
                  x += 2;
                }
                if(MyGameBoard[i][j] == 'X')
                {
                  x += 3;
                }
              }
              else if(j == gameColumns-1) // LAST ROW, LAST COLUMN
              {
                if(MyGameBoard[i][j-1] == 'X')
                {
                  x += 2;
                }
                if(MyGameBoard[i-1][j] == 'X')
                {
                  x += 2;
                }
                if(MyGameBoard[i-1][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i][j] == 'X')
                {
                  x += 3;
                }
              }
              else // LAST ROW, MIDDLE SECTION
              {
                if(MyGameBoard[i][j-1] == 'X')
                {
                  x += 2;
                }
                if(MyGameBoard[i-1][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i-1][j] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i-1][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i][j+1] == 'X')
                {
                  x += 2;
                }
                if(MyGameBoard[i][j] == 'X')
                {
                  x++;
                }
              }
            }
            else
            {
              if(j == 0)
              {
                if(MyGameBoard[i-1][j] == 'X')
                {
                  x += 2;
                }
                if(MyGameBoard[i-1][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j] == 'X')
                {
                  x += 2;
                }
                if(MyGameBoard[i][j] == 'X')
                {
                  x++;
                }
              }
              else if(j == gameColumns-1)
              {
                if(MyGameBoard[i-1][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i-1][j] == 'X')
                {
                  x += 2;
                }
                if(MyGameBoard[i][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j] == 'X')
                {
                  x += 2;
                }
                if(MyGameBoard[i][j] == 'X')
                {
                  x++;
                }
              }
              else
              {
                if(MyGameBoard[i-1][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i-1][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i-1][j] == 'X')
                {
                  x++;
                }
              }
            }


          switch(x) // calculate how many neighbors and add element to next generation
          {
            case 0:
              tempArr[i][j] = '-';
              break;
            case 1:
              tempArr[i][j] = '-';
              break;
            case 2:
              tempArr[i][j] = MyGameBoard[i][j];
              break;
            case 3:
              tempArr[i][j] = 'X';
              break;
            case 4:
              tempArr[i][j] = '-';
              break;
            default:
              tempArr[i][j] = '-';
              break;
          }
        }
      }
      bool check = true; //check to see if repeated grid
      for(int i = 0; i < gameRows; i++)
      {
        for(int j = 0; j < gameColumns; j++)
        {
          if(MyGameBoard[i][j] != tempArr[i][j])
          {
            check = false;
          }
        }
      }
      if(check)// stop the while loop if stabilize
      {
        flow = false;
      }
      if(speedChoice == 1)
      {
        cout << generationCount << endl;
        generationCount++;
        for(int i = 0; i < gameRows; i++)
        {
          for(int j = 0; j < gameColumns; j++)
          {
            cout << tempArr[i][j];
            MyGameBoard[i][j] = tempArr[i][j];
          }
          cout << endl;
        }
        sleep(5); // pause for 5 seconds between generations
      }
      else if (speedChoice == 2)
      {
        cout << generationCount << endl;
        generationCount++;
        for(int i = 0; i < gameRows; i++)
        {
          for(int j = 0; j < gameColumns; j++)
          {
            cout << tempArr[i][j];
            MyGameBoard[i][j] = tempArr[i][j];
          }
          cout << endl;
        }
        cout << "Press Enter to continue: ";
        cin.ignore(); // able to pause generations with an enter key
        cout << endl;
      }
      else
      {
        outFile.open(printFile, ofstream::out | ofstream::app);
        if(generationCount == 1)
        {
          outFile << "0" << endl;
          for(int i = 0; i < gameRows; i++)
          {
            for(int j = 0; j < gameColumns; j++)
            {
              outFile << MyGameBoard[i][j];
            }
            outFile << endl;
          }
          outFile << endl;
        }
        outFile << endl;
        outFile << generationCount << endl;
        generationCount++;
        for(int i = 0; i < gameRows; i++)
        {
          for(int j = 0; j < gameColumns; j++)
          {
            outFile << tempArr[i][j];
            MyGameBoard[i][j] = tempArr[i][j];
          }
          outFile << endl;
        }
        outFile << endl;
        outFile.close();
      }
    }
  }
  void GameMaster::doughnutMode()
  {
    char tempArr[gameRows][gameColumns];
    bool flow = true;
    while(flow)
    {
      for(int i = 0; i < gameRows; i++)
      {
        for(int j = 0; j < gameColumns; j++)
        {
          int x = 0;
          if(i == 0)
          {
              if(j == 0) // 0,0 ONLY
              {
                if(MyGameBoard[i+1][j] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[gameRows-1][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[gameRows-1][j] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[gameRows-1][gameColumns-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i][gameColumns-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][gameColumns-1] == 'X')
                {
                  x++;
                }
              }
              else if(j == gameColumns-1) // 0, LAST COLUMN
              {
                if(MyGameBoard[i][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][0] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[0][0] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[gameRows-1][0] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[gameRows-1][gameColumns-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[gameRows-1][j-1] == 'X')
                {
                  x++;
                }
              }
              else // 0,1 0,2 0,3 0,4
              {
                if(MyGameBoard[i][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[gameRows-1][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[gameRows-1][j] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[gameRows-1][j-1] == 'X')
                {
                  x++;
                }
              }
            }
            else if(i == gameRows - 1)
            {

              if(j == 0) // LAST ROW, COLUMN 0
              {
                if(MyGameBoard[i-1][j] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i-1][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[gameRows-1][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[0][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[0][0] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[0][gameColumns-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i][gameColumns-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i-1][gameColumns-1] == 'X')
                {
                  x++;
                }
              }
              else if(j == gameColumns-1) // LAST ROW, LAST COLUMN
              {
                if(MyGameBoard[i][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i-1][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i-1][j] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i-1][0] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i][0] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[0][0] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[0][j] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[0][j-1] == 'X')
                {
                  x++;
                }
              }
              else // LAST ROW, MIDDLE SECTION
              {
                if(MyGameBoard[i][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i-1][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i-1][j] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i-1][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[0][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[0][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[0][j] == 'X')
                {
                  x++;
                }
              }
            }
            else
            {
              if(j == 0)
              {
                if(MyGameBoard[i-1][j] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i-1][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i-1][gameColumns-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i][gameColumns-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][gameColumns-1] == 'X')
                {
                  x++;
                }
              }
              else if(j == gameColumns-1)
              {
                if(MyGameBoard[i-1][j] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i-1][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][0] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i][0] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i-1][0] == 'X')
                {
                  x++;
                }
              }
              else
              {
                if(MyGameBoard[i-1][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i-1][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i-1][j] == 'X')
                {
                  x++;
                }
              }
            }


          switch(x)
          {
            case 0:
              tempArr[i][j] = '-';
              break;
            case 1:
              tempArr[i][j] = '-';
              break;
            case 2:
              tempArr[i][j] = MyGameBoard[i][j];
              break;
            case 3:
              tempArr[i][j] = 'X';
              break;
            case 4:
              tempArr[i][j] = '-';
              break;
            default:
              tempArr[i][j] = '-';
              break;
          }
        }
      }
      bool check = true;
      for(int i = 0; i < gameRows; i++)
      {
        for(int j = 0; j < gameColumns; j++)
        {
          if(MyGameBoard[i][j] != tempArr[i][j])
          {
            check = false;
          }
        }
      }
      if(check)
      {
        flow = false;
      }
      if(speedChoice == 1)
      {
        cout << generationCount << endl;
        generationCount++;
        for(int i = 0; i < gameRows; i++)
        {
          for(int j = 0; j < gameColumns; j++)
          {
            cout << tempArr[i][j];
            MyGameBoard[i][j] = tempArr[i][j];
          }
          cout << endl;
        }
        sleep(5);
      }
      else if (speedChoice == 2)
      {
        cout << generationCount << endl;
        generationCount++;
        for(int i = 0; i < gameRows; i++)
        {
          for(int j = 0; j < gameColumns; j++)
          {
            cout << tempArr[i][j];
            MyGameBoard[i][j] = tempArr[i][j];
          }
          cout << endl;
        }
        cout << "Press Enter to continue: ";
        cin.ignore();
        cout << endl;
      }
      else
      {
        outFile.open(printFile, ofstream::out | ofstream::app);
        if(generationCount == 1)
        {
          outFile << "0" << endl;
          for(int i = 0; i < gameRows; i++)
          {
            for(int j = 0; j < gameColumns; j++)
            {
              outFile << MyGameBoard[i][j];
            }
            outFile << endl;
          }
          outFile << endl;
        }
        outFile << endl;
        outFile << generationCount << endl;
        generationCount++;
        for(int i = 0; i < gameRows; i++)
        {
          for(int j = 0; j < gameColumns; j++)
          {
            outFile << tempArr[i][j];
            MyGameBoard[i][j] = tempArr[i][j];
          }
          outFile << endl;
        }
        outFile << endl;
        outFile.close();
      }
    }

  }
  void GameMaster::classicMode()
  {
    char tempArr[gameRows][gameColumns];
    bool flow = true;
    while(flow)
    {
      for(int i = 0; i < gameRows; i++)
      {
        for(int j = 0; j < gameColumns; j++)
        {
          int x = 0;
          if(i == 0)
          {
              if(j == 0) // 0,0 ONLY
              {
                if(MyGameBoard[i][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j+1] == 'X')
                {
                  x++;
                }
              }
              else if(j == gameColumns-1) // 0, LAST COLUMN
              {
                if(MyGameBoard[i][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j-1] == 'X')
                {
                  x++;
                }
              }
              else // 0,1 0,2 0,3 0,4
              {
                if(MyGameBoard[i][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i][j+1] == 'X')
                {
                  x++;
                }
              }
            }
            else if(i == gameRows - 1)
            {

              if(j == 0) // LAST ROW, COLUMN 0
              {
                if(MyGameBoard[i-1][j] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i-1][j+1] == 'X')
                {
                  x++;
                }
              }
              else if(j == gameColumns-1) // LAST ROW, LAST COLUMN
              {
                if(MyGameBoard[i][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i-1][j] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i-1][j-1] == 'X')
                {
                  x++;
                }
              }
              else // LAST ROW, MIDDLE SECTION
              {
                if(MyGameBoard[i][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i-1][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i-1][j] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i-1][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i][j+1] == 'X')
                {
                  x++;
                }
              }
            }
            else
            {
              if(j == 0)
              {
                if(MyGameBoard[i-1][j] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i-1][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j] == 'X')
                {
                  x++;
                }
              }
              else if(j == gameColumns-1)
              {
                if(MyGameBoard[i-1][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i-1][j] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j] == 'X')
                {
                  x++;
                }
              }
              else
              {
                if(MyGameBoard[i-1][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j-1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i+1][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i-1][j+1] == 'X')
                {
                  x++;
                }
                if(MyGameBoard[i-1][j] == 'X')
                {
                  x++;
                }
              }
            }


          switch(x)
          {
            case 0:
              tempArr[i][j] = '-';
              break;
            case 1:
              tempArr[i][j] = '-';
              break;
            case 2:
              tempArr[i][j] = MyGameBoard[i][j];
              break;
            case 3:
              tempArr[i][j] = 'X';
              break;
            case 4:
              tempArr[i][j] = '-';
              break;
            default:
              tempArr[i][j] = '-';
              break;
          }
        }
      }
      bool check = true;
      for(int i = 0; i < gameRows; i++)
      {
        for(int j = 0; j < gameColumns; j++)
        {
          if(MyGameBoard[i][j] != tempArr[i][j])
          {
            check = false;
          }
        }
      }
      if(check)
      {
        flow = false;
      }
      if(speedChoice == 1)
      {
        cout << generationCount << endl;
        generationCount++;
        for(int i = 0; i < gameRows; i++)
        {
          for(int j = 0; j < gameColumns; j++)
          {
            cout << tempArr[i][j];
            MyGameBoard[i][j] = tempArr[i][j];
          }
          cout << endl;
        }
        sleep(5);
      }
      else if (speedChoice == 2)
      {
        cout << generationCount << endl;
        generationCount++;
        for(int i = 0; i < gameRows; i++)
        {
          for(int j = 0; j < gameColumns; j++)
          {
            cout << tempArr[i][j];
            MyGameBoard[i][j] = tempArr[i][j];
          }
          cout << endl;
        }
        cout << "Press Enter to continue: ";
        cin.ignore();
        cout << endl;
      }
      else
      {
        outFile.open(printFile, ofstream::out | ofstream::app);
        if(generationCount == 1)
        {
          outFile << "0" << endl;
          for(int i = 0; i < gameRows; i++)
          {
            for(int j = 0; j < gameColumns; j++)
            {
              outFile << MyGameBoard[i][j];
            }
            outFile << endl;
          }
          outFile << endl;
        }
        outFile << endl;
        outFile << generationCount << endl;
        generationCount++;
        for(int i = 0; i < gameRows; i++)
        {
          for(int j = 0; j < gameColumns; j++)
          {
            outFile << tempArr[i][j];
            MyGameBoard[i][j] = tempArr[i][j];
          }
          outFile << endl;
        }
        outFile << endl;
        outFile.close();
      }
    }
  }
  void GameMaster::originalPrint()
  {
    cout << "0" << endl; // print original generation
    for(int i = 0; i < gameRows; i++)
    {
      for(int j = 0; j < gameColumns; j++)
      {
        cout << MyGameBoard[i][j];
      }
      cout << endl;
    }
  }
