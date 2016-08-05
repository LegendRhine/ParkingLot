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
    : pathHudu (0.0f),
    arrangeState (0),
    leftFrontPathShow (false),
    rightFrontPathShow (false),
    leftRearPathShow (true),
    rightRearPathShow (true),
    shouldShowForecastPath (false),
    shouldShowViewLine (false),
    xiexiang (false),
    fanxiexiang (false),
    clearAllRestingCars (false)
{
	addAndMakeVisible (trainingCar = new TrainingCar (this));
}

ParkingLot::~ParkingLot()
{
}
//=========================================================================
void ParkingLot::paint (Graphics& g)
{
    // draw pathes...
    if (leftFrontPathShow)
    {
        g.setColour (Colours::lightgreen);
        g.strokePath (leftFrontPath, PathStrokeType (0.5f));
    }

    if (rightFrontPathShow)
    {
        g.setColour (Colours::lightgreen);
        g.strokePath (rightFrontPath, PathStrokeType (0.5f));
    }

    if (leftRearPathShow)
    {
        g.setColour (Colours::lightpink);
        g.strokePath (leftRearPath, PathStrokeType (0.5f));
    }

    if (rightRearPathShow)
    {
        g.setColour (Colours::lightpink);
        g.strokePath (rightRearPath, PathStrokeType (0.5f));
    }

    // draw forecast-path
    if (shouldShowForecastPath)
    {   
        forecastPath1.clear ();
        forecastPath2.clear ();

        static float dashArray[2] = { 2, 5 };
        g.setColour (Colours::yellow);

        // straightforward forecast-line
        if (0 == trainingCar->getTurningAngle()) // straight forward
        {
            // left forecast line
            Line<float> leftLine (trainingCar->getX() + 0.5f, trainingCar->getY() - 0.5f, 
                trainingCar->getX() + 0.5f, trainingCar->getBottom() + 0.5f);

            leftLine = leftLine.withShortenedStart (-600.f).withShortenedEnd (-600.f);
            leftLine.applyTransform (trainingCar->getTransform());

            g.drawDashedLine (leftLine, dashArray, 2, 0.8f);

            // right forecast line
            Line<float> rightLine (trainingCar->getRight() + 0.5f, trainingCar->getY() - 0.5f, 
                trainingCar->getRight() - 0.5f, trainingCar->getBottom() + 0.5f);

            rightLine = rightLine.withShortenedStart (-600.0f).withShortenedEnd (-600.f);
            rightLine.applyTransform (trainingCar->getTransform());

            g.drawDashedLine (rightLine, dashArray, 2, 0.8f);
        }
        else  // turning forecast-line
        {
            // zuixiao zhuanwan banjing
            const float fromInnerWheel = trainingCar->getDistanceFromInnerWheel();
            Point<float> frontPoint;

            if (trainingCar->getTurningAngle() < 0)
                frontPoint.setXY (trainingCar->getRight() - 0.f, trainingCar->getY() + 0.f);
            else
                frontPoint.setXY (trainingCar->getX() - 0.f, trainingCar->getY() + 0.f);

            frontPoint.applyTransform (trainingCar->getTransform());

            const float banjing = polePoint.getDistanceFrom (frontPoint) + 1.f;
            //DBG (banjing);
            
            if (trainingCar->getTurningAngle() < 0)  // turn left
            {
                forecastPath1.addCentredArc (polePoint.getX(), polePoint.getY(),
                    banjing, banjing,
                    pathHudu, -float_Pi / 5.0f, float_Pi + float_Pi / 5.0f, true);

                forecastPath2.addCentredArc (polePoint.getX(), polePoint.getY(),
                    fromInnerWheel - 1.f, fromInnerWheel - 1.f,
                    pathHudu, -float_Pi / 5.0f, float_Pi + float_Pi / 5.0f, true);
            }
            else // turn right
            {
                forecastPath1.addCentredArc (polePoint.getX(), polePoint.getY(),
                    banjing, banjing,
                    pathHudu, float_Pi / 5.0f, -float_Pi - float_Pi / 5.0f, true);

                forecastPath2.addCentredArc (polePoint.getX(), polePoint.getY(),
                    fromInnerWheel - 1.f, fromInnerWheel - 1.f,
                    pathHudu, float_Pi / 5.0f, -float_Pi - float_Pi / 5.0f, true);
            }

            PathStrokeType strokeType (0.3f);

            strokeType.createDashedStroke (forecastPath1, forecastPath1, dashArray, 2);
            g.strokePath (forecastPath1, strokeType);

            strokeType.createDashedStroke (forecastPath2, forecastPath2, dashArray, 2);
            g.strokePath (forecastPath2, strokeType);
        }        
    }

    // draw pole
    /*g.setColour (Colours::red);
    g.fillEllipse (polePoint.getX() - 5, polePoint.getY() - 5, 10.f, 10.f);*/

    // show the area of the car and its transformed area
	/*g.setColour (Colours::darkred);
	g.fillRect (trainingCar->getBounds ().expanded (8));

	g.setColour (Colours::darkgoldenrod);
	g.fillRect (trainingCar->getBoundsInParent ().expanded (5));*/
}
//=========================================================================
void ParkingLot::resized ()
{
    pathHudu = 0.0f;
    const int fromInnerWheel = roundToInt (trainingCar->getDistanceFromInnerWheel());

    trainingCar->setTransform (AffineTransform ());
	trainingCar->setCentrePosition (getWidth() / 2, CarLength + 179);
    trainingCar->reset();

    polePoint.setXY (0.f, 0.f);
    resetPath();
    arrangeRestingCars (xiexiang, fanxiexiang);
}

//=================================================================================================
void ParkingLot::resetPath ()
{
    getCurrentCheckPoints();

    leftFrontPath.clear();
    rightFrontPath.clear();
    leftRearPath.clear();
    rightRearPath.clear();

    repaint();

    leftFrontPath.startNewSubPath (checkPoints[0].transformedBy (trainingCar->getTransform()).toFloat());
    rightFrontPath.startNewSubPath (checkPoints[1].transformedBy (trainingCar->getTransform()).toFloat());
    leftRearPath.startNewSubPath (checkPoints[2].transformedBy (trainingCar->getTransform()).toFloat());
    rightRearPath.startNewSubPath (checkPoints[3].transformedBy (trainingCar->getTransform()).toFloat());
}

//=================================================================================================
void ParkingLot::placeAfterSetDirection (const int newAngle)
{
    if (newAngle == 0)
        return;
    
    // first, place the pole-point base on transformed car
    const float fromInnerWheel = trainingCar->getDistanceFromInnerWheel();

    Point<float> leftRearPoint (trainingCar->getX() + 0.f, trainingCar->getY() + 190.f);
    Point<float> rightRearPoint (trainingCar->getRight() + 0.f, trainingCar->getY() + 190.f);

    leftRearPoint.applyTransform (trainingCar->getTransform());
    rightRearPoint.applyTransform (trainingCar->getTransform());

    Line<float> banjing (leftRearPoint, rightRearPoint);
    const bool isTurningLeft = newAngle < 0;

    // place the pole point
    polePoint = banjing.getPointAlongLine (isTurningLeft ? -fromInnerWheel : (fromInnerWheel + CarWidth));
    
    // second, place the car base on pole-point
    const double centerX = polePoint.getX() + (isTurningLeft ? (fromInnerWheel + 50.0) : (-fromInnerWheel - 50.0));
    const double centerY = polePoint.getY() - 70.0;

    trainingCar->setCentrePosition (roundToIntAccurate (centerX), roundToIntAccurate (centerY));
    trainingCar->setTransform (AffineTransform::rotation (pathHudu, polePoint.getX(), polePoint.getY()));

    // zhuanwan banjing
    /*Point<float> frontPoint;

    if (isTurningLeft)
        frontPoint.setXY (trainingCar->getRight(), trainingCar->getY());
    else
        frontPoint.setXY (trainingCar->getX(), trainingCar->getY());

    frontPoint.applyTransform (trainingCar->getTransform());
    DBG (polePoint.getDistanceFrom (frontPoint));*/

}

//=================================================================================================
void ParkingLot::mouseUp (const MouseEvent& e)
{
    trainingCar->mouseUp (e);
}

//=================================================================================================
void ParkingLot::mouseDown (const MouseEvent& e)
{
    trainingCar->mouseDown (e);
    beginDragAutoRepeat (IntervelHoldMouse);
}

//=================================================================================================
void ParkingLot::mouseDrag (const MouseEvent& e)
{
    trainingCar->mouseDrag (e);
}

//=================================================================================================
void ParkingLot::mouseWheelMove (const MouseEvent&, const MouseWheelDetails& wheel)
{
    const bool direction = (wheel.deltaY > 0);
    
    if (!moveTheCar (direction))
        moveTheCar (!direction);
}

//=================================================================================================
bool ParkingLot::isInterestedInDragSource (const SourceDetails& dragSourceDetails)
{
    return (dragSourceDetails.sourceComponent == trainingCar);
}

//=================================================================================================
void ParkingLot::itemDropped (const SourceDetails& details)
{
    String offsetPointString (details.description.toString());
    const int offsetX = offsetPointString.upToFirstOccurrenceOf (",", false, true).getIntValue();
    const int offsetY = offsetPointString.fromFirstOccurrenceOf (",", false, true).getIntValue();

    const int x = details.localPosition.getX() - offsetX;
    const int y = details.localPosition.getY() - offsetY;

    placeTheCarAfterDraged (x, y);
}

//=================================================================================================
bool ParkingLot::keyPressed (const KeyPress& key)
{
    DBG ("hello");
    return true;
}

//=================================================================================================
void ParkingLot::placeTheCarAfterDraged (const int newX, const int newY)
{
    // for crash check.. first, create a 'fake' car
    ScopedPointer<TrainingCar> newCar = new TrainingCar (this);

    newCar->setTurningAngle (trainingCar->getTurningAngle());
    newCar->setBounds (trainingCar->getBounds());
    newCar->setTransform (trainingCar->getTransform());
    newCar->setAlpha (trainingCar->getAlpha());

    // then, move the real car, and perform check..
    trainingCar->setTransform (AffineTransform ());
    trainingCar->setTopLeftPosition (newX, newY);

    getCurrentCheckPoints();

    if (isCrashed())
    {
        trainingCar = newCar;
        addAndMakeVisible (trainingCar);
    }
    else
    {
        newCar = nullptr;
        pathHudu = 0.0f;
        resetPath();

        const float fromInnerWheel = trainingCar->getDistanceFromInnerWheel();

        if (trainingCar->getTurningAngle() < 0)
            polePoint.setXY (trainingCar->getX() - fromInnerWheel, trainingCar->getY() + 190.f);
        else
            polePoint.setXY (trainingCar->getRight() + fromInnerWheel, trainingCar->getY() + 190.f);
    }  

    repaint();  // for real-time change forecast-lines
}

//=================================================================================================
const bool ParkingLot::moveTheCar (const bool backward)
{
    if (0 == trainingCar->getTurningAngle())  // straight forward
    {
        const int dist = (backward ? StraightStep : -StraightStep);
        trainingCar->setTopLeftPosition (trainingCar->getX(), trainingCar->getY() + dist);
    }
    else 
    {
        const float eachHudu = trainingCar->getCurrentEachHudu();

        if (trainingCar->getTurningAngle() < 0)
            pathHudu += backward ? eachHudu : -eachHudu;
        else
            pathHudu += backward ? -eachHudu : eachHudu;

        trainingCar->setTransform (AffineTransform::rotation (pathHudu, polePoint.getX(), polePoint.getY()));        
    }

    getCurrentCheckPoints();

    if (isCrashed())
    {
        SplashScreen* splash = new SplashScreen ("Splash",
            ImageCache::getFromMemory (BinaryData::crashed_png, BinaryData::crashed_pngSize),
            false);

        splash->deleteAfterDelay (RelativeTime (1), true); 
        return false;
    }
    else if (isSuccessful())
    {
        SplashScreen* splash = new SplashScreen ("Splash",
            ImageCache::getFromMemory (BinaryData::good_png, BinaryData::good_pngSize),
            false);

        splash->deleteAfterDelay (RelativeTime (2.5), true);
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

    return true;
}

//=================================================================================================
void ParkingLot::showLeftFrontPath (const bool showThem)
{
    leftFrontPathShow = showThem;
    repaint();
}

//=================================================================================================
void ParkingLot::showRightFrontPath (const bool showIt)
{
    rightFrontPathShow = showIt;
    repaint();
}

//=================================================================================================
void ParkingLot::showLeftRearPath (const bool showIt)
{
    leftRearPathShow = showIt;
    repaint();
}

//=================================================================================================
void ParkingLot::showRightRearPath (const bool showIt)
{
    rightRearPathShow = showIt;
    repaint();
}

//=================================================================================================
void ParkingLot::showForecastPath (const bool showIt)
{
    shouldShowForecastPath = showIt;
    repaint();
}

//=================================================================================================
void ParkingLot::showViewLine (const bool showIt)
{
    shouldShowViewLine = showIt;
    repaint();
}

//=================================================================================================
void ParkingLot::transparentTrainingCar (const bool transparentIt)
{
    trainingCar->setAlpha (transparentIt ? 0.3f : 1.f);
}

//=================================================================================================
void ParkingLot::setSlopedRestingCars (const bool slope, const bool backslash)
{
    xiexiang = slope;
    fanxiexiang = backslash;

    resized();
}

//=================================================================================================
const int ParkingLot::getFieldState () const
{
    if (restingCars.size() < 1)
        return 0;   // training field

    else  // -1-parking field, 1-block (hard) field
        return (restingCars[0]->getWidth() >= CarWidth) ? -1 : 1;
}

//=================================================================================================
void ParkingLot::setFieldState (const int stateCode)
{
    if (0 == stateCode)  // training field
    {
        clearAllRestingCars = true;
        restingCars.clear();

        stopAreaOne = stopAreaTwo = stopAreaThree = nullptr;
        resetPath();

        // tell maincomponent don't draw stop-lines
        getParentComponent()->repaint();
    }

    else if (-1 == stateCode)  // parking field
    {
        trainingCar->setAlpha (1.f);
        clearAllRestingCars = false;
    }
    else  // hard (block) field
    {
        clearAllRestingCars = true;
        restingCars.clear();

        stopAreaOne = stopAreaTwo = stopAreaThree = nullptr;
        resetPath();

        // tell maincomponent don't draw stop-lines
        getParentComponent()->repaint();
    }

    resized();
}

//=================================================================================================
const bool ParkingLot::isCrashed()
{
    AffineTransform atf (trainingCar->getTransform());

    for (int i = checkPoints.size(); --i >= 0; )
    {
        Point<int> p (checkPoints[i].transformedBy (atf));

        if (!contains (p))
            return true;

        Component* comp = getComponentAt (p);

        for (int j = 0; j < restingCars.size(); ++j)
        {
            if (comp == restingCars[j])
                return true;
        }
    }

    return false;
}

//=================================================================================================
const bool ParkingLot::isSuccessful ()
{
    if (stopAreaOne == nullptr || stopAreaTwo == nullptr || stopAreaThree == nullptr)
        return false;

    AffineTransform atf (trainingCar->getTransform());

    for (int i = checkPoints.size(); --i >= 0; )
    {
        Point<int> p (checkPoints[i].transformedBy (atf));

        Rectangle<int> stopOne (stopAreaOne->getBounds().transformedBy (stopAreaOne->getTransform()));
        Rectangle<int> stopTwo (stopAreaTwo->getBounds().transformedBy (stopAreaTwo->getTransform()));
        Rectangle<int> stopThree (stopAreaThree->getBounds().transformedBy (stopAreaThree->getTransform()));

        if (stopOne.contains (p) || stopTwo.contains (p) || stopThree.contains (p))
            continue;
        else
            return false;
    }

    return true;
}

//=================================================================================================
void ParkingLot::getCurrentCheckPoints ()
{
    checkPoints.clearQuick();

    const int x = trainingCar->getX();
    const int y = trainingCar->getY();
    const int w = trainingCar->getWidth();
    const int h = trainingCar->getHeight();
    const int r = trainingCar->getRight();
    const int b = trainingCar->getBottom();

    // front conners
    const int frontGap = 3;
    checkPoints.add (Point<int> (x + frontGap, y + frontGap)); // index: 0
    checkPoints.add (Point<int> (r - frontGap, y + frontGap)); // 1

    // rear links/path point
    checkPoints.add (Point<int> (x, b - 50)); //  2
    checkPoints.add (Point<int> (r, b - 50));  // 3

    // rear conners
    checkPoints.add (Point<int> (x + frontGap, b - frontGap));
    checkPoints.add (Point<int> (r - frontGap, b - frontGap));

    // top and bottom sides, 8-20
    for (int i = 1; i < 20; ++i)
    {
        checkPoints.add (Point<int> (x + i * (w / 20), y - 1));
        checkPoints.add (Point<int> (x + i * (w / 20), b + 1));
    }
    
    // left and right sides,
    for (int i = 1; i < 40; ++i)
    {
        if (i != 11)  // alreay added (rear path point)
        {
            checkPoints.add (Point<int> (x - 1, y + i * (h / 40)));
            checkPoints.add (Point<int> (r + 1, y + i * (h / 40)));
        }
    }
}

//=================================================================================================
void ParkingLot::arrangeRestingCars (const bool slope, const bool backslash)
{
    restingCars.clear();
    stopAreaOne = stopAreaTwo = stopAreaThree = nullptr;

    if (clearAllRestingCars)
        return;

    if (!slope)
        arrangeState = 0;
    else
        arrangeState = backslash ? -1 : 1;
  
    const int hGap = 25 + (slope ? 50 : 0);
    const int vGap = 45;    
    const int hNumbers = getHeight() / (CarWidth + hGap) +
                         ((getHeight() % (CarWidth + hGap) == 0) ? 0 : 1);    
    const int vNumbers = getHeight() / (CarLength + vGap) +
                         ((getHeight() % (CarLength + vGap) == 0) ? 0 : 1);
    
    // left side for h-car arrange
    for (int i = hNumbers; --i >= 0; )
    {
        Component* car = nullptr;

        if (i == 3)
        {
            car = stopAreaOne = new StopArea();
            car->setSize (CarLength + 8, CarWidth + 8);
            car->setTopLeftPosition (6, (CarWidth + hGap) * i + 14);
        }
        else
        {
            car = new RestingCar();
            restingCars.add (car);
            car->setSize (CarLength, CarWidth);
            car->setTopLeftPosition (10, (CarWidth + hGap) * i + 15);            
        }
        
        addAndMakeVisible (car);
        car->toBack();

        // slope and backslash
        if (slope)
        {
            const float cx (car->getBounds().toFloat().getCentreX());
            const float cy (car->getBounds().toFloat().getCentreY());
            const float hudu = float_Pi / 4.0f;

            car->setTransform (AffineTransform::rotation (backslash ? hudu : -hudu, cx, cy));
        }        
    }
    
    // right side for h-car arrange
    for (int i = hNumbers; --i >= 0; )
    {
        Component* car = nullptr;

        if (i == 1)
        {
            car = stopAreaTwo = new StopArea();
            car->setSize (CarLength + 8, CarWidth + 8);
            car->setTopLeftPosition (getWidth() - 14 - CarLength, (CarWidth + hGap) * i + 4);
        }
        else
        {
            car = new RestingCar();
            restingCars.add (car);
            car->setSize (CarLength, CarWidth);
            car->setTopLeftPosition (getWidth() - 8 - CarLength, (CarWidth + hGap) * i + 15);
        }
        
        addAndMakeVisible (car);
        car->toBack();

        // slope and backslash
        if (slope)
        {
            const float cx (car->getBounds().toFloat().getCentreX());
            const float cy (car->getBounds().toFloat().getCentreY());
            const float hudu = float_Pi / 4.0f;

            car->setTransform (AffineTransform::rotation (backslash ? -hudu : hudu, cx, cy));
        }
    }
    
    // v-car arrange
    for (int i = 0; i < vNumbers; ++i)
    {
        Component* car = nullptr;

        if (i != 1)
        {
            car = new RestingCar();
            restingCars.add (car);
            car->setSize (CarWidth, CarLength);
            car->setTopLeftPosition (getWidth() / 2 - CarWidth / 2, (CarLength + vGap) * i + 8);
        }
        else
        {
            car = stopAreaThree = new StopArea();
            car->setSize (CarWidth + 8, CarLength + 8);
            car->setTopLeftPosition (getWidth() / 2 - CarWidth / 2 - 4, (CarLength + vGap) * i + 10);
        }

        addAndMakeVisible (car);
        car->toBack();
    }
}


