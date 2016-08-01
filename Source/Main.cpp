/*
  ==============================================================================

    Main application class.

  ==============================================================================
*/

#include "JuceHeader.h"
#include "MainComponent.h"

//==============================================================================
class ParkingLotApplication  : public JUCEApplication
{
public:
    //==============================================================================
    ParkingLotApplication() {}

    const String getApplicationName() override       { return ProjectInfo::projectName; }
    const String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override       { return true; }

    //==============================================================================
    void initialise (const String&) override    { mainWindow = new MainWindow (getApplicationName()); }
    void shutdown() override    { mainWindow = nullptr; }
    void systemRequestedQuit() override    { quit(); }
    void anotherInstanceStarted (const String& ) override    { }

    //==============================================================================
    /** Main window */
    class MainWindow    : public DocumentWindow
    {
    public:
        MainWindow (String name)  : DocumentWindow (name,
                                                    Colours::lightgrey,
                                                    DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
            setContentOwned (new MainComponent(), true);

			setResizable (true, false);
			setResizeLimits (1280, 780, 3800, 3800);

			centreWithSize (getWidth (), getHeight ());
			setVisible (true);
        }

        void closeButtonPressed() override
        {
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    ScopedPointer<MainWindow> mainWindow;
};

//==============================================================================

START_JUCE_APPLICATION (ParkingLotApplication)
