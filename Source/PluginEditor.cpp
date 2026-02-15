/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleEQAudioProcessorEditor::SimpleEQAudioProcessorEditor (SimpleEQAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
    peakFreqSliderAttachment(audioProcessor.apvts, "peak_freq", peakFreqSlider),
    peakQualitySliderAttachment(audioProcessor.apvts, "peak_gain", peakGainSlider),
    peakGainSliderAttachment(audioProcessor.apvts, "peak_quality", peakQualitySlider),
    lowCutFreqSliderAttachment(audioProcessor.apvts, "lowcut_freq", lowCutFreqSlider),
    highCutFreqSliderAttachment(audioProcessor.apvts, "highcut_freq", highCutFreqSlider),
    lowCutSlopeSliderAttachment(audioProcessor.apvts, "lowcut_slope", lowCutSlopeSlider),
    highCutSlopeSliderAttachment(audioProcessor.apvts, "highcut_slope", highCutSlopeSlider)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    for(auto* comp : getComps())
    {
        addAndMakeVisible(comp);
    }
    setSize (600, 400);
}

SimpleEQAudioProcessorEditor::~SimpleEQAudioProcessorEditor()
{
}

//==============================================================================
void SimpleEQAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void SimpleEQAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();

    auto responseArea = bounds.removeFromTop(bounds.getHeight() / 3.f);

    auto lowCutArea  = bounds.removeFromLeft(bounds.getWidth() / 3.f);
    auto highCutArea = bounds.removeFromRight(bounds.getWidth() / 2.f);

    lowCutFreqSlider.setBounds(lowCutArea.removeFromTop(lowCutArea.getHeight() / 2.f));
    lowCutSlopeSlider.setBounds(lowCutArea);
    
    highCutFreqSlider.setBounds(highCutArea.removeFromTop(highCutArea.getHeight() / 2.f));
    highCutSlopeSlider.setBounds(highCutArea);

    peakFreqSlider.setBounds(bounds.removeFromTop(bounds.getHeight() / 3.f));
    peakGainSlider.setBounds(bounds.removeFromTop(bounds.getHeight() / 2.f));
    peakQualitySlider.setBounds(bounds);
}


std::vector<juce::Component*> SimpleEQAudioProcessorEditor::getComps()
{
    return
    {
        &peakFreqSlider,
        &peakGainSlider,
        &peakQualitySlider,
        &lowCutFreqSlider,
        &highCutFreqSlider,
        &lowCutSlopeSlider,
        &highCutSlopeSlider
    };
}
