#include "pch.h"
#include <algorithm>

#include "psc/builtinFunctions/functions.h"
#include "psc/error.h"
#include "psc/file.h"
#include "psc/scope/context.h"
#include "psc/types/types.h"
#include "psc/variable.h"
PSC::BuiltinFnGyatt::BuiltinFnGyatt()
    : Function("Gyatt", PSC::DataType::STRING)
{

}

void PSC::BuiltinFnGyatt::run(PSC::Context &ctx) {

    auto ret = std::make_unique<PSC::String>("GYATT");

    ctx.returnValue = std::make_unique<NodeResult>(std::move(ret), PSC::DataType::STRING);
}
