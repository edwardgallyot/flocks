#pragma once

#include "aminals_processor.hpp"

namespace flocks
{

class Processor final : public aminals::Processor
{
    juce::AudioProcessorEditor* create_editor() override;
    const juce::String get_name() const override;
};

}
