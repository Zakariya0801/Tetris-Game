/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You don't need to change anything in the driver code/main function except the part(s) where instructed.
 * You are expected to define your functionalities in the "functionality.h" header and call them here in the instructed part(s).
 * The game is started with a small box, you need to create other possible in "pieces.h" file in form of array.
    E.g., Syntax for 2 pieces, each having four coordinates -> int Pieces[2][4];
 * Load the images into the textures objects from img directory.
 * Don't make any changes to the "utils.h" header file except for changing the coordinate of screen or global variables of the game.
 * SUGGESTION: If you want to make changes in "utils.h", do it once you complete rest of the functionalities.
 * TIP: You can study SFML for drawing scenes, sprites and window.
 * */
 /*
	ZAKARIYA ABBAS
	22I-0801
	CS-E 
 */
#include <iostream>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"

using namespace sf;
int main(){
    srand(time(0));
    std::cout << "Enter Your Name: ";
    std::string name;
    std::cin>>name;
    RenderWindow window(VideoMode(400, 480), title);
    //Textures for sprite
    Texture obj1, obj2, obj3, obj4, obj6, one, two, three, four, five, six, seven, eight, nine, zero, menus;
    //Fonts and Text 
    Font font;
    font.loadFromFile("Fonts/arial.ttf");
    Text text_score, Levels, level_num, my_menu;
    text_score.setFont(font), Levels.setFont(font), level_num.setFont(font), my_menu.setFont(font);
    //Objects for sprite
    obj1.loadFromFile("img/tiles.png");
    obj2.loadFromFile("img/background.png");
    obj3.loadFromFile("img/frame.png");
    obj4.loadFromFile("img/shadow_1.png");
    obj6.loadFromFile("img/game_over.png");
    menus.loadFromFile("img/menu.png");
    one.loadFromFile("img/one.png");
    two.loadFromFile("img/two.png");
    three.loadFromFile("img/three.png");
    four.loadFromFile("img/four.png");
    five.loadFromFile("img/five.png");
    six.loadFromFile("img/six.png");
    seven.loadFromFile("img/seven.png");
    eight.loadFromFile("img/eight.png");
    nine.loadFromFile("img/nine.png");
    zero.loadFromFile("img/zero.png");
    //SPRITES
    Sprite sprite(obj1),my_sprite0(obj1),my_sprite1(obj1), my_sprite2(obj1), background(obj2), frame(obj3), shadow(obj4), game_over(obj6);
    Sprite zeros(zero), ones(one), twos(two), threes(three), fours(four), fives(five), sixs(six), sevens(seven), eights(eight), nines(nine), menu(menus);
    int delta_x=0, colorNum=1, level=1, bomb_count=1, lines = 0, count = 0;
    float timer=0, delay=0.5, my_timer = 1;
    bool rotate=0, right=0, left=0, flag=0, bombs=0, jump=0, pause = 0, over=0;
    int score[3] = {0,0,0}, next_block[3][4][2], my_color[3];
    
    //next block suggestion
    for(int x=0 ; x<3 ; x++)
        {
           int n=rand()%3;
           my_color[x] = 1+rand()%7;
           for (int i=0; i<4 ; i++)
           {
             
             next_block[x][i][0] = BLOCKS[n][i] % 4;
	     next_block[x][i][1] = BLOCKS[n][i] / 4;
                }
        }
    Clock clock;
    while (window.isOpen()){
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;
        
        //---Event Listening Part---//
        Event e;
        while (window.pollEvent(e)){                    //Event is occurring - until the game is in running state
            if (e.type == Event::Closed)                   //If cross/close is clicked/pressed
                window.close();                            //Opened window disposes
            if (e.type == Event::KeyPressed) {             //If any other key (not cross) is pressed
                if (e.key.code == Keyboard::Up)            //Check if the other key pressed is UP key
                    rotate = true;                         //Rotation gets on
                else if (e.key.code == Keyboard::Left)     //Check if the other key pressed is LEFT key
                     delta_x = -1;        		     //Change in X-Axis - Negative
                else if (e.key.code == Keyboard::Right)    //Check if the other key pressed is RIGHT key
                     delta_x = 1;                          //Change in X-Axis - Positive
                else if (e.key.code == Keyboard::Space)    //Check if other key presses is space key
                     jump = true;                          //changes position to end
                else if (e.key.code == Keyboard::P || e.key.code == Keyboard::H) //checks if key pressed is P or H
                     pause = true;                          //pauses the game
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))   //Just another way to detect key presses without event listener
            delay=0.05;                                    //If DOWN key is pressed, delay in falling piece decreases from 0 to 0.05

        ///////////////////////////////////////////////
        ///*** START CALLING YOUR FUNCTIONS HERE ***///
        if((int)my_timer%150 == 0)
        {        shrinker();
                 my_timer+=1;
        }
        int shadow_x[4] = {0}, shadow_y [4] = {0};
        if(pause)
        {
            while(window.pollEvent(e)){
                if (e.type == Event::KeyPressed) {
                    if (e.key.code == Keyboard::P || e.key.code == Keyboard::Escape)
                     pause = false;
                }
            }  
        }
        
        //removing shadow before any function to avoid overlap
        else{
        my_timer+=0.001;
        shadow_remove();
        if (lines>=6){                  //Increasing level after every 6 lines cancelling
            level++;
            lines = 0;
        }
        line_check(flag, lines, score);
        fallingPiece(timer, delay, colorNum, my_color, flag, bomb_count, level, next_block);               //Example: fallingPiece() function is called here
        //Delay and bomb falling according
        switch (level)
        {
            case 1:
                    delay = 0.5;
                    if (bomb_count % 10 ==0)
                    {
                        bombs = bomb(bomb_count);
                    }
                    break;
        
            case 2:
                    delay = 0.3;
                    if (bomb_count % 15 ==0)
                    {
                       bombs = bomb(bomb_count);
                    }
                    break;
            case 3:
                    delay = 0.2;
                    if (bomb_count % 20 ==0)
                    {
                       bombs = bomb(bomb_count);
                    }
                    break;
        }
        if(bombs)
        {
            bomb_check(bombs, colorNum, bomb_count, flag);
        }
        if(delta_x != 0 && !bombs){
        	delta_x = shift(delta_x);
        }
        if(rotate && !bombs){
        	rotate = rotator();
        }
        for(int i=0 ; i<4 ; i++)
        	if(gameGrid[point_1[i][1]+1][point_1[i][0]] || point_1[i][1]+1 == M)
        	{	
        		fix_piece(colorNum);		
        	}
        
        shadow_draw(shadow_x, shadow_y);
        for(int i=0 ; i<4 ; i++)
        {
                shadow_x[i] = point_1[i][0];
        }
        if (jump)
        {
            for(int i=0 ; i<4 ; i++)
                point_1[i][1] = shadow_y[i];
            jump = false;
        }
        score_setting(score);
        for(int i=0 ; i<N ;i++)
        {
            if(gameGrid[0][i])
                over = true;
        }
        }
        ///*** YOUR CALLING STATEMENTS END HERE ***///
        //////////////////////////////////////////////
        window.clear(Color::Black);
        window.draw(background);
        //SELF DEFINED GAME OVER SPRITE
        if(over)
        {
            game_over.setTexture(obj6);
            game_over.setPosition(Vector2f(40,150));
            window.draw(game_over);
            if(count == 0)
            {
                std::fstream file("high_scores.txt");
                file<<name<<" "<<score[2] << score[1] << score[0] <<std::endl;
                file.close();
		count++;
	    }
        }
        else{
        //SELF DEFINED SHADOW SPRITE
        for(int i=0 ; i<4 ;i++){
          	shadow.setTexture(obj4);
          	shadow.setPosition(Vector2f((shadow_x[i]+0.1)*18,(shadow_y[i])*18));
        	shadow.move(28,31);
          	window.draw(shadow);
          }
        for (int i=0; i<M; i++){
            for (int j=0; j<N; j++){
                if (gameGrid[i][j]==0 || gameGrid[i][j]==9)
                    continue;
                sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
                sprite.setPosition(j*18,i*18);
                sprite.move(28,31); //offset
                window.draw(sprite);
            }
        }	
        for (int i=0; i<4; i++){
            sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
            sprite.setPosition(point_1[i][0]*18,point_1[i][1]*18);
            sprite.move(28,31);
            window.draw(sprite);
          }
        //SPRITE FOR SHOWING NEXT BLOCKS ON SCREEN
        for (int i=0; i<4; i++)
        {
            my_sprite0.setTextureRect(IntRect(my_color[0]*18,0,18,18));
            my_sprite0.setPosition((next_block[0][i][0]*18)+300,(next_block[0][i][1]*18)+100);
            my_sprite0.move(28,31);
            window.draw(my_sprite0);
        }
        switch (level)
        {
        case 1:
                for (int i=0; i<4; i++)
                {
                        my_sprite1.setTextureRect(IntRect(my_color[1]*18,0,18,18));
                        my_sprite1.setPosition((next_block[1][i][0]*18)+300,(next_block[1][i][1]*18)+200);
                        my_sprite1.move(28,31);
                        window.draw(my_sprite1);
                }
                for (int i=0; i<4; i++)
                {
                        my_sprite2.setTextureRect(IntRect(my_color[2]*18,0,18,18));
                        my_sprite2.setPosition((next_block[2][i][0]*18)+300,(next_block[2][i][1]*18)+300);
                        my_sprite2.move(28,31);
                        window.draw(my_sprite2);
                }
                break;
        case 2:
                for (int i=0; i<4; i++)
                {
                        my_sprite1.setTextureRect(IntRect(my_color[1]*18,0,18,18));
                        my_sprite1.setPosition((next_block[1][i][0]*18)+300,(next_block[1][i][1]*18)+200);
                        my_sprite1.move(28,31);
                        window.draw(my_sprite1);
                }
                break;
        }
        }
        text_score.setString("Score");
        text_score.setCharacterSize(30);
        text_score.setFillColor(Color::Red);
        text_score.setStyle(Text::Bold);
        text_score.setPosition(Vector2f(230, 100));
        window.draw(text_score);
        switch (level)
        {
        case 1:
                level_num.setString("1");
                break;
        case 2: 
                level_num.setString("2");
                break;
        case 3:
                level_num.setString("3");
                break;
        }
        Levels.setString("Level");
        Levels.setCharacterSize(30), level_num.setCharacterSize(30);
        Levels.setFillColor(Color::Red), level_num.setFillColor(Color::Red);
        Levels.setStyle(Text::Bold), level_num.setStyle(Text::Bold);
        Levels.setPosition(Vector2f(230, 300)), level_num.setPosition(Vector2f(260, 350));
        window.draw(Levels), window.draw(level_num);
        //SPRITES FOR SHOWING SCORE ON SCREEN
        for (int i = 0; i < 3; i++)
        {
            switch (score[i])
            {
            case 0:
                    switch (i)
                    {
                    case 0:
                            zeros.setTexture(zero);
                            zeros.setPosition(Vector2f(290, 150));
                            window.draw(zeros);
                            break;
                    case 1:
                            zeros.setTexture(zero);
                            zeros.setPosition(Vector2f(260, 150));
                            window.draw(zeros);
                            break;
                    case 2:
                            zeros.setTexture(zero);
                            zeros.setPosition(Vector2f(230, 150));
                            window.draw(zeros);
                            break;
                    }
                    break;
            case 1:
                    switch (i)
                    {
                    case 0:
                            ones.setTexture(one);
                            ones.setPosition(Vector2f(290, 150));
                            window.draw(ones);
                            break;
                    case 1:
                            ones.setTexture(one);
                            ones.setPosition(Vector2f(260, 150));
                            window.draw(ones);
                            break;
                    case 2:
                            ones.setTexture(one);
                            ones.setPosition(Vector2f(230, 150));
                            window.draw(ones);
                            break;
                    }
                    break;
            case 2:
                    switch (i)
                    {
                    case 0:
                            twos.setTexture(two);
                            twos.setPosition(Vector2f(290, 150));
                            window.draw(twos);
                            break;
                    case 1:
                            twos.setTexture(two);
                            twos.setPosition(Vector2f(260, 150));
                            window.draw(twos);
                            break;
                    case 2:
                            twos.setTexture(two);
                            twos.setPosition(Vector2f(230, 150));
                            window.draw(twos);
                            break;
                    }
                    break;
            case 3:
                    switch (i)
                    {
                    case 0:
                            threes.setTexture(three);
                            threes.setPosition(Vector2f(290, 150));
                            window.draw(threes);
                            break;
                    case 1:
                            threes.setTexture(three);
                            threes.setPosition(Vector2f(260, 150));
                            window.draw(threes);
                            break;
                    case 2:
                            threes.setTexture(three);
                            threes.setPosition(Vector2f(230, 150));
                            window.draw(threes);
                            break;
                    }
                    break;
            case 4:
                    switch (i)
                    {
                    case 0:
                            fours.setTexture(four);
                            fours.setPosition(Vector2f(290, 150));
                            window.draw(fours);
                            break;
                    case 1:
                            fours.setTexture(four);
                            fours.setPosition(Vector2f(260, 150));
                            window.draw(fours);
                            break;
                    case 2:
                            fours.setTexture(four);
                            fours.setPosition(Vector2f(230, 150));
                            window.draw(fours);
                            break;
                    }
                    break;
            case 5:
                    switch (i)
                    {
                    case 0:
                            fives.setTexture(five);
                            fives.setPosition(Vector2f(290, 150));
                            window.draw(fives);
                            break;
                    case 1:
                            fives.setTexture(five);
                            fives.setPosition(Vector2f(260, 150));
                            window.draw(fives);
                            break;
                    case 2:
                            fives.setTexture(five);
                            fives.setPosition(Vector2f(230, 150));
                            window.draw(fives);
                            break;
                    }
                    break;
            case 6:
                    switch (i)
                    {
                    case 0:
                            sixs.setTexture(six);
                            sixs.setPosition(Vector2f(290, 150));
                            window.draw(sixs);
                            break;
                    case 1:
                            sixs.setTexture(six);
                            sixs.setPosition(Vector2f(260, 150));
                            window.draw(sixs);
                            break;
                    case 2:
                            sixs.setTexture(six);
                            sixs.setPosition(Vector2f(230, 150));
                            window.draw(sixs);
                            break;
                    }
                    break;
            case 7:
                    switch (i)
                    {
                    case 0:
                            sevens.setTexture(seven);
                            sevens.setPosition(Vector2f(290, 150));
                            window.draw(sevens);
                            break;
                    case 1:
                            sevens.setTexture(seven);
                            sevens.setPosition(Vector2f(260, 150));
                            window.draw(sevens);
                            break;
                    case 2:
                            sevens.setTexture(seven);
                            sevens.setPosition(Vector2f(230, 150));
                            window.draw(sevens);
                            break;
                    }
                    break;
            case 8:
                    switch (i)
                    {
                    case 0:
                            eights.setTexture(eight);
                            eights.setPosition(Vector2f(290, 150));
                            window.draw(eights);
                            break;
                    case 1:
                            eights.setTexture(eight);
                            eights.setPosition(Vector2f(260, 150));
                            window.draw(eights);
                            break;
                    case 2:
                            eights.setTexture(eight);
                            eights.setPosition(Vector2f(230, 150));
                            window.draw(eights);
                            break;
                    }
                    break;
            case 9:
                    switch (i)
                    {
                    case 0:
                            nines.setTexture(nine);
                            nines.setPosition(Vector2f(290, 150));
                            window.draw(nines);
                            break;
                    case 1:
                            nines.setTexture(nine);
                            nines.setPosition(Vector2f(260, 150));
                            window.draw(nines);
                            break;
                    case 2:
                            nines.setTexture(nine);
                            nines.setPosition(Vector2f(230, 150));
                            window.draw(nines);
                            break;
                    }
                    break;
        }
        }     
            
        //---The Final on Which Everything is Drawn Over is Loaded---//
        window.draw(frame);
        //SELF-DEFINED MENU SPRITE
        if(pause)
        {
            menu.setTexture(menus);
            menu.setPosition(Vector2f(20,30));
            window.draw(menu);
            my_menu.setString("   Resume   ");
            my_menu.setCharacterSize(20);
            my_menu.setFillColor(Color::Black);
            my_menu.setStyle(Text::Bold);
            my_menu.setPosition(Vector2f(50, 70));
            window.draw(my_menu);
            my_menu.setString("   HighScore   ");
            my_menu.setPosition(Vector2f(40, 110));
            window.draw(my_menu);
        }    
        //---The Window that now Contains the Frame is Displayed---//
        window.display();
    }
    return 0;
}
