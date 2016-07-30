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
	setSize (100, 240);
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

	// driver
	g.setColour (Colours::grey);
	g.fillEllipse (15.0f, 100.0f, 20.0f, 30.0f);

	// links
	g.setColour (Colours::black);
	g.drawHorizontalLine (50, 10.0f, getWidth () - 10.0f);
	g.drawHorizontalLine (190, 10.0f, getWidth () - 10.0f);
	
	// rear wheels
	g.fillRect (5, 170, 10, 40);
	g.fillRect (85, 170, 10, 40);

	// front wheels
	if (0 == direction)
	{
		g.fillRect (2, 30, 10, 40);
		g.fillRect (88, 30, 10, 40);
	}
	else if (-1 == direction)
	{
		g.drawLine (5.0f, 32.0f, 23.0f, 69.0f, 10.0f);
		g.drawLine (78.0f, 32.0f, 96.0f, 69.0f, 10.0f);
	}
	else if (1 == direction)
	{
		g.drawLine (23.0f, 32.0f, 5.0f, 69.0f, 10.0f);
		g.drawLine (96.0f, 32.0f, 78.0f, 69.0f, 10.0f);
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

