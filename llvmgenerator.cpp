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

void LLVMGenerator::mainProto()
{
	// set the return type
	llvm::FunctionType *funcType = llvm::FunctionType::get(llvm::Type::getInt32Ty(context), false);
	// get the main func
	llvm::Function *mainFunc = 
    llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main", module);

    // set the main as a entry
    llvm::BasicBlock *entry = llvm::BasicBlock::Create(context, "entrypoint", mainFunc);
  	builder.SetInsertPoint(entry);

}

llvm::Value* LLVMGenerator::call(std::string &callee, std::vector<llvm::Value *> arguments)
{
//todo
	llvm::Function *CalleeF = module->getFunction(callee);
	if (CalleeF == 0)
		return Error("Unknown function referenced");

		// If argument mismatch Error.
		if (CalleeF->arg_size() != arguments.size())
		return Error("Incorrect # arguments passed");

	return builder.CreateCall(CalleeF, arguments, "calltmp");
}

void LLVMGenerator::proto(std::string &name, std::vector<std::string> arguments)
{
	// // only doubles now 
	// std::vector<Type*> Doubles(arguments.size(),
 //                             llvm::Type::getDoubleTy(context));
 //  	FunctionType *FT = FunctionType::get(llvm::Type::getDoubleTy(context),
 //                                       Doubles, false);

 //  Function *F = Function::Create(FT, llvm::Function::ExternalLinkage, name, module);
 //  if (F->getName() != name) {
 //    // Delete the one we just made and get the existing one.
 //    F->eraseFromParent();
 //    F = module->getFunction(name);
    
 //    // If F already has a body, reject this.
 //    if (!F->empty()) {
 //      Error("redefinition of function");
 //      return 0;
 //    }
    
 //    // If F took a different number of args, reject.
 //    if (F->arg_size() != arguments.size()) {
 //      Error("redefinition of function with different # args");
 //      return 0;
 //    }
 //  }
  
 //  // Set names for all arguments.
 //  unsigned Idx = 0;
 //  for (Function::arg_iterator AI = F->arg_begin(); Idx != arguments.size();
 //       ++AI, ++Idx) {
 //    AI->setName(arguments[Idx]);
    
 //    // Add arguments to variable symbol table.
 //    // NamedValues[arguments[Idx]] = AI;
 //  }
  
 //  return F;
}

void LLVMGenerator::retVoid()
{
	//todo
	builder.CreateRetVoid();
}

void LLVMGenerator::ret(llvm::Value *val)
{
	builder.CreateRet(val);
}

void LLVMGenerator::classDef()
{
//todo
}

llvm::Value* LLVMGenerator::integerNum(int num)
{
	// may have a bug
	return llvm::ConstantInt::get(context, llvm::APInt(32, num, true));  
}

llvm::Value* LLVMGenerator::doubleNum(double num)
{
	return llvm::ConstantFP::get(context, llvm::APFloat(num));
}

llvm::Value* LLVMGenerator::identifier(std::string name)
{
	//TODO
}

llvm::Value *LLVMGenerator::expression(char op, int left, int right)
{
//todo

	llvm::Value *result;
	llvm::Value *leftSide = integerNum(left);
	llvm::Value	*rightSide = integerNum(right);

	std::cout << "Wrapper:";
	std::cout << left << op << right << std::endl;
	std::cout << "result: ";
	switch(op)
	{
		case '+':
			std::cout << left + right << std::endl;
			result = builder.CreateAdd(leftSide, rightSide, "addtmp");
			break;
		case '-':
			std::cout << left - right << std::endl;
			result = builder.CreateSub(leftSide, rightSide, "subtmp");
			break;
		case '*':
			std::cout << left * right << std::endl;
			result = builder.CreateMul(leftSide, rightSide, "multmp");
			break;
		case '/':
			std::cout << left / right << std::endl;
			//signed int div~?
			result = builder.CreateSDiv(leftSide, rightSide, "divtmp");
			break;
	}
	return result;
}

llvm::Value *LLVMGenerator::expression(char op, double left, double right)
{
//todo

	llvm::Value *result;
	llvm::Value *leftSide = doubleNum(left);
	llvm::Value	*rightSide = doubleNum(right);

	std::cout << "Wrapper:";
	std::cout << left << op << right << std::endl;
	std::cout << "result: ";
	switch(op)
	{
		case '+':
			std::cout << left + right << std::endl;
			result = builder.CreateFAdd(leftSide, rightSide, "addtmp");
			break;
		case '-':
			std::cout << left - right << std::endl;
			result = builder.CreateFSub(leftSide, rightSide, "subtmp");
			break;
		case '*':
			std::cout << left * right << std::endl;
			result = builder.CreateFMul(leftSide, rightSide, "multmp");
			break;
		case '/':
			std::cout << left / right << std::endl;
			//signed int div~?
			result = builder.CreateFDiv(leftSide, rightSide, "divtmp");
			break;
	}
	return result;
}

void LLVMGenerator::array()
{
//todo
}

void LLVMGenerator::external()
{
//todo
}

llvm::Function *LLVMGenerator::getFuncName(std::string funcname)
{
	return module->getFunction(funcname);
}

void LLVMGenerator::dump()
{
	module->dump();
}

void LLVMGenerator::run(llvm::Function *F)
{
	llvm::InitializeNativeTarget();
	std::string sError;
	llvm::ExecutionEngine* executeEngine = llvm::EngineBuilder(module).setErrorStr(&sError).create();
	if (!executeEngine) {  
        fprintf(stderr, "Creating ExecutionEngine error: %s\n", sError.c_str());  
        exit(EINVAL);  
    }
	std::cout << "Run...\n";
	llvm::verifyFunction(*F);
	F->dump();
	void *FPtr = executeEngine->getPointerToFunction(F);
	std::cout << "Get The Pointer...\n";
	// Cast it to the right type (takes no arguments, returns a double) so we
	// can call it as a native function.
	int (*FP)() = (int (*)())(intptr_t)FPtr;
	fprintf(stderr, "Evaluated: %d\n", FP());  
}