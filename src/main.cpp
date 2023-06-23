#include "cross2d/c2d.h"
#include <fstream>
#include <filesystem>
#include <iostream>

using namespace c2d;
namespace fs = std::filesystem;

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

// void showResults()
// {
//     auto *renderer = new C2DRenderer();
//     renderer->setClearColor(Color::Transparent);

//     auto showResults = new Text("... Sukses ...", 70);
//     showResults->setOrigin(Origin::Center);
//     showResults->setPosition(renderer->getSize().x / 2, renderer->getPosition().y + 120);
//     renderer->add(showResults);
// }

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
}

int main(int argc, char **argv)
{
    // char fps[64];

    // create the main renderer
    auto *renderer = new C2DRenderer();
    renderer->setClearColor(Color::Black);
    // renderer->io = io;
    // renderer->path = path;

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
    auto buttons = new C2DTexture(renderer->getIo()->getRomFsPath() + "buttons.png");

    // create a sprite
    auto sprite = new Sprite(buttons, getTextureRect(buttons, 0));
    sprite->setOrigin(Origin::Center);
    sprite->setPosition(renderer->getSize().x / 2, renderer->getSize().y / 2);
    // sprite->setSize(renderer->getSize().x / 10, renderer->getSize().y / 10);
    sprite->setVisibility(Visibility::Visible);
    renderer->add(sprite);

    auto text = new Text("Press (A) to Change The Language", 50);
    text->setOrigin(Origin::Center);
    text->setFillColor(Color::Red);
    text->setOutlineColor(Color::White);
    text->setOutlineThickness(2);
    text->setPosition(sprite->getPosition().x, sprite->getPosition().y - 50);
    text->setVisibility(Visibility::Visible);
    renderer->add(text);

    auto successText = new Text("!!! Success Change Language to Indonesian !!!", 50);
    successText->setOrigin(Origin::Center);
    successText->setFillColor(Color::Red);
    successText->setOutlineColor(Color::White);
    successText->setOutlineThickness(2);
    successText->setPosition(sprite->getPosition().x, sprite->getPosition().y - 30);
    successText->setVisibility(Visibility::Hidden);
    renderer->add(successText);

    auto credit = new C2DText("Developed by Reggi49");
    credit->setOutlineColor(Color::Red);
    credit->setOutlineThickness(1);
    credit->setOrigin(Origin::BottomRight);
    credit->setPosition(renderer->getSize());
    renderer->add(credit);

    // auto *info = new Text("Status");
    // renderer->add(info);

    // main loop
    while (true)
    {
        unsigned int keys = renderer->getInput()->getButtons();
        // exit if START or SELECT is pressed (+/- on switch)
        if (keys & Input::Button::Start || keys & Input::Button::Select)
        {
            break;
        }

        if (keys & Input::Button::A)
        {
            text->setVisibility(Visibility::Hidden);
            sprite->setVisibility(Visibility::Hidden);

            const fs::path sourcePath = "romfs:/rename";
            const fs::path destinationPath = "/atmosphere/contents/rename";

            copyDirectory(sourcePath, destinationPath);
            successText->setVisibility(Visibility::Visible, true);
            // std::cout << "Folder copied successfully." << std::endl;
            // try
            // {
                // std::copy(dir1, dir2, std::filesystem::copy_options::recursive);
                //              //|fs::copy_options::overwrite_existing
                //              | fs::copy_options::recursive))
                // fs::copy(dir1, dir2, 
                //             fs::copy_options::overwrite_existing
                //             | fs::copy_options::recursive);
                // successText->setVisibility(Visibility::Visible, true);
                // snprintf(fps, 63, "Sukses %.2g",
                //          renderer->getFps() );
                // info->setString(fps);
            // }
            // catch (...)
            // {
            //     snprintf(fps, 63, "FPS: %.2g/60\nDELTA: %f",
            //              renderer->getFps(),
            //              renderer->getDeltaTime().asSeconds());
            //     info->setString(fps);
                // printf("Failed to Change The Language");
                    //     cerr
                    // << e.what() << endl;
            // }

            // return 0;
            // snprintf(128,128, "button A pressedd");
            // successText->setVisibility(Visibility::Visible, true);

            // SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
            //                              "Info",
            //                              "Suksses",
            //                              NULL);
            // SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Info", "Suksses", NULL);
            // showResults();
        }

        // stop if any key is pressed
        // if (renderer->getInput()->getButtons())
        // {
        //     break;
        // }

        // draw everything
        renderer->flip();
    }

    // cleanup
    // will delete child's (textures, shapes, text..)
    delete (renderer);

    return 0;
}