/*
  ==============================================================================

	DeckGUI.h
	Created: 31 Jan 2023 9:21:59pm
	Author:  Admiral Gen. Aladeen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"


class DeckGUI :
	public juce::Component,
	public juce::Button::Listener,
	public juce::Slider::Listener,
	public juce::FileDragAndDropTarget,
	public juce::Timer{
public:
	DeckGUI(DJAudioPlayer* player,
		juce::AudioFormatManager& formatManagerToUse,
		juce::AudioThumbnailCache& cacheToUse);
	~DeckGUI();

	void paint(juce::Graphics&) override;
	void resized() override;

	/**
	Implement Button listener
	**/
	void buttonClicked(juce::Button* button) override;

	/**
	Implement Slider listener
	**/
	void sliderValueChanged(juce::Slider* slider) override;
	/**
	Implement Timer
	**/
	void timerCallback() override;
	void playTrack(juce::URL url);
private:
	
	//==============================================================================
	//  Misc
	//==============================================================================
	DJAudioPlayer* player;
	juce::FileChooser fChooser{ "Select a file..." };
	WaveformDisplay waveformDisplay;
	double posSkipValue{ 0.01 };
	//==============================================================================
	//  Buttons
	//==============================================================================

	juce::TextButton playButton{ "Play" };
	juce::TextButton pauseButton{ "Pause" };
	juce::TextButton stopButton{ "Stop" };
	juce::TextButton loadButton{ "Load" };
	juce::TextButton rewindButton{ "Rew" };
	juce::TextButton forwardButton{ "FF" };

	//==============================================================================
	//  Sliders
	//==============================================================================

	juce::Slider volSlider;
	juce::Slider speedSlider;
	juce::Slider posSlider;

	//==============================================================================
	//  Drag and Drop
	//==============================================================================
	bool isInterestedInFileDrag(const juce::StringArray& files) override;
	void filesDropped(const juce::StringArray& files, int x, int y)override;
	//==============================================================================
	//  Macros
	//==============================================================================

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI);
};