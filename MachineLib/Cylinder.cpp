/**
 * @file Cylinder.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include "Cylinder.h"

namespace cse335
{


/**
 * Draw the cylinder
 *
 * The X coordinate is the left side of the cylinder.
 * The Y coordinate is the center of the cylinder horizontally.
 *
 * @param graphics Graphics device to draw on
 * @param x X location of left center end of cylinder
 * @param y Y location of left center end of cylinder
 * @param rotation Current rotation angle in turns
 */
void Cylinder::Draw(const std::shared_ptr<wxGraphicsContext> &graphics, double x, double y, double rotation)
{
    wxBrush cylinderBrush(mColor);
    graphics->SetBrush(cylinderBrush);
    if(mBorderColor != wxTRANSPARENT)
    {
        wxPen cylinderPen(mBorderColor);
        graphics->SetPen(cylinderPen);
    }
    else
    {
        graphics->SetPen(*wxTRANSPARENT_PEN);
    }

    // Draw the rod
    graphics->DrawRectangle(x, y - mDiameter / 2.0, mLength, mDiameter);

    // The current cylinder rotation angle including the offset in radians
    double angle = (rotation + mOffset) * M_PI * 2.0;    // In radians

    if(mNumLines > 0)
    {
        // The lines we'll draw
        wxPen linePen(mLineColor, mLineWidth);
        linePen.SetCap(wxCAP_BUTT);
        graphics->SetPen(linePen);

        for(int i = 0; i < mNumLines; i++)
        {
            double s = sin(angle);
            double c = cos(angle);

            if(c > 0)       // Test if on the visible side
            {
                double y2 = y - s * (mDiameter - mLineWidth) / 2;
                graphics->StrokeLine(x + 1, y2, x + mLength, y2);
            }

            angle += M_PI * 2 / mNumLines;
        }

    }

}

}
