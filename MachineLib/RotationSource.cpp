/**
 * @file RotationSource.cpp
 * @author Thomas Conley
 */

#include "pch.h"
#include "RotationSource.h"
#include <cmath>

#include "IRotationSink.h"

RotationSource::RotationSource() {}

/**
 * Add a sink/component to the vector
 * @param sink
 */
void RotationSource::AddSink(std::shared_ptr<IRotationSink> sink)
{
    mSinks.push_back(sink);
}

/**
 * Set each sinks rotation
 * @param rotation
 */
void RotationSource::Rotate(double rotation)
{
    for (auto sink : mSinks)
    {
        sink->SetRotation(rotation);
        //sink->Advance(rotation);
    }
}