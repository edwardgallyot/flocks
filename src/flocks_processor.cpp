#include "flocks_processor.hpp"
#include "flocks_editor.hpp"
#include "flocks_params.hpp"

using namespace flocks;

Processor::Processor() :
    params(*this, {
        make_param(Parameter::Bypass),
        make_param(Parameter::Volume),
        make_param(Parameter::Attack),
        make_param(Parameter::Release),
        make_param(Parameter::Reverb),
        make_param(Parameter::Cutoff),
        make_param(Parameter::Reverse)
    }),
    sampler()
{
}

juce::AudioProcessorEditor* Processor::create_editor()
{
    return new Editor(*this);
}

const juce::String Processor::get_name() const
{
    return JucePlugin_Name;
}

void Processor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    this->sampler.prepare(sampleRate, samplesPerBlock);
}

void Processor::processBlock (juce::AudioBuffer<float>& samples, juce::MidiBuffer& midi)
{
    this->sampler.process(samples, midi);
}

void Processor::releaseResources()
{
    this->sampler.release();
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Processor();
}


