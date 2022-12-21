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
    ConsoleHandle handle;
public:
    CGame(ConsoleHandle&);
    ~CGame();
    string getName();
    string getPassWord();
    bool getSound();
    void addCar(int x, int y);
    void addTruck(int x, int y);
    void addBird(int x, int y);
    void addDinausor(int x, int y);
    void addTrafficLight(TrafficLight& newLight);
    void createCarList();
    void createTruckList();
    void createBirdList();
    void createDinausorList();
    void createTrafficLightList();
    void moveAllObject();
    void drawAllMovingObject();
    void clearAllData();
    vector<CCar> getCarList();
    vector<CTruck> getTruckList();
    vector<CBird> getBirdList();
    vector<CDinausor> getDinausorList();
    vector<TrafficLight> getTrafficLightList();
    void gameMenu();
    void drawMap(string dataFile);
    int failGame();
    string loadGame();
    void SetSound();
    void SetBackGround();
    void settingMenu();
    int pauseGamePanel();
    void endGame();
    void readData(string dataFile);
    void saveGame(int k = 0);
    void saveGamePanel();
    string inputPassWord();
    void deleteGame();
};