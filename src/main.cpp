#include <iostream>

const int SIZE = 10;

void printField(int field[][SIZE], int rows){
    int columns = sizeof(field[0]) / sizeof(field[0][0]);
    std::cout << std::endl;
    for(int i =0; i < rows; ++i){
        for(int j =0; j < columns; ++j){
            if(field[i][j] == 1) std::cout << "X" << " ";
            else if(field[i][j] == 3) std::cout << "*" << " ";
            else std::cout << "." << " ";
        }
        std::cout << std::endl;
    }
}

int shot(int row, int col, int field[][SIZE]){
    int result = 0;
    if(field[row][col] == 1){
        std::cout << "Hit the target!" << std::endl;
        field[row][col] = 3;
        result = 1;
    }else{
        std::cout << "Off target!" << std::endl;
    }
    return result;
}

void rankingShips(int field[][SIZE]){
    int count = 4;
    int ship = 1;
    int row, col;
    std::string position = "H";

    for(int k = 0; k < 4; ++k){
        std::cout << "a ship with a size - " << ship << std::endl;

        for(int i = 0; i < count; ++i){
            bool flag;
            do{
                flag = false;
                std::cout << "Enter start coordinates: ";
                std::cin >> row >> col;
                if(ship > 1){
                    std::cout << "Enter position horizontal or vertical (H/V): ";
                    std::cin >> position;
                }

                if(position == "V" || position == "H"){
                    for(int l = 0; l < ship; ++l){
                        if(position == "H"){
                            if(row < 0 || row > SIZE-1 || col < 0
                                    || col + ship > SIZE || field[row][col + l] != 0){
                                flag = true;
                                break;
                            };
                        }else if(position == "V"){
                            if(row < 0 || row + ship > SIZE || col < 0
                                    || col > SIZE-1 || field[row + l][col] != 0){
                                flag = true;
                                break;
                            };
                        }
                    }
                }else {
                    flag = true;
                }
                if(flag) std::cout << "Something went wrong, please try again." << std::endl;
            }while(flag);

            for(int j = 0; j < ship; ++j){
                if(position == "H"){
                    field[row][col + j] = 1;
                    if(row - 1 > 0)field[row - 1][col + j] = 2;
                    if(row + 1 < 10)field[row + 1][col + j] = 2;
                    if(col - 1 > 0 && j == 0)field[row][col - 1] = 2;
                    if(col + ship + 1 < 10 && j == 0)field[row][col + ship] = 2;
                }else if(position == "V"){
                    field[row + j][col] = 1;
                    if(col - 1 > 0)field[row + j][col - 1] = 2;
                    if(col + 1 < 10)field[row + j][col + 1] = 2;
                    if(row - 1 > 0 && j == 0)field[row - 1][col] = 2;
                    if(row + ship + 1 < 10 && j == 0)field[row + ship][col] = 2;
                }                
            }
            printField(field, SIZE);
        }
        ++ship;
        --count;
    }
    std::cout << std::endl;
}

void gamePlayer(int field1[][SIZE], int field2[][SIZE]){
    int shipsPlayer1 = 20;
    int shipsPlayer2 = 20;
    int player = 1;
    int counter = 0;

    while(shipsPlayer1 && shipsPlayer2){
        int row, col;
        std::cout << "Player " << player << ", enter coordinates for the shot: ";
        std::cin >> row >> col;
        while(row < 0 || row > 9 || col < 0 || col > 9){
            std::cout << "wrong coordinates.\nre-enter coordinates: ";
            std::cin >> row >> col;
        }

        if(counter % 2 == 0){
            shipsPlayer2 -= shot(row, col, field2);
            player = 2;
            printField(field2, SIZE);
        }else{
            shipsPlayer1 -= shot(row, col, field1);
            player = 1;
            printField(field1, SIZE);
        }
        ++counter;
    }
    player = player == 1 ? 2 : 1;

    std::cout << "******** Won by Player " << player << " ********" << std::endl;
}

int main()
{
    int fieldPlayer1[SIZE][SIZE]{0};
    int fieldPlayer2[SIZE][SIZE]{0};

    std::cout << "Player 1 fill in the field:" << std::endl;
    rankingShips(fieldPlayer1);
    std::cout << std::endl << "Player 2 fill in the field:" << std::endl;
    rankingShips(fieldPlayer2);

    gamePlayer(fieldPlayer1, fieldPlayer2);

    return 0;
}


// Морской бой

// Требуется реализовать упрощённую игру в Морской бой. 
// Игровое поле размером 10 на 10 клеток. Участвует двое игроков. 
// В арсенале каждого из них: 4 маленьких кораблика размером 
// в одну клетку, 3 небольших корабля размером в две клетки, 
// 2 средних корабля размером в три клетки и один большой 
// корабль размером в четыре клетки. Для простоты, клетки 
// поля пронумерованы по вертикали от 0 до 9, и по 
// горизонтали также от 0 до 9. Мы не будем использовать 
// классические наименования клеток, такие как B4, C6, 
// а просто два индекса. Вначале игроки по очереди 
// расставляют корабли, начиная с самых маленьких 
// и заканчивая большими. Маленькие корабли в одну 
// клетку расставляются с помощью указания лишь одной 
// клетки-точки на поле, к примеру 2,1. 
// Корабли размерностью от двух клеток и выше, 
// расставляются с помощью координат их начала и конца, 
// к примеру: 0,1 - 0,3. Корабли могут быть 
// установлены только строго вертикально, или горизонтально. 
// Установка корабля по диагонали — недопустимо, 
// в случае которого об этом тоже надо сообщить пользователю. 
// Если корабль не может быть размещён на заданных клетках 
// из-за того, что он столкнётся с другим кораблём 
// (окажется на его клетках) или выйдет за пределы поля вообще, 
// то игроку должно быть сделано предупреждение, после которого 
// он должен переставить корабль на новые валидные координаты. 
// Замечу, в нашем упрощённом варианте игры, мы не будем 
// обсчитывать соприкосновения кораблей друг с другом, а 
// потому корабли вполне можно будет размещать друг к другу 
// вплотную — борт к борту. После того как все корабли были 
// расставлены начинается игра. Игроки по очереди атакуют 
// друг друга, называя координаты выстрела. После выстрела, 
// в консоль выводится информация о его результате: попал или мимо. 
// Если выстрел успешен, клетка, на которой был корабль 
// (или его фрагмент) затирается и становится пустой. 
// Игра заканчивается тогда, когда все корабли одной из 
// сторон будут полностью уничтожены. Как только это 
// произойдёт в консоль выводится информация с номером игрока, который победил.