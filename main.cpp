#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "map.hpp"
#include "view.h"


class Player { // класс Игрока
public:
    bool life = true;
    bool onGround = true;
    bool ALIVE = true;
    
	float dx, dy, speed = 0; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
    float x = 810;
    float y = 750;
    float w = 135;
    float h = 200;

    sf::Sprite up, down;

	int dir = 0; //направление (direction) движения игрока
    std::map<int, std::vector<sf::Sprite> > Sprites;
    sf::Sprite sprite; // спрайт, который сейчас используется

	Player(sf::Sprite up, sf::Sprite down) {  //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
        this->up = up;
        this->down = down;

        sprite.setPosition(x, y);
	}

	
    float getplayercoordinateX(){	//этим методом будем забирать координату Х	
		return x;
	}
	float getplayercoordinateY(){	//этим методом будем забирать координату Y 	
		return y;
	}
 
 
	void update(float time) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
	{
        if (dir == -1) // летит вниз
            dy = 0.1;
        else if (dir == 0) // стоит на месте
            dy = 0.01;
        else if (dir == 1) // летит вверх
            dy = -0.1;
        else if (dir == 2) // быстро летит вверх
            dy = -0.6;
        else
            dy = 0;

        x += 0.08 * time;
		y += dy*time; //аналогично по y
        checkCollisionWithMap(0, dy);
 
		speed = 0;//зануляем скорость, чтобы персонаж остановился.
		sprite.setPosition(x,y); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
    }

    void checkCollisionWithMap(float Dx, float Dy)//ф ция проверки столкновений с картой
	{
		for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты
		for (int j = x / 32; j<(x + w) / 32; j++)
		{
			if (TileMap[i][j] == '1')//если элемент наш тайлик земли? то
			{
				if (Dy>0){ y = i * 32 - h;  dy = 0; onGround = true; }//по Y вниз=>идем в пол(стоим на месте) или падаем. В этот момент надо вытолкнуть персонажа и поставить его на землю, при этом говорим что мы на земле тем самым снова можем прыгать
				if (Dy<0){y = i * 32 + 32;  dy = 0;}//столкновение с верхними краями карты(может и не пригодиться)
				if (Dx>0){x = j * 32 - w; }//с правым краем карты
				if (Dx<0){x = j * 32 + 32;}// с левым краем карты

                ALIVE = false;
			}
		}
	}	
};




int main()
{
    // создание окна

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");

    // создание глобальных часов

    sf::Clock CLOCK;
    
    
    // создание движущегося фона




    sf::Texture FLY_UP_TILESET;
    FLY_UP_TILESET.loadFromFile("./images/shar_up.png");

    sf::Texture FLY_DOWN_TILESET;
    FLY_DOWN_TILESET.loadFromFile("./images/shar_down.png");

    sf::Sprite FLY_UP;
    FLY_UP.setTexture(FLY_UP_TILESET);

    sf::Sprite FLY_DOWN;
    FLY_DOWN.setTexture(FLY_DOWN_TILESET);





    //




    sf::Image map_image;//объект изображения для карты
	map_image.loadFromFile("images/MAP.png");//загружаем файл для карты
	sf::Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	sf::Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом

    Player p(FLY_UP, FLY_DOWN);
            p.dir = 0;
    float currentframe = 0;

    readMap();


    while (window.isOpen() && p.ALIVE)
    {
        std::cout << p.y << std::endl;
        float time = CLOCK.getElapsedTime().asMicroseconds();
        CLOCK.restart();
        time = time / 800;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // if (event.type == sf::Event::KeyPressed)
            // {
            //     if (event.key.code == sf::Keyboard::A) // идем налево
            //     {
            //         // ----- сдвиг обоин (всегда на 1)
            //         if (BACKGROUND_SPRITE_2.getPosition().x == 1920) // левая обоина полностью ушла из кадра
            //         {
            //             BACKGROUND_SPRITE_1.setPosition(-1919, 0);
            //             BACKGROUND_SPRITE_2.setPosition(0, 0);
            //         }
            //         else
            //         {
            //             BACKGROUND_SPRITE_1.move(sf::Vector2f {0.01 * time, 0});
            //             BACKGROUND_SPRITE_2.move(sf::Vector2f {0.01 * time, 0});
            //         }
            //         // -----
            //     }
                    
            //     if (event.key.code == sf::Keyboard::D)
            //     {
            //         // ----- сдвиг обоин (всегда на 1)
            //         if (BACKGROUND_SPRITE_1.getPosition().x == -1920) // левая обоина полностью ушла из кадра
            //         {
            //             BACKGROUND_SPRITE_1.setPosition(0, 0);
            //             BACKGROUND_SPRITE_2.setPosition(1920, 0);
            //         }
            //         else
            //         {
            //             BACKGROUND_SPRITE_1.move(sf::Vector2f {-0.01 * time, 0});
            //             BACKGROUND_SPRITE_2.move(sf::Vector2f {-0.01 * time, 0});
            //         }
            //         // -----
            //     }
            // }
        }

 		// if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		// 	p.dir = 1; 
        //     p.speed = 0.2;
		// 	currentframe += 0.01*time;
		// 	p.sprite = p.Sprites[1][int(currentframe) % p.Sprites[1].size()];
        //     facing = 1;
        //     getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
		// }
 
		// else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		// 	p.dir = 2;
        //     p.speed = 0.2;//направление вправо, см выше
		// 	currentframe += 0.01*time;
		// 	p.sprite = p.Sprites[2][int(currentframe) % p.Sprites[2].size()];
        //     facing = 2;
        //     getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
		// }
 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { 
			p.dir = 1; 

			currentframe += 0.005*time;
			p.sprite = p.up;
            
            getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { 
			p.dir = -1; 

			currentframe += 0.005*time;
			p.sprite = p.down;

            getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
		}
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            p.dir = 2; 

			currentframe += 0.005*time;
			p.sprite = p.down;

            getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
        }
        else
        {
            p.dir = 0;

			currentframe += 0.005*time;
            p.sprite = p.down;

            getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
        }

		p.update(time);
        viewmap(time);//функция скроллинга карты, передаем ей время sfml
        view.setSize(1920, 1080);
		window.setView(view);

        // std::cout << p.sprite.getPosition().x << " " << p.sprite.getPosition().y << std::endl;



        window.clear();
        
        
        // ----- начало отрисовки заднего плана


        // отрисовка первого и второго движущихся кусков обоев
        // window.draw(BACKGROUND_SPRITE_1); 
        // window.draw(BACKGROUND_SPRITE_2);

        // отрисовка недвижущейся луны

        // ----- конец отрисовка заднего плана

        for (int i = 0; i < HEIGHT_MAP; i++)
            for (int j = 0; j < WIDTH_MAP; j++)
            {
                std::cout << i << " " << j << std::endl;
                // std::cout << "lol" << std::endl;
                if (TileMap[i][j] == '0')
                {
                    s_map.setTextureRect(sf::IntRect(32, 0, 32, 32));
                    s_map.setPosition(j * 32, i * 32);

                    window.draw(s_map);
                }
                else if (TileMap[i][j] == '1')
                {
                    s_map.setTextureRect(sf::IntRect(0, 0, 32, 32));
                    s_map.setPosition(j * 32, i * 32);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат
    
                    window.draw(s_map);//рисуем квадратики на экран
                }
                else if (TileMap[i][j] == '2')
                {
                    s_map.setTextureRect(sf::IntRect(32, 0, 32, 32));
                    s_map.setPosition(j * 32, i * 32);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат
    
                    window.draw(s_map);//рисуем квадратики на экран
                }
                // if (TileMap[i][j] == 32)   s_map.setTextureRect(sf::IntRect(0, 0, 32, 32));//если встретили символ s, то рисуем 2й квадратик
                // if ((TileMap[i][j] == 11)) s_map.setTextureRect(sf::IntRect(32, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик
    
    
                
            }

        window.draw(p.sprite);

        window.display();
    }

    return 0;
}
