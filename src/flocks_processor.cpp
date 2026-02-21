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
    })
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

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Processor();
}
