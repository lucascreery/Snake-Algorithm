#include <SFML/Graphics.hpp>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int **map;
int **hamilton;
int apple[2];
int width = 20;
int height = 20;
int snakeLen = 3;
int direction = 0;
bool fail = false;
/*
up = 0
left = 1
down = 2
right = 3
*/

void updateMap(){
  int head[2];
  int nextStep[2];
  int dist = 0;
  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      if(map[i][j] == 1){
        head[0] = i;
        head[1] = j;
      }
    }
  }
  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      if(map[i][j] > 0){
        map[i][j]++;
      }
      if(map[i][j] == snakeLen + 1){
        map[i][j] = 0;
      }
    }
  }
  //printf("(%i, %i)\t%i\t to", head[0], head[1], hamilton[head[0]][head[1]]);
  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      if(hamilton[i][j] == (hamilton[head[0]][head[1]] + 1) % (width * height)){
        //printf("(%i, %i)\n", i, j);
        nextStep[0] = i;
        nextStep[1] = j;
        j = height;
        i = width;
        dist = sqrt(pow(apple[0] - nextStep[0] , 2) + pow(apple[1] - nextStep[1], 2));
      }
    }
  }
  if(snakeLen < (width * height) * 0.6){
    int tempNext[2];
    tempNext[0] = nextStep[0];
    tempNext[1] = nextStep[1];
    for(int a = 1; a < 200; a++){
      for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
          if(hamilton[i][j] == (hamilton[head[0]][head[1]] + a) % (width * height)){
            if(map[i][j] != 0){
              i = width;
              j = height;
              a = 200;
            }else if(abs(head[0] - i) < 2 && head[1] == j){
              tempNext[0] = i;
              tempNext[1] = j;
            }else if(abs(head[1] - j) < 2 && head[0] == i){
              tempNext[0] = i;
              tempNext[1] = j;
            }
          }
        }
      }
    }
    for(int a = 1; a < 50; a++){
      for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
          if(hamilton[i][j] == (hamilton[tempNext[0]][tempNext[1]] + a) % (width * height)){
            if(map[i][j] > 0){
              i = width;
              j = height;
              a = 200;
              tempNext[0] = nextStep[0];
              tempNext[1] = nextStep[1];
            }
          }
        }
      }
    }
    nextStep[0] = tempNext[0];
    nextStep[1] = tempNext[1];
  }
  if(map[nextStep[0]][nextStep[1]] == -1){
    snakeLen += 3;
    if(snakeLen > width * height){
      fail = true;
    }
    while(map[apple[0]][apple[1]] != 0){
      apple[0] = rand() % width;
      apple[1] = rand() % height;
//      printf("(%i, %i)\n", apple[0], apple[1]);
    }
    map[apple[0]][apple[1]] = -1;
  }
  if(map[nextStep[0]][nextStep[1]] > 0){
    fail = true;
  }
  map[nextStep[0]][nextStep[1]] = 1;
/*  switch(direction){
    case 0: //up
    if(map[head[0]][head[1] - 1] > 0){
      fail = true;
    }
    if(map[head[0]][head[1] - 1] == -1){
      snakeLen ++;
      while(map[apple[0]][apple[1]] > 0){
        apple[0] = rand() % width;
        apple[1] = rand() % height;
      }
    }
    if(head[1] == 0){
      fail = true;
    }
    if(!fail){
      map[head[0]][head[1] - 1] = 1;
    }
    break;

    case 1: //left
    if(map[head[0] - 1][head[1]] > 0){
      fail = true;
    }
    if(map[head[0] - 1][head[1]] == -1){
      snakeLen ++;
      while(map[apple[0]][apple[1]] > 0){
        apple[0] = rand() % width;
        apple[1] = rand() % height;
      }
    }
    if(head[0] == 0){
      fail = true;
    }
    if(!fail){
      map[head[0] - 1][head[1]] = 1;
    }
    break;

    case 2: //down
    if(map[head[0]][head[1] + 1] > 0){
      fail = true;
    }
    if(map[head[0]][head[1] + 1] == -1){
      snakeLen ++;
      while(map[apple[0]][apple[1]] > 0){
        apple[0] = rand() % width;
        apple[1] = rand() % height;
      }
    }
    if(head[1] == height){
      fail = true;
    }
    if(!fail){
      map[head[0]][head[1] + 1] = 1;
    }
    break;

    case 3: //right
    if(map[head[0] + 1][head[1]] > 0){
      fail = true;
    }
    if(map[head[0] + 1][head[1]] == -1){
      snakeLen ++;
      while(map[apple[0]][apple[1]] > 0){
        apple[0] = rand() % width;
        apple[1] = rand() % height;
      }
    }
    if(head[0] == width){
      fail = true;
    }
    if(!fail){
      map[head[0] + 1][head[1]] = 1;
    }
    break;
  }
  */
  return;
}

bool tryHamilton(int x, int y, int step){
  if(step == (width * height)){
    if(hamilton[x][y] == 0){
      return true;
    }else{
      return false;
    }
  }
  if(hamilton[x][y] != -1){
    return false;
  }
  hamilton[x][y] = step;
  if(x < width - 1){
    if(tryHamilton(x + 1, y, step + 1)){
      return true;
    }
  }
  if(y < height - 1){
    if(tryHamilton(x, y + 1, step + 1)){
      return true;
    }
  }
  if(x > 0){
    if(tryHamilton(x - 1, y, step + 1)){
      return true;
    }
  }
  if(y > 0){
    if(tryHamilton(x, y - 1, step + 1)){
      return true;
    }
  }
  hamilton[x][y] = -1;
  return false;
}

bool createHailton(){
  if(tryHamilton(0, 0, 0)){
    return true;
  }
  return false;
}

int main(int argc, char **argv){
  srand(time(NULL));

  char* p;
  width = strtol(argv[1], &p, 10);
  if (*p != '\0'){
    printf("invalid argument\n");
    return 1;
  }
  height = strtol(argv[2], &p, 10);
  if (*p != '\0'){
    printf("invalid argument\n");
    return 1;
  }

  apple[0] = rand() % width;
  apple[1] = rand() % height;
  map = (int **)malloc(width * sizeof(int *));
  for(int i = 0; i < width; i++){
    map[i] = (int *)malloc(height * sizeof(int));
  }
  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      map[i][j] = 0;
    }
  }
  hamilton = (int **)malloc(width * sizeof(int *));
  for(int i = 0; i < width; i++){
    hamilton[i] = (int *)malloc(height * sizeof(int));
  }
  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      hamilton[i][j] = -1;
    }
  }
  map[apple[0]][apple[1]] = -1;
  map[int(width / 2)][int(height / 2)] = 1;

  if(!createHailton()){
    printf("Failed to create Hamilton Cycle. :(\n");
    return 1;
  }else{
    for(int i = 0; i < height; i++){
      for(int j = 0; j < width; j++){
        printf("%i\t", hamilton[j][i]);
      }
      printf("\n");
    }
  }

  sf::RenderWindow window(sf::VideoMode(width * 20, height * 20), "Snake", sf::Style::Titlebar | sf::Style::Close);

  clock_t t;
  t = clock();

  while (window.isOpen()) {
    clock_t elapsed = clock() - t;
    if(elapsed > 10 && !fail){
      updateMap();
      t = clock();
    }

    sf::Event event;
    while (window.pollEvent(event)) {
        switch(event.type){
          case sf::Event::Closed:
          window.close();
          break;

          case sf::Event::KeyPressed:
          switch(event.key.code){
            case sf::Keyboard::Up:
            if(direction != 2)
              direction = 0;
            break;
            case sf::Keyboard::Left:
            if(direction != 3)
              direction = 1;
            break;
            case sf::Keyboard::Down:
            if(direction != 0)
              direction = 2;
            break;
            case sf::Keyboard::Right:
            if(direction != 1)
              direction = 3;
            break;
          }
          break;
        }
    }

    window.clear();
    for(int i = 0; i < width; i++){
      for(int j = 0; j < height; j++){
        sf::RectangleShape rect(sf::Vector2f(19,19));
        rect.setPosition(i*20, j*20);
        if(map[i][j] == 0){
          rect.setFillColor(sf::Color(0, 0, 0));
        }else if(map[i][j] == -1){
          rect.setFillColor(sf::Color(250, 0, 0));
        }else{
          rect.setFillColor(sf::Color(0, 250, 0));
        }
        window.draw(rect);
      }
    }
    window.display();
  }

  return 0;
}
