#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include "CAnimal.h"
#include "CVehicle.h"
#include "CPeople.h"
#include "ConsoleHandle.h"
#include "CTrafficLight.h"
#include "Point.h"
#include <utility>
#include<thread>
using namespace std;
#pragma comment(lib, "winmm.lib")

void playDeathSound() {
    PlaySound(TEXT("sound/human_die.wav"), NULL, SND_FILENAME);
}


#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

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
    string userName;
    string passWord;
public:
    CGame()
    {
        this->people = new CPeople(94, 43);
        difficulty = 105;
        stage = 1;
        live = 3;
        sound = true;
        userName = passWord = "";
    }
    ~CGame()
    {
        deleteGame();
    }
    string getName()
    {
        return userName;
    }
    string getPassWord()
    {
        return passWord;
    }
    bool getSound()
    {
        return sound;
    }
    void addCar(int x, int y)
    {
        CCar newCar(x, y);
        carList.push_back(newCar);
    }
    void addTruck(int x, int y)
    {
        CTruck newTruck(x, y);
        truckList.push_back(newTruck);
    }
    void addBird(int x, int y)
    {
        CBird newBird(x, y);
        birdList.push_back(newBird);
    }
    void addDinausor(int x, int y)
    {
        CDinausor newDinausor(x, y);
        dinausorList.push_back(newDinausor);
    }
    void addTrafficLight(TrafficLight& newLight)
    {
        lightList.push_back(newLight);
    }
    void createCarList(ConsoleHandle& handle)
    {
        if (carList.size() <= 0)
        {
            CCar newCar(33, 10);
            carList.push_back(newCar);
            return;
        }
        auto it = carList.begin();
        srand(time(NULL));
        int n = (rand() % 10) + 3;
        if ((*it).getPos().x == 162)
        {
            (*it).deleteVehicle(handle, lightList[0]);
            carList.erase(it);
        }
        if (carList.size() < stage / 6 + 3)
        {
            if (carList[carList.size() - 1].getPos().x > carList[0].getLength() + 21 + 13 + n)
            {
                CCar newCar(33-carList[0].getLength(), 10);
                carList.push_back(newCar);
            }
        }
    }
    void createTruckList(ConsoleHandle& handle)
    {
        if (truckList.size() <= 0)
        {
            CTruck newTruck(33, 28);
            truckList.push_back(newTruck);
            return;
        }
        auto it = truckList.begin();
        srand(time(NULL));
        int n = (rand() % 10) + 3;
        if ((*it).getPos().x == 162)
        {
            (*it).deleteVehicle(handle, lightList[1]);
            truckList.erase(it);
        }
        if (truckList.size() < stage / 6 + 3)
        {
            if (truckList[truckList.size() - 1].getPos().x > truckList[0].getLength() + 14 + 21 + n)
            {
                CTruck newTruck(33-truckList[0].getLength(), 28);
                truckList.push_back(newTruck);
            }
        }
    }
    void createBirdList(ConsoleHandle& handle)
    {
        if (birdList.size() <= 0)
        {
            CBird newBird(162, 18);
            birdList.push_back(newBird);
            return;
        }
        auto it = birdList.begin();
        srand(time(NULL));
        int n = (rand() % 10) + 3;
        if ((*it).getPos().x <= 20)
        {
            (*it).deleteAnimal(handle);
            birdList.erase(it);
        }
        if (birdList.size() < stage / 6 + 3)
        {
            if (birdList[birdList.size() - 1].getPos().x < 162 - n - 2 * birdList[0].getLength())
            {
                CBird newBird(162, 18);
                birdList.push_back(newBird);
            }
        }
    }
    void createDinausorList(ConsoleHandle& handle)
    {
        if (dinausorList.size() <= 0)
        {
            CDinausor newDinausor(162, 36);
            dinausorList.push_back(newDinausor);
            return;
        }
        auto it = dinausorList.begin();
        srand(time(NULL));
        int n = (rand() % 10) + 3;
        if ((*it).getPos().x <= 20)
        {
            (*it).deleteAnimal(handle);
            dinausorList.erase(it);
        }
        if (dinausorList.size() < stage / 6 + 3)
        {
            if (dinausorList[dinausorList.size() - 1].getPos().x < 162 - n - 2 * dinausorList[0].getLength())
            {
                CDinausor newDinausor(162, 36);
                dinausorList.push_back(newDinausor);
            }
        }
    }
    void createTrafficLightList()
    {
        lightList.resize(2);
        lightList[0].setPos(164, 7);
        lightList[1].setPos(164, 25);
    }
    void moveAllObject(ConsoleHandle& handle)
    {
        for (int i = 0; i < carList.size(); i++)
            carList[i].Move(lightList[0]);
        createCarList(handle);
        for (int i = 0; i < truckList.size(); i++)
            truckList[i].Move(lightList[1]);
        createTruckList(handle);
        for (int i = 0; i < birdList.size(); i++)
            birdList[i].Move();
        createBirdList(handle);
        for (int i = 0; i < dinausorList.size(); i++)
            dinausorList[i].Move();
        createDinausorList(handle);
        for (int i = 0; i < lightList.size(); i++)
            lightList[i].changeType(handle);
    }
    void drawAllMovingObject(ConsoleHandle& handle)
    {
        for (int i = 0; i < carList.size(); i++) {
            carList[i].drawCar(handle);
        }
        for (int i = 0; i < truckList.size(); i++) {
            truckList[i].drawTruck(handle);
        }
        for (int i = 0; i < birdList.size(); i++) {
            birdList[i].drawBird(handle);
        }
        for (int i = 0; i < dinausorList.size(); i++) {
            dinausorList[i].drawDinausor(handle);
        }
        for (int i = 0; i < lightList.size(); i++) {
            lightList[i].drawLight(handle);
        }
        handle.updateObstacle(33, 2, "GameMap.txt");
        people->draw(handle);
        handle.draw();
        for (int i = 0; i < carList.size(); i++)
        {
            carList[i].deleteVehicle(handle, lightList[0]);
        }
        for (int i = 0; i < truckList.size(); i++)
        {
            truckList[i].deleteVehicle(handle, lightList[1]);
        }
        for (int i = 0; i < dinausorList.size(); i++)
        {
            dinausorList[i].deleteAnimal(handle);
        }
        for (int i = 0; i < birdList.size(); i++)
        {
            birdList[i].deleteAnimal(handle);
        }
    }
    void clearAllData()
    {
        userName = passWord = "";
        difficulty = 100;
        live = 3;
        stage = 1;
        carList.clear();
        truckList.clear();
        birdList.clear();
        dinausorList.clear();
        lightList.clear();
        people->setPos(94, 43);
    }
    vector<CCar> getCarList()
    {
        return carList;
    }
    vector<CTruck> getTruckList()
    {
        return truckList;
    }
    vector<CBird> getBirdList()
    {
        return birdList;
    }
    vector<CDinausor> getDinausorList()
    {
        return dinausorList;
    }
    vector<TrafficLight> getTrafficLightList()
    {
        return lightList;
    }
    void gameMenu(ConsoleHandle& handle) {
        string fileData = "NewGameData.dat";
        int line = 1;
        string fileNamePrefix = "Menu-";
        string fileNameSuffix = ".txt";
        string fileName = "Menu-1.txt";
        handle.drawTitle();
        handle.drawMenu(fileName);
        int c = 0;
        while (1)
        {
            c = 0;
            switch ((c = _getch())) {
            case KEY_UP:
                line--;
                if (line == 0) line = 1;
                fileName = fileNamePrefix + char(line + 48) + fileNameSuffix;
                handle.drawMenu(fileName);
                break;
            case KEY_DOWN:
                line++;
                if (line == 6) line = 5;
                fileName = fileNamePrefix + char(line + 48) + fileNameSuffix;
                handle.drawMenu(fileName);
                break;
            case VK_RETURN:
                if (line == 1) { //new game
                    fileData = "NULL.dat";
                    drawMap(handle, fileData);
                    handle.clear();
                    handle.drawTitle();
                    handle.drawMenu(fileName);
                    clearAllData();
                }
                else if (line == 2) //load game
                {
                    handle.clear();
                    fileData = loadGame(handle);
                    handle.drawMenu(fileName);
                    if (fileData.compare("NULL.dat") != 0)
                        drawMap(handle, fileData);
                    handle.clear();
                    handle.drawTitle();
                    handle.drawMenu(fileName);
                    clearAllData();
                }
                else if (line == 3) //setting
                {
                    settingMenu(handle);
                    handle.drawMenu(fileName);
                }
                else if (line == 4) {   //about
                    handle.drawAbout();
                    handle.drawTitle();
                    handle.drawMenu(fileName);
                }
                else if (line == 5) //exit
                {
                    handle.clear();
                    handle.draw();
                    return;
                }
                break;
            default:
                break;
            }
        }
    }
    void drawMap(ConsoleHandle& handle, string dataFile) {
        handle.clear();
        string name = "";
        for (int i = 0; i < dataFile.length() - 4; i++)
            name += dataFile[i];
        if (dataFile.compare("NULL.dat") != 0)
        {
            readData(dataFile);
            while (1)
            {
                string pass = inputPassWord(handle);
                if (pass == "")
                    return;
                if (passWord.compare(pass) != 0)
                {
                    int option = handle.drawPassWordError();
                    if (option == 27)
                        return;

                }
                else
                {
                    handle.clear();
                    break;
                }
            }

            if (live == 0)
            {
                handle.drawNotAlive();
                return;
            }
        }
        else
        {
            createCarList(handle);
            createBirdList(handle);
            createTruckList(handle);
            createDinausorList(handle);
            createTrafficLightList();
        }
        int ch;
        handle.DrawGameMap();
        while (1) {
            //detect keyboard
            if (_kbhit()) {
                ch = _getch();
                if (ch == 224)
                {
                    ch = _getch();
                    people->erasePeople(handle);
                    if (ch == KEY_LEFT) {
                        people->Left();
                    }
                    else if (ch == KEY_RIGHT) {
                        people->Right();
                    }
                    else if (ch == KEY_DOWN) {
                        people->Down();
                    }
                    else if (ch == KEY_UP) {
                        people->Up();
                    }
                    people->draw(handle);
                }
                else if (ch == 'p' || ch == 'P') {
                    int option = pauseGamePanel(handle);
                    if (option == 1 || option == 3) // resume || setting
                        continue;
                    else if (option == 2 || option == 4)   // save game || exit
                    {
                        clearAllData();
                        return;
                    }
                }
            }
            handle.drawHeart(live);
            handle.drawStage(stage);
            handle.drawString(18, 21, to_string(5 - difficulty / 25));
            drawAllMovingObject(handle);
            moveAllObject(handle);
            Sleep(difficulty);
            if (people->isImpact(carList) || people->isImpact(truckList) || people->isImpact(birdList) || people->isImpact(dinausorList))
            {
                live--;
                thread t1(playDeathSound);
                people->drawDeathEffect(handle);
                t1.join();
                drawAllMovingObject(handle);
                if (live == 0)
                {
                    endGame(handle, name);
                    return;
                }
                people->draw(handle);
                handle.draw();
                int option = failGame(handle);
                if (option == 1 || option == 3)
                {
                    handle.eraseHeart();
                    continue;
                }
                else if (option == 4)
                    return;
                handle.eraseHeart();
            }
            if (people->isFinish()) {
                people->erasePeople(handle);
                people->setPos(94, 43);
                if (difficulty > 5)
                    difficulty -= 25;
                else
                    difficulty = 105;
                stage++;
            }
        }
    }
    string loadGame(ConsoleHandle& handle)
    {
        vector<si> playerList = handle.drawLoadGameMenu("LoadGameMenu.txt");
        string fileData = ".dat";
        vector <char> saveName;
        int c = 0;
        while (1) {
            c = 0;
            c = handle.lowerGetch();
            if ((c >= 'a' && c <= 'z' || c == ' ') && saveName.size() <= 10)
                saveName.push_back(c);
            else if (c == 27)   //exit
            {
                handle.eraseLoadGameMenu(playerList);
                return "NULL" + fileData;
            }
            else if (c == 8)    //backspace
            {
                if (saveName.size() > 0)
                    saveName.pop_back();
            }
            else if (c == 13)   //enter
            {
                string tmp = "";
                for (int i = 0; i < saveName.size(); i++)
                    tmp = tmp + saveName[i];
                for (int i = 0; i < playerList.size(); i++)
                    if (playerList[i].first.compare(tmp) == 0)
                    {
                        handle.eraseLoadGameMenu(playerList);
                        return tmp + fileData;
                    }
                handle.drawNameNotExit();
                saveName.clear();
                handle.drawLoadGameMenu("LoadGameMenu.txt");
            }
            handle.writeNameToConsole(ConsoleHandle::getCenterX(53)+14, ConsoleHandle::getCenterY(14 + playerList.size(), 14) + 6 + playerList.size(), saveName);
        }
        handle.eraseLoadGameMenu(playerList);
        return "NULL" + fileData;
    }
    void settingMenu(ConsoleHandle& handle)
    {
        int line = 1;
        string fileNamePrefix = "Setting-";
        string fileNameSuffix = ".txt";
        string fileName = "Setting-1.txt";
        handle.drawSettingMenu(fileName);
        bool isInPauseMenu = true;
        int c = 0;
        while (isInPauseMenu) {
            c = 0;
            switch ((c = _getch())) {
            case KEY_UP:
                line--;
                if (line == 0) line = 1;
                fileName = fileNamePrefix + char(line + 48) + fileNameSuffix;
                handle.drawSettingMenu(fileName);
                break;
            case KEY_DOWN:
                line++;
                if (line == 3) line = 2;
                fileName = fileNamePrefix + char(line + 48) + fileNameSuffix;
                handle.drawSettingMenu(fileName);
                break;
            case 'b':
                return;
            case VK_RETURN:
                if (line == 1) {
                    isInPauseMenu = false;
                    sound = true;
                    handle.eraseSettingMenu();
                    return;
                }
                if (line == 2) {
                    isInPauseMenu = false;
                    sound = false;
                    handle.eraseSettingMenu();
                    return;
                }
            default:
                break;
            }
        }
    }
    int failGame(ConsoleHandle& handle) {
        int line = 1;
        string fileNamePrefix = "FailGame-";
        string fileNameSuffix = ".txt";
        string fileName = "FailGame-1.txt";
        handle.drawFailGameMenu(fileName);
        bool isInFailGameMenu = true;
        int c = 0;
        while (isInFailGameMenu) {
            c = 0;
            switch ((c = _getch())) {
            case KEY_UP:
                line--;
                if (line == 0) line = 1;
                fileName = fileNamePrefix + char(line + 48) + fileNameSuffix;
                handle.drawFailGameMenu(fileName);
                break;
            case KEY_DOWN:
                line++;
                if (line == 5) line = 4;
                fileName = fileNamePrefix + char(line + 48) + fileNameSuffix;
                handle.drawFailGameMenu(fileName);
                break;
            case VK_RETURN:
                if (line == 1) {    //resume
                    isInFailGameMenu = false;
                    handle.eraseFailGameMenu();
                    people->erasePeople(handle);
                    people->setPos(94, 43);
                    return 1;
                }
                if (line == 2) {    //save game
                    handle.eraseFailGameMenu();
                    saveGamePanel(handle);
                    handle.eraseSaveGamePanel();
                    handle.DrawGameMap();
                    drawAllMovingObject(handle);
                    handle.drawFailGameMenu(fileName);
                }
                if (line == 3)  //setting
                {
                    settingMenu(handle);
                    handle.eraseSettingMenu();
                    handle.DrawGameMap();
                    drawAllMovingObject(handle);
                    handle.drawFailGameMenu(fileName);
                }
                if (line == 4) {    //exit
                    isInFailGameMenu = false;
                    return 4;
                }
                break;
            default:
                break;
            }
        }
    }
    int pauseGamePanel(ConsoleHandle& handle) {
        int line = 1;
        string fileNamePrefix = "PauseMenu-";
        string fileNameSuffix = ".txt";
        string fileName = "PauseMenu-1.txt";
        handle.drawPauseMenu(fileName);
        bool isInPauseMenu = true;
        int c = 0;
        while (isInPauseMenu) {
            c = 0;
            switch ((c = _getch())) {
            case KEY_UP:
                line--;
                if (line == 0) line = 1;
                fileName = fileNamePrefix + char(line + 48) + fileNameSuffix;
                handle.drawPauseMenu(fileName);
                break;
            case KEY_DOWN:
                line++;
                if (line == 5) line = 4;
                fileName = fileNamePrefix + char(line + 48) + fileNameSuffix;
                handle.drawPauseMenu(fileName);
                break;
            case VK_RETURN:
                if (line == 1) {    //resume
                    isInPauseMenu = false;
                    handle.erasePauseMenu();
                    return 1;
                }
                if (line == 2) {    //save game
                    saveGamePanel(handle);
                    handle.eraseSaveGamePanel();
                    if(userName!="" && passWord != "")
                        return 2;
                    handle.clear();
                    handle.DrawGameMap();
                    drawAllMovingObject(handle);
                    handle.drawPauseMenu(fileName);
                }
                if (line == 3)  //setting
                {
                    settingMenu(handle);
                    handle.eraseSettingMenu();
                    handle.DrawGameMap();
                    drawAllMovingObject(handle);
                    handle.drawPauseMenu(fileName);
                }
                if (line == 4) {    //exit
                    isInPauseMenu = false;
                    return 4;
                }
                break;
            default:
                break;
            }
        }
    }
    void endGame(ConsoleHandle& handle, string name)
    {
        int option = handle.drawEndGame();
        if (option == 27)
            return;
        if (option == VK_RETURN)
        {
            handle.DrawGameMap();
            drawAllMovingObject(handle);
            saveGamePanel(handle);
            handle.eraseSaveGamePanel();
        }
    }
    //void readData(string dataFile) {
    //    ifstream fi;
    //    fi.open(dataFile);
    //    string buffer;
    //    int n, posX, posY;
    //    //Car;
    //    fi >> buffer;
    //    fi >> n;
    //    for (int i = 0; i < n; i++) {
    //        fi >> posX >> posY;
    //        addCar(posX, posY);
    //    }
    //    //Truck;
    //    fi >> buffer;
    //    fi >> n;
    //    for (int i = 0; i < n; i++) {
    //        fi >> posX >> posY;
    //        addTruck(posX, posY);
    //    }
    //    //Bird;
    //    fi >> buffer;
    //    fi >> n;
    //    for (int i = 0; i < n; i++) {
    //        fi >> posX >> posY;
    //        addBird(posX, posY);
    //    }
    //    //Dinausor;
    //    fi >> buffer;
    //    fi >> n;
    //    for (int i = 0; i < n; i++) {
    //        fi >> posX >> posY;
    //        addDinausor(posX, posY);
    //    }
    //    //TrafficLight
    //    fi >> buffer;
    //    fi >> n;
    //    int currentTime, time, type;
    //    for (int i = 0; i < n; i++) {
    //        fi >> posX >> posY;
    //        TrafficLight newLight(posX, posY);
    //        fi >> currentTime >> time >> type;
    //        newLight.setTime(currentTime, time);
    //        newLight.setType(type);
    //        addTrafficLight(newLight);
    //    }
    //    //Human
    //    fi >> buffer;
    //    fi >> posX >> posY;
    //    people->setPos(posX, posY);

    //    //Stage;
    //    fi >> buffer;
    //    fi >> stage;

    //    //Difficulty
    //    fi >> buffer;
    //    fi >> difficulty;

    //    //live
    //    fi >> buffer;
    //    fi >> live;

    //    //userName
    //    fi >> buffer;
    //    fi >> userName;

    //    //password
    //    fi >> buffer;
    //    fi >> passWord;

    //    fi.close();
    //}
    void readData(string dataFile) {
        ifstream fi;
        fi.open(dataFile,ios::in|ios::binary);
        string buffer;
        int n, posX, posY;

        //Car
        fi.read((char*)&n, sizeof(int));
        cout << n << endl;
        for (int i = 0; i < n; i++) {
            Point p;
            fi.read((char*)&p, sizeof(Point));
            cout << p.x << " " << p.y << endl;
            addCar(p.x, p.y);
        }
        
        //Truck
        fi.read((char*)&n, sizeof(int));
        for (int i = 0; i < n; i++) {
            Point p;
            fi.read((char*)&p, sizeof(Point));
            addTruck(p.x, p.y);
        }

        //Bird
        fi.read((char*)&n, sizeof(int));
        for (int i = 0; i < n; i++) {
            Point p;
            fi.read((char*)&p, sizeof(Point));
            addBird(p.x, p.y);
        }

        //Dinausor
        fi.read((char*)&n, sizeof(int));
        cout << n << endl;
        for (int i = 0; i < n; i++) {
            Point p;
            fi.read((char*)&p, sizeof(Point));
            cout << p.x << " " << p.y << endl;
            addDinausor(p.x, p.y);
        }

        //TrafficLight
        fi.read((char*)&n, sizeof(int));
        cout << n << endl;
        for (int i = 0; i < n; i++) {
            Point p;
            fi.read((char*)&p, sizeof(Point));
            cout << p.x << " " << p.y << " ";
            TrafficLight newLight(p.x, p.y);
            int currentTime = 0, time = 0, type = 0;
            fi.read((char*)&currentTime, sizeof(int));
            fi.read((char*)&time, sizeof(int));
            fi.read((char*)&type, sizeof(int));
            cout << currentTime << " " << time << " " << type << endl;
            newLight.setTime(currentTime, time);
            newLight.setType(type);
            addTrafficLight(newLight);
        }

        //Human
        Point po;
        fi.read((char*)&po, sizeof(Point));
        cout << po.x << " " << po.y << endl;
        people->setPos(po.x, po.y);

        //Stage;
        fi.read((char*)&stage, sizeof(int));
        cout << stage << endl;

        //Difficulty
        fi.read((char*)&difficulty, sizeof(int));
        cout << difficulty << endl;

        //live
        fi.read((char*)&live, sizeof(int));
        cout << live << endl;

        //userName
        fi.read((char*)&userName, sizeof(string));
        cout << userName << endl;

        //password
        fi.read((char*)&passWord, sizeof(string));
        cout << passWord << endl;

        fi.close();
    }
    /*void saveGame(ConsoleHandle& handle, int k = 0) {
        string fileName = userName;
        ofstream fo;
        if (k != 1)
        {
            fo.open("LoadGame.txt", ios::app);
            fo << fileName << " " << stage << endl;
            fo.close();
        }
        else
        {
            fstream file;
            file.open("LoadGame.txt", ios::in | ios::out);
            if (file)
            {
                while (!file.eof())
                {
                    string tmp1;
                    int tmp2;
                    file >> tmp1;
                    int p = 0;
                    p = file.tellp();
                    if (tmp1.compare(fileName) == 0)
                    {
                        p++;
                        file.seekp(p);
                        file << stage;
                        break;
                    }
                    file >> tmp2;
                }
            }
        }
        fileName += ".txt";
        fo.open(fileName);

        fo << "//Car//" << '\n';
        fo << carList.size() << '\n';
        for (int i = 0; i < carList.size(); i++) {
            Point cord = carList[i].getPos();
            fo << cord.x << char(32) << cord.y << '\n';
        }

        fo << "//Truck//" << '\n';
        fo << truckList.size() << '\n';
        for (int i = 0; i < truckList.size(); i++) {
            Point cord = truckList[i].getPos();
            fo << cord.x << char(32) << cord.y << '\n';
        }

        fo << "//Bird//" << '\n';
        fo << birdList.size() << '\n';
        for (int i = 0; i < birdList.size(); i++) {
            Point cord = birdList[i].getPos();
            fo << cord.x << char(32) << cord.y << '\n';
        }

        fo << "//Dinausor//" << '\n';
        fo << dinausorList.size() << '\n';
        for (int i = 0; i < dinausorList.size(); i++) {
            Point cord = dinausorList[i].getPos();
            fo << cord.x << char(32) << cord.y << '\n';
        }

        fo << "//TrafficLight//" << '\n';
        fo << lightList.size() << '\n';
        for (int i = 0; i < lightList.size(); i++) {
            fo << lightList[i].getPos().x << char(32) << lightList[i].getPos().y << char(32) << lightList[i].getCurrentTime() << char(32) << lightList[i].getTime();
            if (lightList[i].getStatus().compare("Light-2.txt") == 0)
                fo << " 2" << endl;
            else
                fo << " 1" << endl;
        }

        fo << "//Human//" << '\n';
        Point cord = people->getPos();
        fo << cord.x << char(32) << cord.y << '\n';

        fo << "//stage//" << '\n';
        fo << stage << '\n';

        fo << "//difficuly//" << '\n';
        fo << difficulty << '\n';

        fo << "//live//" << '\n';
        fo << live << '\n';

        fo << "//username//" << '\n';
        fo << userName << '\n';

        fo << "//password//" << '\n';
        fo << passWord << '\n';

        fo.close();
    }*/
    void saveGame(ConsoleHandle& handle, int k = 0) {
        string fileName = userName;
        ofstream fo;
        if (k != 1)
        {
            fo.open("LoadGame.txt", ios::app);
            fo << fileName << " " << stage << endl;
            fo.close();
        }
        else
        {
            fstream file;
            file.open("LoadGame.txt", ios::in | ios::out);
            if (file)
            {
                while (!file.eof())
                {
                    string tmp1;
                    int tmp2;
                    file >> tmp1;
                    int p = 0;
                    p = file.tellp();
                    if (tmp1.compare(fileName) == 0)
                    {
                        p++;
                        file.seekp(p);
                        file << stage;
                        break;
                    }
                    file >> tmp2;
                }
            }
        }
        fileName += ".dat";
        fo.open(fileName,ios::out|ios::binary);

        //car
        int n = carList.size();
        fo.write((char*)&n, sizeof(int));
        for (int i = 0; i < carList.size(); i++) {
            Point cord = carList[i].getPos();
            fo.write((char*)&cord, sizeof(Point));
        }

        //truck
        n = truckList.size();
        fo.write((char*)&n, sizeof(int));
        for (int i = 0; i < truckList.size(); i++) {
            Point cord = truckList[i].getPos();
            fo.write((char*)&cord, sizeof(Point));
        }

        //Bird
        n = birdList.size();
        fo.write((char*)&n, sizeof(int));
        for (int i = 0; i < birdList.size(); i++) {
            Point cord = birdList[i].getPos();
            fo.write((char*)&cord, sizeof(Point));
        }

        //Dinausor
        n = dinausorList.size();
        fo.write((char*)&n, sizeof(int));
        for (int i = 0; i < dinausorList.size(); i++) {
            Point cord = dinausorList[i].getPos();
            fo.write((char*)&cord, sizeof(Point));
        }

        //TrafficLight
        n = lightList.size();
        fo.write((char*)&n, sizeof(int));
        for (int i = 0; i < lightList.size(); i++) {
            Point cord = lightList[i].getPos();
            fo.write((char*)&cord, sizeof(Point));
            int x = lightList[i].getCurrentTime();
            fo.write((char*)&x, sizeof(int));
            x = lightList[i].getTime();
            fo.write((char*)&x, sizeof(int));
            if (lightList[i].getStatus().compare("Light-2.txt") == 0)
                x = 2;
            else
                x = 1;
            fo.write((char*)&x, sizeof(int));
        }

        //Human
        Point cord = people->getPos();
        fo.write((char*)&cord, sizeof(Point));

        //stage
        fo.write((char*)&stage, sizeof(int));

        //difficuly
        fo.write((char*)&difficulty, sizeof(int));

        //live
        fo.write((char*)&live, sizeof(int));

        //userName
        fo.write((char*)&userName, sizeof(string));

        //password
        fo.write((char*)&passWord, sizeof(string));

        fo.close();
    }
    void saveGamePanel(ConsoleHandle& handle) {
        if (userName != "")
        {
            int k = 1;
            saveGame(handle,1);
            handle.drawSaveDataPanel();
            return;
        }
        vector <char> saveName;
        string fileName = "SaveGamePanel.txt";
        vector<si> playerList = handle.drawSavePanel(fileName);
        int c = 0;
        while (1) {
            c = 0;
            c = handle.lowerGetch();
            
            if ((c >= 'a' && c <= 'z') && saveName.size() <= 9)
                saveName.push_back(c);
            else if (c == 27)   //exit
                return;
            else if (c == 8)
            {
                if (saveName.size() > 0)
                    saveName.pop_back();
            }
            else if (c == 13)   //save
            {
                if (saveName.size() > 0)
                {
                    string s = "";
                    for (int i = 0; i < saveName.size(); i++)
                        s += saveName[i];
                    bool tmp = false;
                    for (int i = 0; i < playerList.size(); i++)
                        if (playerList[i].first.compare(s) == 0)
                        {
                            tmp = true;
                            handle.drawNameCreated("NameCreated.txt");
                            Sleep(3000);
                            saveName.clear();
                        }
                    if (tmp == true)
                    {
                        handle.clear();
                        handle.DrawGameMap();
                        drawAllMovingObject(handle);
                        handle.drawSavePanel("SaveGamePanel.txt");
                        continue;
                    }
                    userName = s;
                    string pass = inputPassWord(handle);
                    if (pass == "")
                        return;
                    passWord = pass;
                    saveGame(handle);
                    handle.drawSaveDataPanel();
                    return;
                }
            }
            handle.writeNameToConsole(ConsoleHandle::getCenterX(52, 33, 162)+15, ConsoleHandle::getCenterY(20, 2, 47) + 2, saveName);
        }
    }
    string inputPassWord(ConsoleHandle& handle)
    {
        vector <char> pass;
        string fileName = "PassWord.txt";
        handle.drawInputPassWord(fileName);
        int c = 0;
        handle.drawString(ConsoleHandle::getCenterX(52) + 15, ConsoleHandle::getCenterY(12, 14) + 1, userName);
        while (1) {
            c = 0;
            c = handle.lowerGetch();

            if ((c >= 'a' && c <= 'z') && pass.size() <= 9)
                pass.push_back(c);
            else if (c == 27)   //exit
                return "";
            else if (c == 8)
            {
                if (pass.size() > 0)
                    pass.pop_back();
            }
            else if (c == 13 && pass.size() == 10)   //save
            {
                if (pass.size() > 0)
                {
                    string res = "";
                    for (int i = 0; i < pass.size(); i++)
                        res += pass[i];
                    return res;
                }
            }
            handle.writeNameToConsole(ConsoleHandle::getCenterX(52) + 18, ConsoleHandle::getCenterY(12, 14) + 3, pass);
        }
    }
    void deleteGame()
    {
        delete people;
        userName = passWord = "";
        clearAllData();
    }
};