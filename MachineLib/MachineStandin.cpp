/**
 * @file MachineStandin.cpp
 *
 * @author Charles Owen
 *
 * DO NOT CHANGE THIS FILE!
 */

#include "pch.h"
#include "MachineStandin.h"
#include <sstream>


/**
 * Constructor
 */
MachineStandin::MachineStandin()
{
}


/**
* Draw the machine at the currently specified location
* @param graphics Graphics object to render to
*/
void MachineStandin::DrawMachine(std::shared_ptr<wxGraphicsContext> graphics)
{
    const int LineSize = 18;
    const int LineSpacing = 22;

    wxPen pen(wxColour(139, 69, 19), 1);
	const int StandinWidth = 300;
	const int StandinHeight = 200;

    graphics->SetPen(pen);
    graphics->SetBrush(*wxTRANSPARENT_BRUSH);
	graphics->DrawRectangle((mX - StandinWidth/2), (mY - StandinHeight),
            StandinWidth, StandinHeight);

    graphics->SetPen(*wxBLACK_PEN);
    graphics->StrokeLine(mX - 10, mY - 10, mX + 10, mY + 10);
    graphics->StrokeLine(mX + 10, mY - 10, mX - 10, mY + 10);

    wxFont coordFont(wxSize(0, 10),
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL);
    graphics->SetFont(coordFont, *wxWHITE);
    std::wstringstream str;
    str << L"(" << mX << L"," << mY << L")";
    graphics->DrawText(str.str(), mX + 15, mY - 10);

	const int OuterRadius = 90;
	const int InnerRadius = 80;
	const int NumTeeth = 20;

	const int GearX = 0;
	const int GearY = -StandinHeight / 2;

    wxPen gearPen(wxColour(0, 128, 0));
    graphics->SetPen(gearPen);

	int x = mX + GearX;
	int y = mY + GearY;

	for (int i = 0; i < NumTeeth; i++)
	{
		double angle1 = i * 2 * M_PI / NumTeeth;
		double angle2 = (i + 0.5) * 2 * M_PI / NumTeeth;
		double angle3 = (i + 1.0) * 2 * M_PI / NumTeeth;

		graphics->StrokeLine((x + OuterRadius * cos(angle1)), (y + OuterRadius * sin(angle1)),
			(x + OuterRadius * cos(angle2)), (y + OuterRadius * sin(angle2)));
		graphics->StrokeLine((x + OuterRadius * cos(angle2)), (y + OuterRadius * sin(angle2)),
			(x + InnerRadius * cos(angle2)), (y + InnerRadius * sin(angle2)));
		graphics->StrokeLine((x + InnerRadius * cos(angle2)), (y + InnerRadius * sin(angle2)),
			(x + InnerRadius * cos(angle3)), (y + InnerRadius * sin(angle3)));
		graphics->StrokeLine((x + InnerRadius * cos(angle3)), (y + InnerRadius * sin(angle3)),
			(x + OuterRadius * cos(angle3)), (y + OuterRadius * sin(angle3)));

	}


    y = mY - LineSize * 3.5;
    CenteredString(graphics, L"Machine goes here!", mX, y, LineSize);
    y -= LineSpacing;

    {
        std::wstringstream str1;
        str1 << L"Machine: " << mMachine << std::ends;
        CenteredString(graphics, str1.str(), mX, y, LineSize);
        y -= LineSpacing;
    }

    {
        std::wstringstream str1;
        str1 << L"Frame: " << mFrame << std::ends;
        CenteredString(graphics, str1.str(), mX, y, LineSize);
        y -= LineSpacing;
    }

}


/**
 * Draw a centered string
 *
 * @param graphics Graphics object
 * @param str String to draw
 * @param x X location of bottom center of string
 * @param y Y location of bottom center of string
 * @param dy String height
 */
void MachineStandin::CenteredString(std::shared_ptr<wxGraphicsContext> graphics, const std::wstring &str, int x, int y, int dy)
{
    y -= dy;

    wxFont font(wxSize(0, dy),
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL);
    graphics->SetFont(font, *wxWHITE);

    double width, height;
    graphics->GetTextExtent(str, &width, &height);
    graphics->DrawText(str, x - width/2, y);
}