/*
  ==============================================================================

    Car.cpp
    Created: 29 Jul 2016 2:58:02pm
    Author:  mit2000

  ==============================================================================
*/

#include "CommonData.h"
#include "TrainingCar.h"

//==============================================================================
TrainingCar::TrainingCar ()
	: direction (0)
{
	setSize (CarWidth, CarLength);
}

//=================================================================================================
void TrainingCar::reset ()
{
    direction = 0;
    repaint ();
}

//=========================================================================
void TrainingCar::paint (Graphics& g)
{    
    // whole car
    g.setColour (Colours::lightseagreen);
    g.fillRoundedRectangle (getLocalBounds ().toFloat (), 15.0f);

    // border
    g.setColour (Colours::lightgrey);
    g.drawRoundedRectangle (getLocalBounds ().toFloat (), 15.0f, 0.5f);

    // an identity for forward direction
    g.setColour (Colours::lightgrey.withAlpha (0.45f));
    g.setFont (20.0f);
    g.drawSingleLineText ("S", getWidth() / 2 - 6, 30);
        
    // driver
    g.setColour (Colours::black.withAlpha (0.65f));
    g.fillEllipse (15.0f, 100.0f, 16.0f, 22.0f);

    // links
    g.drawHorizontalLine (45, 15.0f, getWidth () - 15.0f);
    g.drawHorizontalLine (190, 15.0f, getWidth () - 15.0f);

    // rear wheels
    g.fillRect (6, 170, 10, 40);
    g.fillRect (84, 170, 10, 40);

    // front wheels
    if (0 == direction)
    {
        g.fillRect (7, 25, 10, 40);
        g.fillRect (83, 25, 10, 40);
    }
    else if (-1 == direction)
    {
        g.drawLine (5.0f, 27.0f, 23.0f, 64.0f, 10.0f);
        g.drawLine (78.0f, 27.0f, 96.0f, 64.0f, 10.0f);
    }
    else if (1 == direction)
    {
        g.drawLine (23.0f, 27.0f, 5.0f, 64.0f, 10.0f);
        g.drawLine (96.0f, 27.0f, 78.0f, 64.0f, 10.0f);
    }
}

//=================================================================================================
void TrainingCar::setDirection (const int newDirection)
{
    const int oldFangxiang = direction;
    direction = newDirection;

    if (oldFangxiang != direction)
        repaint ();
}

