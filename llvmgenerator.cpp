#include "llvmgenerator.h"

using namespace llvmgenerator;

llvm::LLVMContext& LLVMGenerator::context = llvm::getGlobalContext();

llvm::Module* LLVMGenerator::module = new llvm::Module("Our Code", LLVMGenerator::context);

llvm::IRBuilder<> LLVMGenerator::builder = llvm::IRBuilder<>(LLVMGenerator::context);

LLVMGenerator::LLVMGenerator()
{
	externalPrint();
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

llvm::Value* LLVMGenerator::call(const std::string &callee, const std::vector<llvm::Value *> &arguments)
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

llvm::Value *LLVMGenerator::callPrint(llvm::Value *arg)
{
	llvm::Value *callee = externalPrint();
	std::vector<llvm::Value *> v;
	v.push_back(arg);
	v.insert(v.begin(), builder.CreateGlobalStringPtr("output: %d\t\n"));
	std::cout << v[0] << std::endl;
	return builder.CreateCall(callee, v, "PRINT_via_printf");
}

llvm::Function *LLVMGenerator::proto(const std::string &name, const std::vector<std::string> &arguments)
{
	// only doubles now 
	std::vector<llvm::Type *> Doubles(arguments.size(),
	                         llvm::Type::getDoubleTy(context));
	// the return type only supports double now
		llvm::FunctionType *FT = llvm::FunctionType::get(llvm::Type::getDoubleTy(context),
	                                   Doubles, false);

	llvm::Function *F = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, name, module);
	if (F->getName() != name) 
	{
		// Delete the one we just made and get the existing one.
		F->eraseFromParent();
		F = module->getFunction(name);

		// If F already has a body, reject this.
		if (!F->empty()) 
		{
	  		Error("redefinition of function");
	  		return 0;
		}

		// If F took a different number of args, reject.
		if (F->arg_size() != arguments.size()) 
		{
	  		Error("redefinition of function with different # args");
	  		return 0;
		}
	}

	// Set names for all arguments.
	unsigned Idx = 0;
	for (llvm::Function::arg_iterator AI = F->arg_begin(); Idx != arguments.size();
	   ++AI, ++Idx) {
		AI->setName(arguments[Idx]);

		// Add arguments to variable symbol table.
		// NamedValues[arguments[Idx]] = AI;
	}

	return F;
}

llvm::Function *LLVMGenerator::func(const std::string &name, const std::vector<std::string> &arguments)
{
	llvm::Function *TheFunction = proto(name, arguments);
  	if (TheFunction == 0)
    	return 0;
  
  	// Create a new basic block to start insertion into.
  	llvm::BasicBlock *BB = llvm::BasicBlock::Create(context, "entry", TheFunction);
  	builder.SetInsertPoint(BB);

 //  	// generate the body code
	// if (Value *RetVal = Body->Codegen()) 
	// {
	// 	// Finish off the function.
	// 	builder.CreateRet(RetVal);

	// // Validate the generated code, checking for consistency.
	// verifyFunction(*TheFunction);

	// return TheFunction;
	// }

	// Error reading body, remove function.
	// TheFunction->eraseFromParent();
	// return 0;
	return TheFunction;
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

llvm::Value *LLVMGenerator::globalString(const std::string &num)
{
	return builder.CreateGlobalStringPtr(num);
}

llvm::Value* LLVMGenerator::integerNum(const int &num)
{
	// may have a bug
	return llvm::ConstantInt::get(context, llvm::APInt(32, num, true));  
}

llvm::Value* LLVMGenerator::doubleNum(const double &num)
{
	return llvm::ConstantFP::get(context, llvm::APFloat(num));
}

llvm::Value* LLVMGenerator::identifier(const std::string &name)
{
	//TODO
	return 0;
}

llvm::Value *LLVMGenerator::expression(const char &op, const int &left, const int &right)
{
//todo

	llvm::Value *result;
	llvm::Value *leftSide = integerNum(left);
	llvm::Value	*rightSide = integerNum(right);
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
		//have bugs:double
		case '<':
    		leftSide = builder.CreateFCmpULT(leftSide, rightSide, "cmptmp");
    		// Convert bool 0/1 to double 0.0 or 1.0
    		return builder.CreateUIToFP(leftSide, llvm::Type::getDoubleTy(context),
                                "booltmp");
		default:
			return 0;
	}
	return result;
}

llvm::Value *LLVMGenerator::expression(const char &op, const double &left, const double &right)
{
//todo

	llvm::Value *result;
	llvm::Value *leftSide = doubleNum(left);
	llvm::Value	*rightSide = doubleNum(right);
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
		//have bugs:double
		case '<':
    		leftSide = builder.CreateFCmpULT(leftSide, rightSide, "cmptmp");
    		// Convert bool 0/1 to double 0.0 or 1.0
    		return builder.CreateUIToFP(leftSide, llvm::Type::getDoubleTy(context),
                                "booltmp");
		default:
			return 0;
	}
	return result;
}

llvm::Value *LLVMGenerator::expression(const char &op, llvm::Value *leftSide, llvm::Value *rightSide)
{
	llvm::Value *result;
	switch(op)
	{
		case '+':
			result = builder.CreateFAdd(leftSide, rightSide, "addtmp");
			break;
		case '-':
			result = builder.CreateFSub(leftSide, rightSide, "subtmp");
			break;
		case '*':
			result = builder.CreateFMul(leftSide, rightSide, "multmp");
			break;
		case '/':
			//signed int div~?
			result = builder.CreateFDiv(leftSide, rightSide, "divtmp");
			break;
		//have bugs:double
		case '<':
    		leftSide = builder.CreateFCmpULT(leftSide, rightSide, "cmptmp");
    		// Convert bool 0/1 to double 0.0 or 1.0
    		return builder.CreateUIToFP(leftSide, llvm::Type::getDoubleTy(context),
                                "booltmp");
		default:
			return 0;
	}
	return result;
}

void LLVMGenerator::array()
{
//todo
}

llvm::Value *LLVMGenerator::ifStat(llvm::Value *cond)
{
	return 0;
}

llvm::Constant *LLVMGenerator::externalPrint()
{
	std::vector<llvm::Type *> args;
	args.push_back(builder.getInt8PtrTy());

	llvm::Constant *printf_func = module->getOrInsertFunction("printf",
										llvm::FunctionType::get(builder.getInt32Ty(), args,
		/*must be true to get other params*/true));

	return printf_func;
}

llvm::Function *LLVMGenerator::getFuncName(const std::string &funcname)
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