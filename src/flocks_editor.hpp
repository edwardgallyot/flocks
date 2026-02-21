#pragma once 

#include "flocks_processor.hpp"
#include "aminals_editor.hpp"

namespace flocks
{
class Editor final : public aminals::Editor
{
public:
    Editor(Processor&);
};
}
