
#include "flocks_processor.hpp"
#include "flocks_editor.hpp"
#include "flocks_params.hpp"

using namespace flocks;

Processor::Processor() :
    arena(),
    params(arena.make_unique<aminals::Parameter_List>(*this, juce::AudioProcessorValueTreeState::ParameterLayout {
        make_param<Parameter::Bypass>(),
        make_param<Parameter::Volume>(),
        make_param<Parameter::Attack>(),
        make_param<Parameter::Release>(),
        make_param<Parameter::Reverb>(),
        make_param<Parameter::Cutoff>(),
        make_param<Parameter::Reverse>()
    })),
    sampler(arena.make_unique<aminals::Sampler>())
{
}

Processor::~Processor()
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
    // TODO(edg): Set this up so it takes a global location!
	this->sampler->set_streaming_file("/home/edg/dev/aminal_juce/flocks/src/flocks_map.bin");
    this->sampler->prepare(sampleRate, samplesPerBlock);
}

void Processor::processBlock (juce::AudioBuffer<float>& samples, juce::MidiBuffer& midi)
{
    this->sampler->process(samples, midi);
}

void Processor::releaseResources()
{
    this->sampler->release();
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Processor();
}

static_assert(Processor::Memory_Bytes >= sizeof(aminals::Sampler) + /*Some extra space*/ (1024 * 64));
