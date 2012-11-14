// This file is part of Dust Racing 2D.
// Copyright (C) 2012 Jussi Lind <jussi.lind@iki.fi>
//
// Dust Racing 2D is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// Dust Racing 2D is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Dust Racing 2D. If not, see <http://www.gnu.org/licenses/>.

#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include <vector>
#include <memory>

namespace MTFH {

class MenuItem;

class Menu
{
public:

    //! Default styles
    enum MenuStyle
    {
        MS_VERTICAL_LIST,
        MS_HORIZONTAL_LIST,
        MS_SHOW_ONE // Show only one item at a time
    };

    //! Constructor.
    Menu(std::string id, int width, int height, MenuStyle style = MS_VERTICAL_LIST);

    //! Destructor.
    virtual ~Menu();

    std::string id() const;

    //! Renders the menu items. See also MenuItemView.
    virtual void render();

    //! Selection up.
    virtual void up();

    //! Selection down.
    virtual void down();

    //! Current item left.
    virtual void left();

    //! Current item right.
    virtual void right();

    //! Select the current item.
    virtual void selectCurrentItem();

    //! Return current item or nullptr if no items added.
    MenuItem * currentItem() const;

    //! Return selected item or nullptr if no item added.
    //! Pressing enter on an item selects it.
    MenuItem * selectedItem() const;

    //! Add item to the menu.
    virtual void addItem(MenuItem & menuItem, bool takeOwnership = false);

    //! Use this if the current menu stack needs to be
    //! completely quit, for example when the execution
    //! should move from the menu to the actual game.
    void setDone(bool done);

    //! \returns true if done.
    bool done() const;

    //! Called when the menu is entered. Call parent implementation if overridden.
    virtual void enter();

    //! Returns the width of the menu.
    int width() const;

    //! Returns the height of the menu.
    int height() const;

    //! Return the current index.
    int currentIndex() const;

    //! Set default wrap behavior.
    void setWrapAround(bool wrapAround);

    //! Set current index. Clamp if out-of-range.
    void setCurrentIndex(int index);

    //! Set current index. Wrap around if out-of-range.
    void setCurrentIndexWrapAround(int index);

    //! Exits and pops the menu stack. The menu can call this
    //! also by itself.
    void exit();

private:

    void updateFocus();

    std::vector<MenuItem *> m_items;
    typedef std::shared_ptr<MenuItem> MenuItemPtr;
    typedef std::vector<MenuItemPtr> MenuItemVector;
    MenuItemVector m_ownedMenuItems;
    std::string m_id;
    int m_width, m_height;
    int m_currentIndex;
    int m_selectedIndex;
    MenuStyle m_style;
    bool m_done;
    bool m_wrapAround;
};

} // namespace MTFH

#endif // MENU_HPP