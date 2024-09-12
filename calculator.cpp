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
        window.clear(sf::Color(30, 30, 30));

        //font
        sf::Font font;
        if(!font.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")){
            std::cerr<<"error loading font"<<std::endl;
            return 1;
        }

        //calculator display screen
        sf::RectangleShape display(sf::Vector2f(334,107));
        display.setPosition(sf::Vector2f(33, 51));
        display.setFillColor(sf::Color::White);
        display.setOutlineColor(sf::Color::Black);
        display.setOutlineThickness(2);
        window.draw(display);

        // Numbers and buttons
        sf::RectangleShape buttons[16];
        sf::Text number[16];
        for (int i = 0; i < 16; i++) {
            float verti = (float)i/4;
            float xaxis = 55 + (i % 4) * (26 + 53);
            float yaxis = display.getPosition().y + 142 + verti * 35;
            buttons[i].setSize(sf::Vector2f(53, 43));
            buttons[i].setPosition(sf::Vector2f(xaxis, yaxis));
            buttons[i].setFillColor(sf::Color::White);
            buttons[i].setOutlineColor(sf::Color::Black);
            buttons[i].setOutlineThickness(2);

            number[i].setFont(font);
            number[i].setCharacterSize(16);
            number[i].setFillColor(sf::Color::Black);
            number[i].setString(std::to_string(i));
            number[i].setPosition(buttons[i].getPosition() + sf::Vector2f(30, 10));
        }
        //display
        for(int i = 0; i < 16; i++){
            window.draw(buttons[i]);
            window.draw(number[i]);
        }
        window.display();
    }

    return 0;
}
