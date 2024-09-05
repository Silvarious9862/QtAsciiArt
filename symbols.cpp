#include "symbols.h"
#include <iostream>

bool drawSymbol(QString symbol)
{
    try {
        QImage img(15, 15, QImage::Format_RGB666);  // create an image
        img.setColorCount(24);  // set bitcount
        img.fill(Qt::black);    // fill white
        QPainter painter(&img);       // painter obj

        QFont font("Consolas", 25);
        painter.setFont(font);  // using font consolas 10

        QRectF rectangle;
        rectangle.setCoords(0,0,15,15);

        painter.setPen(Qt::white);
        painter.drawText(rectangle, Qt::AlignCenter, symbol);

        QString filename = "symbol.bmp";
        img.save(filename);
    }
    catch(std::exception& ex)
    {
        std::cerr << ex.what() << "\n";
        return false;
    }
    return true;
}
