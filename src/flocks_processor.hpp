#pragma once

#include "aminals_processor.hpp"
#include "aminals_parameter_list.hpp"
#include "aminals_sampler.hpp"
#include "aminals_arena.hpp"

namespace flocks
{

class Processor final : public aminals::Processor
{
public:
    using aminals::Processor::processBlock;
    
    Processor();
    ~Processor();
    
    juce::AudioProcessorEditor* create_editor() override;
    const juce::String get_name() const override;
    
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi) override;
    void releaseResources() override; 
    
private:
    using Arena = aminals::Arena<1024*1024>;
    Arena arena;
    Arena::Ptr<aminals::Parameter_List> params;
    Arena::Ptr<aminals::Sampler> sampler;
};
}
