#include <chrono>

#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window; // Defines new window

    // Set window properties
    window.create(sf::VideoMode(300, 90), "Clock");
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(30);

    // Clock label size in pixels
    const unsigned int text_size = 60;

    // Define the format of the time string
    const char *format = "%H:%M:%S"; // Hours:Minutes:Seconds

    sf::Font font; // Defines digital clock font

    // Try to load the font
    if (!font.loadFromFile("KdamThmorPro-Regular.ttf"))
    {
        exit(1);
    }

    sf::Text text; // Defines clock label

    // Set label properties
    text.setFont(font);
    text.setString("00:00:00");
    text.setCharacterSize(text_size);
    text.setFillColor(sf::Color::Blue);

    bool set_text_position = true; // To set the label position at the start

    // Run the program as long as the window is open
    while (window.isOpen())
    {
        // Event handler
        sf::Event event;

        // Check all the window's events that were triggered since the last iteration of the loop
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Get the current time using std::chrono
        auto currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        // Time container
        std::tm timeInfo;

        // Convert the current time to a tm structure
        localtime_r(&currentTime, &timeInfo); // For Windows: change to localtime_s(&timeInfo, &currentTime);

        // Extract seconds as an integer
        int seconds = timeInfo.tm_sec;

        // Convert the current time into the specified format
        char timeString[100]; // Stores time as a string
        strftime(timeString, sizeof(timeString), format, &timeInfo);

        // Clear the window with black color
        window.clear(sf::Color::Black);

        // Draw text
        text.setString(timeString);
        if (set_text_position || !seconds)
        {
            sf::FloatRect text_bounds = text.getLocalBounds();
            sf::Vector2u window_size = window.getSize();
            text.setPosition((window_size.x - text_bounds.width) / 2, (window_size.y - text_size) / 2 - 6);
            set_text_position = false;
        }
        window.draw(text);

        // End the current frame
        window.display();
    }

    return 0;
}
