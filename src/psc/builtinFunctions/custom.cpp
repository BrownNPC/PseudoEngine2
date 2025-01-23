#include "psc/builtinFunctions/functions.h"

#include "psc/procedure.h"
#include "psc/scope/block.h"
#include "psc/scope/context.h"
#include "psc/types/datatypes.h"
#include "psc/types/types.h"
#include "psc/variable.h"

#include <memory>
#include <raylib.h>
#include <unistd.h>
// helper function
template<typename T>
auto getVariable(PSC::Context& ctx, const std::string& name, PSC::DataType type)
  -> decltype(std::declval<PSC::Variable>().get<T>().value)
{
  PSC::Variable* var = ctx.getVariable(name);
  if (var == nullptr || var->type != type)
    std::abort();
  return var->get<T>().value;
}

PSC::RLInitWindow::RLInitWindow()
  : PSC::Procedure("INIT_WINDOW")
{
  parameters.reserve(3);
  parameters.emplace_back("width", PSC::DataType::INTEGER, false);
  parameters.emplace_back("height", PSC::DataType::INTEGER, false);
  parameters.emplace_back("title", PSC::DataType::STRING, false);
}

void PSC::RLInitWindow::run(PSC::Context& ctx)
{
  int w = getVariable<Integer>(ctx, "width", PSC::DataType::INTEGER);
  int h = getVariable<Integer>(ctx, "height", PSC::DataType::INTEGER);
  std::string t = getVariable<String>(ctx, "title", PSC::DataType::STRING);
  InitWindow(w, h, t.c_str());
}

PSC::RLWindowShouldClose::RLWindowShouldClose()
  : PSC::Function("WINDOW_SHOULD_CLOSE", PSC::DataType::BOOLEAN)

{
}
void PSC::RLWindowShouldClose::run(PSC::Context& ctx)
{
  auto ret = std::make_unique<Boolean>();

  // Set the return value
  ret->value = WindowShouldClose();
  ctx.returnValue =
    std::make_unique<NodeResult>(std::move(ret), PSC::DataType::BOOLEAN);
}

PSC::RLBeginDrawing::RLBeginDrawing()
  : PSC::Procedure("BEGIN_DRAWING")

{
}
void PSC::RLBeginDrawing::run(PSC::Context& )
{
  BeginDrawing();
}

PSC::RLEndDrawing::RLEndDrawing()
  : PSC::Procedure("END_DRAWING")

{
}
void PSC::RLEndDrawing::run(PSC::Context& )
{
  EndDrawing();
}
