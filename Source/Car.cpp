/*
  ==============================================================================

    Car.cpp
    Created: 29 Jul 2016 2:58:02pm
    Author:  mit2000

  ==============================================================================
*/

#include "Car.h"
#include "MainComponent.h"
#include "CommonData.h"

//==============================================================================
Car::Car (MainContentComponent* mainComp_)
	: mainComp (mainComp_),
	fangxiang (0)
{
	setSize (100, 240);
}

//=================================================================================================
void Car::reset ()
{
    fangxiang = 0;
    repaint ();
}

//=========================================================================
void Car::paint (Graphics& g)
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
	if (0 == fangxiang)
	{
		g.fillRect (2, 30, 10, 40);
		g.fillRect (88, 30, 10, 40);
	}
	else if (-1 == fangxiang)
	{
		g.drawLine (5.0f, 32.0f, 23.0f, 69.0f, 10.0f);
		g.drawLine (78.0f, 32.0f, 96.0f, 69.0f, 10.0f);
	}
	else if (1 == fangxiang)
	{
		g.drawLine (23.0f, 32.0f, 5.0f, 69.0f, 10.0f);
		g.drawLine (96.0f, 32.0f, 78.0f, 69.0f, 10.0f);
	}
}

//=================================================================================================
void Car::mouseUp (const MouseEvent& e)
{
    // todo...
	const int oldFangxiang = fangxiang;

	if (e.mods.isLeftButtonDown ())
		fangxiang = -1;
	else if (e.mods.isRightButtonDown ())
		fangxiang = 1;
	else if (e.mods.isMiddleButtonDown ())
		fangxiang = 0;

	mainComp->placeTheCar (oldFangxiang, fangxiang);

	if (oldFangxiang != fangxiang)
		repaint ();
}

//=================================================================================================
void Car::mouseWheelMove (const MouseEvent& /*event*/, const MouseWheelDetails& wheel)
{
	move (wheel.deltaY > 0);
}

//=================================================================================================
void Car::move (const bool backward)
{
    //todo...

    if (0 == fangxiang)  // straight forward
    {
        const int dist (backward ? StraightStep : -StraightStep);
        setTopLeftPosition (getX(), getY() + dist);

        Component* leftPole (mainComp->getPlacer (true));
        Component* rightPole (mainComp->getPlacer (false));

        leftPole->setTopLeftPosition (leftPole->getX(), leftPole->getY() + dist);
        rightPole->setTopLeftPosition (rightPole->getX(), rightPole->getY() + dist);
    }
    else if (-1 == fangxiang) // -1 is turn left
    {
        mainComp->moveTheCar (backward, true);
    }
    else  // 1 is turn right
    {
        mainComp->moveTheCar (!backward, false);
    }
}

