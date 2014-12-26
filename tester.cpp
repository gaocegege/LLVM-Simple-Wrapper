#include "llvmgenerator.h"

int main()
{
	llvmgenerator::LLVMGenerator testClass;
	std::vector<std::string> v;
	llvm::Value *arg;
	arg = testClass.integerNum(1);
	v.push_back("x");
	testClass.mainProto();
	llvm::Value *val = testClass.identifier("gaoce");
	llvm::Value *valarr = testClass.array("gaocegege");
	testClass.callPrint(val);
	testClass.ret(testClass.expression('/', 1, 2));
	testClass.dump();
	testClass.run(testClass.getFuncName("main"));
}