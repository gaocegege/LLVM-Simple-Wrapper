#include "llvmgenerator.h"

int main()
{
	llvmgenerator::LLVMGenerator testClass;
	testClass.mainProto();
	testClass.expression('+', 1, 2);
	testClass.expression('+', 1, 2);
	testClass.ret(testClass.expression('+', 1, 2));
	testClass.dump();
	testClass.run(testClass.getFuncName("main"));
}