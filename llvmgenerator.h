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
		llvm::Value *call(const std::string &callee, const std::vector<llvm::Value *> &arguments);
		llvm::Value *callPrint(llvm::Value *arg);

		// name->		function name
		// arguments->	function arguments
		// $return->	//todo	
		llvm::Function *func(const std::string &name, const std::vector<std::string> &arguments);
		void retVoid();
		void ret(llvm::Value *val);

		// class define*
		void classDef();

		// var define
		llvm::Value *globalString(const std::string &num);
		llvm::Value *integerNum(const int &num);
		llvm::Value *doubleNum(const double &num);
		llvm::Value *identifier(const std::string &name);

		// expression
		llvm::Value *expression(const char &op, const int &left, const int &right);
		llvm::Value *expression(const char &op, const double &left, const double &right);
		llvm::Value *expression(const char &op, llvm::Value *leftSide, llvm::Value *rightSide);
		// array define
		void array();

		// control flow
		llvm::Value *ifStat(llvm::Value *cond);

		// external function define
		llvm::Constant *externalPrint();

		//debuger help func and JIT
		void dump();
		llvm::Function *getFuncName(const std::string &funcname);
		void run(llvm::Function *F);

	private:
		static llvm::LLVMContext &context;
		static llvm::Module *module;
		static llvm::IRBuilder<> builder;
		llvm::Value *Error(const char *Str){std::cout << "Err\n";return 0;}
		
		//func proto
		llvm::Function *proto(const std::string &name, const std::vector<std::string> &arguments);
	};
}

#endif