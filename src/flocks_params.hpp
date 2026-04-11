namespace flocks
{
    enum class Parameter
    {
        Bypass,
        Volume,
        Attack,
        Release,
        Reverb,
        Cutoff,
        Reverse,
    };

    constexpr const char* get_param_name(Parameter p)
    {
        switch (p)
        {
            case Parameter::Bypass:  return "Bypass";
            case Parameter::Volume:  return "Volume";
            case Parameter::Attack:  return "Attack";
            case Parameter::Release: return "Release";
            case Parameter::Reverb:  return "Reverb";
            case Parameter::Cutoff:  return "Cutoff";
            case Parameter::Reverse: return "Reverse";
        }
        return "";
    }

    constexpr const char* get_param_id(Parameter p)
    {
        return get_param_name(p);
    }

    template <Parameter P>
    std::unique_ptr<juce::RangedAudioParameter> make_param()
    {
        const auto pid = get_param_id(P);
        const auto name = get_param_name(P);
        switch (P)
        {
            case Parameter::Bypass:
                return std::make_unique<juce::AudioParameterBool>(
                    pid,
                    name,
                    false
                );

            case Parameter::Volume:
                return std::make_unique<juce::AudioParameterFloat>(
                    pid,
                    name,
                    juce::NormalisableRange<float>(0.0f, 1.0f),
                    0.8f
                );

            case Parameter::Attack:
                return std::make_unique<juce::AudioParameterFloat>(
                    pid,
                    name,
                    juce::NormalisableRange<float>(0.1f, 5.0f),
                    1.0f
                );

            case Parameter::Release:
                return std::make_unique<juce::AudioParameterFloat>(
                    pid,
                    name,
                    juce::NormalisableRange<float>(0.1f, 5.0f),
                    1.0f
                );

            case Parameter::Reverb:
                return std::make_unique<juce::AudioParameterFloat>(
                    pid,
                    name,
                    juce::NormalisableRange<float>(0.0f, 1.0f),
                    0.2f
                );

            case Parameter::Cutoff:
                return std::make_unique<juce::AudioParameterFloat>(
                    pid,
                    name,
                    juce::NormalisableRange<float>(20.0f, 20000.0f, 0.0f, 0.5f),
                    1000.0f
                );

            case Parameter::Reverse:
                return std::make_unique<juce::AudioParameterBool>(
                    pid,
                    name,
                    false
                );
        }

        return {};
    }
}
 
