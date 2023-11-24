#include <chrono>

#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window;

    window.create(sf::VideoMode(200, 60), "Clock");
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(30);

    sf::Font font;
    if (!font.loadFromFile("KdamThmorPro-Regular.ttf"))
    {
        exit(1);
    }

    unsigned int text_size = 40;

    sf::Text text;
    text.setFont(font);
    text.setString("00:00:00");
    text.setCharacterSize(text_size); // in pixels, not points!
    text.setFillColor(sf::Color::Blue);

    bool set_text_position = true;

    // Run the program as long as the window is open
    while (window.isOpen())
    {
        // Check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Get the current time using std::chrono
        auto currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        // Convert the current time to a tm structure
        std::tm timeInfo;
        localtime_r(&currentTime, &timeInfo); // For Windows: change to localtime_s(&timeInfo, &currentTime);

        // Define the format of the time string
        const char *format = "%H:%M:%S"; // Hours:Minutes:Seconds

        // Convert the current time into the specified format
        char timeString[100];
        strftime(timeString, sizeof(timeString), format, &timeInfo);

        // Clear the window with black color
        window.clear(sf::Color::Black);

        // Draw text
        text.setString(timeString);
        if (set_text_position)
        {
            sf::FloatRect text_bounds = text.getLocalBounds();
            sf::Vector2u window_size = window.getSize();
            text.setPosition((window_size.x - text_bounds.width) / 2, (window_size.y - text_size) / 2 - 4);
            set_text_position = false;
        }
        window.draw(text);

        // End the current frame
        window.display();
    }

    return 0;
}
