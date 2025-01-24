#include "psc/builtinFunctions/functions.h"

#include "psc/procedure.h"
#include "psc/scope/context.h"
#include "psc/types/datatypes.h"
#include "psc/types/types.h"
#include "psc/variable.h"

#include <raylib.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <memory>
#include <ostream>
// helper function
PSC::Variable*
getVariable(PSC::Context& ctx, const std::string& name, PSC::DataType type) {
  auto* var = ctx.getVariable(name);
  if (var == nullptr || var->type != type)
    std::abort();
  return var;
}
template <typename T>
auto getVariableValue(
    PSC::Context& ctx,
    const std::string& name,
    PSC::DataType type) {
  PSC::Variable* var = getVariable(ctx, name, type);
  return var->get<T>().value;
}
template <typename T>
T getMemberVariable(
    PSC::Composite& compo,
    const std::string& memberName) // Changed to const reference for efficiency
{
  // Get the member
  auto* member = compo.getMember(memberName);
  if (!member) {
    throw std::runtime_error("MEMBER NOT FOUND: " + memberName);
  }

  // Ensure the member name matches
  if (member->name != memberName) {
    throw std::runtime_error(
        "MEMBER NAME MISMATCH: Expected " + memberName + ", Found " +
        member->name);
  }

  // Perform dynamic cast to the desired type
  auto* var = dynamic_cast<PSC::Variable*>(member);
  auto res = var->get<T>();
  return res;
};
//-----------------------------------------------
//
//
//
//
PSC::RLInitWindow::RLInitWindow() : PSC::Procedure("INIT_WINDOW") {
  parameters.reserve(3);
  parameters.emplace_back("width", PSC::DataType::INTEGER, false);
  parameters.emplace_back("height", PSC::DataType::INTEGER, false);
  parameters.emplace_back("title", PSC::DataType::STRING, false);
}

void PSC::RLInitWindow::run(PSC::Context& ctx) {
  int w = getVariableValue<Integer>(ctx, "width", PSC::DataType::INTEGER);
  int h = getVariableValue<Integer>(ctx, "height", PSC::DataType::INTEGER);
  std::string t = getVariableValue<String>(ctx, "title", PSC::DataType::STRING);
  InitWindow(w, h, t.c_str());
}

PSC::RLWindowShouldClose::RLWindowShouldClose()
    : PSC::Function("WINDOW_SHOULD_CLOSE", PSC::DataType::BOOLEAN)

{}
void PSC::RLWindowShouldClose::run(PSC::Context& ctx) {
  auto ret = std::make_unique<Boolean>();

  // Set the return value
  ret->value = WindowShouldClose();
  ctx.returnValue =
      std::make_unique<NodeResult>(std::move(ret), PSC::DataType::BOOLEAN);
}

PSC::RLBeginDrawing::RLBeginDrawing()
    : PSC::Procedure("BEGIN_DRAWING")

{}
void PSC::RLBeginDrawing::run(PSC::Context&) {
  BeginDrawing();
}

PSC::RLEndDrawing::RLEndDrawing()
    : PSC::Procedure("END_DRAWING")

{}
void PSC::RLEndDrawing::run(PSC::Context&) {
  EndDrawing();
}

PSC::RLDrawText::RLDrawText() : Procedure("DRAW_TEXT") {
  parameters.reserve(4);
  parameters.emplace_back("text", PSC::DataType::STRING, false);
  parameters.emplace_back("posX", PSC::DataType::INTEGER, false);
  parameters.emplace_back("posY", PSC::DataType::INTEGER, false);
  parameters.emplace_back("fontSize", PSC::DataType::INTEGER, false);
  parameters.emplace_back("color", PSC::DataType::COMPOSITE, false);
}

void PSC::RLDrawText::run(PSC::Context& ctx) {
  auto text = getVariableValue<String>(ctx, "text", PSC::DataType::STRING);
  auto posX = getVariableValue<Integer>(ctx, "posX", PSC::DataType::INTEGER);
  auto posY = getVariableValue<Integer>(ctx, "posY", PSC::DataType::INTEGER);
  auto fontSize =
      getVariableValue<Integer>(ctx, "fontSize", PSC::DataType::INTEGER);
  auto* COLOR = getVariable(ctx, "color", PSC::DataType::COMPOSITE);
  auto color = COLOR->get<Composite>();

  auto r = getMemberVariable<Integer>(color, "R");
  auto g = getMemberVariable<Integer>(color, "G");
  auto b = getMemberVariable<Integer>(color, "B");
  auto a = getMemberVariable<Integer>(color, "A");

  DrawText(text.c_str(), posX, posY, fontSize, Color(r, g, b, a));
}
