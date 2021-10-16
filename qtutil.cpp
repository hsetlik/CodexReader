#include "qtutil.h"


QColor MyQtUtil::colorLerp(const QColor& colorA, const QColor& colorB, float p)
{
    auto greaterRed = (colorA.red() > colorB.red()) ? colorA.red() : colorB.red();
    auto lesserRed = (colorA.red() > colorB.red()) ? colorB.red() : colorA.red();
    auto greaterGreen = (colorA.green() > colorB.green()) ? colorA.green() : colorB.green();
    auto lesserGreen = (colorA.green() > colorB.green()) ? colorB.green() : colorA.green();
    auto greaterBlue = (colorA.blue() > colorB.blue()) ? colorA.blue() : colorB.blue();
    auto lesserBlue = (colorA.blue() > colorB.blue()) ? colorB.blue() : colorA.blue();
    auto greaterAlpha = (colorA.alpha() > colorB.alpha()) ? colorA.alpha() : colorB.alpha();
    auto lesserAlpha = (colorA.alpha() > colorB.alpha()) ? colorB.alpha() : colorA.alpha();
    auto newRed = lesserRed + ((float)(greaterRed - lesserRed) * p);
    auto newGreen = lesserGreen + ((float)(greaterGreen - lesserGreen) * p);
    auto newBlue = lesserBlue + ((float)(greaterBlue - lesserBlue) * p);
    auto newAlpha = lesserAlpha + ((float)(greaterAlpha - lesserAlpha) * p);
    return QColor (newRed, newGreen, newBlue, newAlpha);
}
