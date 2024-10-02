/*
  ==============================================================================

	WaveformDisplay.cpp
	Created: 1 Feb 2023 6:51:43pm
	Author:  Admiral Gen. Aladeen

  ==============================================================================
*/

#include "WaveformDisplay.h"

WaveformDisplay::WaveformDisplay(juce::AudioFormatManager& formatManagerToUse,
	juce::AudioThumbnailCache& cacheToUse)
	: audioThumbnail(1000, formatManagerToUse, cacheToUse), fileLoaded(false), position(0)

{
	audioThumbnail.addChangeListener(this);
}
WaveformDisplay::~WaveformDisplay() {

}
void WaveformDisplay::loadURL(juce::URL audioURL) {
	audioThumbnail.clear();
	fileLoaded = audioThumbnail.setSource(new juce::URLInputSource(audioURL));
}

void WaveformDisplay::paint(juce::Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
	g.setColour(juce::Colours::grey);
	g.drawRect(getLocalBounds(), 1);
	g.setColour(juce::Colours::orange);

	if (fileLoaded)
	{
		g.setColour(juce::Colours::lightgreen);
		audioThumbnail.drawChannel(g, getLocalBounds(), 0, audioThumbnail.getTotalLength(), 0, 1);
		g.drawRect(position * getWidth(), 0, getWidth() / 20, getHeight());

	}
	else
	{
		g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId)); // clea
		g.setColour(juce::Colours::black);
		g.drawRect(getLocalBounds(), 1); // draw an outline around the component
		g.setColour(juce::Colours::green);
		g.setFont(24.0f);
		g.drawText("Waveform here!", getLocalBounds(),
			juce::Justification::centred, true); // draw some placeholder text
	}

}
void WaveformDisplay::resized() {

}
void WaveformDisplay::changeListenerCallback(juce::ChangeBroadcaster* source)
{
	DBG("wfd: change received! ");
	repaint();
}
void WaveformDisplay::setPositionRelative(double pos)
{
	if (pos != position)
	{
		position = pos;
		repaint();
	}
}