#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>

int main(){
    sf::RenderWindow window(sf::VideoMode(400, 600), "Calculator", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(60);

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

    // text for display screen
    sf::Text displayText;
    displayText.setFont(font);
    displayText.setCharacterSize(30);
    displayText.setFillColor(sf::Color::Black);
    displayText.setPosition(40, 70);

    std::string currentInput = "";
    std::string operand1 = "";
    std::string operand2 = "";
    char operation = '\0';

    // Numbers and buttons
    sf::RectangleShape buttons[18];
    sf::Text number[18];

    // Button dimensions and spacing
    const int buttonWidth = 53;
    const int buttonHeight = 43;
    const int xspacing = 26;
    const int yspacing = 35;
    int n = 9;
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
        number[i].setPosition(buttons[i].getPosition() + sf::Vector2f(20, 12));

        if(i != 3 && i != 7 && i != 11 && i != 13 && i != 14 && i != 15 && i != 16 && i != 17){
            number[i].setString(std::to_string(n));
            n--;
        }
        if(i == 3) number[i].setString("/");
        if(i == 7) number[i].setString("x");
        if(i == 11) number[i].setString("-");
        if(i == 13){
            number[i].setString(".");
            number[i].setCharacterSize(30);
            number[i].setPosition(buttons[i].getPosition() + sf::Vector2f(20, 0));
        }
        if(i == 14) number[i].setString("C");
        if(i == 15) number[i].setString("+");
        if(i == 16){
            number[i].setString("Calculator");
            buttons[i].setSize(sf::Vector2f(211, 43));
        }
        if(i == 17){
            number[i].setString("=");
            int a = 55 + 3 * (buttonWidth + xspacing);
            buttons[i].setPosition(sf::Vector2f(a, b));
            number[i].setPosition(buttons[i].getPosition() + sf::Vector2f(20, 12));
        }
    }

    //main body
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            //checking mouse click
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                //getting mouse position
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                //checking button clicked
                for(int i = 0; i < 18; i++){
                    if(buttons[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))){
                        std::string clickedString = number[i].getString().toAnsiString();
                        //if clear screen button
                        if(clickedString == "C"){
                            currentInput = "";
                            operand1 = "";
                            operand2 = "";
                            operation = '\0';
                        }
                        else if(clickedString == "+" || clickedString == "-" || clickedString == "x" || clickedString == "/"){
                            if (!operand1.empty()){
                                operation = clickedString[0];  // Store the operator
                                currentInput = operand1 + " " + operation + " ";  // Update display
                            }
                        }
                        else if(clickedString == "="){
                            if(!operand1.empty() && !operand2.empty() && operation != '\0'){
                                float result = 0;
                                float op1 = std::stof(operand1);
                                float op2 = std::stof(operand2);

                                switch(operation){
                                    case '+': result = op1 + op2; break;
                                    case '-': result = op1 - op2; break;
                                    case 'x': result = op1 * op2; break;
                                    case '/':
                                        if(op2 != 0)
                                            result = op1 / op2;
                                        else
                                            currentInput = "Error (Div by 0)";
                                        break;
                                }
                                if(currentInput != "Error (Div by 0)"){
                                    currentInput = std::to_string(result);  // Update display with result
                                }
                                operand1 = currentInput;  // Store result in operand1
                                operand2 = "";
                                operation = '\0';  // Reset operator
                            }
                        }
                        else if(clickedString != "Calculator"){
                            if(operation == '\0'){
                                operand1 += clickedString;  // Append to operand1
                                currentInput = operand1;
                            }
                            else{
                                operand2 += clickedString;  // Append to operand2
                                currentInput = operand1 + " " + operation + " " + operand2;
                            }
                        }
                        // Update the display text
                        displayText.setString(currentInput);
                    }
                }
            }
        }
        //background color
        window.clear(sf::Color(30, 30, 30));

        //display
        window.draw(display);
        for(int i = 0; i < 18; i++){
            window.draw(buttons[i]);
            window.draw(number[i]);
        }
        window.draw(displayText);
        window.display();
    }

    return 0;
}
