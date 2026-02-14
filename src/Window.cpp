#include "Window.hpp"
#include <iostream>
#include "../Button.hpp"

Window::Window(const unsigned int& _width, const unsigned int& _height, std::string const& _title)
    : width(_width),
    height(_height),
    title(_title) {
    window.create(sf::VideoMode::getDesktopMode(), title, sf::Style::Resize | sf::Style::Close);
    window.clear(sf::Color::Black);

    window.setActive(false);

    std::thread thread(&Window::render_thread, this);

    sf::Event event;
    while (isWindowOpen() && !close_window.load()) {
        if (window.waitEvent(event)) {
            event_queue.push(event);
        }
    }
    if (thread.joinable())
        thread.join();
    window.setActive(true);
    window.close();
}

bool Window::isWindowOpen() {
    std::lock_guard<std::mutex> fullscreen_lock(window_mutex);
    return window.isOpen();
}

void Window::render_thread() {
    auto lastUpdateTime = std::chrono::steady_clock::now();
    int cookieCount = 0;
    int grammaCount = 0;
    int gardenCount = 0;
    int mineCount = 0;
    int factoryCount = 0;
	int godCount = 0;
    int cookiesPerSecond = 0;

    float grammaPrice = 10;
    float gardenPrice = 100;
    float minePrice = 1000;
    float factoryPrice = 25000;
	float godPrice = 300000;

    // Einheitliche Größe für Bilder
    const float imageWidth = 80.0f;  // Zielbreite in Pixeln
    const float imageHeight = 80.0f; // Zielhöhe in Pixeln


    sf::Texture cookieTexture;
    if (!cookieTexture.loadFromFile("Img/cookie.png")) {
        std::cout << "Error loading image\n";
    }

    sf::Texture grammaTexture;
    if (!grammaTexture.loadFromFile("Img/gramma.jpg")) {
        std::cout << "Error loading image\n";
    }

    sf::Texture farmTexture;
    if (!farmTexture.loadFromFile("Img/farm.png")) {
        std::cout << "Error loading image\n";
    }

    sf::Texture mineTexture;
    if (!mineTexture.loadFromFile("Img/mine.jpg")) {
        std::cout << "Error loading image\n";
    }

    sf::Texture factoryTexture;
    if (!factoryTexture.loadFromFile("Img/factory.jpg")) {
        std::cout << "Error loading image\n";
    }

    sf::Texture godTexture;
    if (!godTexture.loadFromFile("Img/god.jpg")) {
        std::cout << "Error loading image\n";
    }

    sf::Vector2u grammaSize = grammaTexture.getSize();
    sf::Vector2u farmSize = farmTexture.getSize();
    sf::Vector2u mineSize = mineTexture.getSize();
    sf::Vector2u factorySize = factoryTexture.getSize();
    sf::Vector2u godSize = godTexture.getSize();

    // Skalierung für einheitliche Bildgröße berechnen
    float grammaScaleX = imageWidth / grammaSize.x;
    float grammaScaleY = imageHeight / grammaSize.y;
    float farmScaleX = imageWidth / farmSize.x;
    float farmScaleY = imageHeight / farmSize.y;
    float mineScaleX = imageWidth / mineSize.x;
    float mineScaleY = imageHeight / mineSize.y;
    float factoryScaleX = imageWidth / mineSize.x;
    float factoryScaleY = imageHeight / mineSize.y;
	float godScaleX = imageWidth / godSize.x;
	float godScaleY = imageHeight / godSize.y;

    sf::Sprite cookieSprite(cookieTexture);
    cookieSprite.setPosition(sf::VideoMode::getDesktopMode().width / 2, 50);

    sf::Sprite grammaSprite(grammaTexture);
    grammaSprite.setScale(grammaScaleX, grammaScaleY);
    grammaSprite.setPosition(width / 2 - 200, height / 2 + 100);

    sf::Sprite farmSprite(farmTexture);
    farmSprite.setScale(farmScaleX, farmScaleY);
    farmSprite.setPosition(width / 2 - 200, height / 2 + 220);

    sf::Sprite mineSprite(mineTexture);
    mineSprite.setScale(mineScaleX, mineScaleY);
    mineSprite.setPosition(width / 2 - 200, height / 2 + 340);

    sf::Sprite factorySprite(factoryTexture);
    factorySprite.setScale(factoryScaleX, factoryScaleY);
    factorySprite.setPosition(width / 2 - 200, height / 2 + 460);

    sf::Sprite godSprite(godTexture);
    godSprite.setScale(godScaleX, godScaleY);
    godSprite.setPosition(width / 2 - 200, height / 2 + 580);

    sf::Font font;
    if (!font.loadFromFile("Fonts/Mvdawlatulislam-Z8dJ.ttf")) {
        std::cout << "Fehler beim Laden der Schriftart!\n";
        return;
    }

    sf::Text text("", font, 50);
    text.setFillColor(sf::Color::Black);
    text.setPosition(width / 2 - text.getGlobalBounds().width - 200, height / 2 - text.getGlobalBounds().height / 2 - 200);

    sf::Text leveltext("Level: ", font, 100);
    leveltext.setFillColor(sf::Color::Black);
    leveltext.setPosition(width / 2 - leveltext.getGlobalBounds().width + 1000, height / 2 - leveltext.getGlobalBounds().height / 2 + 500);

    // Einheitliche Buttons
    float buttonWidth = 250;
    float buttonHeight = 80;
    float buttonX = width / 2 - 100;

    Button grammaButton(buttonX, height / 2 + 100, buttonWidth, buttonHeight, "Grandma: 10", font);
    Button gardenButton(buttonX, height / 2 + 220, buttonWidth, buttonHeight, "Garden: 100", font);
    Button mineButton(buttonX, height / 2 + 340, buttonWidth, buttonHeight, "Mine: 1000", font);
    Button factoryButton(buttonX, height / 2 + 460, buttonWidth, buttonHeight, "factory: 25000", font);
	Button godButton(buttonX, height / 2 + 580, buttonWidth, buttonHeight, "God: 300000", font);

    window.setActive();

    // Anzeigen für gekaufte Items
    sf::Text grammaText("", font, 50);
    grammaText.setFillColor(sf::Color::Black);

    sf::Text gardenText("", font, 50);
    gardenText.setFillColor(sf::Color::Black);

    sf::Text mineText("", font, 50);
    mineText.setFillColor(sf::Color::Black);

    sf::Text factoryText("", font, 50);
    factoryText.setFillColor(sf::Color::Black);

    sf::Text godText("", font, 50);
	godText.setFillColor(sf::Color::Black);

    // Funktion zum Aktualisieren des Textes
    auto updateText = [&]() {
		cookiesPerSecond = grammaCount + (gardenCount * 5) + (mineCount * 250) + (factoryCount * 1000) + (godCount * 30000);
        text.setString("Cookies\n" + std::to_string(cookieCount) + "\nCookies per second: " + std::to_string(cookiesPerSecond));

        // Level bestimmen
        std::string level;
        if (cookiesPerSecond < 1000)
            level = "Noob";
        else if (cookiesPerSecond >= 1000 && cookiesPerSecond < 25000)
            level = "Pro";
        else if (cookiesPerSecond >= 25000 && cookiesPerSecond < 100000)
            level = "Hacker";
        else
            level = "God";

        leveltext.setString("Level: " + level);

        // Update der Anzahl-Anzeigen
        grammaText.setString("x " + std::to_string(grammaCount));
        gardenText.setString("x " + std::to_string(gardenCount));
        mineText.setString("x " + std::to_string(mineCount));
        factoryText.setString("x " + std::to_string(factoryCount));
		godText.setString("x " + std::to_string(godCount));

        // Positionierung neben den Buttons (ohne getX()/getY())
        grammaText.setPosition(width / 2 + 200, height / 2 + 100);
        gardenText.setPosition(width / 2 + 200, height / 2 + 220);
        mineText.setPosition(width / 2 + 200, height / 2 + 340);
        factoryText.setPosition(width / 2 + 200, height / 2 + 460);
		godText.setPosition(width / 2 + 200, height / 2 + 580);
        };

    auto buyUpgrade = [&](int& count, float& cost, Button& button, const std::string& name) {
        if (cookieCount >= static_cast<int>(cost)) {
            cookieCount -= static_cast<int>(cost);
            count++;
            cost *= 1.2f;  // Preis um 20 % erhöhen

            // Setze den Button-Text neu, wobei der Name des Upgrades beibehalten wird
            button.setLabel(name + ": " + std::to_string(static_cast<int>(cost)));

            updateText();
        }
        };


    grammaButton.setOnClick([&]() { buyUpgrade(grammaCount, grammaPrice, grammaButton, "Grandma"); });
    gardenButton.setOnClick([&]() { buyUpgrade(gardenCount, gardenPrice, gardenButton, "Garden"); });
    mineButton.setOnClick([&]() { buyUpgrade(mineCount, minePrice, mineButton, "Mine"); });
    factoryButton.setOnClick([&]() { buyUpgrade(factoryCount, factoryPrice, factoryButton, "Factory"); });
	godButton.setOnClick([&]() { buyUpgrade(godCount, godPrice, godButton, "God"); });

    updateText(); // Start-Text setzen

    while (!close_window) {
        window.clear(sf::Color(245, 161, 66));

        // Keksproduktion pro Sekunde aktualisieren
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration<float>(now - lastUpdateTime).count() >= 1.0f) {
            cookieCount += grammaCount + (gardenCount * 5) + (mineCount * 250) + (factoryCount * 1000) + (godCount * 30000);
            updateText();
            lastUpdateTime = now;
        }

        while (auto event = event_queue.pop_if_not_empty()) {
            switch (event->type) {
            case sf::Event::Closed:
                close_window.store(true);
                break;
            case sf::Event::MouseButtonPressed: {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (cookieSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    cookieCount += std::max(1, cookiesPerSecond / 10);
                    updateText();
                        
                }
            } break;
            }

            // Button-Event-Handling
            grammaButton.handleEvent(*event, window);
            gardenButton.handleEvent(*event, window);
            mineButton.handleEvent(*event, window);
            factoryButton.handleEvent(*event, window);
			godButton.handleEvent(*event, window);
        }

        // Buttons aktivieren/deaktivieren basierend auf Cookie-Anzahl
        grammaButton.setEnabled(cookieCount >= static_cast<int>(grammaPrice));
        gardenButton.setEnabled(cookieCount >= static_cast<int>(gardenPrice));
        mineButton.setEnabled(cookieCount >= static_cast<int>(minePrice));
        factoryButton.setEnabled(cookieCount >= static_cast<int>(factoryPrice));
		godButton.setEnabled(cookieCount >= static_cast<int>(godPrice));

        // Rendern
        window.draw(cookieSprite);
		window.draw(grammaSprite);
		window.draw(farmSprite);
		window.draw(mineSprite);
        window.draw(factorySprite);
		window.draw(godSprite);
        window.draw(text);
		window.draw(leveltext);
        window.draw(grammaText);
        window.draw(gardenText);
        window.draw(mineText);
		window.draw(factoryText);
		window.draw(godText);
        grammaButton.draw(window);
        gardenButton.draw(window);
        mineButton.draw(window);
		factoryButton.draw(window);
		godButton.draw(window);
        window.display();
    }
}

