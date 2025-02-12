/**
 * @file Cylinder.h
 * @author Charles Owen
 *
 * @version 1.00
 *
 * Simple cylinder class that is used by the shaft, pulleys, and
 * anything else that needs a cylinder that expresses rotation.
 */

#ifndef _CYLINDER_H
#define _CYLINDER_H

namespace cse335
{

/**
 * Simple rod class that is used by the shaft and
 * anything else that needs a rod that expresses rotation.
 */
class Cylinder
{
private:
    /// Cylinder diameter
    int mDiameter = 0;

    /// Cylinder length
    int mLength = 0;

    /// The color to draw the cylinder
    wxColour mColor = *wxWHITE;

    /// The color to draw the border around the cylinder
    wxColour mBorderColor = *wxBLACK;

    /// The color to draw the moving lines on the cylinder
    wxColour mLineColor = *wxBLACK;

    /// The width to draw the moving lines
    int mLineWidth = 1;

    /// Number of lines to draw
    int mNumLines = 0;

    /// Offset to prevent the lines from all lining up
    double mOffset = 0;

public:
    /**
     * Constructor
     */
    Cylinder() = default;

    /// Copy constructor (disabled)
    Cylinder(const Cylinder &) = delete;

    /// Assignment operator
    void operator=(const Cylinder &) = delete;

    /**
     * Set the cylinder size
     * @param diameter Cylinder diameter in pixels
     * @param length Cylinder length in pixels
     */
    void SetSize(int diameter, int length)
    {
        mDiameter = diameter;
        mLength = length;
    }

    /**
     * Set the cylinder color
     * @param color Color to draw the cylinder
     */
    void SetColour(const wxColour &color) { mColor = color; }

    /**
     * Set the border color drawn around the cylinder
     * @param color Color to set
     */
    void SetBorderColor(const wxColour &color) {mBorderColor = color;}

    /**
     * Set lines that appear on the cylinder that show it is turning
     * @param color Color of the lines
     * @param width How wide to draw the lines
     * @param num Number of lines to draw
     */
    void SetLines(const wxColour &color, int width, int num)
    {
        mLineColor = color;
        mLineWidth = width;
        mNumLines = num;
    }

    /**
     * Optional offset added to the rotation of the lines.
     *
     * This is provided so you can avoid them all looking the
     * exact same with the lines at the same angle. This makes
     * it look a bit more realistic.
     *
     * @param offset
     */
    void SetOffset(double offset) {mOffset = offset;}

    void Draw(const std::shared_ptr<wxGraphicsContext> &graphics, double x, double y, double rotation);
};

}
#endif //_CYLINDER_H
