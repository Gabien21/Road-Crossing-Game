#include "CGame.h"

int SOUND = 1;
void playDeathSound() {
    mciSendString(TEXT("open \"sound/human_die.mp3\" type mpegvideo alias mp3"), NULL, 0, NULL);
    mciSendString(TEXT("play mp3"), NULL, 0, NULL);
}

void playFinishSound() {

    mciSendString(TEXT("open \"sound/finish.mp3\" type mpegvideo alias mp3"), NULL, 0, NULL);
    mciSendString(TEXT("play mp3"), NULL, 0, NULL);
}

void playEndGameSound() {
    mciSendString(TEXT("open \"sound/endGame.mp3\" type mpegvideo alias mp3"), NULL, 0, NULL);
    mciSendString(TEXT("play mp3"), NULL, 0, NULL);
}


void playMusic() {
    PlaySound(TEXT("sound/MenuMusic.wav"), NULL, SND_ASYNC | SND_LOOP);
}

void StopPlaySound()
{
    PlaySound(0, 0, 0);
}

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

CGame::CGame()
{
    this->people = new CPeople(94, 43);
    difficulty = 125;
    stage = 1;
    live = 3;
    sound = true;
    color = WHITE;
    userName = passWord = "";
}
CGame::~CGame()
{
    deleteGame();
}
string CGame::getName()
{
    return userName;
}
string CGame::getPassWord()
{
    return passWord;
}
bool CGame::getSound()
{
    return sound;
}
void CGame::addCar(int x, int y)
{
    CCar newCar(x, y);
    carList.push_back(newCar);
}
void CGame::addTruck(int x, int y)
{
    CTruck newTruck(x, y);
    truckList.push_back(newTruck);
}
void CGame::addBird(int x, int y)
{
    CBird newBird(x, y);
    birdList.push_back(newBird);
}
void CGame::addDinausor(int x, int y)
{
    CDinausor newDinausor(x, y);
    dinausorList.push_back(newDinausor);
}
void CGame::addTrafficLight(TrafficLight& newLight)
{
    lightList.push_back(newLight);
}
void CGame::createCarList(ConsoleHandle& handle)
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
            CCar newCar(33 - carList[0].getLength(), 10);
            carList.push_back(newCar);
        }
    }
}
void CGame::createTruckList(ConsoleHandle& handle)
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
            CTruck newTruck(33 - truckList[0].getLength(), 28);
            truckList.push_back(newTruck);
        }
    }
}
void CGame::createBirdList(ConsoleHandle& handle)
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
void CGame::createDinausorList(ConsoleHandle& handle)
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
void CGame::createTrafficLightList()
{
    lightList.resize(2);
    lightList[0].setPos(164, 7);
    lightList[1].setPos(164, 25);
}
void CGame::moveAllObject(ConsoleHandle& handle)
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
void CGame::drawAllMovingObject(ConsoleHandle& handle)
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
void CGame::clearAllData()
{
    userName = passWord = "";
    difficulty = 125;
    color = WHITE;
    COLOR = color;
    at = (COLOR == WHITE) ? 0 : 15;
    live = 3;
    stage = 1;
    carList.clear();
    truckList.clear();
    birdList.clear();
    dinausorList.clear();
    lightList.clear();
    people->setPos(94, 43);
}
vector<CCar> CGame::getCarList()
{
    return carList;
}
vector<CTruck> CGame::getTruckList()
{
    return truckList;
}
vector<CBird> CGame::getBirdList()
{
    return birdList;
}
vector<CDinausor> CGame::getDinausorList()
{
    return dinausorList;
}
vector<TrafficLight> CGame::getTrafficLightList()
{
    return lightList;
}
void CGame::gameMenu(ConsoleHandle& handle) {
    string fileData = "NewGameData.dat";
    int line = 1;
    if (sound == 1)
    {
        thread t1(playMusic);
        t1.join();
    }
    handle.drawLoading();
    handle.clear();
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
                handle.drawTitle();
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
void CGame::drawMap(ConsoleHandle& handle, string dataFile) {
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
        handle.drawString(18, 21, to_string(6 - difficulty / 25));
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
                thread tmp(playEndGameSound);
                tmp.join();
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
            thread t(playFinishSound);
            t.join();

            people->erasePeople(handle);
            people->setPos(94, 43);
            if (difficulty > 25)
                difficulty -= 25;
            else
                difficulty = 125;
            stage++;
        }
    }
}

int CGame::failGame(ConsoleHandle& handle) {
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
                people->setPos(94, 43);
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

string CGame::loadGame(ConsoleHandle& handle)
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
        handle.writeNameToConsole(ConsoleHandle::getCenterX(53) + 14, ConsoleHandle::getCenterY(14 + playerList.size(), 14) + 6 + playerList.size(), saveName);
    }
    handle.eraseLoadGameMenu(playerList);
    return "NULL" + fileData;
}

void CGame::SetSound(ConsoleHandle& handle)
{
    int line = 1;
    string fileName = "SetSound.txt";
    handle.drawSettingSoundMenu(fileName);
    string s = (sound == 1) ? "ON" : "OFF";
    handle.drawString(ConsoleHandle::getCenterX(38) + 35, ConsoleHandle::getCenterY(7, 14) + 3, s, 2);
    bool isInPauseMenu = true;
    int c = 0;
    while (isInPauseMenu) {
        c = 0;
        if ((c = _getch()))
        {
            if (c == KEY_UP)
            {
                line--;
                if (line == 0) line = 1;
                s = (sound == 1) ? "ON" : "OFF";
                handle.eraseString(ConsoleHandle::getCenterX(38) + 35, ConsoleHandle::getCenterY(7, 14) + 3, 3);
                handle.drawString(ConsoleHandle::getCenterX(38) + 35, ConsoleHandle::getCenterY(7, 14) + 3, s, 2);
            }
            else if (c == KEY_DOWN)
            {
                line++;
                if (line == 3) line = 2;
                s = (sound == 0) ? "ON" : "OFF";
                handle.eraseString(ConsoleHandle::getCenterX(38) + 35, ConsoleHandle::getCenterY(7, 14) + 3, 3);
                handle.drawString(ConsoleHandle::getCenterX(38) + 35, ConsoleHandle::getCenterY(7, 14) + 3, s, 4);
            }
            else if (c == 'b' || c == 'B')
            {
                handle.eraseSettingSoundMenu();
                return;
            }
            else if (c == 13)
            {
                if (line == 2) {
                    isInPauseMenu = false;
                    if (sound == 1)
                    {
                        thread t(StopPlaySound);
                        t.join();
                    }
                    else
                    {
                        thread t(playMusic);
                        t.join();
                    }
                    sound = !sound;
                }
                handle.eraseSettingSoundMenu();
            }
        }
    }
}
void CGame::SetBackGround(ConsoleHandle& handle)
{
    int line = 1;
    string fileName = "SetSound.txt";
    handle.drawSettingBackGroundMenu(fileName);
    string s = (color == WHITE) ? "WHITE" : "BLACK";
    handle.drawString(ConsoleHandle::getCenterX(38) + 34, ConsoleHandle::getCenterY(7, 14) + 3, s, 2);
    bool isInPauseMenu = true;
    int c = 0;
    while (isInPauseMenu) {
        c = 0;
        if ((c = _getch()))
        {
            if (c == KEY_UP)
            {
                line--;
                if (line == 0) line = 1;
                s = (color == WHITE) ? "WHITE" : "BLACK";
                handle.eraseString(ConsoleHandle::getCenterX(38) + 34, ConsoleHandle::getCenterY(7, 14) + 3, 5);
                handle.drawString(ConsoleHandle::getCenterX(38) + 34, ConsoleHandle::getCenterY(7, 14) + 3, s, 2);
            }
            else if (c == KEY_DOWN)
            {
                line++;
                if (line == 3) line = 2;
                s = (color != WHITE) ? "WHITE" : "BLACK";
                handle.eraseString(ConsoleHandle::getCenterX(38) + 34, ConsoleHandle::getCenterY(7, 14) + 3, 5);
                handle.drawString(ConsoleHandle::getCenterX(38) + 34, ConsoleHandle::getCenterY(7, 14) + 3, s, 4);
            }
            else if (c == 'b' || c == 'B')
            {
                handle.eraseSettingSoundMenu();
                return;
            }
            else if (c == 13)
            {
                if (line == 2) {
                    isInPauseMenu = false;
                    color = (color == WHITE) ? DARK : WHITE;
                    COLOR = color;
                    at = (COLOR == WHITE) ? 0 : 15;
                }
                handle.eraseSettingSoundMenu();
            }
        }
    }
}
void CGame::settingMenu(ConsoleHandle& handle)
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
        if ((c = _getch()))
        {
            if (c == KEY_UP)
            {
                line--;
                if (line == 0) line = 1;
                fileName = fileNamePrefix + char(line + 48) + fileNameSuffix;
                handle.drawSettingMenu(fileName);
            }
            else if (c == KEY_DOWN)
            {
                line++;
                if (line == 3) line = 2;
                fileName = fileNamePrefix + char(line + 48) + fileNameSuffix;
                handle.drawSettingMenu(fileName);
            }
            else if (c == 'b' || c == 'B')
            {
                return;
            }
            else if (c == 13)
            {
                if (line == 1) {
                    SetSound(handle);
                    handle.drawSettingMenu(fileName);
                }
                else if (line == 2) {
                    SetBackGround(handle);
                    handle.drawSettingMenu(fileName);
                }
            }
        }
    }
}


int CGame::pauseGamePanel(ConsoleHandle& handle) {
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
                if (userName != "" && passWord != "")
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
void CGame::endGame(ConsoleHandle& handle, string name)
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

void CGame::readData(string dataFile) {
    ifstream fi;
    fi.open(dataFile, ios::in | ios::binary);
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

void CGame::saveGame(ConsoleHandle& handle, int k) {
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
    fo.open(fileName, ios::out | ios::binary);

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
void CGame::saveGamePanel(ConsoleHandle& handle) {
    if (userName != "")
    {
        int k = 1;
        saveGame(handle, 1);
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
        handle.writeNameToConsole(ConsoleHandle::getCenterX(52, 33, 162) + 15, ConsoleHandle::getCenterY(20, 2, 47) + 2, saveName);
    }
}
string CGame::inputPassWord(ConsoleHandle& handle)
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
void CGame::deleteGame()
{
    delete people;
    userName = passWord = "";
    clearAllData();
}