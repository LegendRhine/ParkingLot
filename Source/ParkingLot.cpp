/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "ParkingLot.h"
#include "TrainingCar.h"
#include "CommonData.h"

//==============================================================================
ParkingLot::ParkingLot()
	: pathHudu (0.0f)
{
	addAndMakeVisible (car = new TrainingCar());
    addChildComponent (leftPlacer = new PolePlacer());
    addChildComponent (rightPlacer = new PolePlacer());

    setSize (1200, 800);
}

ParkingLot::~ParkingLot()
{
}
//=========================================================================
void ParkingLot::paint (Graphics& g)
{
    g.fillAll (Colours::darkgrey);

	/*g.setColour (Colours::darkred);
	g.fillRect (car->getBounds ().expanded (8));

	g.setColour (Colours::darkgoldenrod);
	g.fillRect (car->getBoundsInParent ().expanded (5));	*/
}
//=========================================================================
void ParkingLot::resized ()
{
    pathHudu = 0.0f;

    car->setTransform (AffineTransform());
	car->setCentreRelative (0.5f, 0.5f);
    car->reset();

    leftPlacer->setTransform (AffineTransform());
    leftPlacer->setCentrePosition (car->getX() - FromInnerWheel, car->getY() + 190);
    leftPlacer->setVisible (false);

    rightPlacer->setTransform (AffineTransform());
    rightPlacer->setCentrePosition (car->getRight() + FromInnerWheel, car->getY() + 190);
    rightPlacer->setVisible (false);

    getCurrentCheckPoints();
}

//=================================================================================================
void ParkingLot::setDirection (const int newDirection)
{
    const int oldFangxiang = car->getDirection();

    car->setDirection (newDirection);
    placeTheCar (oldFangxiang, newDirection);

    if (newDirection == 0)
    {
        leftPlacer->setVisible (false);
        rightPlacer->setVisible (false);
    }
    else if (newDirection == -1)
    {
        leftPlacer->setVisible (true);
        rightPlacer->setVisible (false);

        leftPlacer->toFront(false);
    }
    else if (newDirection == 1)
    {
        leftPlacer->setVisible (false);
        rightPlacer->setVisible (true);

        rightPlacer->toFront(false);
    }
}

//=================================================================================================
void ParkingLot::placeTheCar (const int oldFangxiang, const int newFangxiang)
{
    if (newFangxiang != 0 && oldFangxiang != newFangxiang)  
    {
        int centerX = 0;
        int centerY = 0;
        AffineTransform aft;

        // First, place the car base on the matches placer, then transform the car. 
        // the pole base on the placer.
        // second, place two placer base on the car, then transform them.
        if (newFangxiang == -1)
        {
            centerX = leftPlacer->getBoundsInParent().getCentreX() + FromInnerWheel + 50;
            centerY = leftPlacer->getBoundsInParent().getCentreY() - 70;
            aft = AffineTransform::rotation (pathHudu,
                centerX - FromInnerWheel - 50.0000001f, centerY + 70.0000001f);
        }
        else
        {
            centerX = rightPlacer->getBoundsInParent().getCentreX() - FromInnerWheel - 50;
            centerY = rightPlacer->getBoundsInParent().getCentreY() - 70;
            aft = AffineTransform::rotation (pathHudu,
                centerX + FromInnerWheel + 50.0000001f, centerY + 70.0000001f);
        }

        car->setCentrePosition (centerX, centerY);
        leftPlacer->setCentrePosition (car->getX() - FromInnerWheel, car->getY() + 190);
        rightPlacer->setCentrePosition (car->getRight() + FromInnerWheel, car->getY() + 190);

        car->setTransform (aft);
        leftPlacer->setTransform (aft);
        rightPlacer->setTransform (aft);
    }
}

//=================================================================================================
void ParkingLot::mouseUp (const MouseEvent& e)
{
    if (e.mods.isLeftButtonDown())
        setDirection (-1);
    else if (e.mods.isRightButtonDown())
        setDirection (1);
    else if (e.mods.isMiddleButtonDown())
        setDirection (0);
}

//=================================================================================================
void ParkingLot::mouseWheelMove (const MouseEvent&, const MouseWheelDetails& wheel)
{
    moveTheCar (wheel.deltaY > 0);
}

//=================================================================================================
void ParkingLot::moveTheCar (const bool backward)
{
    if (0 == car->getDirection())  // straight forward
    {
        const int dist (backward ? StraightStep : -StraightStep);
        car->setTopLeftPosition (car->getX(), car->getY() + dist);

        leftPlacer->setTopLeftPosition (leftPlacer->getX(), leftPlacer->getY() + dist);
        rightPlacer->setTopLeftPosition (rightPlacer->getX(), rightPlacer->getY() + dist);
    }
    else if (-1 == car->getDirection()) // -1 is turn left
    {
        turnDirection (backward, true);
    }
    else  if (1 == car->getDirection()) // 1 is turn right
    {
        turnDirection (!backward, false);
    }

    getCurrentCheckPoints();

    // check crash...
    if (isCrashed())
    {
        if (AlertWindow::showNativeDialogBox ("Warning", "Crashed!!", true))
            moveTheCar (!backward);
        else
            reset();
    }
}

//=================================================================================================
const bool ParkingLot::isCrashed ()
{
    AffineTransform atf (car->getTransform());

    for (int i = checkPoints.size(); --i >= 0; )
    {
        Point<int> p (checkPoints[i].transformedBy (atf));
        Component* comp = getComponentAt (p);

        if (!contains (p) || (comp != nullptr && comp != this))
            return true;
    }

    return false;
}

//=================================================================================================
void ParkingLot::getCurrentCheckPoints ()
{
    checkPoints.clearQuick();

    // add 24 points of the car for crash-check
    const int x = car->getX();
    const int y = car->getY();
    const int w = car->getWidth();
    const int h = car->getHeight();
    const int r = car->getRight();
    const int b = car->getBottom();

    // 4 conners
    checkPoints.add (Point<int> (x, y - 1));
    checkPoints.add (Point<int> (r, y - 1));
    checkPoints.add (Point<int> (r, b + 1));
    checkPoints.add (Point<int> (x, b + 1));

    // 4 sides
    checkPoints.add (Point<int> (x + w / 4, y - 1));
    checkPoints.add (Point<int> (x + w / 2, y - 1));
    checkPoints.add (Point<int> (r - w / 4, y - 1));

    checkPoints.add (Point<int> (x + w / 4, b + 1));
    checkPoints.add (Point<int> (x + w / 2, b + 1));
    checkPoints.add (Point<int> (r - w / 4, b + 1));

    checkPoints.add (Point<int> (x - 1, y + h / 8));
    checkPoints.add (Point<int> (x - 1, y + h / 4));
    checkPoints.add (Point<int> (x - 1, y + h * 3 / 8));
    checkPoints.add (Point<int> (x - 1, y + h / 2));
    checkPoints.add (Point<int> (x - 1, b - h * 3 / 8));
    checkPoints.add (Point<int> (x - 1, b - h / 4));
    checkPoints.add (Point<int> (x - 1, b - h / 8));

    checkPoints.add (Point<int> (r + 1, y + h / 8));
    checkPoints.add (Point<int> (r + 1, y + h / 4));
    checkPoints.add (Point<int> (r + 1, y + h * 3 / 8));
    checkPoints.add (Point<int> (r + 1, y + h / 2));
    checkPoints.add (Point<int> (r + 1, b - h * 3 / 8));
    checkPoints.add (Point<int> (r + 1, b - h / 4));
    checkPoints.add (Point<int> (r + 1, b - h / 8));
}

//=================================================================================================
void ParkingLot::reset ()
{
    leftPlacer->setVisible (false);
    rightPlacer->setVisible (false);

    resized();
}

//=================================================================================================
void ParkingLot::turnDirection (const bool shunshizhen, const bool turnLeft)
{
    pathHudu += shunshizhen ? EachHudu : -EachHudu;

    const int x = turnLeft ? (car->getX() - FromInnerWheel) : (car->getRight() + FromInnerWheel);
    const int y = car->getY() + 190;

    AffineTransform aft (AffineTransform::rotation (pathHudu, float(x), float(y)));
    car->setTransform (aft);
    rightPlacer->setTransform (aft);
    leftPlacer->setTransform (aft);
}

