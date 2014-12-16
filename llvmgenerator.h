#ifndef LLVMGENERATOR_HPP
#define LLVMGENERATOR_HPP

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/IRBuilder.h"

namespace llvmgenerator
{
	class LLVMGenerator
	{
	public:
		LLVMGenerator();
		~LLVMGenerator();
		// main block
		void mainFunc();
		// function call
		void call();
		// function define
		void func();
		void ret();
		// class define
		void classDef();

		// var define
		void var();
		// expression
		void expression();
		// array define
		void array();

		// external function define
		void externalFunc();

		void dump();

	private:
		static llvm::LLVMContext &context;
		static llvm::Module *module;
		static llvm::IRBuilder<> builder;
		
	};
}

#endif