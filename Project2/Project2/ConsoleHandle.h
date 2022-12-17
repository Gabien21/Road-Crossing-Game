#pragma once
#include <Windows.h>
#include <string>
#include <conio.h>
#include <iostream>
#include <vector>
#include <utility>
#include <tchar.h>

using namespace std;
#define consoleWidth 176
#define consoleHeight 50	

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

typedef pair<string, int> si;

CHAR_INFO consoleBuffer[consoleWidth * consoleHeight];
SMALL_RECT consoleWriteArea = { 0, 0, consoleWidth - 1, consoleHeight - 1 };
COORD characterBufferSize = { consoleWidth, consoleHeight };
COORD characterPosition = { 0, 0 };
HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);

class ConsoleHandle
{
private:
    int width;
    int height;
public:
    ConsoleHandle()
    {
        FixConsoleWindow();
        clear();
    }
    static int getCenterX(int a, int x = 0, int y = consoleWidth)
    {
        return x + (y - x) / 2 - a / 2;
    }
    static int getCenterY(int b, int x = 0, int y = consoleHeight)
    {
        return x + (y - x) / 2 - b / 2;
    }
    void gotoXY(int x, int y) {
        COORD point;
        point.X = x;
        point.Y = y;
        SetConsoleCursorPosition(wHnd, point);
    }
    void SetColor(int color)
    {
        SetConsoleTextAttribute(wHnd, color);
    }
    void HideCursor() {
        CONSOLE_CURSOR_INFO info;
        info.dwSize = 100;
        info.bVisible = FALSE;
        SetConsoleCursorInfo(wHnd, &info);
    }
    void FixConsoleWindow() {
        HWND consoleWindow = GetConsoleWindow();
        LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
        style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
        SetWindowLong(consoleWindow, GWL_STYLE, style);

        SetConsoleTitle(_T("Road Crossing Game Group 11"));
        COORD const size = { consoleWidth , consoleHeight + 2 };
        SMALL_RECT const minimal_window = { 0, 0, 1, 1 };
        SetConsoleWindowInfo(wHnd, TRUE, &minimal_window);
        SetConsoleScreenBufferSize(wHnd, size);
        SMALL_RECT const window = { 0, 0, size.X - 1, size.Y - 1 };
        SetConsoleWindowInfo(wHnd, TRUE, &window);
        SetConsoleCP(65001);
        HideCursor();

    }
    void resizeConsole(int width, int height)
    {
        HWND console = GetConsoleWindow();
        RECT r;
        GetWindowRect(console, &r);
        MoveWindow(console, r.left, r.top, width, height, true);
    }
    void drawGraphic(int mX, int mY, string graphicFile, int atribute = 240) {
        ifstream op;
        op.open(graphicFile);
        vector<string> line;
        string tmp;
        while (getline(op, tmp))
            line.push_back(tmp);
        for (int y = 0; y < line.size(); ++y)
        {
            for (int x = 0; x < line[y].size(); ++x)
            {
                consoleBuffer[mX + x + consoleWidth * (mY + y)].Char.AsciiChar = line[y][x];
                consoleBuffer[mX + x + consoleWidth * (mY + y)].Attributes = atribute;
            }
        }
        WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
        op.close();
    }
    void drawString(int mX, int mY, string s, int atribute = 240) {
        for (int x = 0; x < s.length(); ++x)
        {
            consoleBuffer[mX + x + consoleWidth * (mY)].Char.AsciiChar = s[x];
            consoleBuffer[mX + x + consoleWidth * (mY)].Attributes = atribute;
        }
        WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
    }
    void eraseString(int mX, int mY, int n, int atribute = 240)
    {
        for (int x = 0; x < n; ++x)
        {
            consoleBuffer[mX + x + consoleWidth * (mY)].Char.AsciiChar = ' ';
            consoleBuffer[mX + x + consoleWidth * (mY)].Attributes = atribute;
        }
    }
    void eraseGraphic(int mX, int mY, int a, int b, int atribute = 240,int c = 0, int d = consoleWidth) {
        for (int y = 0; y < a; ++y)
        {
            for (int x = 0; x < b; ++x)
            {
                if (mX + x >= c && mX + x <= d)
                {
                    consoleBuffer[mX + x + consoleWidth * (mY + y)].Char.AsciiChar = ' ';
                    consoleBuffer[mX + x + consoleWidth * (mY + y)].Attributes = 240;
                }
            }
        }
    }
    void updateObstacle(int mX, int mY, string graphicFile, int atribute = 240, int a = 0, int b = consoleWidth) {
        ifstream op;
        op.open(graphicFile);
        vector<string> line;
        string tmp;
        while (getline(op, tmp))
            line.push_back(tmp);
        for (int y = 0; y < line.size(); ++y)
        {
            for (int x = 0; x < line[y].size(); ++x)
            {
                if (mX+x>=a && mX + x <= b)
                {
                    consoleBuffer[mX + x + consoleWidth * (mY + y)].Char.AsciiChar = line[y][x];
                    consoleBuffer[mX + x + consoleWidth * (mY + y)].Attributes = atribute;
                }
            }
        }
        op.close();
    }
    void updateString(int mX, int mY, string s, int atribute) {
        for (int x = 0; x < s.length(); ++x)
        {
            consoleBuffer[mX + x + consoleWidth * (mY)].Char.AsciiChar = s[x];
            consoleBuffer[mX + x + consoleWidth * (mY)].Attributes = atribute;
        }
    }
    void draw()
    {
        WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
    }
    void clear()
    {
        for (int y = 0; y < consoleHeight; ++y)
        {
            for (int x = 0; x < consoleWidth; ++x)
            {
                consoleBuffer[x + consoleWidth * y].Char.AsciiChar = ' ';
                consoleBuffer[x + consoleWidth * y].Attributes = 240;
            }
        }
    }
    void drawTitle() {
        updateObstacle(getCenterX(152), 0, "GameTitle0.txt", 240);
    }
    void eraseTitle()
    {
        eraseGraphic(getCenterX(152), 0, 14, 170);
    }
    void drawMenu(string menuFileName) {
        updateObstacle(getCenterX(52), getCenterY(18,14), menuFileName);
        draw();
    }
    void eraseMenu()
    {
        eraseGraphic(getCenterX(52), getCenterY(18, 14), 18, 52);
    }
    void drawStage(int stage) {

        drawString(19, 10, to_string(stage));
    }
    vector<si> drawLoadGameMenu(string loadGameMenu) {
        drawTitle();
        eraseMenu();
        vector<si> playerList;
        ifstream fin;
        string dataFile = "LoadGame.txt";
        fin.open(dataFile, ios::in);
        while (!fin.eof())
        {
            si tmp;
            fin >> tmp.first >> tmp.second;
            playerList.push_back(tmp);
        }
        playerList.pop_back();
        fin.close();
        drawGraphic(getCenterX(53), getCenterY(14+playerList.size(),14), loadGameMenu);
        int i = 0;
        for (; i < playerList.size(); i++)
        {
            drawString(62, getCenterY(14 + playerList.size(),14) + 5 + i, "|");
            drawString(75 - (playerList[i].first).length() / 2, getCenterY(14 + playerList.size(), 14) + 5 + i, playerList[i].first);
            drawString(87, getCenterY(14 + playerList.size(), 14) + 5 + i, "|");
            drawString(102, getCenterY(14 + playerList.size(), 14) + 5 + i, to_string(playerList[i].second));
            drawString(114, getCenterY(14 + playerList.size(), 14) + 5 + i, "|");
        }
        drawGraphic(getCenterX(53), getCenterY(14 + playerList.size(), 14) + 5 + i, "LoadGameMenu-2.txt");
        return playerList;
    }
    void eraseLoadGameMenu(vector<si> list)
    {
        eraseGraphic(getCenterX(53), getCenterY(14 + list.size(), 14), 14 + list.size(), 53);
    }
    void drawPauseMenu(string pauseMenuFileName) {
        // x1 = 33; x2 = 162; y1 = 2;y2 = 47
        drawGraphic(getCenterX(52,33,162), getCenterY(16,2,47), pauseMenuFileName);
    }
    void erasePauseMenu()
    {
        eraseGraphic(getCenterX(52, 33, 162), getCenterY(16, 2, 47), 16, 52);
    }
    void drawFailGameMenu(string faileGameMenuFileName) {
        drawGraphic(getCenterX(20,33,162), getCenterY(13,2,47), faileGameMenuFileName);
    }
    void eraseFailGameMenu()
    {
        eraseGraphic(getCenterX(20, 33, 162), getCenterY(13, 2, 47), 13, 19);
    }
    void DrawGameMap()
    {
        drawGraphic(5, 2, "GameMap2.txt");
        vector<si> playerList;
        ifstream fin;
        string dataFile = "LoadGame.txt";
        fin.open(dataFile);
        if (!fin)
            return;
        while (!fin.eof())
        {
            si tmp;
            fin >> tmp.first >> tmp.second;
            playerList.push_back(tmp);
        }
        playerList.pop_back();
        fin.close();
        for (int i = 0; i < playerList.size() - 1; i++)
            for (int j = i + 1; j < playerList.size(); j++)
                if (playerList[i].second < playerList[j].second)
                    swap(playerList[i], playerList[j]);
        int n = 38;
        for (int i = 0; i < 3 && i < playerList.size(); i++)
        {
            drawString(9, n+i, playerList[i].first);
            drawString(13, n+1+i, to_string(playerList[i].second));
            n+=2;
        }
    }
    void drawSettingMenu(string settingMenuFileName) {
        clear();
        drawTitle();
        drawGraphic(getCenterX(38), getCenterY(7, 14), settingMenuFileName);
    }
    void eraseSettingMenu()
    {
        eraseTitle();
        eraseGraphic(getCenterX(38), getCenterY(7, 14), 7, 38);
    }
    void drawNameNotExit()
    {
        clear();
        drawTitle();
        drawGraphic(getCenterX(19), getCenterY(8, 14), "NameNotExit.txt");
        while (1) {
            char c = _getch();
            if (c == 'b')
                return;
        }
    }
    void earseNameNotExit()
    {
        eraseGraphic(getCenterX(19), getCenterY(8, 14), 8, 19);
    }
    void drawAbout() {
        clear();
        drawTitle();
        drawGraphic(getCenterX(53), getCenterY(11, 14), "About.txt");
        while (1) {
            char c = _getch();
            if (c == 'b')
            {
                clear();
                return;
            }
        }
    }
    vector<si> drawSavePanel(string savePanelFileName) {
        drawGraphic(getCenterX(52, 33, 162), getCenterY(20, 2, 47)+1, savePanelFileName);
        vector<si> playerList;
        ifstream fin;
        string dataFile = "LoadGame.txt";
        fin.open(dataFile);
        if (!fin)
            return playerList;
        while (!fin.eof())
        {
            si tmp;
            fin >> tmp.first >> tmp.second;
            playerList.push_back(tmp);
        }
        playerList.pop_back();
        fin.close();
        return playerList;
    }
    void eraseSaveGamePanel()
    {
        eraseGraphic(getCenterX(52, 33, 162), getCenterY(20, 2, 47)+1, 20, 52);
    }
    void drawSaveDataPanel()
    {
        clear();
        drawTitle();
        drawGraphic(getCenterX(37), getCenterY(4, 14), "SaveData.txt");
        while (1) {
            char c = _getch();
            if (c == 'b')
            {
                clear();
                return;
            }
        }
    }
    void eraseSaveDataPanel()
    {
        eraseTitle();
        eraseGraphic(getCenterX(37), getCenterY(4, 14), 4, 37);
    }
    void writeNameToConsole(int x, int y, vector <char> name) {
        string s = "";
        for (int i = 0; i < name.size(); i++)
            s += name[i];
        s += "_";
        if (name.size() <= 10)
            for (int i = 0; i <= (10 - name.size()); i++)
                s += " ";
        drawString(x, y, s);
    }
    char lowerGetch() {
        char c = _getch();
        c = tolower(c);
        return c;
    }
    void drawHeart(int n)
    {
        if (n <= 0)
            return;
        int mX, mY;
        mX = getCenterX(2 * n - 1, 6, 31);
        mY = 30;
        for (int i = 0; i < 2*n-1; i+=2)
        {
            consoleBuffer[mX + i + consoleWidth * (mY)].Char.AsciiChar = (char)3;
            consoleBuffer[mX + i + consoleWidth * (mY)].Attributes = 244;
        }
    }
    void eraseHeart()
    {
        int mX, mY;
        int n = 3;
        mX = getCenterX(2 * n - 1, 6, 31);
        mY = 30;
        for (int i = 0; i < 2 * n - 1; i++)
        {
            consoleBuffer[mX + i + consoleWidth * (mY)].Char.AsciiChar = ' ';
            consoleBuffer[mX + i + consoleWidth * (mY)].Attributes = 240;
        }
    }
    void drawNotAlive()
    {
        clear();
        drawTitle();
        drawGraphic(getCenterX(38), getCenterY(11, 14), "NotAlive.txt");
        while (1) {
            char c = _getch();
            if (c == 'b')
            {
                clear();
                return;
            }
        }
    }
    int drawEndGame()
    {
        clear();
        drawTitle();
        drawGraphic(getCenterX(36), getCenterY(6, 14), "EndGame.txt");
        while (1) {
            int c = _getch();
            if (c == 27 || c == VK_RETURN)
            {
                clear();
                return c;
            }
        }
    }
    int drawPassWordError()
    {
        clear();
        drawTitle();
        drawGraphic(getCenterX(40), getCenterY(6, 14), "PassWordError.txt");
        while (1) {
            int c = _getch();
            if (c == 27 || c == (int)'b')
            {
                clear();
                return c;
            }
        }
    }
    void drawInputPassWord(string savePanelFileName)
    {
        clear();
        drawTitle();
        drawGraphic(getCenterX(52), getCenterY(12, 14), savePanelFileName);
    }
    void drawNameCreated(string savePanelFileName)
    {
        clear();
        drawTitle();
        drawGraphic(getCenterX(35), getCenterY(3, 14), savePanelFileName);
    }
    void eraseInputPassWord()
    {
        eraseGraphic(getCenterX(52, 33, 162), getCenterY(12, 2, 47) + 1, 12, 52);
    }
};