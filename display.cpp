#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

int main() {
    
    sf::RenderWindow window(sf::VideoMode(800, 600), "Running Game HUD"); /////
    
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font!" << std::"\n";
        return -1;
    }
    
    int score = 0;
    int level = 1;
    int maxlevel = 5;
    int coinvalue = 5;
    
    sf::Text scoreText, levelText, statusText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(25);           /////
    scoreText.setFillColor(sf::Color::White); /////
    scoreText.setPosition(10, 10);            /////
    
    levelText.setFont(font);
    levelText.setCharacterSize(25);           /////
    levelText.setFillColor(sf::Color::White); /////
    levelText.setPosition(10, 40);            /////
    
    statusText.setFont(font);
    statusText.setCharacterSize(25);          /////
    statusText.setFillColor(sf::Color::Red);  /////
    statusText.setPosition(400, 300);         /////
    statusText.setString("");
    
    bool gameOver = false;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        if (!gameOver) {

            score += coinvalue; 
            score += 10; 
            
            if (score % 100 == 0 && level < maxlevel) {
                level++;
                coinvalue = level * 5; 
                
                switch (level) {
                    case 2: statusText.setString("Great");          break;
                    case 3: statusText.setString("Excellent!");     break;
                    case 4: statusText.setString("Excellent!");     break;
                    case 5: statusText.setString("Perfect!");       break;
                    case 6: statusText.setString("You’ve got it!"); break;
                }
                sf::FloatRect textRect = statusText.getLocalBounds();
                statusText.setOrigin(textRect.width / 2 , textRect.height / 2);
                statusText.setPosition(400, 300);
            }
        }
        
        ///////////////////////////////////////////////////////////////////
        std::ostringstream scoreStream;
        scoreStream << "Score: " << score;
        scoreText.setString(scoreStream.str());
        
        std::ostringstream levelStream;
        levelStream << "Level: " << level;
        levelText.setString(levelStream.str());
        
        ///////////////////////////////////////////////////////////////////
        window.clear();
        window.draw(scoreText);
        window.draw(levelText);
        if (statusText.getString() != "") {
            window.draw(statusText);
        }
        window.display();
    }
    
    return 0;
}
