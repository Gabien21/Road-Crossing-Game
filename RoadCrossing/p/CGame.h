#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include "CPeople.h"
#include <utility>
#include<thread>
#include <mciapi.h>
using namespace std;
#pragma comment(lib, "winmm.lib")

typedef pair<string, int> si;

class CGame
{
private:
    vector<CCar> carList;
    vector<CTruck> truckList;
    vector<CBird> birdList;
    vector<CDinausor> dinausorList;
    vector<TrafficLight> lightList;
    CPeople* people;
    int difficulty;
    int stage;
    bool sound;
    int live;
    int color;
    string userName;
    string passWord;
public:
    CGame();
    ~CGame();
    string getName();
    string getPassWord();
    bool getSound();
    void addCar(int x, int y);
    void addTruck(int x, int y);
    void addBird(int x, int y);
    void addDinausor(int x, int y);
    void addTrafficLight(TrafficLight& newLight);
    void createCarList(ConsoleHandle& handle);
    void createTruckList(ConsoleHandle& handle);
    void createBirdList(ConsoleHandle& handle);
    void createDinausorList(ConsoleHandle& handle);
    void createTrafficLightList();
    void moveAllObject(ConsoleHandle& handle);
    void drawAllMovingObject(ConsoleHandle& handle);
    void clearAllData();
    vector<CCar> getCarList();
    vector<CTruck> getTruckList();
    vector<CBird> getBirdList();
    vector<CDinausor> getDinausorList();
    vector<TrafficLight> getTrafficLightList();
    void gameMenu(ConsoleHandle& handle);
    void drawMap(ConsoleHandle& handle, string dataFile);
    int failGame(ConsoleHandle& handle);
    string loadGame(ConsoleHandle& handle);
    void SetSound(ConsoleHandle& handle);
    void SetBackGround(ConsoleHandle& handle);
    void settingMenu(ConsoleHandle& handle);
    int pauseGamePanel(ConsoleHandle& handle);
    void endGame(ConsoleHandle& handle, string name);
    void readData(string dataFile);
    void saveGame(ConsoleHandle& handle, int k = 0);
    void saveGamePanel(ConsoleHandle& handle);
    string inputPassWord(ConsoleHandle& handle);
    void deleteGame();
};