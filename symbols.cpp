#include "symbols.h"
#include <iostream>

bool drawSymbol(QString symbol, quint32 fontSize)
{
    try {
        QFont font("Consolas");
        font.setPixelSize(fontSize);
        font.setStyleHint(QFont::Monospace, QFont::PreferBitmap);
        font.setFixedPitch(true);

        QTextOption option;
        option.setAlignment(Qt::AlignLeft);

        // need only to obtain correct perfectRect
        QImage dummyImg(200, 200, QImage::Format_RGB666);
        QPainter painter;

        painter.begin(&dummyImg);
        painter.setFont(font);
        painter.setPen(Qt::white);  // color of symbol - white on black background
        // rect size should be big enaught to fit symbol
        const auto perfectRect = painter.boundingRect(QRectF(0, 0, 1000, 1000), symbol, option);
        painter.end();

        QImage img(perfectRect.size().toSize(), QImage::Format_RGB666);
        img.setColorCount(24);
        img.fill(Qt::black);

        painter.begin(&img);
        painter.setFont(font);
        painter.setPen(Qt::white);  // color of symbol - white on black background
        painter.drawText(perfectRect, Qt::AlignLeft, symbol);
        painter.end();

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
