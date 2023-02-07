#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

int main()
{
    sf::RenderWindow window(sf::VideoMode(120, 120), "TicTacToe");
    window.setFramerateLimit(60);
    
    sf::Texture texture1, texture2, board_texture;

    texture1.loadFromFile("../graphic/toe1.png");
    texture2.loadFromFile("../graphic/toe2.png");
    board_texture.loadFromFile("../graphic/board.png");

    std::shared_ptr<sf::Sprite> board = std::make_shared<sf::Sprite>();
    board->setTexture(board_texture);
    board->setTextureRect(sf::IntRect(0, 0, 120, 120));
    board->setPosition(0, 0);

    std::vector<std::shared_ptr<sf::Sprite>> pawns;
    int turn=0;
    int blocked[]={0,0,0,0,0,0,0,0,0};
    int positions[][2] = {{0,80},{40,80},{80,80},{0,40},{40,40},{80,40},{0,0},{40,0},{80,0}};
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }

            if (event.type == sf::Event::KeyPressed)
            { 
                if(event.key.code == sf::Keyboard::Backspace){
                    pawns.clear();
                    for(int i =0; i<9;i++) blocked[i]=0;
                    turn=0;
                    break;
                }

                int key = event.key.code;
                int position;
                
                if(key>=27 && key<=35){
                    position = key-27;
                }
                if(key>=76 && key<=84){
                    position = key-76;
                }
                
                if(position>=0 && position<9){
                        
                    std::shared_ptr<sf::Sprite> pawn = std::make_shared<sf::Sprite>();
                    pawn->setTextureRect(sf::IntRect(0, 0, 38, 38));
                    
                    if(blocked[position]==0){
                        if(turn%2==0){
                            pawn->setTexture(texture1);
                        }
                        else{
                            pawn->setTexture(texture2);
                        }
                        pawn->setPosition(positions[position][0]+1, positions[position][1]+1);
                        blocked[position]=1;
                        pawns.push_back(pawn);
                        turn++;
                    }
                }
            }
        }

        window.clear();
        
        window.draw(*board);
        
        for(auto& pawn:pawns){
            window.draw(*pawn);
        }
        
        window.display();
    }

    return 0;
}