/**
 * @file Polygon.cpp
 *
 * @author Anik Momtaz
 * @author Charles Owen
 */

#include "pch.h"

#ifndef WIN32
#include <execinfo.h>
#endif

#include <sstream>
#include <wx/hyperlink.h>
#include <wx/generic/hyperlink.h>
#include "Polygon.h"

using namespace cse335;

/**
 * Constructor
 */
Polygon::Polygon() : mBrush(*wxBLACK)
{
}

/**
 * Destructor
 */
Polygon::~Polygon()
{
}

/**
 * Add a point to the polygon. Convenience version that accepts doubles.
 * @param x X value for point in the current display unit
 * @param y Y value for point in the current display unit
 */
void Polygon::AddPoint(double x, double y)
{
    if(mHasDrawn)
    {
        // Our polygon MUST have at least three points
        Assert(false,
               L"You cannot add points to the polygon after it has been drawn.",
               L"https://cse335.egr.msu.edu/polygon/o/");
        return;
    }

    mPoints.push_back(wxPoint2DDouble(x, y));
}


/**
 * Create a rectangle.
 *
 * If the height parameter is not supplied and an image
 * has been set, the height will be computed so as to
 * keep the original image aspect ratio correct.
 *
 * @param x Left side X
 * @param y Bottom left Y
 * @param width Width of the rectangle
 * @param height Height of the rectangle
 */
void Polygon::Rectangle(double x, double y, double width, double height)
{
    if(width <= 0)
    {
        // Optional automatic width determination from image
        if(!Assert(mImage != nullptr,
                   L"You must select an image before calling Rectangle with no specified width."))
        {
            return;
        }

        width = mImage->GetWidth();
    }

    if(height <= 0)
    {
        // Optional automatic height determination from image
        if(!Assert(mImage != nullptr,
                   L"You must select an image before calling Rectangle with no specified height."))
        {
            return;
        }

        height = (int)(width * mImage->GetHeight() / mImage->GetWidth());
    }

    if(mInvertedY)
    {
        AddPoint(x, y);
        AddPoint(x + width, y);
        AddPoint(x + width, y + height);
        AddPoint(x, y + height);
    }
    else
    {
        AddPoint(x, y);
        AddPoint(x, y - height);
        AddPoint(x + width, y - height);
        AddPoint(x + width, y);
    }
}

/**
 * Create a rectangle where 0,0 is the bottom center of the rectangle.
 *
 * Must set an image first if not providing a width and height.
 *
 * @param width Width of the rectangle in pixels. If not supplied, use the image width.
 * @param height Height of the rectangle in pixels. If not supplied, select a height such
 * that the aspect ratio matches that of the image.
 */
void Polygon::BottomCenteredRectangle(double width, double height)
{
    if(width == 0)
    {
        if(!Assert(mImage != nullptr,
                   L"You must select an image before calling BottomCenteredRectangle with no width."))
        {
            return;
        }

        width = GetImageWidth();
    }
    else if(height == 0)
    {
        if(!Assert(mImage != nullptr,
                   L"You must select an image before calling BottomCenteredRectangle with no height."))
        {
            return;
        }

        height = width * GetImageHeight() / GetImageWidth();
    }

    Rectangle(-width/2, 0, width, height);
}


/**
 * Create a centered square at location 0,0
 * @param size Width and height of the square
 */
void Polygon::CenteredSquare(double size)
{
    if(size == 0)
    {
        if(!Assert(mImage != nullptr,
                   L"You must select an image before calling BottomCenteredRectangle."))
        {
            return;
        }

        size = mImage->GetWidth();
    }

    if(mInvertedY)
    {
        Rectangle(-size / 2, -size / 2, size, size);
    }
    else
    {
        Rectangle(-size / 2, size / 2, size, size);
    }

}


/**
 * Create a circle centered on (0,0)
 * @param radius Circle radius
 * @param steps Number of steps in circle (0=default)
 */
void Polygon::Circle(double radius, int steps)
{
    mIsCircle = true;

    for (int i = 0; i < steps; i++)
    {
        double angle = double(i) / double(steps) * M_PI * 2;
        AddPoint(radius * cos(angle), radius * sin(angle));
    }
}


/**
 * Set the color of the polygon. If we set a color, images are not used.
 * @param color Color to set the polygon to
 */
void Polygon::SetColor(wxColour color)
{
    mBrush.SetColour(color);
    mMode = Mode::Color;
}

/**
 * Set an image we will use as a texture for the polygon
 * @param filename Image filename
 */
void Polygon::SetImage(std::wstring filename)
{
    // Prevent error popup from wxWidgets
    wxLogNull logNo;

    mImage = std::make_unique<wxImage>();
    if(mImage->LoadFile(filename, wxBITMAP_TYPE_ANY))
    {
        mMode = Mode::Image;
    }
    else
    {
        std::wstringstream str;
        str << L"Unable to load '" << filename << "'" << std::endl;
        wxMessageBox(str.str(), L"Polygon Image File Load Failure!");
        mImage = nullptr;
    }
}



/**
 * Draw the polygon
 * @param graphics Graphics object to draw on
 * @param x X location to draw in pixels
 * @param y Y location to draw in pixels
 * @param rotation Amount of rotation to apply to the polygon in turns (optional parameter)
 */
void Polygon::DrawPolygon(std::shared_ptr<wxGraphicsContext> graphics, double x, double y, double rotation)
{
    if(mPoints.size() < 3)
    {
        // Our polygon MUST have at least three points
        Assert(false,
               L"You must specify a shape when using Polygon. At least three points must be provided.",
               L"https://cse335.egr.msu.edu/polygon/c/");
        return;
    }

    mHasDrawn = true;

#ifndef WIN32
    if(mOpacity < 1)
    {
        // Layer opacity does not work on Windows systems.
        graphics->BeginLayer(mOpacity);
    }
#endif

    switch (mMode) {
        case Mode::Color:
            DrawColorPolygon(graphics, x, y, rotation);
            break;

        case Mode::Image:
            DrawImagePolygon(graphics, x, y, rotation);
            break;

        default:
            // If this assertion fails, the no color or image was
            // indicated for this polygon. Be sure to call
            Assert(false,
                   L"You must specify either a color or an image when using Polygon",
                   L"https://cse335.egr.msu.edu/polygon/c/");
            break;
    }

#ifndef WIN32
    if(mOpacity < 1)
    {
        graphics->EndLayer();
    }
#endif
}



/**
 * Draw the polygon as a solid color-filled polygon
 * @param graphics Graphics object to draw on
 * @param x X location to draw in pixels
 * @param y Y location to draw in pixels
 * @param rotation Amount of rotation to apply to the polygon in turns
 */
void Polygon::DrawColorPolygon(std::shared_ptr<wxGraphicsContext> graphics, double x, double y, double rotation)
{
    if(mPath.IsNull())
    {
        // Create the graphics path
        mPath = graphics->CreatePath();

        mPath.MoveToPoint(mPoints[0].m_x, mPoints[0].m_y);
        for(size_t i=1; i<mPoints.size(); i++)
        {
            mPath.AddLineToPoint(mPoints[i].m_x, mPoints[i].m_y);
        }
        mPath.CloseSubpath();
    }

    graphics->PushState();

    graphics->Translate(x, y);
    graphics->Rotate(rotation * M_PI * 2);

    graphics->SetBrush(mBrush);
    graphics->FillPath(mPath);

    graphics->PopState();
}

/**
 * Draw the polygon as a texture mapped image.
 *
 * This is accomplished by drawing the bitmap image clipped
 * by the supplied polygon points.
 *
 * @param graphics Graphics object to draw on
 * @param x X location to draw in pixels
 * @param y Y location to draw in pixels
 * @param rotation Amount of rotation to apply to the polygon in turns
 */
void Polygon::DrawImagePolygon(std::shared_ptr<wxGraphicsContext> graphics, double x, double y, double rotation)
{
    if(mBitmapDirty || mGraphicsBitmap.IsNull())
    {
#ifdef WIN32
        // Implementation of opacity for Windows systems.
        // Windows does not support transparency layers.
        if(mOpacity < 1) {
            // Ensure the image has an alpha map
            if (!mImage->HasAlpha()) {
                mImage->InitAlpha();
            }

            wxImage img = mImage->Copy();

            unsigned char *alpha = img.GetAlpha();
            for(int i=0; i<img.GetWidth()*img.GetHeight(); i++)
            {
                alpha[i] = int(alpha[i] * mOpacity);
            }

            mGraphicsBitmap = graphics->CreateBitmapFromImage(img);
        }
        else
        {
            mGraphicsBitmap = graphics->CreateBitmapFromImage(*mImage);
        }
#else
        mGraphicsBitmap = graphics->CreateBitmapFromImage(*mImage);
#endif

        //
        // Determine the top left and the size of the
        // region covered by our polygon
        //
        mImageClipRegionTopLeft = mPoints[0];
        auto imageClipRegionBottomRight = mPoints[0];

        for(auto point : mPoints)
        {
            if(point.m_x < mImageClipRegionTopLeft.m_x) {
                mImageClipRegionTopLeft.m_x = point.m_x;
            }

            if(point.m_y < mImageClipRegionTopLeft.m_y) {
                mImageClipRegionTopLeft.m_y = point.m_y;
            }

            if(point.m_x > imageClipRegionBottomRight.m_x) {
                imageClipRegionBottomRight.m_x = point.m_x;
            }

            if(point.m_y > imageClipRegionBottomRight.m_y) {
                imageClipRegionBottomRight.m_y = point.m_y;
            }
        }

        mImageClipRegionSize = imageClipRegionBottomRight - mImageClipRegionTopLeft;

        mImageClipRegion.Clear();
        std::vector<wxPoint> points;
        for(auto point : mPoints)
        {
            points.push_back(wxPoint(int(point.m_x - mImageClipRegionTopLeft.m_x + 0.5),
                                     int(point.m_y - mImageClipRegionTopLeft.m_y + 0.5)));
        }

        mImageClipRegion = wxRegion(points.size(), &points[0]);
        mBitmapDirty = false;
    }

    graphics->PushState();

    graphics->Translate(x, y);
    graphics->Rotate(rotation * M_PI * 2);

    graphics->Translate(mImageClipRegionTopLeft.m_x, mImageClipRegionTopLeft.m_y);
    graphics->Clip(mImageClipRegion);

    if(mInvertedY)
    {
        // Flip the bitmap upside down
        graphics->Scale(1, -1);
        graphics->DrawBitmap(mGraphicsBitmap, 0, -mImageClipRegionSize.m_y, mImageClipRegionSize.m_x, mImageClipRegionSize.m_y);
    }
    else
    {
        graphics->DrawBitmap(mGraphicsBitmap, 0, 0, mImageClipRegionSize.m_x, mImageClipRegionSize.m_y);
    }

    graphics->PopState();
}

/**
 * Convenience function to draw a crosshair.
 * @param graphics Graphics object to draw on
 * @param x X location for crosshair center
 * @param y Y location for crosshair center
 * @param size Size (width and height) of the crosshair in pixels (optional, default=
 * @param color Crosshair color (optional, default=red)
 */
void Polygon::DrawCrosshair(std::shared_ptr<wxGraphicsContext> graphics, double x, double y,
                            int size, wxColor color)
{
    wxPen pen(color);
    graphics->SetPen(pen);
    graphics->StrokeLine(x-size/2, y, x+size/2, y);
    graphics->StrokeLine(x, y-size/2, x, y+size/2);
}

/**
 * Get the width of any set image for this polygon. This may not be
 * the width we actually draw, but is the size of the polygon itself.
 * @return Width in pixels
 */
int Polygon::GetImageWidth()
{
    if(!Assert(mImage != nullptr, L"You must specify an image before you can call GetImageWidth()"))
    {
        return 0;
    }

    return mImage->GetWidth();
}


/**
 * Get the height of any set image for this polygon. This may not be
 * the height we actually draw, but is the size of the polygon itself.
 * @return Height in pixels
 */
int Polygon::GetImageHeight()
{
    if(!Assert(mImage != nullptr, L"You must specify an image before you can call GetImageHeight()"))
    {
        return 0;
    }

    return mImage->GetHeight();
}


/**
 * Assertion for Polygon that provides pop-up help.
 * @param condition Condition that is expected to the true.
 * @param msg Message that is provide if the condition is not true
 * @param url Optional URL to display with the error
 * @return Assertion condition result, true if condition is true
 */
bool Polygon::Assert(bool condition, wxString msg, const wxString &url)
{
    if(condition)
    {
        return true;
    }

    // Set a breakpoint on this line to determine where
    // in your code the error comes from.
    if(mDelayedMessage == nullptr)
    {
        mDelayedMessage = std::make_shared<DelayedMessage>();

    }

    msg += "\n \n";

#ifndef WIN32
    enum Constexpr { MAX_SIZE = 1024 };
    void *array[MAX_SIZE];
    size_t size = backtrace(array, MAX_SIZE);
    char **strings = backtrace_symbols(array, size);
    //std::shared_ptr<char *> strings(backtrace_symbols(array, size));
    if(size > 6)
    {
        size = 6;
    }

    for (int i = 2; i < size; i++)
    {
        msg += strings[i];
        msg += "\n";
    }
    free(strings);
#endif

    mDelayedMessage->Fire(msg, url);

    return false;
}

/**
 * Set the opacity of the polygon rendering.
 *
 * Currently only works for images.
 *
 * @param opacity Opacity from 0 to 1
 */
void Polygon::SetOpacity(double opacity)
{
    if(opacity != mOpacity)
    {
        if(!Assert(opacity >= 0 && opacity <= 1,
                   L"Values passed to Polygon::SetOpacity must be in the range 0 to 1."))
        {
            return;
        }

        // We have an opacity change
        mOpacity = opacity;
#ifdef WIN32
        mBitmapDirty = true;
#endif
    }
}


/**
 * Get the average luminance of a block of pixels in a supplied image.
 * @param x Top left X in pixels
 * @param y Top left Y in pixels
 * @param wid Width of the block to average
 * @param hit Height of the block to average
 * @return Luminance in the range 0-1, where 0 is black.
 */
double Polygon::AverageLuminance(int x, int y, int wid, int hit)
{
    assert(mMode == Mode::Image);

    double sum = 0;
    int cnt = 0;

    for (int i = x; i < x + wid; i++)
    {
        if (i < 0 || i >= GetImageWidth())
        {
            continue;
        }

        for (int j = y; j < y + hit; j++)
        {
            if (j < 0 || j >= GetImageHeight())
            {
                continue;
            }

            double red = mImage->GetRed(i, j);
            double grn = mImage->GetGreen(i, j);
            double blu = mImage->GetBlue(i, j);
            sum += red + grn + blu;
            cnt += 3;
        }
    }

    if (cnt == 0)
    {
        return 0;
    }

    return (sum / cnt) / 255.0;
}

/**
 * Get the center point for the polygon
 * @return Center point (average of all points)
 */
wxPoint2DDouble Polygon::Center()
{
    if(mPoints.size() < 3)
    {
        // Our polygon MUST have at least three points
        Assert(false,
               L"You must specify a shape when using Polygon. At least three points must be provided.",
               L"https://cse335.egr.msu.edu/polygon/c/");
        return wxPoint2DDouble();
    }

    if(mIsCircle)
    {
        return wxPoint2DDouble(0, 0);
    }

    wxPoint2DDouble center;
    for(auto v : mPoints)
    {
        center += v;
    }

    center = center / (int)mPoints.size();

    return center;
}

/**
 * Get a bounding box that encloses the entire polygon
 * @return Bounding box
 */
wxRect2DDouble Polygon::BoundingBox()
{
    if(mPoints.size() < 3)
    {
        // Our polygon MUST have at least three points
        Assert(false,
               L"You must specify a shape when using Polygon. At least three points must be provided.",
               L"https://cse335.egr.msu.edu/polygon/c/");
        return wxRect2DDouble();
    }

    if(mIsCircle)
    {
        auto radius = Radius();
        return wxRect2DDouble(-radius, -radius, radius*2, radius*2);
    }

    auto p1x = mPoints[0].m_x;
    auto p1y = mPoints[0].m_y;

    wxRect2DDouble box(p1x, p1y, 0, 0);

    for(auto v : mPoints)
    {
        box.Union(v);
    }

    return box;
}


//editor-fold desc="Code to support the deferred assertion message box" defaultstate="collapsed">

/**
 * Fire a message display after a delay. This is done since it is not
 * possible to bring up a dialog box in a Draw function, which is
 * where most errors occur.
 * @param msg Message to display
 * @param url Optional URL for help
 */
void Polygon::DelayedMessage::Fire(const wxString& msg, const wxString& url) {
    if(mFired)
    {
        return;
    }

    mMessage = msg;
    mURL = url;
    auto ret = Start(10, wxTIMER_ONE_SHOT);
    //mFired = true;
}


/**
 * Handle the timer event so we can display the dialog box.
 */
void Polygon::DelayedMessage::Notify()
{
    mFired = true;

    wxDialog dialog(wxTheApp->GetTopWindow(), wxID_ANY, L"Polygon Class Usage Error");

    dialog.SetSizeHints( wxDefaultSize, wxDefaultSize );

    auto sizer = new wxBoxSizer( wxVERTICAL );

    auto m_staticText1 = new wxStaticText( &dialog, wxID_ANY, mMessage, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
    m_staticText1->Wrap( 300 );
    sizer->Add( m_staticText1, 0, wxALL|wxEXPAND, 15 );

    if(!mURL.IsEmpty())
    {
        auto m_staticText2 = new wxGenericHyperlinkCtrl( &dialog, wxID_ANY, mURL, mURL, wxDefaultPosition, wxDefaultSize );
        sizer->Add( m_staticText2, 0, wxALL|wxEXPAND, 5 );
    }

    auto m_button1 = new wxButton( &dialog, wxID_OK, wxT("Ok"), wxDefaultPosition, wxDefaultSize, 0 );
    sizer->Add( m_button1, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );


    dialog.SetSizer( sizer );
    dialog.Layout();
    sizer->Fit( &dialog );

    dialog.Centre(wxBOTH);
    dialog.ShowModal();
}
///editor-fold>

