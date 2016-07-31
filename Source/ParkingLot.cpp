/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "CommonData.h"
#include "ParkingLot.h"
#include "TrainingCar.h"
#include "RestingCar.h"

//==============================================================================
ParkingLot::ParkingLot()
	: pathHudu (0.0f)
{
	addAndMakeVisible (trainingCar = new TrainingCar());
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

    // draw path...
    g.setColour (Colours::lightgreen);
    g.strokePath (leftFrontPath, PathStrokeType (0.5f));
    g.strokePath (rightFrontPath, PathStrokeType (0.5f));

    g.setColour (Colours::lightpink);
    g.strokePath (leftRearPath, PathStrokeType (0.5f));
    g.strokePath (rightRearPath, PathStrokeType (0.5f));

	/*g.setColour (Colours::darkred);
	g.fillRect (car->getBounds ().expanded (8));

	g.setColour (Colours::darkgoldenrod);
	g.fillRect (car->getBoundsInParent ().expanded (5));	*/
}
//=========================================================================
void ParkingLot::resized ()
{
    pathHudu = 0.0f;

    trainingCar->setTransform (AffineTransform());
	trainingCar->setCentreRelative (0.5f, 0.5f);
    trainingCar->reset();

    leftPlacer->setTransform (AffineTransform());
    leftPlacer->setCentrePosition (trainingCar->getX() - FromInnerWheel, trainingCar->getY() + 190);
    leftPlacer->setVisible (false);

    rightPlacer->setTransform (AffineTransform());
    rightPlacer->setCentrePosition (trainingCar->getRight() + FromInnerWheel, trainingCar->getY() + 190);
    rightPlacer->setVisible (false);

    getCurrentCheckPoints();
    arrangeRestingCars();

    // path...
    leftFrontPath.clear();
    rightFrontPath.clear();
    leftRearPath.clear();
    rightRearPath.clear();

    leftFrontPath.startNewSubPath (checkPoints[0].toFloat());
    rightFrontPath.startNewSubPath (checkPoints[1].toFloat());
    leftRearPath.startNewSubPath (checkPoints[2].toFloat());
    rightRearPath.startNewSubPath (checkPoints[3].toFloat());
}

//=================================================================================================
void ParkingLot::setDirection (const int newDirection)
{
    const int oldFangxiang = trainingCar->getDirection();

    trainingCar->setDirection (newDirection);
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

        trainingCar->setCentrePosition (centerX, centerY);
        leftPlacer->setCentrePosition (trainingCar->getX() - FromInnerWheel, trainingCar->getY() + 190);
        rightPlacer->setCentrePosition (trainingCar->getRight() + FromInnerWheel, trainingCar->getY() + 190);

        trainingCar->setTransform (aft);
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
    if (0 == trainingCar->getDirection())  // straight forward
    {
        const int dist (backward ? StraightStep : -StraightStep);
        trainingCar->setTopLeftPosition (trainingCar->getX(), trainingCar->getY() + dist);

        leftPlacer->setTopLeftPosition (leftPlacer->getX(), leftPlacer->getY() + dist);
        rightPlacer->setTopLeftPosition (rightPlacer->getX(), rightPlacer->getY() + dist);
    }
    else if (-1 == trainingCar->getDirection()) // -1 is turn left
    {
        turnDirection (backward, true);
    }
    else  if (1 == trainingCar->getDirection()) // 1 is turn right
    {
        turnDirection (!backward, false);
    }

    getCurrentCheckPoints();

    if (isCrashed())
    {
        if (AlertWindow::showNativeDialogBox ("Warning", "Crashed!!", true))
            moveTheCar (!backward);
        else
            reset();
    }
    else  // link path point and draw them...
    {
        AffineTransform atf (trainingCar->getTransform());

        leftFrontPath.lineTo (checkPoints[0].toFloat().transformedBy (atf));
        rightFrontPath.lineTo (checkPoints[1].toFloat().transformedBy (atf));
        leftRearPath.lineTo (checkPoints[2].toFloat().transformedBy (atf));
        rightRearPath.lineTo (checkPoints[3].toFloat().transformedBy (atf));

        repaint();
    }
}

//=================================================================================================
const bool ParkingLot::isCrashed()
{
    AffineTransform atf (trainingCar->getTransform());

    for (int i = checkPoints.size(); --i >= 0; )
    {
        Point<int> p (checkPoints[i].transformedBy (atf));
        Component* comp = getComponentAt (p);

        if (!contains (p) || (comp != nullptr && comp != this && comp != trainingCar))
            return true;
    }

    return false;
}

//=================================================================================================
void ParkingLot::getCurrentCheckPoints ()
{
    checkPoints.clearQuick();

    // add 24 points of the car for crash-check
    const int x = trainingCar->getX();
    const int y = trainingCar->getY();
    const int w = trainingCar->getWidth();
    const int h = trainingCar->getHeight();
    const int r = trainingCar->getRight();
    const int b = trainingCar->getBottom();

    // front conners
    checkPoints.add (Point<int> (x + 3, y + 3));
    checkPoints.add (Point<int> (r - 3, y + 3));

    // rear path point
    checkPoints.add (Point<int> (x, b - h / 4)); 
    checkPoints.add (Point<int> (r, b - h / 4)); 

    // rear conners
    checkPoints.add (Point<int> (x + 4, b - 4));
    checkPoints.add (Point<int> (r - 4, b - 4));

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
    checkPoints.add (Point<int> (x - 1, b - h / 8));

    checkPoints.add (Point<int> (r + 1, y + h / 8));
    checkPoints.add (Point<int> (r + 1, y + h / 4));
    checkPoints.add (Point<int> (r + 1, y + h * 3 / 8));
    checkPoints.add (Point<int> (r + 1, y + h / 2));
    checkPoints.add (Point<int> (r + 1, b - h * 3 / 8));
    checkPoints.add (Point<int> (r + 1, b - h / 8));
}

//=================================================================================================
void ParkingLot::arrangeRestingCars()
{
    restingCars.clear (true);


}

//=================================================================================================
void ParkingLot::reset()
{
    leftPlacer->setVisible (false);
    rightPlacer->setVisible (false);

    resized();
}

//=================================================================================================
void ParkingLot::turnDirection (const bool shunshizhen, const bool turnLeft)
{
    pathHudu += shunshizhen ? EachHudu : -EachHudu;

    const int x = turnLeft ? (trainingCar->getX() - FromInnerWheel) : (trainingCar->getRight() + FromInnerWheel);
    const int y = trainingCar->getY() + 190;

    AffineTransform aft (AffineTransform::rotation (pathHudu, float(x), float(y)));
    trainingCar->setTransform (aft);
    rightPlacer->setTransform (aft);
    leftPlacer->setTransform (aft);
}

