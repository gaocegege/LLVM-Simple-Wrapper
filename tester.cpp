#include "llvmgenerator.h"

int main()
{
	llvmgenerator::LLVMGenerator testClass;
	std::vector<std::string> v;
	llvm::Value *arg;
	arg = testClass.integerNum(1);
	v.push_back("x");
	testClass.mainProto();
	testClass.externalPrint();
	testClass.callPrint(arg);
	testClass.ret(testClass.expression('/', 1, 2));
	testClass.dump();
	testClass.run(testClass.getFuncName("main"));
}