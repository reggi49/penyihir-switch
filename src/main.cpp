#include "cross2d/c2d.h"
#include <fstream>
#include <filesystem>
#include <iostream>

using namespace c2d;
namespace fs = std::filesystem;
bool isKeyPressed = false;

IntRect getTextureRect(Texture *texture, int direction)
{
    int width = (int)texture->getSize().x / 4;
    int height = (int)texture->getSize().y / 4;
    IntRect rect = {0, 0, width, height};

    switch (direction)
    {
    case 1:
        rect.top = height;
        break;
    case 2:
        rect.top = height * 2;
        break;
    case 3:
        rect.top = height * 3;
        rect.left = width;
        break;
    default:
        break;
    }

    return rect;
}

void processKeyPress()
{
    // std::cout << "Key pressed!" << std::endl;
    // printf("Key pressed!");
    isKeyPressed = true;
}

void copyFile(const fs::path &sourcePath, const fs::path &destinationPath)
{
    std::ifstream sourceFile(sourcePath, std::ios::binary);
    std::ofstream destinationFile(destinationPath, std::ios::binary);
    if (!sourceFile || !destinationFile)
    {
        std::cout << "Failed to open file." << std::endl;
        return;
    }

    destinationFile << sourceFile.rdbuf();

    sourceFile.close();
    destinationFile.close();
}

void copyDirectory(const fs::path &sourcePath, const fs::path &destinationPath)
{
    // if (fs::exists(destinationPath))
    // {
    //     fs::remove_all(destinationPath);
    //     // std::cout << "Folder deleted successfully." << std::endl;
    // }
    // else
    // {
    //     fs::create_directories(destinationPath);
    // }

    fs::create_directories(destinationPath);

    for (const auto &entry : fs::directory_iterator(sourcePath))
    {
        const fs::path &sourceFilePath = entry.path();
        const fs::path &destinationFilePath = destinationPath / sourceFilePath.filename();

        if (fs::is_directory(sourceFilePath))
        {
            copyDirectory(sourceFilePath, destinationFilePath);
        }
        else
        {
            copyFile(sourceFilePath, destinationFilePath);
        }
    }
    std::cout << "Copy completed " << std::endl;
}

int main(int argc, char **argv)
{
    char fps[64];

    // create the main renderer
    auto *renderer = new C2DRenderer();
    renderer->setClearColor(Color::Black);

    // create a background and add it to the main renderer
    // auto bg = new Background({renderer->getSize().x / 2, renderer->getSize().y,
    //                           renderer->getSize().x * (20 * m_scaling.x), renderer->getSize().y * (10 * m_scaling.y)});
    // bg->setOrigin(Origin::Bottom);
    // gameView->add(bg);
 
    // bg with texture
    auto *texture = new C2DTexture(renderer->getIo()->getRomFsPath() + "bg.jpeg");
    texture->setOrigin(Origin::Center);
    texture->setPosition(renderer->getSize().x / 2, renderer->getSize().y / 2);
    texture->setSize(renderer->getSize().x, renderer->getSize().y);
    renderer->add(texture);

    // create a buttons texture for the sprite
    // auto buttons = new C2DTexture(renderer->getIo()->getRomFsPath() + "buttons.png");

    // create a sprite
    // auto sprite = new Sprite(buttons, getTextureRect(buttons, 0));
    // sprite->setOrigin(Origin::Center);
    // sprite->setPosition(renderer->getSize().x / 2, renderer->getSize().y / 2);
    // sprite->setVisibility(Visibility::Visible);
    // renderer->add(sprite);

    auto changeLanguage = new Text("Press (A) to Change The Language", 50);
    changeLanguage->setOrigin(Origin::Center);
    changeLanguage->setFillColor(Color::Red);
    changeLanguage->setOutlineColor(Color::White);
    changeLanguage->setOutlineThickness(2);
    changeLanguage->setPosition(renderer->getSize().x / 2, renderer->getSize().y / 2);
    changeLanguage->setVisibility(Visibility::Visible);
    renderer->add(changeLanguage);

    auto cancelLanguage = new Text("Press (B) to Cancel", 50);
    cancelLanguage->setOrigin(Origin::Center);
    cancelLanguage->setFillColor(Color::Red);
    cancelLanguage->setOutlineColor(Color::White);
    cancelLanguage->setOutlineThickness(2);
    cancelLanguage->setPosition(renderer->getSize().x / 2, renderer->getSize().y / 2 + 70);
    cancelLanguage->setVisibility(Visibility::Visible);
    renderer->add(cancelLanguage);

    auto processingLanguage = new Text("Patching Language ...", 50);
    processingLanguage->setOrigin(Origin::Center);
    processingLanguage->setFillColor(Color::Red);
    processingLanguage->setOutlineColor(Color::White);
    processingLanguage->setOutlineThickness(2);
    processingLanguage->setPosition(changeLanguage->getPosition().x, changeLanguage->getPosition().y - 50);
    processingLanguage->setVisibility(Visibility::Hidden);
    renderer->add(processingLanguage);

    auto successText = new Text("!!! Success Change Language to Indonesian, Press B to Closes !!!", 50);
    successText->setOrigin(Origin::Center);
    successText->setFillColor(Color::Red);
    successText->setOutlineColor(Color::White);
    successText->setOutlineThickness(2);
    successText->setPosition(renderer->getSize().x / 2, renderer->getSize().y / 2);
    successText->setVisibility(Visibility::Hidden);
    renderer->add(successText);

    auto credit = new C2DText("Developed by Reggi49");
    credit->setOutlineColor(Color::Red);
    credit->setOutlineThickness(1);
    credit->setOrigin(Origin::BottomRight);
    credit->setPosition(renderer->getSize());
    renderer->add(credit);

    auto *text = new Text("FPS: 60/60");
    renderer->add(text);

    // main loop
    while (true)
    {
        unsigned int keys = renderer->getInput()->getButtons();
        // exit if START or SELECT or B is pressed (+/- on switch)
        if (keys & Input::Button::Start || keys & Input::Button::Select || keys & Input::Button::B)
        {
            break;
        }

        if (!isKeyPressed)
        {
            if (keys & Input::Button::A)
            {
                processKeyPress();
                changeLanguage->setVisibility(Visibility::Hidden);
                cancelLanguage->setVisibility(Visibility::Hidden);
                // processingLanguage->setVisibility(Visibility::Visible, true);

                // sprite->setVisibility(Visibility::Hidden);

                copyDirectory(sourcePath, destinationPath);

                // processingLanguage->setVisibility(Visibility::Hidden, true);
                successText->setVisibility(Visibility::Visible, true);
            }
        }
            // isKeyPressed = false;

            snprintf(fps, 65, "FPS: %.2g/60\nFreeze means patching is in progress : %f",
                     renderer->getFps(),
                     renderer->getDeltaTime()
                         .asSeconds());
            text->setString(fps);

            // draw everything
            renderer->flip();
        }

    // cleanup
    // will delete child's (textures, shapes, text..)
    delete (renderer);

    return 0;
}