#pragma once
#include <string>
#include <vector>
#include <memory>
#include "lexer/tokens.h"
#include "psc/variable.h"
#include "psc/array.h"
#include "psc/procedure.h"
#include "nodes/nodeResult.h"

namespace PSC {
    class Context {
    private:
        Context *parent;
        std::string name;
        std::vector<std::unique_ptr<Variable>> variables;
        std::vector<std::unique_ptr<Array>> arrays;
        std::vector<std::unique_ptr<Procedure>> procedures;
        std::vector<std::unique_ptr<Function>> functions;
        std::vector<std::unique_ptr<EnumTypeDefinition>> enums;
        std::vector<std::unique_ptr<PointerTypeDefinition>> pointers;
        std::vector<std::unique_ptr<CompositeTypeDefinition>> composites;

    public:
        const Token *switchToken = nullptr;

        const bool isFunctionCtx;
        std::unique_ptr<NodeResult> returnValue;
        const PSC::DataType returnType;

        Context(Context *parent, const std::string &name);

        Context(Context *parent, const std::string &name, bool isFunctionCtx, PSC::DataType returnType);

        // For copying composites
        explicit Context(const Context &other);

        // Only for composites
        void copyVariableData(const Context &other);

        static std::unique_ptr<Context> createGlobalContext();

        Context *getParent() const;

        const std::string &getName() const;

        void addVariable(Variable *variable);

        Variable *getVariable(const std::string &varName);

        void addProcedure(std::unique_ptr<Procedure> &&procedure);

        Procedure *getProcedure(const std::string &procedureName);

        void addFunction(std::unique_ptr<Function> &&function);

        Function *getFunction(const std::string &functionName);

        void addArray(std::unique_ptr<Array> &&array);

        Array *getArray(const std::string &arrayName);

        PSC::DataType getType(const Token &token);

        bool isIdentifierType(const Token &identifier);

        Enum *getEnumElement(const std::string &value);

        void createEnumDefinition(EnumTypeDefinition &&definition);

        void createPointerDefinition(PointerTypeDefinition &&definition);

        void createCompositeDefinition(CompositeTypeDefinition &&definition);

        const EnumTypeDefinition *getEnumDefinition(const std::string &name);

        const PointerTypeDefinition *getPointerDefinition(const std::string &name);

        const CompositeTypeDefinition *getCompositeDefinition(const std::string &name);
    };
}
