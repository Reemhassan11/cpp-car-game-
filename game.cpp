
#include <SFML/Graphics.hpp>  // SFML graphics library
#include <optional>           // SFML 3 event handling
#include <vector>             // Dynamic arrays for cars and decorations
#include <string>             // Text and score strings
#include <algorithm>          // std::min, std::max, and std::clamp
#include <random>             // Random traffic lanes and colors
#include <cmath>              // Mathematical functions


// ============================================================
// 1. GAME CONFIGURATION
// ============================================================

// Window dimensions.
const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

// Road dimensions and boundaries.
const float ROAD_LEFT = 200.f;
const float ROAD_RIGHT = 600.f;

// Player car dimensions.
const float CAR_WIDTH = 64.f;
const float CAR_HEIGHT = 112.f;

// Player movement speed.
const float PLAYER_SPEED = 390.f;

// Starting world speed.
const float START_SPEED = 260.f;

// Maximum world speed.
const float MAX_SPEED = 900.f;


// ============================================================
// 2. CAR STRUCTURE
// ============================================================

// This structure contains all the shapes needed to draw a car.
// Both the player's car and traffic cars use this structure.

struct Car
{
    sf::ConvexShape body;

    sf::RectangleShape roof;
    sf::RectangleShape frontWindow;
    sf::RectangleShape rearWindow;

    sf::RectangleShape hoodStripe;

    sf::RectangleShape wheel1;
    sf::RectangleShape wheel2;
    sf::RectangleShape wheel3;
    sf::RectangleShape wheel4;

    sf::RectangleShape wheelDetail1;
    sf::RectangleShape wheelDetail2;
    sf::RectangleShape wheelDetail3;
    sf::RectangleShape wheelDetail4;

    sf::RectangleShape headlight1;
    sf::RectangleShape headlight2;

    sf::RectangleShape taillight1;
    sf::RectangleShape taillight2;

    sf::RectangleShape frontBumper;
    sf::RectangleShape rearBumper;

    sf::RectangleShape mirror1;
    sf::RectangleShape mirror2;
};


// ============================================================
// 3. TRAFFIC CAR STRUCTURE
// ============================================================

// Stores a traffic car and its current position.

struct TrafficCar
{
    Car car;

    float x;
    float y;

    // Prevents the same car from increasing the score twice.
    bool counted = false;
};


// ============================================================
// 4. ROAD DECORATION STRUCTURE
// ============================================================

// Stores the shapes used to create a roadside tree.

struct RoadsideTree
{
    float x;
    float y;

    sf::CircleShape shadow;
    sf::RectangleShape trunk;

    sf::CircleShape crown;
    sf::CircleShape crownDetail;
    sf::CircleShape highlight;
};


// ============================================================
// 5. ROAD TEXTURE STRUCTURE
// ============================================================

// Small rectangles create texture on the asphalt.

struct RoadSpeck
{
    sf::RectangleShape shape;
};


// ============================================================
// 6. CREATE A DETAILED CAR
// ============================================================

Car createCar(sf::Color color)
{
    Car car;

    // --------------------------------------------------------
    // Main car body
    // --------------------------------------------------------

    // Create an eight-point polygon instead of a plain rectangle.
    // This gives the car a more realistic top-down silhouette.

    car.body.setPointCount(8);

    car.body.setPoint(0, {16.f, 0.f});
    car.body.setPoint(1, {48.f, 0.f});
    car.body.setPoint(2, {60.f, 16.f});
    car.body.setPoint(3, {64.f, 92.f});
    car.body.setPoint(4, {54.f, 112.f});
    car.body.setPoint(5, {10.f, 112.f});
    car.body.setPoint(6, {0.f, 92.f});
    car.body.setPoint(7, {4.f, 16.f});

    car.body.setFillColor(color);
    car.body.setOutlineColor(sf::Color(25, 25, 25));
    car.body.setOutlineThickness(2.f);


    // --------------------------------------------------------
    // Car roof
    // --------------------------------------------------------

    car.roof.setSize({44.f, 55.f});

    // Make the roof slightly darker than the body.
    car.roof.setFillColor(
        sf::Color(color.r / 2, color.g / 2, color.b / 2)
    );

    car.roof.setOutlineColor(sf::Color(20, 20, 20));
    car.roof.setOutlineThickness(2.f);


    // --------------------------------------------------------
    // Front and rear windows
    // --------------------------------------------------------

    car.frontWindow.setSize({40.f, 19.f});
    car.frontWindow.setFillColor(sf::Color(125, 205, 230));
    car.frontWindow.setOutlineColor(sf::Color(25, 40, 55));
    car.frontWindow.setOutlineThickness(1.f);

    car.rearWindow.setSize({40.f, 19.f});
    car.rearWindow.setFillColor(sf::Color(45, 75, 100));
    car.rearWindow.setOutlineColor(sf::Color(25, 40, 55));
    car.rearWindow.setOutlineThickness(1.f);


    // --------------------------------------------------------
    // Hood stripe
    // --------------------------------------------------------

    car.hoodStripe.setSize({6.f, 17.f});
    car.hoodStripe.setFillColor(sf::Color(240, 240, 240));


    // --------------------------------------------------------
    // Four black wheels
    // --------------------------------------------------------

    car.wheel1.setSize({12.f, 26.f});
    car.wheel2.setSize({12.f, 26.f});
    car.wheel3.setSize({12.f, 26.f});
    car.wheel4.setSize({12.f, 26.f});

    car.wheel1.setFillColor(sf::Color(15, 15, 15));
    car.wheel2.setFillColor(sf::Color(15, 15, 15));
    car.wheel3.setFillColor(sf::Color(15, 15, 15));
    car.wheel4.setFillColor(sf::Color(15, 15, 15));


    // --------------------------------------------------------
    // Wheel details
    // --------------------------------------------------------

    // Small gray rectangles represent the wheel rims.

    car.wheelDetail1.setSize({4.f, 13.f});
    car.wheelDetail2.setSize({4.f, 13.f});
    car.wheelDetail3.setSize({4.f, 13.f});
    car.wheelDetail4.setSize({4.f, 13.f});

    car.wheelDetail1.setFillColor(sf::Color(150, 150, 150));
    car.wheelDetail2.setFillColor(sf::Color(150, 150, 150));
    car.wheelDetail3.setFillColor(sf::Color(150, 150, 150));
    car.wheelDetail4.setFillColor(sf::Color(150, 150, 150));


    // --------------------------------------------------------
    // Headlights
    // --------------------------------------------------------

    car.headlight1.setSize({13.f, 7.f});
    car.headlight2.setSize({13.f, 7.f});

    car.headlight1.setFillColor(sf::Color(255, 245, 150));
    car.headlight2.setFillColor(sf::Color(255, 245, 150));


    // --------------------------------------------------------
    // Rear lights
    // --------------------------------------------------------

    car.taillight1.setSize({13.f, 7.f});
    car.taillight2.setSize({13.f, 7.f});

    car.taillight1.setFillColor(sf::Color(255, 30, 30));
    car.taillight2.setFillColor(sf::Color(255, 30, 30));


    // --------------------------------------------------------
    // Front and rear bumpers
    // --------------------------------------------------------

    car.frontBumper.setSize({42.f, 5.f});
    car.rearBumper.setSize({42.f, 5.f});

    car.frontBumper.setFillColor(sf::Color(190, 190, 190));
    car.rearBumper.setFillColor(sf::Color(190, 190, 190));


    // --------------------------------------------------------
    // Side mirrors
    // --------------------------------------------------------

    car.mirror1.setSize({9.f, 13.f});
    car.mirror2.setSize({9.f, 13.f});

    car.mirror1.setFillColor(sf::Color(35, 35, 35));
    car.mirror2.setFillColor(sf::Color(35, 35, 35));

    return car;
}


// ============================================================
// 7. POSITION ALL CAR PARTS
// ============================================================

// Moving the car means updating the position of every component.
// The x and y arguments represent the top-left of the car body.

void positionCar(Car& car, float x, float y)
{
    car.body.setPosition({x, y});

    // Roof and windows.
    car.roof.setPosition({x + 10.f, y + 25.f});
    car.frontWindow.setPosition({x + 12.f, y + 30.f});
    car.rearWindow.setPosition({x + 12.f, y + 62.f});

    // Decorative stripe.
    car.hoodStripe.setPosition({x + 29.f, y + 7.f});

    // Left wheels.
    car.wheel1.setPosition({x - 5.f, y + 19.f});
    car.wheel3.setPosition({x - 5.f, y + 72.f});

    // Right wheels.
    car.wheel2.setPosition({x + 57.f, y + 19.f});
    car.wheel4.setPosition({x + 57.f, y + 72.f});

    // Wheel rim details.
    car.wheelDetail1.setPosition({x - 1.f, y + 25.f});
    car.wheelDetail2.setPosition({x + 61.f, y + 25.f});
    car.wheelDetail3.setPosition({x - 1.f, y + 78.f});
    car.wheelDetail4.setPosition({x + 61.f, y + 78.f});

    // Front headlights.
    car.headlight1.setPosition({x + 9.f, y + 3.f});
    car.headlight2.setPosition({x + 42.f, y + 3.f});

    // Rear lights.
    car.taillight1.setPosition({x + 9.f, y + 101.f});
    car.taillight2.setPosition({x + 42.f, y + 101.f});

    // Bumpers.
    car.frontBumper.setPosition({x + 11.f, y + 1.f});
    car.rearBumper.setPosition({x + 11.f, y + 106.f});

    // Side mirrors.
    car.mirror1.setPosition({x - 6.f, y + 34.f});
    car.mirror2.setPosition({x + 61.f, y + 34.f});
}


// ============================================================
// 8. DRAW ALL CAR PARTS
// ============================================================

void drawCar(sf::RenderWindow& window, const Car& car)
{
    // Draw wheels first so the body appears on top of them.
    window.draw(car.wheel1);
    window.draw(car.wheel2);
    window.draw(car.wheel3);
    window.draw(car.wheel4);

    // Draw wheel rim details.
    window.draw(car.wheelDetail1);
    window.draw(car.wheelDetail2);
    window.draw(car.wheelDetail3);
    window.draw(car.wheelDetail4);

    // Draw side mirrors.
    window.draw(car.mirror1);
    window.draw(car.mirror2);

    // Draw the main car body.
    window.draw(car.body);

    // Draw the bumpers.
    window.draw(car.frontBumper);
    window.draw(car.rearBumper);

    // Draw the roof and windows.
    window.draw(car.roof);
    window.draw(car.frontWindow);
    window.draw(car.rearWindow);

    // Draw the hood stripe.
    window.draw(car.hoodStripe);

    // Draw headlights and rear lights.
    window.draw(car.headlight1);
    window.draw(car.headlight2);
    window.draw(car.taillight1);
    window.draw(car.taillight2);
}


// ============================================================
// 9. CREATE A ROADSIDE TREE
// ============================================================

RoadsideTree createTree(float x, float y)
{
    RoadsideTree tree;

    tree.x = x;
    tree.y = y;

    // Tree shadow.
    tree.shadow.setRadius(27.f);
    tree.shadow.setScale({1.2f, 0.55f});
    tree.shadow.setFillColor(sf::Color(20, 70, 20, 100));

    // Brown tree trunk.
    tree.trunk.setSize({14.f, 35.f});
    tree.trunk.setFillColor(sf::Color(100, 60, 30));

    // Main dark green tree crown.
    tree.crown.setRadius(27.f);
    tree.crown.setFillColor(sf::Color(15, 90, 30));
    tree.crown.setOutlineColor(sf::Color(10, 60, 20));
    tree.crown.setOutlineThickness(2.f);

    // Smaller green circle to add depth.
    tree.crownDetail.setRadius(18.f);
    tree.crownDetail.setFillColor(sf::Color(35, 125, 40));

    // Small highlight.
    tree.highlight.setRadius(6.f);
    tree.highlight.setFillColor(sf::Color(90, 160, 55));

    return tree;
}


// ============================================================
// 10. POSITION A TREE
// ============================================================

void positionTree(RoadsideTree& tree)
{
    tree.shadow.setPosition({tree.x - 33.f, tree.y + 40.f});

    tree.trunk.setPosition({tree.x - 7.f, tree.y + 15.f});

    tree.crown.setPosition({tree.x - 27.f, tree.y - 10.f});

    tree.crownDetail.setPosition({tree.x - 9.f, tree.y - 20.f});

    tree.highlight.setPosition({tree.x + 5.f, tree.y - 10.f});
}


// ============================================================
// 11. DRAW A TREE
// ============================================================

void drawTree(sf::RenderWindow& window, const RoadsideTree& tree)
{
    window.draw(tree.shadow);
    window.draw(tree.trunk);
    window.draw(tree.crown);
    window.draw(tree.crownDetail);
    window.draw(tree.highlight);
}


// ============================================================
// 12. MAIN FUNCTION
// ============================================================

int main()
{
    // --------------------------------------------------------
    // Create the game window.
    // --------------------------------------------------------

    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Ultimate Car Racing Game"
    );

    // Limit rendering to 60 frames per second.
    window.setFramerateLimit(60);


    // ========================================================
    // 13. LOAD THE FONT
    // ========================================================

    sf::Font font;

    // Load Arial from the Windows Fonts directory.
    bool fontLoaded = font.openFromFile(
        "C:/Windows/Fonts/arial.ttf"
    );

    // Score display.
    sf::Text scoreText(font);
    scoreText.setCharacterSize(25);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({28.f, 20.f});

    // Speed display.
    sf::Text speedText(font);
    speedText.setCharacterSize(19);
    speedText.setFillColor(sf::Color(255, 230, 120));
    speedText.setPosition({28.f, 53.f});

    // Controls display.
    sf::Text controlsText(font);
    controlsText.setCharacterSize(15);
    controlsText.setFillColor(sf::Color::White);
    controlsText.setString("LEFT / RIGHT or A / D");
    controlsText.setPosition({560.f, 20.f});

    // Game over message.
    sf::Text gameOverText(font);
    gameOverText.setCharacterSize(55);
    gameOverText.setFillColor(sf::Color(255, 60, 60));
    gameOverText.setString("GAME OVER");
    gameOverText.setPosition({235.f, 205.f});

    // Final score.
    sf::Text finalScoreText(font);
    finalScoreText.setCharacterSize(27);
    finalScoreText.setFillColor(sf::Color::White);
    finalScoreText.setPosition({290.f, 275.f});

    // Restart instructions.
    sf::Text restartText(font);
    restartText.setCharacterSize(22);
    restartText.setFillColor(sf::Color(255, 230, 100));
    restartText.setString("Press R to Restart");
    restartText.setPosition({290.f, 335.f});


    // ========================================================
    // 14. CREATE THE BACKGROUND
    // ========================================================

    // Full green grass background.
    sf::RectangleShape grass({800.f, 600.f});
    grass.setFillColor(sf::Color(45, 125, 42));

    // Slightly darker grass strips add visual texture.
    std::vector<sf::RectangleShape> grassStrips;

    for (int i = 0; i < 12; i++)
    {
        sf::RectangleShape strip({800.f, 4.f});

        strip.setPosition({0.f, i * 55.f});

        strip.setFillColor(sf::Color(35, 110, 35, 100));

        grassStrips.push_back(strip);
    }


    // ========================================================
    // 15. CREATE THE ROAD
    // ========================================================

    sf::RectangleShape road({400.f, 600.f});

    road.setPosition({200.f, 0.f});

    road.setFillColor(sf::Color(52, 54, 58));

    // Road shoulder strips.
    sf::RectangleShape leftShoulder({12.f, 600.f});
    leftShoulder.setPosition({200.f, 0.f});
    leftShoulder.setFillColor(sf::Color(95, 95, 95));

    sf::RectangleShape rightShoulder({12.f, 600.f});
    rightShoulder.setPosition({588.f, 0.f});
    rightShoulder.setFillColor(sf::Color(95, 95, 95));


    // ========================================================
    // 16. ROAD BOUNDARY LINES
    // ========================================================

    sf::RectangleShape leftEdge({4.f, 600.f});
    leftEdge.setPosition({212.f, 0.f});
    leftEdge.setFillColor(sf::Color::White);

    sf::RectangleShape rightEdge({4.f, 600.f});
    rightEdge.setPosition({584.f, 0.f});
    rightEdge.setFillColor(sf::Color::White);


    // ========================================================
    // 17. DASHED LANE MARKINGS
    // ========================================================

    // Create two lane dividers.
    // This gives the road three traffic lanes.

    std::vector<sf::RectangleShape> roadLines;

    for (int i = 0; i < 8; i++)
    {
        for (float x : {330.f, 463.f})
        {
            sf::RectangleShape line({7.f, 42.f});

            line.setPosition({x, i * 90.f});

            line.setFillColor(sf::Color(245, 245, 245));

            roadLines.push_back(line);
        }
    }


    // ========================================================
    // 18. ROAD ASPHALT TEXTURE
    // ========================================================

    // Small gray marks create a subtle asphalt effect.

    std::mt19937 randomEngine(std::random_device{}());

    std::uniform_real_distribution<float> speckX(220.f, 575.f);
    std::uniform_real_distribution<float> speckY(0.f, 600.f);
    std::uniform_int_distribution<int> grayValue(65, 100);

    std::vector<RoadSpeck> roadSpecks;

    for (int i = 0; i < 45; i++)
    {
        RoadSpeck speck;

        speck.shape.setSize({2.f, 6.f});

        int gray = grayValue(randomEngine);

        speck.shape.setFillColor(
            sf::Color(gray, gray, gray)
        );

        speck.shape.setPosition({
            speckX(randomEngine),
            speckY(randomEngine)
        });

        roadSpecks.push_back(speck);
    }


    // ========================================================
    // 19. CREATE ROADSIDE TREES
    // ========================================================

    std::vector<RoadsideTree> trees;

    // Seven trees on each side of the road.
    for (int i = 0; i < 7; i++)
    {
        float treeY = i * 110.f - 100.f;

        // Left roadside tree.
        trees.push_back(createTree(70.f, treeY));

        // Right roadside tree.
        trees.push_back(createTree(710.f, treeY + 45.f));
    }

    // Position all the trees initially.
    for (auto& tree : trees)
    {
        positionTree(tree);
    }


    // ========================================================
    // 20. CREATE THE PLAYER CAR
    // ========================================================

    // Create a red sports car.
    Car playerCar = createCar(sf::Color(220, 25, 35));

    // Starting player position.
    float playerX = 368.f;

    // Keep the player's vertical position fixed.
    const float playerY = 450.f;

    // Position all car components.
    positionCar(playerCar, playerX, playerY);


    // ========================================================
    // 21. CREATE TRAFFIC CAR COLORS AND LANES
    // ========================================================

    // Different traffic car colors.
    sf::Color trafficColors[] =
    {
        sf::Color(30, 110, 230),   // Blue
        sf::Color(240, 190, 25),   // Yellow
        sf::Color(160, 50, 190),   // Purple
        sf::Color(235, 235, 235), // White
        sf::Color(30, 180, 145),  // Turquoise
        sf::Color(230, 100, 20)   // Orange
    };

    // X coordinates of the three traffic lanes.
    float lanes[] =
    {
        235.f,
        368.f,
        501.f
    };

    // Store all traffic cars.
    std::vector<TrafficCar> trafficCars;

    // Random lane selection.
    std::uniform_int_distribution<int> laneDistribution(0, 2);

    // Random car color selection.
    std::uniform_int_distribution<int> colorDistribution(0, 5);


    // ========================================================
    // 22. GAME VARIABLES
    // ========================================================

    // Player score.
    float score = 0.f;

    // Time survived.
    float gameTime = 0.f;

    // Current world speed.
    float worldSpeed = START_SPEED;

    // Traffic spawning timer.
    float spawnTimer = 0.f;

    // Initial time between traffic cars.
    float spawnInterval = 1.25f;

    // Game state.
    bool gameOver = false;


    // ========================================================
    // 23. GAME CLOCK
    // ========================================================

    // Used to calculate the time between frames.
    sf::Clock gameClock;


    // ========================================================
    // 24. MAIN GAME LOOP
    // ========================================================

    while (window.isOpen())
    {
        // Calculate elapsed time since the previous frame.
        // Clamp it to avoid huge movement after a pause.
        float dt = std::min(
            gameClock.restart().asSeconds(),
            0.05f
        );


        // ====================================================
        // 25. HANDLE WINDOW EVENTS
        // ====================================================

        while (const std::optional event = window.pollEvent())
        {
            // Close the game if the window close button is clicked.
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }


        // ====================================================
        // 26. RESTART THE GAME
        // ====================================================

        if (gameOver &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
        {
            // Reset player position.
            playerX = 368.f;

            // Reset score and game time.
            score = 0.f;
            gameTime = 0.f;

            // Restore starting speed.
            worldSpeed = START_SPEED;

            // Reset traffic spawning.
            spawnTimer = 0.f;
            spawnInterval = 1.25f;

            // Remove all traffic cars.
            trafficCars.clear();

            // Restart the game.
            gameOver = false;
        }


        // ====================================================
        // 27. UPDATE THE GAME
        // ====================================================

        if (!gameOver)
        {
            // ------------------------------------------------
            // UPDATE TIME AND SCORE
            // ------------------------------------------------

            gameTime += dt;

            // Increase the score while the player survives.
            score += dt * 10.f;


            // ------------------------------------------------
            // INCREASE GAME SPEED OVER TIME
            // ------------------------------------------------

            // The game becomes faster as time passes.
            // Speed increases by 24 units every second.
            worldSpeed = std::min(
                MAX_SPEED,
                START_SPEED + gameTime * 24.f
            );

            // Traffic cars appear more frequently over time.
            spawnInterval = std::max(
                0.48f,
                1.25f - gameTime * 0.012f
            );


            // ------------------------------------------------
            // PLAYER MOVEMENT
            // ------------------------------------------------

            // Move left using the LEFT arrow or A.
            if (
                sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)
            )
            {
                playerX -= PLAYER_SPEED * dt;
            }

            // Move right using the RIGHT arrow or D.
            if (
                sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)
            )
            {
                playerX += PLAYER_SPEED * dt;
            }

            // Prevent the car from crossing the road boundaries.
            playerX = std::clamp(
                playerX,
                215.f,
                521.f
            );

            // Update all player car components.
            positionCar(playerCar, playerX, playerY);


            // ------------------------------------------------
            // MOVE THE ROAD LINES
            // ------------------------------------------------

            for (auto& line : roadLines)
            {
                sf::Vector2f position = line.getPosition();

                // Move the road lines downwards.
                position.y += worldSpeed * dt;

                // Recycle the line after it leaves the screen.
                if (position.y > 650.f)
                {
                    position.y -= 720.f;
                }

                line.setPosition(position);
            }


            // ------------------------------------------------
            // MOVE THE ASPHALT TEXTURE
            // ------------------------------------------------

            for (auto& speck : roadSpecks)
            {
                sf::Vector2f position = speck.shape.getPosition();

                // Make the road texture move with the road.
                position.y += worldSpeed * 0.8f * dt;

                // Recycle texture marks.
                if (position.y > 610.f)
                {
                    position.y -= 620.f;
                    position.x = speckX(randomEngine);
                    speck.shape.setPosition(position);
                }
                else
                {
                    speck.shape.setPosition(position);
                }
            }


            // ------------------------------------------------
            // MOVE THE ROADSIDE TREES
            // ------------------------------------------------

            for (auto& tree : trees)
            {
                // Trees move more slowly than the road markings.
                tree.y += worldSpeed * 0.72f * dt;

                // Recycle trees after they leave the screen.
                if (tree.y > 680.f)
                {
                    tree.y -= 770.f;
                }

                // Update all tree component positions.
                positionTree(tree);
            }


            // ------------------------------------------------
            // CREATE NEW TRAFFIC CARS
            // ------------------------------------------------

            spawnTimer += dt;

            if (spawnTimer >= spawnInterval)
            {
                spawnTimer = 0.f;

                // Randomly select a lane.
                int selectedLane = laneDistribution(randomEngine);

                float laneX = lanes[selectedLane];

                // Avoid spawning a car too close to another car
                // in the same lane.
                bool laneBusy = false;

                for (const auto& enemy : trafficCars)
                {
                    if (
                        std::abs(enemy.x - laneX) < 1.f &&
                        enemy.y < 140.f
                    )
                    {
                        laneBusy = true;
                        break;
                    }
                }

                // Spawn only if the selected lane is clear.
                if (!laneBusy)
                {
                    // Select a random traffic car color.
                    int selectedColor = colorDistribution(randomEngine);

                    // Create a detailed traffic car.
                    Car newCar = createCar(
                        trafficColors[selectedColor]
                    );

                    // Position it above the visible screen.
                    positionCar(newCar, laneX, -140.f);

                    // Add it to the traffic vector.
                    trafficCars.push_back({
                        newCar,
                        laneX,
                        -140.f,
                        false
                    });
                }
            }


            // ------------------------------------------------
            // MOVE TRAFFIC CARS
            // ------------------------------------------------

            for (auto& enemy : trafficCars)
            {
                // Move traffic towards the bottom of the screen.
                enemy.y += worldSpeed * dt;

                // Update all parts of the traffic car.
                positionCar(enemy.car, enemy.x, enemy.y);

                // Award points when a car passes the player.
                if (
                    !enemy.counted &&
                    enemy.y > playerY + CAR_HEIGHT
                )
                {
                    score += 25.f;
                    enemy.counted = true;
                }
            }


            // ------------------------------------------------
            // REMOVE TRAFFIC CARS OFF SCREEN
            // ------------------------------------------------

            for (int i = 0; i < (int)trafficCars.size(); )
            {
                if (trafficCars[i].y > 680.f)
                {
                    // Remove the traffic car.
                    trafficCars.erase(
                        trafficCars.begin() + i
                    );
                }
                else
                {
                    i++;
                }
            }


            // ------------------------------------------------
            // COLLISION DETECTION
            // ------------------------------------------------

            for (const auto& enemy : trafficCars)
            {
                // Check whether the player and enemy bodies overlap.
                if (
                    playerCar.body.getGlobalBounds().findIntersection(
                        enemy.car.body.getGlobalBounds()
                    )
                )
                {
                    // End the game after a collision.
                    gameOver = true;

                    break;
                }
            }
        }


        // ====================================================
        // 28. UPDATE THE HUD
        // ====================================================

        int displayedScore = static_cast<int>(score);

        // Update the score text.
        scoreText.setString(
            "SCORE: " + std::to_string(displayedScore)
        );

        // Show the current speed.
        speedText.setString(
            "SPEED: " +
            std::to_string(static_cast<int>(worldSpeed))
        );

        // Update the final score.
        finalScoreText.setString(
            "FINAL SCORE: " + std::to_string(displayedScore)
        );


        // ====================================================
        // 29. DRAW THE BACKGROUND
        // ====================================================

        window.clear();

        // Draw the grass.
        window.draw(grass);

        // Draw subtle grass strips.
        for (const auto& strip : grassStrips)
        {
            window.draw(strip);
        }


        // ====================================================
        // 30. DRAW ROADSIDE TREES
        // ====================================================

        for (const auto& tree : trees)
        {
            drawTree(window, tree);
        }


        // ====================================================
        // 31. DRAW THE ROAD
        // ====================================================

        window.draw(road);

        // Draw road shoulders.
        window.draw(leftShoulder);
        window.draw(rightShoulder);

        // Draw road boundaries.
        window.draw(leftEdge);
        window.draw(rightEdge);


        // ====================================================
        // 32. DRAW ROAD TEXTURE
        // ====================================================

        for (const auto& speck : roadSpecks)
        {
            window.draw(speck.shape);
        }


        // ====================================================
        // 33. DRAW LANE MARKINGS
        // ====================================================

        for (const auto& line : roadLines)
        {
            window.draw(line);
        }


        // ====================================================
        // 34. DRAW TRAFFIC CARS
        // ====================================================

        for (const auto& enemy : trafficCars)
        {
            drawCar(window, enemy.car);
        }


        // ====================================================
        // 35. DRAW THE PLAYER CAR
        // ====================================================

        drawCar(window, playerCar);


        // ====================================================
        // 36. DRAW THE HUD
        // ====================================================

        if (fontLoaded)
        {
            // Draw score and speed information.
            window.draw(scoreText);
            window.draw(speedText);
            window.draw(controlsText);
        }


        // ====================================================
        // 37. GAME OVER SCREEN
        // ====================================================

        if (gameOver)
        {
            // Create a dark transparent overlay.
            sf::RectangleShape overlay({800.f, 600.f});

            overlay.setFillColor(
                sf::Color(0, 0, 0, 175)
            );

            window.draw(overlay);

            // Display game over information.
            if (fontLoaded)
            {
                window.draw(gameOverText);
                window.draw(finalScoreText);
                window.draw(restartText);
            }
        }


        // ====================================================
        // 38. DISPLAY THE FRAME
        // ====================================================

        // Show the completed frame.
        window.display();
    }

    // Exit successfully.
    return 0;
}
