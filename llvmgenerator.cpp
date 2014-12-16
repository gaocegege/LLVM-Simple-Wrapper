#include "llvmgenerator.h"

using namespace llvmgenerator;

llvm::LLVMContext& LLVMGenerator::context = llvm::getGlobalContext();

llvm::Module* LLVMGenerator::module = new llvm::Module("Our Code", LLVMGenerator::context);

llvm::IRBuilder<> LLVMGenerator::builder = llvm::IRBuilder<>(LLVMGenerator::context);

LLVMGenerator::LLVMGenerator()
{

}

LLVMGenerator::~LLVMGenerator()
{

}

void LLVMGenerator::mainFunc()
{
	// set the return type
	llvm::FunctionType *funcType = llvm::FunctionType::get(builder.getVoidTy(), false);
	// get the main func
	llvm::Function *mainFunc = 
    llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main", module);

    // set the main as a entry
    llvm::BasicBlock *entry = llvm::BasicBlock::Create(context, "entrypoint", mainFunc);
  	builder.SetInsertPoint(entry);

}

void LLVMGenerator::call()
{
//todo
}

void LLVMGenerator::func()
{
//todo
}

void LLVMGenerator::ret()
{
	builder.CreateRetVoid();
}

void LLVMGenerator::classDef()
{
//todo
}

void LLVMGenerator::var()
{
//todo
}

void LLVMGenerator::expression()
{
//todo
}

void LLVMGenerator::array()
{
//todo
}

void LLVMGenerator::externalFunc()
{
//todo
}

void LLVMGenerator::dump()
{
	module->dump();
}