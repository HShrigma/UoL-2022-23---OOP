/*
  ==============================================================================

	Track.h
	Created: 10 Mar 2023 11:53:03pm
	Author:  Admiral Gen. Aladeen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Track
{
public:
	Track(juce::URL _path);
	~Track();
	//==============================================================================
	//  Getters
	//==============================================================================
	juce::URL getPath();
	juce::String getTitle();
	juce::String getFormat();
	juce::String getDate();
private:
	//gets URL to track
	juce::URL trackPath;
	//gets value from trackpath url
	juce::String trackFormat;
	juce::String trackDate;
	juce::String trackTitle;
};
