/*
  ==============================================================================

    Track.cpp
    Created: 10 Mar 2023 11:53:03pm
    Author:  Admiral Gen. Aladeen

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Track.h"

//==============================================================================
Track::Track(juce::URL _path)
{
    trackPath = _path;
    juce::String temp = trackPath.getFileName();
    trackTitle = temp.substring(0, temp.indexOf("."));
    trackFormat = temp.substring(trackPath.getFileName().indexOf("."), temp.length());
    trackDate = juce::Time::getCurrentTime().toString(true,true,true,true);
}

Track::~Track()
{
}

juce::URL Track::getPath() {
    return trackPath;
}
juce::String Track::getTitle() {
    return trackTitle;
}
juce::String Track::getFormat() {
    return trackFormat;
}
juce::String Track::getDate() {
    return trackDate;
}