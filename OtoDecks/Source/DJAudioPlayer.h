/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 29 Jan 2023 9:50:08pm
    Author:  Admiral Gen. Aladeen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class DJAudioPlayer: public juce::AudioSource {
public:
    //==============================================================================
    DJAudioPlayer(juce::AudioFormatManager& formatManager);

    ~DJAudioPlayer();
    
    //==============================================================================
    //override implements
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    
    //==============================================================================
    void loadURL(juce::URL audioURL);
    void setGain(double gain);
    void setSpeed(double ratio);
    void setPosition(double posInSecs);
    void setPositionRelative(double pos);

    //==============================================================================
    void start();
    void stop();
    //==============================================================================
    double getPositionRelative();


private:
    juce::AudioFormatManager& formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSrc;
    juce::AudioTransportSource transportSrc;
    juce::ResamplingAudioSource resamplingSrc{ &transportSrc,false,2 };

};