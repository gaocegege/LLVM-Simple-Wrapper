#include "llvmgenerator.h"

int main()
{
	llvmgenerator::LLVMGenerator testClass;
	std::vector<std::string> v;
	llvm::Value *arg;
	arg = testClass.integerNum(1);
	v.push_back("x");
	testClass.mainProto();

	// test for define
	llvm::Value *val = testClass.identifier("gaoce");
	llvm::Value *valarr = testClass.array("gaocegege", 3);

	//test for set values
	testClass.setArrayValue(valarr, testClass.integerNum(10), 1);
	testClass.setValue(val, testClass.integerNum(10));

	//test for get values
	testClass.callPrint(testClass.getArrayValue(valarr, 1));
	testClass.callPrint(testClass.getValue(val));

	testClass.ret(testClass.expression('+', val, testClass.getValue(val)));
	testClass.run(testClass.getFuncName("main"));
}