/*
  ==============================================================================

	PlaylistComponent.cpp
	Created: 1 Feb 2023 11:35:41pm
	Author:  Admiral Gen. Aladeen

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"
#include "DeckGUI.h"

//==============================================================================
PlaylistComponent::PlaylistComponent(DeckGUI* _deck1, DeckGUI* _deck2) : deck1(_deck1), deck2(_deck2) {
	// In your constructor, you should add any child components, and
	// initialise any special settings that your component needs.
	addAndMakeVisible(tableComponent);
	tableComponent.setModel(this);
	addAndMakeVisible(loadButton);
	loadButton.addListener(this);
	int colWidth = 160;
	tableComponent.getHeader().setStretchToFitActive(true);
	tableComponent.getHeader().addColumn("", 1, colWidth);
	tableComponent.getHeader().addColumn("", 2, colWidth);
	tableComponent.getHeader().addColumn("Track title", 3, colWidth);
	tableComponent.getHeader().addColumn("Format", 4, colWidth);
	tableComponent.getHeader().addColumn("Date added", 5, colWidth);

}

PlaylistComponent::~PlaylistComponent()
{
}

void PlaylistComponent::paint(juce::Graphics& g)
{
	/* This demo code just fills the component's background and
	   draws some placeholder text to get you started.

	   You should replace everything in this method with your own
	   drawing code..
	*/

	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background

	g.setColour(juce::Colours::grey);
	g.drawRect(getLocalBounds(), 1);   // draw an outline around the component
}

void PlaylistComponent::resized()
{
	// This method is where you should set the bounds of any child
	// components that your component contains..
	double buttonH = getHeight() / 12;
	double tableH = buttonH * 11;
	loadButton.setBounds(0, 0, getWidth(), buttonH);
	tableComponent.setBounds(0, buttonH, getWidth(), tableH);

}

int PlaylistComponent::getNumRows()
{
	return tracks.size();
}

void PlaylistComponent::paintRowBackground(juce::Graphics& g,
	int rowNumber,
	int width,
	int height,
	bool rowIsSelected)
{
	// just highlight selected rows
	if (rowIsSelected)
	{
		g.fillAll(juce::Colours::orange);
	}
	else {
		g.fillAll(juce::Colours::darkgrey);
	}
}
void PlaylistComponent::paintCell(juce::Graphics& g,
	int rowNumber,
	int columnId,
	int width,
	int height,
	bool rowIsSelected)
{
	if (tracks.size() != 0) {
		if (columnId == 3)
		{
			g.drawText(tracks[rowNumber].getTitle(), // the important bit
				2, 0,
				width - 4, height,
				juce::Justification::centredLeft,
				true);
		}
		if (columnId == 4)
		{
			g.drawText(tracks[rowNumber].getFormat(), // the important bit
				2, 0,
				width - 4, height,
				juce::Justification::centredLeft,
				true);
		}
		if (columnId == 5)
		{
			g.drawText(tracks[rowNumber].getDate(), // the important bit
				2, 0,
				width - 4, height,
				juce::Justification::centredLeft,
				true);
		}
	}

}

void PlaylistComponent::cellClicked(int rowNumber, int columnId, const juce::MouseEvent&)
{
}
juce::Component* PlaylistComponent::refreshComponentForCell(int rowNumber,
	int columnId,
	bool isRowSelected,
	juce::Component* existingComponentToUpdate)
{

		if (existingComponentToUpdate == nullptr && (columnId == 1 || columnId == 2))
		{
			juce::TextButton* btn = new juce::TextButton("play  on Deck " + std::to_string(columnId));
			existingComponentToUpdate = btn;
			btn->addListener(this);
			juce::String id{ std::to_string(rowNumber) + std::to_string(columnId) };
			btn->setComponentID(id);
		}
	return existingComponentToUpdate;

}

void PlaylistComponent::buttonClicked(juce::Button* button)
{
	if (button == &loadButton) {
		auto fileChooserFlags =
			juce::FileBrowserComponent::canSelectFiles;

		fChooser.launchAsync(fileChooserFlags, [this](const juce::FileChooser& chooser)
		{
			juce::File chosenFile = chooser.getResult();
		juce::URL fileURL = juce::URL{ chosenFile };
		Track track{ fileURL };
		tracks.push_back(track);
		tableComponent.updateContent();
		});
	}
	else
	{
		int index = button->getComponentID()[0] - 48;
		if (button->getComponentID()[1] == '1')
		{
			deck1->playTrack(tracks[index].getPath());
		}
		else
		{
			deck2->playTrack(tracks[index].getPath());
		}
	}

}
bool PlaylistComponent::isInterestedInFileDrag(const juce::StringArray& files) {
	return true;
}
void PlaylistComponent::filesDropped(const juce::StringArray& files, int x, int y) {
	for (juce::String filename : files)
	{
		DBG(filename);
		juce::URL fileURL = juce::URL{ juce::File{filename} };
		tracks.push_back(Track{ juce::URL{ fileURL } });
		tableComponent.updateContent();
		return;
	}
}