#pragma once

#include "aminals_processor.hpp"
#include "aminals_parameter_list.hpp"

namespace flocks
{

class Processor final : public aminals::Processor
{
public:
    Processor();
    juce::AudioProcessorEditor* create_editor() override;
    const juce::String get_name() const override;
private:
    aminals::Parameter_List params;
};
}
