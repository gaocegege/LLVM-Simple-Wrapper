#ifndef LLVMGENERATOR_HPP
#define LLVMGENERATOR_HPP

#include <llvm/Support/TargetSelect.h>  
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
// #include "llvm/ExecutionEngine/MCJIT.h"
#include <llvm/ExecutionEngine/SectionMemoryManager.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/PassManager.h>
#include <llvm/Transforms/Scalar.h>
#include <iostream>


#include "../semantic/block_common.hpp"

namespace llvmgenerator
{
	// the lowest wrapper
	class LLVMGenerator
	{
	public:
		LLVMGenerator();
		~LLVMGenerator();
		// main block
		void mainProto();

		// callee->		function name
		// arguments->	function arguments
		// $return->	//todo
		llvm::Value *call(std::string &callee, std::vector<llvm::Value *> arguments);
		
		// name->		function name
		// arguments->	function arguments
		// $return->	//todo	
		void proto(std::string &name, std::vector<std::string> arguments);
		void retVoid();
		void ret(llvm::Value *val);
		// class define
		void classDef();

		// var define
		llvm::Value *integerNum(int num);
		llvm::Value *doubleNum(double num);
		llvm::Value *identifier(std::string name);
		// expression
		// void binaryExp(std::string &op, );
		llvm::Value *expression(char op, int left, int right);
		llvm::Value *expression(char op, double left, double right);
		// array define
		void array();

		// external function define
		void external();

		//debuger help func
		void dump();
		llvm::Function *getFuncName(std::string funcname);
		void run(llvm::Function *F);

	private:
		static llvm::LLVMContext &context;
		static llvm::Module *module;
		static llvm::IRBuilder<> builder;
		//JIT
		// static llvm::ExecutionEngine *executeEngine;

		llvm::Value *Error(const char *Str){std::cout << "Err\n";return 0;}
		
	};
}

#endif