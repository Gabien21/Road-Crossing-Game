#pragma once
#include<iostream>
#include<fstream>
#include<Windows.h>
#include<tchar.h>
#include<vector>
#include<string>
#include <conio.h>
#include "tmp.h"

using namespace std;
#define consoleWidth 176
#define consoleHeight 50	

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

#define DARK 0
#define WHITE 240

typedef pair<string, int> si;



class ConsoleHandle
{
private:
    int width;
    int height;
public:
    ConsoleHandle();
    static int getCenterX(int a, int x = 0, int y = consoleWidth);
    static int getCenterY(int b, int x = 0, int y = consoleHeight);
    void gotoXY(int x, int y);
    void SetColor(int color);
    void HideCursor();
    void FixConsoleWindow();
    void resizeConsole(int width, int height);
    void drawGraphic(int mX, int mY, string graphicFile, int attribute = at);
    void drawString(int mX, int mY, string s, int attribute = at);
    void eraseString(int mX, int mY, int n, int attribute = at);
    void eraseGraphic(int mX, int mY, int a, int b, int attribute = at, int c = 0, int d = consoleWidth);
    void updateObstacle(int mX, int mY, string graphicFile, int attribute = at, int a = 0, int b = consoleWidth);
    void updateString(int mX, int mY, string s, int attribute = at);
    void draw();
    void clear();
    void drawLoading();
    void eraseLoading();
    void drawTitle();
    void eraseTitle();
    void drawMenu(string menuFileName);
    void eraseMenu();
    void drawStage(int stage);
    vector<si> drawLoadGameMenu(string loadGameMenu);
    void eraseLoadGameMenu(vector<si> list);
    void drawPauseMenu(string pauseMenuFileName);
    void erasePauseMenu();
    void drawFailGameMenu(string faileGameMenuFileName);
    void eraseFailGameMenu();
    void DrawGameMap();
    void drawSettingMenu(string settingMenuFileName);
    void eraseSettingMenu();
    void drawSettingSoundMenu(string settingMenuFileName);
    void eraseSettingSoundMenu();
    void drawSettingBackGroundMenu(string settingMenuFileName);
    void eraseSettingBackGroundMenu();
    void drawNameNotExit();
    void earseNameNotExit();
    void drawAbout();
    vector<si> drawSavePanel(string savePanelFileName);
    void eraseSaveGamePanel();
    void drawSaveDataPanel();
    void eraseSaveDataPanel();
    void writeNameToConsole(int x, int y, vector <char> name);
    char lowerGetch();;
    void drawHeart(int n);
    void eraseHeart();
    void drawNotAlive();
    int drawEndGame();
    int drawPassWordError();
    void drawInputPassWord(string savePanelFileName);
    void drawNameCreated(string savePanelFileName);
    void eraseInputPassWord();
};