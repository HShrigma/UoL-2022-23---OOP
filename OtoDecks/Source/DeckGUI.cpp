/*
  ==============================================================================

	DeckGUI.cpp
	Created: 31 Jan 2023 9:21:59pm
	Author:  Admiral Gen. Aladeen

  ==============================================================================
*/

#include "DeckGUI.h"

DeckGUI::DeckGUI(DJAudioPlayer* _player,
	juce::AudioFormatManager& formatManagerToUse,
	juce::AudioThumbnailCache& cacheToUse) : player(_player), // assign _player to our player data member
	waveformDisplay(formatManagerToUse, cacheToUse) {

	//add and make visible buttons
	addAndMakeVisible(playButton);
	addAndMakeVisible(pauseButton);
	addAndMakeVisible(stopButton);
	addAndMakeVisible(loadButton);
	addAndMakeVisible(rewindButton);
	addAndMakeVisible(forwardButton);
	//add and make visible sliders
	addAndMakeVisible(volSlider);
	addAndMakeVisible(speedSlider);
	addAndMakeVisible(posSlider);

	addAndMakeVisible(waveformDisplay);


	//set range
	volSlider.setRange(0.0, 1.0);
	speedSlider.setRange(0.0, 100.0);
	posSlider.setRange(0.0, 1.0);
	//add listeners buttons
	playButton.addListener(this);
	stopButton.addListener(this);
	loadButton.addListener(this);
	pauseButton.addListener(this);
	rewindButton.addListener(this);
	forwardButton.addListener(this);
	//add listeners sliders
	volSlider.addListener(this);
	speedSlider.addListener(this);
	posSlider.addListener(this);

	//set init values sliders
	volSlider.setValue(1.0);
	speedSlider.setValue(1.0);
	startTimer(200);

	//set button colour
	playButton.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::darkgreen);
	playButton.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::green);
	stopButton.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::darkred);
	stopButton.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::red);
	forwardButton.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::darkblue);
	forwardButton.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::blue);
	rewindButton.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::darkblue);
	rewindButton.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::blue);
}

DeckGUI::~DeckGUI() {
	stopTimer();
}

void DeckGUI::paint(juce::Graphics&) {
}

void DeckGUI::resized() {
	double rowH = getHeight() / 8;
	double rowW = getWidth() / 5;
	rewindButton.setBounds(0, 0, rowW, rowH);
	playButton.setBounds(rowW, 0, rowW, rowH);
	pauseButton.setBounds(rowW * 2, 0, rowW, rowH);
	stopButton.setBounds(rowW * 3, 0, rowW, rowH);
	forwardButton.setBounds(rowW * 4, 0, rowW, rowH);

	volSlider.setBounds(0, rowH, getWidth(), rowH);
	speedSlider.setBounds(0, rowH * 2, getWidth(), rowH);
	posSlider.setBounds(0, rowH * 3, getWidth(), rowH);
	waveformDisplay.setBounds(0, rowH * 4, getWidth(), rowH * 2);
	loadButton.setBounds(0, rowH * 6, getWidth(), rowH);
}

void DeckGUI::buttonClicked(juce::Button* button) {

	if (button == &playButton) {
		player->start();
	}
	if (button == &pauseButton) {
		player->stop();
	}
	if (button == &stopButton) {
		player->stop();
		player->setPositionRelative(0);
	}
	if (button == &rewindButton) {
		player->setPositionRelative(player->getPositionRelative() - posSkipValue);
	}
	if (button == &forwardButton) {
		player->setPositionRelative(player->getPositionRelative() + posSkipValue);
	}
	if (button == &loadButton) {
		auto fileChooserFlags =
			juce::FileBrowserComponent::canSelectFiles;
		fChooser.launchAsync(fileChooserFlags, [this](const juce::FileChooser& chooser)
		{
			juce::File chosenFile = chooser.getResult();
		playTrack(juce::URL{ chosenFile });
		});
	}
}
void DeckGUI::sliderValueChanged(juce::Slider* slider) {
	std::string display = "";
	if (slider == &volSlider)
	{
		player->setGain(slider->getValue());
	}
	if (slider == &speedSlider)
	{
		player->setSpeed(slider->getValue());
	}
	if (slider == &posSlider)
	{
		player->setPositionRelative(slider->getValue());
	}
	DBG(display);
}

bool DeckGUI::isInterestedInFileDrag(const juce::StringArray& files) {
	return true;
}
void DeckGUI::filesDropped(const juce::StringArray& files, int x, int y) {
	for (juce::String filename : files)
	{
		DBG(filename);
		juce::URL fileURL = juce::URL{ juce::File{filename} };
		playTrack(fileURL);
		return;
	}
}

void DeckGUI::timerCallback()
{
	waveformDisplay.setPositionRelative(player->getPositionRelative());
}

void DeckGUI::playTrack(juce::URL url) {
	player->loadURL(url);
	waveformDisplay.loadURL(juce::URL{ url });
}