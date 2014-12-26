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
	llvm::Value *buf = testClass.getValue(val);
	testClass.callPrint(buf);
	testClass.ret(testClass.expression('+', buf, buf));
	testClass.run(testClass.getFuncName("main"));
}