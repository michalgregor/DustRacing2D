// This file is part of Dust Racing (DustRAC).
// Copyright (C) 2012 Jussi Lind <jussi.lind@iki.fi>
//
// DustRAC is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// DustRAC is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with DustRAC. If not, see <http://www.gnu.org/licenses/>.

#include "mainmenu.hpp"
#include "menuitem.hpp"
#include "menuitemview.hpp"
#include "menuitemaction.hpp"
#include "menumanager.hpp"
#include "renderer.hpp"

#include <MCLogger>
#include <MCSurface>
#include <MCSurfaceManager>

#include <QApplication>

class QuitAction : public MenuItemAction
{
    //! \reimp
    void fire()
    {
        MCLogger().info() << "Quit selected from the main menu.";
        QApplication::instance()->quit();
    }
};

class PlayAction : public MenuItemAction
{
    //! \reimp
    void fire()
    {
        MCLogger().info() << "Play selected from the main menu.";
        MenuManager::instance().pushMenu("trackSelection");
    }
};

class HelpAction : public MenuItemAction
{
    //! \reimp
    void fire()
    {
        MCLogger().info() << "Help selected from the main menu.";
        MenuManager::instance().pushMenu("help");
    }
};

class CreditsAction : public MenuItemAction
{
    //! \reimp
    void fire()
    {
        MCLogger().info() << "Credits selected from the main menu.";
        MenuManager::instance().pushMenu("credits");
    }
};

class SettingsAction : public MenuItemAction
{
    //! \reimp
    void fire()
    {
        MCLogger().info() << "Settings selected from the main menu.";
        MenuManager::instance().pushMenu("settings");
    }
};

MainMenu::MainMenu(std::string id, int width, int height)
: SurfaceMenu("mainMenuBack", id, width, height, Menu::MS_VERTICAL_LIST)
{
    MenuItem * play = new MenuItem(width, height / 5, "Play");
    play->setView(new MenuItemView(*play), true);
    play->setAction(new PlayAction, true);

    MenuItem * help = new MenuItem(width, height / 5, "Help");
    help->setView(new MenuItemView(*help), true);
    help->setAction(new HelpAction, true);

    MenuItem * credits = new MenuItem(width, height / 5, "Credits");
    credits->setView(new MenuItemView(*credits), true);
    credits->setAction(new CreditsAction, true);

    MenuItem * quit = new MenuItem(width, height / 5, "Quit");
    quit->setView(new MenuItemView(*quit), true);
    quit->setAction(new QuitAction, true);

    MenuItem * settings = new MenuItem(width, height / 5, "Settings");
    settings->setView(new MenuItemView(*settings), true);
    settings->setAction(new SettingsAction, true);

    addItem(*quit,     true);
    addItem(*credits,  true);
    addItem(*settings, true);
    addItem(*help,     true);
    addItem(*play,     true);
}
