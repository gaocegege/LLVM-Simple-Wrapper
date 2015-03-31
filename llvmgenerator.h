#ifndef LLVMGENERATOR_HPP
#define LLVMGENERATOR_HPP

#include <iostream>
#include <vector>
#include <map>
#include <string>

namespace llvm
{
    class Value;
    class Function;
    class Module;
    class BasicBlock;
    class IRBuilderDefault;
    class LLVMContext;
    class Constant;
}

namespace llvmgenerator
{
    // the lowest wrapper
    class LLVMGenerator
    {
    public:
        LLVMGenerator();
        ~LLVMGenerator();
        llvm::LLVMContext &context;
        llvm::Module *module;
        llvm::IRBuilderDefault *builder;
        std::map<std::string, llvm::Value *> nvt;

        // main block
        void mainProto();
        // void quicksort();

        // callee->     function name
        // arguments->  function arguments
        // $return->    //todo
        llvm::Value *call(llvm::Function *callee, const std::vector<llvm::Value *> &arguments);
        llvm::Value *callPrint(llvm::Value *arg);

        // name->       function name
        // arguments->  function arguments
        // $return->    //todo
        llvm::Function *func(const std::string &name, const std::vector<std::string> &arguments, const std::string &returnType);
        void retVoid();
        void ret(llvm::Value *val);

        // class define*
        void classDef();

        // var define
        llvm::Value *globalString(const std::string &num);
        llvm::Value *globalVariable(const std::string &name);
        llvm::Value *integerNum(const int &num);
        llvm::Value *doubleNum(const double &num);
        llvm::Value *identifier(const std::string &name);
        llvm::Value *array(const std::string &name, int size);
        llvm::Value *array(const std::string &name, llvm::Value *size);

        llvm::Value *identifier1(const std::string &name, int size);
        llvm::Value *globalIdentifier1(const std::string &name, int size);

        // value get
        llvm::Value *getValue(llvm::Value *name);
        llvm::Value *getArrayValue(llvm::Value *name, int index);
        llvm::Value *getArrayValue(llvm::Value *name, llvm::Value *index);

        // value set
        llvm::Value *setValue(llvm::Value *name, llvm::Value *value);
        llvm::Value *setArrayValue(llvm::Value *name, llvm::Value *value, int index);
        llvm::Value *setArrayValue(llvm::Value *name, llvm::Value *value, llvm::Value *index);

        // expression
        llvm::Value *expression(const char &op, const int &left, const int &right);
        llvm::Value *expression(const char &op, const double &left, const double &right);
        llvm::Value *expression(const char &op, llvm::Value *leftSide, llvm::Value *rightSide);

        // control flow
        // just for look
        // bug
        llvm::Value *ifStat(llvm::Value *cond);
        llvm::Value *whileStat();

        // label
        llvm::BasicBlock *createBlock(const std::string &name, llvm::Function *func);
        void setInsertBlock(llvm::BasicBlock *block);// need to set the block to insert the code

        // jump by label
        llvm::Value *unConditionJump(llvm::BasicBlock *block);
        llvm::Value *conditionJump(llvm::Value *cond, llvm::BasicBlock *trueBlock, llvm::BasicBlock *falseBlock);

        // external function define
        llvm::Constant *externalPrint();

        // debuger help func and JIT
        void dump();
        llvm::Function *getFuncName(const std::string &funcname);
        void run(llvm::Function *F);

    private:
        inline llvm::Value *Error(const char *str) {
            std::cout << "Err: " << str << std::endl;
            return nullptr;
        }

        // func proto
        llvm::Function *proto(const std::string &name, const std::vector<std::string> &arguments, const std::string &returnType);
    };

    inline LLVMGenerator &instance() {
        static LLVMGenerator lg;
        return lg;
    }
}

#endif