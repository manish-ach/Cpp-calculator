#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

int main(){
    sf::RenderWindow window(sf::VideoMode(400, 600), "Calculator", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(60);

    //main body
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //background color
        window.clear(sf::Color::White);

        //font
        sf::Font font;
        if(!font.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")){
            std::cerr<<"error loading font"<<std::endl;
            return 1;
        }

        //header text and its position
        sf::Text calc("Calculator", font);
        calc.setCharacterSize(20);
        calc.setFillColor(sf::Color::Red);
        calc.setPosition(sf::Vector2f(150, 1));
        window.draw(calc);

        //calculator display screen
        sf::RectangleShape display(sf::Vector2f(300,50));
        display.setPosition(sf::Vector2f(50, calc.getGlobalBounds().height + 10));
        display.setFillColor(sf::Color::White);
        display.setOutlineColor(sf::Color::Black);
        display.setOutlineThickness(2);
        window.draw(display);

        //numbers
        sf::Text number[10];
        for(int i = 0; i < 10; i++){
            number[i].setFont(font);
            number[i].setCharacterSize(16);
            number[i].setFillColor(sf::Color::Black);
            number[i].setString(std::to_string(i));
        }

        int xaxis1, xaxis2, xaxis3;
        xaxis1 = xaxis2 = xaxis3 = 100;
        for(int i = 0; i < 10; i++){
            //1st row
            if(i > 6 && i <= 9){
                number[i].setPosition(sf::Vector2f(xaxis1, display.getPosition().y + 130));
                xaxis1 = xaxis1 + 100;
            }
            //2nd row
            if(i > 3 && i < 7){
                number[i].setPosition(sf::Vector2f(xaxis2, display.getPosition().y + 190));
                xaxis2 = xaxis2 + 100;
            }
            //3rd row
            if(i > 0 && i < 4){
                number[i].setPosition(sf::Vector2f(xaxis3, display.getPosition().y + 250));
                xaxis3 = xaxis3 + 100;
            }
            //4th row
            if(i == 0){
                number[i].setPosition(sf::Vector2f(200, display.getPosition().y + 310));
            }
        }
        //display
        for(int i = 0; i < 10; i++){
            window.draw(number[i]);
        }
        window.display();
    }

    return 0;
}
