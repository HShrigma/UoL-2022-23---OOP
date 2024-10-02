/*
  ==============================================================================

	DJAudioPlayer.cpp
	Created: 29 Jan 2023 9:50:08pm
	Author:  Admiral Gen. Aladeen

  ==============================================================================
*/

#include "DJAudioPlayer.h"
//==============================================================================
DJAudioPlayer::DJAudioPlayer(juce::AudioFormatManager& _formatManager) : formatManager(_formatManager) {

}
DJAudioPlayer::~DJAudioPlayer() {

}

//==============================================================================
void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {

	transportSrc.prepareToPlay(
		samplesPerBlockExpected,
		sampleRate);

	resamplingSrc.prepareToPlay(
		samplesPerBlockExpected,
		sampleRate);
}

void DJAudioPlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) {
	resamplingSrc.getNextAudioBlock(bufferToFill);
}

void DJAudioPlayer::releaseResources() {
	transportSrc.releaseResources();
	resamplingSrc.releaseResources();
}

//==============================================================================
void DJAudioPlayer::loadURL(juce::URL audioURL) {
	auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
	if (reader != nullptr)
	{
		DBG("Reader Created");
		std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true));
		transportSrc.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
		readerSrc.reset(newSource.release());
		transportSrc.start();
	}
}
void DJAudioPlayer::setGain(double gain) {
	if (gain < 0 || gain >1.00)
	{
		DBG(" DJAudioPlayer::setGain Invalid gain value. Input gain should be 0-1");
	}
	else {
		transportSrc.setGain(gain);
	}
}
void DJAudioPlayer::setSpeed(double ratio) {
	if (ratio < 0 || ratio >100.0)
	{
		DBG(" DJAudioPlayer::setSpeed Invalid ratio value. Input ratio should be 0-100");
	}
	else {
		resamplingSrc.setResamplingRatio(ratio);
	}
}
void DJAudioPlayer::setPosition(double posInSecs) {
	transportSrc.setPosition(posInSecs);
}
void DJAudioPlayer::setPositionRelative(double pos) {
	if (pos < 0 || pos > 1.00) {
		DBG("DJAudioPlayer::setPositionRelative Invalid position value. Position should be 0-1");
	}
	else
	{
		double posInSecs = transportSrc.getLengthInSeconds() * pos;
		setPosition(posInSecs);
	}
}


//==============================================================================
void DJAudioPlayer::start() {
	transportSrc.start();
}
void DJAudioPlayer::stop() {
	transportSrc.stop();
}

//==============================================================================
double DJAudioPlayer::getPositionRelative()
{
	return transportSrc.getCurrentPosition() / transportSrc.getLengthInSeconds();
}
