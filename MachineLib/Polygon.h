/**
 * @file Polygon.h
 *
 * @author Anik Momtaz
 * @author Charles Owen
 *
 * @version 1.06
 *
 * Generic polygon class that is used to make shapes we
 * will use in our project.
 *
 * Version history:
 * 1.00 Initial wxWidgets version
 * 1.01 Instrumented to indicate usage errors
 * 1.02 Fixed issue with instrumentation and testing
 * 1.03 Put into cse335 namespace, opacity support
 * 1.04 Added Circle function
 * 1.05 Special version that works with inverted Y axis
 * 1.06 Updated links to the new website
 */

#pragma once

#include <vector>
#include <memory>
#include <string>

namespace cse335 {

/**
 * Generic polygon class that is used to make shapes we
 * will use in our project.
 */
    class Polygon {
    private:
        /// Default number of steps when drawing a circle
        static const int DefaultCircleSteps = 32;

        void DrawColorPolygon(std::shared_ptr<wxGraphicsContext> graphics, double x, double y, double rotation);
        void DrawImagePolygon(std::shared_ptr<wxGraphicsContext> graphics, double x, double y, double rotation);

        /// Graphics path to use to draw
        wxGraphicsPath mPath;

        /// The points that make up the polygon
        std::vector<wxPoint2DDouble> mPoints;

        /// Set true if this polygon is a circle
        bool mIsCircle = false;

        /// A brush to draw the polygon with
        wxBrush mBrush;

        /// The display mode
        enum class Mode {
            Unset, Color, Image
        };

        /// The current mode
        Mode mMode = Mode::Unset;

        /// The basic texture image we load
        std::unique_ptr<wxImage> mImage;

        /// The graphics bitmap we actually draw
        wxGraphicsBitmap mGraphicsBitmap;

        /// The image clip region
        wxRegion mImageClipRegion;

        /// What is the top left point for the clip region?
        wxPoint2DDouble mImageClipRegionTopLeft;

        /// What is the size of the clip region?
        wxPoint2DDouble mImageClipRegionSize;

        /// Set true when DrawPolygon is called
        bool mHasDrawn = false;

        /// Opacity of the polygon - value range to 0 to 1
        double mOpacity = 1.0;

        /// Forces the bitmap to be reloaded
        bool mBitmapDirty = true;

#ifdef POLYGON_DEFAULT_INVERTEDY
        /// Is the Y axis inverted (positive Y is up)?
        bool mInvertedY = false;
#else
        /// Is the Y axis inverted (positive Y is up)?
        bool mInvertedY = false;
#endif

        bool Assert(bool condition, wxString msg, const wxString& url = wxEmptyString);

        //<editor-fold desc="Code to support the deferred assertion message box" defaultstate="collapsed">
        /**
         * Class to display an error message dialog box after a delay
         */
        class DelayedMessage : public wxTimer {
        private:
            void Notify() override;

            /// Message to display
            wxString mMessage;

            /// URL to display
            wxString mURL;

            /// We only allow this to fire one time
            bool mFired = false;

        public:
            DelayedMessage() {}
            void Fire(const wxString& msg, const wxString& url = wxEmptyString);
        };

        /// Delayed message object
        std::shared_ptr<DelayedMessage> mDelayedMessage;
        //</editor-fold>

    public:
        Polygon();

        virtual ~Polygon();

        /// Copy constructor (disabled)
        Polygon(const Polygon &) = delete;

        /// Assignment operator
        void operator=(const Polygon &) = delete;

        void AddPoint(double x, double y);

        void Rectangle(double x, double y, double width = 0, double height = 0);

        void Circle(double radius, int steps=DefaultCircleSteps);

        void CenteredSquare(double size = 0);

        void SetColor(wxColour color);

        void SetImage(std::wstring filename);

        void DrawPolygon(std::shared_ptr<wxGraphicsContext> graphics, double x, double y, double rotation=0);

        virtual void SetOpacity(double opacity);

        int GetImageWidth();

        int GetImageHeight();

        void BottomCenteredRectangle(double width = 0, double height = 0);

        /**
         * Create a rectangle concerned to the bottom
         * @param size Size of the rectangle to craete
         */
        void BottomCenteredRectangle(wxSize size) { BottomCenteredRectangle(size.x, size.y);}

        void
        DrawCrosshair(std::shared_ptr<wxGraphicsContext> graphics, double x, double y, int size = 10, wxColor color = *wxRED);

        double AverageLuminance(int x, int y, int wid, int hit);

        /**
         * Set if the Y axis is supposed to be inverted for this polygon.
         *
         * An inverted Y axis means the positive Y direction is up
         * @param inverted True if inverted Y axis is desired
         */
        void SetInvertedY(bool inverted) {mInvertedY = inverted;}

        /**
         * Is this polygon a circle? We treat a circle special
         * @return true if polygon is a circle
         */
        bool IsCircle() {return mIsCircle;}

        /**
         * Get the radius if this is a circle
         * @return Radius in the display units
         */
        double Radius() {return mPoints[0].m_x;}

        /**
         * Iterator begin function. Allows for iterating over the
         * vertices of the polygon.
         * @return Vertex iterator
         */
        std::vector<wxPoint2DDouble>::iterator begin() {return mPoints.begin();}

        /**
         * Iterator end function. Allows for iterating over the
         * vertices of the polygon.
         * @return Vertex iterator
         */
        std::vector<wxPoint2DDouble>::iterator end() {return mPoints.end();}

        wxPoint2DDouble Center();
        wxRect2DDouble BoundingBox();
    };


}
