// This file is part of Dust Rallycross (DustRAC).
// Copyright (C) 2011 Jussi Lind <jussi.lind@iki.fi>
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

#include <QPainter>
#include "mwwidget.h"

MWWidget::MWWidget(QSizeF size, MWWidget * parent) :
    m_parent(parent),
    m_size(size),
    m_cm({1, 1, 1, 1}),
    m_bgColor(QColor(0, 0, 0, 0)),
    m_bgColor0(QColor(0, 0, 0, 0)),
    m_bgColorPressing(QColor(0, 0, 0, 0)),
    m_clickable(false),
    m_pressing(false)
{
    if (parent)
    {
        setPos(parent->pos());

        if (parent->size().height() < m_size.height())
            m_size.setHeight(parent->size().height());

        if (parent->size().width() < m_size.width())
            m_size.setWidth(parent->size().width());
    }
}

QRectF MWWidget::boundingRect () const
{
    return QRectF(-m_size.width() / 2,
                  -m_size.height() / 2,
                  m_size.width(),
                  m_size.height());
}

void MWWidget::paintBackground(QPainter * painter,
                               const QStyleOptionGraphicsItem * option,
                               QWidget * widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    painter->fillRect(boundingRect(), m_bgColor);
}

void MWWidget::paint(QPainter * painter, const QStyleOptionGraphicsItem * option,
                     QWidget * widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    paintBackground(painter, option, widget);
}

void MWWidget::setContentsMargins(int left, int right, int top, int bottom)
{
    m_cm[0] = left;
    m_cm[1] = right;
    m_cm[2] = top;
    m_cm[3] = bottom;
}

void MWWidget::getContentsMargins(int & left, int & right, int & top, int & bottom) const
{
    left   = m_cm[0];
    right  = m_cm[1];
    top    = m_cm[2];
    bottom = m_cm[3];
}

QSizeF MWWidget::size() const
{
    return m_size;
}

void MWWidget::setBgColor(QColor color)
{
    m_bgColor         = color;
    m_bgColor0        = color;

    int newR = color.red() * 2;
    newR = newR > 255 ? 255 : newR;
    int newG = color.green() * 2;
    newG = newG > 255 ? 255 : newG;
    int newB = color.blue() * 2;
    newB = newB > 255 ? 255 : newB;
    int newA = color.alpha();

    m_bgColorPressing = QColor(newR, newG, newB, newA);
    update();
}

QColor MWWidget::bgColor() const
{
    return m_bgColor;
}

void MWWidget::setClickable(bool enable)
{
    m_clickable = enable;
}

bool MWWidget::clickable() const
{
    return m_clickable;
}

void MWWidget::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    if (m_clickable)
    {
        m_pressing = true;
        m_bgColor  = m_bgColorPressing;
        update();
    }
}

void MWWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
    if (m_clickable && m_pressing)
    {
        m_pressing = false;
        m_bgColor  = m_bgColor0;
        emit clicked();
        update();
    }
}