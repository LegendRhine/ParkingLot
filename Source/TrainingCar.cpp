/*
  ==============================================================================

    Car.cpp
    Created: 29 Jul 2016 2:58:02pm
    Author:  mit2000

  ==============================================================================
*/

#include "CommonData.h"
#include "ParkingLot.h"
#include "TrainingCar.h"

//==============================================================================
TrainingCar::TrainingCar (ParkingLot* park)
	: parkingLot (park),
    fromInnerWheel (0.f),
    eachHudu (0.f),
    turningAngle (0)
{
	setSize (CarWidth, CarLength);
}

//=================================================================================================
void TrainingCar::reset ()
{
    turningAngle = 0;
    repaint ();
}

//=========================================================================
void TrainingCar::paint (Graphics& g)
{    
    // whole car
    g.setColour (Colours::lightseagreen);
    g.fillRoundedRectangle (getLocalBounds ().toFloat (), 15.0f);

    // border
    g.setColour (Colours::grey);
    g.drawRoundedRectangle (getLocalBounds ().toFloat (), 15.0f, 1.0f);

    // an identity for forward direction
    g.setColour (Colours::lightgrey.withAlpha (0.45f));
    g.setFont (20.0f);
    g.drawSingleLineText ("S", getWidth() / 2 - 6, 30);
        
    // driver
    g.setColour (Colours::black.withAlpha (0.65f));
    g.fillEllipse (15.0f, 100.0f, 16.0f, 22.0f);

    // links
    g.drawHorizontalLine (50, 15.0f, getWidth () - 15.0f);
    g.drawHorizontalLine (190, 15.0f, getWidth () - 15.0f);

    // rear wheels
    g.fillRect (6, 170, 10, 40);
    g.fillRect (84, 170, 10, 40);

    // this line repersent 2 front wheels
    Line<float> leftWheel (12.f, 30.f, 12.f, 30.f + 40);
    Line<float> rightWheel (getWidth() - 12.f, 30.f, getWidth() - 12.f, 30.f + 40);

    // turning the wheel
    const float turningHudu = float_Pi / 180.f * turningAngle;

    leftWheel.applyTransform (AffineTransform::rotation (turningHudu, 14.f, 50.f));
    rightWheel.applyTransform (AffineTransform::rotation (turningHudu, getWidth() - 14.f, 50.f));

    // front wheels
    g.drawLine (leftWheel, 10.f);
    g.drawLine (rightWheel, 10.f);
}

//=================================================================================================
void TrainingCar::mouseDrag (const MouseEvent& e)
{
    DragAndDropContainer* dc = dynamic_cast<DragAndDropContainer*>(getParentComponent());

    if (dc != nullptr)
        dc->startDragging (var (e.getPosition().toString()), this);
}

//=================================================================================================
void TrainingCar::mouseDoubleClick (const MouseEvent & e)
{
    const int oldAngle = turningAngle;

    if (e.mods.isLeftButtonDown())
    {
        turningAngle = -33;
    }
    else if (e.mods.isRightButtonDown())
    {
        turningAngle = 33;
    }

    if (oldAngle != turningAngle)
        afterSetAngle (true);
}

//=================================================================================================
void TrainingCar::mouseUp (const MouseEvent& e)
{
    if (e.mouseWasClicked())
    {
        const int oldAngle = turningAngle;

        if (e.mods.isLeftButtonDown())
            turningAngle = jmax (turningAngle - 3, -33);

        else if (e.mods.isRightButtonDown())
            turningAngle = jmin (turningAngle + 3, 33);

        else if (e.mods.isMiddleButtonDown())
            turningAngle = 0;

        if (oldAngle != turningAngle)
            afterSetAngle (true);
    }
}

//=================================================================================================
void TrainingCar::afterSetAngle (const bool shouldRepaintParent)
{
    repaint();

    if (turningAngle != 0)
        fromInnerWheel = Zhouju / std::sin (float_Pi / 180.f * std::abs (turningAngle)) - 150.f;
    else
        fromInnerWheel = 0.f;

    // set current hudu
    for (int i = 3; i <=33; i += 3)
    {
        if (i == std::abs (turningAngle))
        {
            eachHudu = 0.018f / 33.f * i;
            break;
        }
    }

    if (shouldRepaintParent)
    {
        parkingLot->placeAfterSetDirection (turningAngle);
        parkingLot->repaint(); // for real-time change forecast-lines
    }
}

//=================================================================================================
void TrainingCar::mouseWheelMove (const MouseEvent& event, const MouseWheelDetails& wheel)
{
    if (getParentComponent() != nullptr)
        getParentComponent()->mouseWheelMove (event, wheel);
}

//=================================================================================================
void TrainingCar::setTurningAngle (const int newAngle, const bool shouldTellParentRepaint)
{
    turningAngle = newAngle;
    afterSetAngle (shouldTellParentRepaint);
}


