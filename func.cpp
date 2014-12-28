#include "llvmgenerator.h"
#include <iostream>

int main(int argc, char const *argv[])
{
	llvmgenerator::LLVMGenerator testCase;
	std::vector<std::string> v;
	v.push_back("n");
	llvm::Function *func = testCase.func("jiecheng", v);
	// std::cout << llvmgenerator::LLVMGenerator::nvt["n"] << "\n";
	llvm::Value *cond = testCase.expression('>', llvmgenerator::LLVMGenerator::nvt["n"], testCase.integerNum(1));
	// testCase.ret(llvmgenerator::LLVMGenerator::nvt["n"]);
	testCase.ret(testCase.ifStat(cond));
	testCase.mainProto();
	std::vector<llvm::Value *> arg;
	arg.push_back(testCase.integerNum(4));
	testCase.ret(testCase.call("jiecheng", arg));

	testCase.dump();
	testCase.run(testCase.getFuncName("main"));
	return 0;
}