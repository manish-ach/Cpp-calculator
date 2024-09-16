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
        sf::RectangleShape buttons[18];
        sf::Text number[18];

        // Button dimensions and spacing
        const int buttonWidth = 53;
        const int buttonHeight = 43;
        const int xspacing = 26;
        const int yspacing = 35;

        for (int i = 0; i < 18; i++){
            int a = 55 + (i % 4) * (buttonWidth + xspacing);
            int b = (35 + 107 + display.getPosition().y) + (i / 4) * (buttonHeight + yspacing);
            buttons[i].setSize(sf::Vector2f(buttonWidth, buttonHeight));
            buttons[i].setPosition(sf::Vector2f(a, b));
            buttons[i].setFillColor(sf::Color::Green);
            buttons[i].setOutlineColor(sf::Color::Black);
            buttons[i].setOutlineThickness(2);

            number[i].setFont(font);
            number[i].setCharacterSize(16);
            number[i].setFillColor(sf::Color::Black);
            number[i].setString(std::to_string(i));
            number[i].setPosition(buttons[i].getPosition() + sf::Vector2f(20, 12));

            //last 2 special buttons
            if(i == 16){
                buttons[i].setSize(sf::Vector2f(211, 43));
            }
            else if (i == 17) {
                int a = 55 + 3 * (buttonWidth + xspacing);
                buttons[i].setPosition(sf::Vector2f(a, b));
                number[i].setPosition(buttons[i].getPosition() + sf::Vector2f(20, 12));
            }
        }
        //display
        for(int i = 0; i < 18; i++){
            window.draw(buttons[i]);
            window.draw(number[i]);
        }
        window.display();
    }

    return 0;
}
