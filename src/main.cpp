#include <iostream>
#include <vector>

const int n = 10;
int countDecksPlayer1 = 20;
int countDecksPlayer2 = 20;
int x, y, begin_x, begin_y, end_x, end_y, count;
bool hit;

void printField(int (&arr)[n][n]){
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      std::cout << arr[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

void singleShip(int (&arr)[n][n], int x, int y){
  arr[x][y] = 1;
}

void ship(int (&arr)[n][n], int begin_x, int begin_y, int end_x, int end_y, int count){
    for(int i = begin_x; i <= end_x; i++){
      for(int j = begin_y; j <= end_y; j++){
        if(arr[i][j] != 0){
          std::cout << "Error enter" << std::endl;
        }
      }
    }
    if(begin_x > 10 || begin_x < 0 || begin_y > 10 || begin_y < 0 || 
      end_x > 10 || end_x < 0 || end_y > 10 || end_y < 0){
        std::cout << "Error enter" << std::endl;
    }else{
        for(int i = begin_x; i <= end_x; i++){
          for(int j = begin_y; j <= end_y; j++){
            arr[i][j] = count;
          }
        }
    }
}

void shipPlacement(int (&arr)[n][n]){
for(int i = 0; i < 4; i++){
    std::cout << "Single-deck ship" << std::endl;
    std::cin >> x >> y;
    if(x > 10 || x < 0 || y > 10 || y < 0){
      std::cout << "Error enter" << std::endl;
    }else{
      singleShip(arr, x, y);
      printField(arr);
    }
  }

 for(int i = 0; i < 3; i++){
    std::cout << "Two-deck ship" << std::endl;
    std::cout << "Enter the coordinates start" << std::endl;
    std::cin >> begin_x >> begin_y;
    std::cout << "Enter the coordinates of the end" << std::endl;
    std::cin >> end_x >> end_y;
    ship(arr, begin_x, begin_y, end_x, end_y, 2);
    printField(arr);    
  }

  for(int i = 0; i < 2; i++){
    std::cout << "Three-deck ship" << std::endl;
    std::cout << "Enter the coordinates start" << std::endl;
    std::cin >> begin_x >> begin_y;
    std::cout << "Enter the coordinates of the end" << std::endl;
    std::cin >> end_x >> end_y;
    ship(arr, begin_x, begin_y, end_x, end_y, 3);
    printField(arr);    
    }

  for(int i = 0; i < 1; i++){
    std::cout << "Four-deck ship" << std::endl;
    std::cout << "Enter the coordinates start" << std::endl;
    std::cin >> begin_x >> begin_y;
    std::cout << "Enter the coordinates of the end" << std::endl;
    std::cin >> end_x >> end_y;
    ship(arr, begin_x, begin_y, end_x, end_y, 4);
    printField(arr);    
  }
}

void battle(int (&arr)[n][n], int shot_x, int shot_y){
  if(arr[shot_x][shot_y] != 0){
    std::cout << "There is a hit" << std::endl;
    arr[shot_x][shot_y] = 0;
    hit = true;
  }else {
    std::cout << "Miss" << std::endl;
  }
}


int main(){
  std::cout << "Sea_Battle_v.2" << std::endl;

  int arrField_pleyer_1[n][n] = {};
  int arrField_pleyer_2[n][n] = {};
  int shot_x, shot_y;
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      arrField_pleyer_1[i][j] = 0;
    }
  }
  
  std::cout << "Player 1" << std::endl;
  shipPlacement(arrField_pleyer_1);
  
  std::cout << "Player 2" << std::endl;
  shipPlacement(arrField_pleyer_2);

  while (countDecksPlayer1 > 0 || countDecksPlayer2 > 0)
  {
    hit = false;
    std::cout << "Player's turn 1" << std::endl;
    std::cout << "Enter the coordinates of the shot" << std::endl;
    std::cin >> shot_x >> shot_y;
    battle(arrField_pleyer_2, shot_x, shot_y);
    if(hit)
      countDecksPlayer2--;

    hit = false;
    std::cout << "Player's turn 2" << std::endl;
    std::cout << "Enter the coordinates of the shot" << std::endl;
    std::cin >> shot_x >> shot_y;
    battle(arrField_pleyer_1, shot_x, shot_y);
    if(hit)
      countDecksPlayer1--;

    if(countDecksPlayer2 == 0){
      std::cout << "Player 1 win" << std::endl;
    }else if(countDecksPlayer1 == 0){
      std::cout << "Player 2 win" << std::endl;
    }
  }

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