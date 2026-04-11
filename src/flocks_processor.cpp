
#include "flocks_processor.hpp"
#include "flocks_editor.hpp"
#include "flocks_params.hpp"
#include "flocks_map.h"

using namespace flocks;

struct Processor::Impl
{
	Impl(Processor& p) : params(p, juce::AudioProcessorValueTreeState::ParameterLayout {
        make_param<Parameter::Bypass>(),
        make_param<Parameter::Volume>(),
        make_param<Parameter::Attack>(),
        make_param<Parameter::Release>(),
        make_param<Parameter::Reverb>(),
        make_param<Parameter::Cutoff>(),
        make_param<Parameter::Reverse>()
		}),
			 sampler()
		{}
	
	aminals::Parameter_List params;
    aminals::Sampler sampler;
	FLOCKS_SAMPLE_COUNTS sample_counts;
	FLOCKS_SAMPLE_VOICES voice_assignments;
	juce::SmoothedValue<float> output_value;
	std::vector<float> output_gain_buffer;
};

Processor::Processor() :
    arena(),
    impl(arena.make_unique<flocks::Processor::Impl>(*this))
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
	this->impl->sampler.set_streaming_file("/home/edg/dev/aminal_juce/flocks/src/flocks_map.bin");
	this->impl->sampler.set_total_sizes(SAMPLE_MAP_TOTAL_SIZES, NUM_FLOCKS_SAMPLES);
	this->impl->sampler.set_offsets(SAMPLE_MAP_OFFSETS, NUM_FLOCKS_SAMPLES);
	this->impl->sampler.set_channel_strides(SAMPLE_MAP_CHANNEL_SIZES, NUM_FLOCKS_SAMPLES);
	this->impl->sampler.set_midi_map(MIDI_MAP);
	this->impl->sampler.set_sample_names(SAMPLE_NAMES, NUM_FLOCKS_SAMPLES);
	this->impl->sampler.set_voice_assignments(this->impl->voice_assignments.VOICES, NUM_FLOCKS_SAMPLES);
    this->impl->sampler.prepare(sampleRate, samplesPerBlock);
	this->impl->output_gain_buffer.resize((size_t)samplesPerBlock);
	this->impl->output_value.reset(sampleRate, 0.1f);
}

void Processor::processBlock (juce::AudioBuffer<float>& samples, juce::MidiBuffer& midi)
{
	this->impl->sampler.set_release(this->impl->params.get_tree().getRawParameterValue(get_param_name(Parameter::Release))->load());
	this->impl->sampler.set_attack(this->impl->params.get_tree().getRawParameterValue(get_param_name(Parameter::Attack))->load());


    this->impl->sampler.process(samples, midi);

	this->impl->output_value.setTargetValue(this->impl->params.get_tree().getRawParameterValue(get_param_name(Parameter::Volume))->load());
	for (int s = 0; s < samples.getNumSamples(); ++s)
	{
		this->impl->output_gain_buffer[(size_t)s] = this->impl->output_value.getNextValue();
	}
	for (int c = 0; c < samples.getNumChannels(); ++c)
	{
		juce::FloatVectorOperations::multiply(samples.getWritePointer(c), this->impl->output_gain_buffer.data(), samples.getNumSamples());
	}
}

void Processor::releaseResources()
{
    this->impl->sampler.release();
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Processor();
}

static_assert(Processor::Memory_Bytes >= sizeof(flocks::Processor::Impl));
