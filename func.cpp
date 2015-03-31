#include "llvmgenerator.h"
#include <iostream>

int main(int argc, char const *argv[])
{
	llvmgenerator::LLVMGenerator testCase;
	llvm::Value *id = testCase.globalVariable("cece");
	std::vector<std::string> v;
	v.push_back("n");
	llvm::Function *func = testCase.func("jiecheng", v, "int");
	std::cout << testCase.nvt["n"] << "\n";
	testCase.getArrayValue(id, testCase.integerNum(1));
	testCase.callPrint(testCase.getArrayValue(id, testCase.integerNum(1)));
	llvm::Value *cond = testCase.expression('>', testCase.nvt["n"], testCase.integerNum(1));
	// testCase.ret(testCase.nvt["n"]);
	testCase.ret(testCase.ifStat(cond));
	testCase.mainProto();
	std::vector<llvm::Value *> arg;
	arg.push_back(testCase.integerNum(4));
	testCase.ret(testCase.call(func, arg));

	testCase.dump();
	testCase.run(testCase.getFuncName("main"));
	return 0;
}