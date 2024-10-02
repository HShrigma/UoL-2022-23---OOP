/*
  ==============================================================================

	PlaylistComponent.h
	Created: 1 Feb 2023 11:35:41pm
	Author:  Admiral Gen. Aladeen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DeckGUI.h"
#include "Track.h"

//==============================================================================
/*
*/
class PlaylistComponent :
	public juce::Component,
	public juce::TableListBoxModel,
	public juce::FileDragAndDropTarget,
	public juce::Button::Listener

{
public:
	PlaylistComponent(DeckGUI* _deck1, DeckGUI* _deck2);
	~PlaylistComponent() override;

	void paint(juce::Graphics&) override;
	void resized() override;

	int getNumRows() override;

	void paintRowBackground(juce::Graphics& g,
		int rowNumber,
		int width,
		int height,
		bool rowIsSelected) override;
	void paintCell(juce::Graphics& g,
		int rowNumber,
		int columnId,
		int width,
		int height,
		bool rowIsSelected) override;
	virtual void cellClicked(int rowNumber, int columnId, const juce::MouseEvent&);
	Component* refreshComponentForCell(int rowNumber,
		int columnId,
		bool isRowSelected,
		Component* existingComponentToUpdate) override;
	void buttonClicked(juce::Button* button) override;

private:

	//==============================================================================
	//  Table Content
	//==============================================================================
	std::vector<Track> tracks{};
	juce::TableListBox tableComponent;
	//==============================================================================
	//  External Links
	//==============================================================================
	DeckGUI* deck1;
	DeckGUI* deck2;
	//==============================================================================
	//  Load files
	//==============================================================================
	juce::TextButton loadButton{ "add to Playlist" };
	juce::FileChooser fChooser{ "Select a file..." };
	juce::File dir{ juce::File::getCurrentWorkingDirectory().getChildFile("paths.txt")};
	//==============================================================================
	//  Drag and Drop
	//==============================================================================
	bool isInterestedInFileDrag(const juce::StringArray& files) override;
	void filesDropped(const juce::StringArray& files, int x, int y)override;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaylistComponent)
};
