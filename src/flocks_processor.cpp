#include "flocks_processor.hpp"
#include "flocks_editor.hpp"

using namespace flocks;

juce::AudioProcessorEditor* Processor::create_editor()
{
    return new Editor(*this);
}

const juce::String Processor::get_name() const
{
    return JucePlugin_Name;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Processor();
}
