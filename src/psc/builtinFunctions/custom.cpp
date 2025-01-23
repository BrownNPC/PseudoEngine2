#include "pch.h"
#include <algorithm>

#include "psc/builtinFunctions/functions.h"
#include "psc/error.h"
#include "psc/file.h"
#include "psc/scope/context.h"
#include "psc/types/types.h"
#include "psc/variable.h"
PSC::BuiltinFnGyatt::BuiltinFnGyatt()
    : Function("LENGTH", PSC::DataType::INTEGER)
{
    parameters.emplace_back("String", PSC::DataType::STRING, false);
}

void PSC::BuiltinFnGyatt::run(PSC::Context &ctx) {
    PSC::Variable *var = ctx.getVariable("String");
    if (var == nullptr || var->type != PSC::DataType::STRING) std::abort();

    int_t len = (int_t) var->get<PSC::String>().value.size();
    auto ret = std::make_unique<PSC::Integer>(len);

    ctx.returnValue = std::make_unique<NodeResult>(std::move(ret), PSC::DataType::INTEGER);
}
