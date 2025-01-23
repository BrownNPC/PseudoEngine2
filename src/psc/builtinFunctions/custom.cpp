#include "psc/builtinFunctions/functions.h"

#include "psc/procedure.h"
#include "psc/scope/context.h"
#include "psc/types/datatypes.h"
#include "psc/types/types.h"
#include "psc/variable.h"

#include <raylib.h>
void check(PSC::Variable* var, PSC::DataType type)
{
  if (var == nullptr || var->type != type)
    std::abort();
}

PSC::RLInitWindow::RLInitWindow()
  : PSC::Procedure("InitWindow")
{
  parameters.reserve(3);
  parameters.emplace_back("width", PSC::DataType::INTEGER, false);
  parameters.emplace_back("height", PSC::DataType::INTEGER, false);
  parameters.emplace_back("title", PSC::DataType::STRING, false);
}

void PSC::RLInitWindow::run(PSC::Context& ctx)
{
  PSC::Variable* width = ctx.getVariable("width");
  PSC::Variable* height = ctx.getVariable("height");
  PSC::Variable* title = ctx.getVariable("title");
  check(width, PSC::DataType::INTEGER);
  check(height, PSC::DataType::INTEGER);
  check(title, PSC::DataType::STRING);
  auto w = width->get<Integer>().value;
  auto h = height->get<Integer>().value;
  auto t = title->get<String>().value;
  InitWindow(w,h,t.c_str());
}
