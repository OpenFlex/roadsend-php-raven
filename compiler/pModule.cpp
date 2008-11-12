/* ***** BEGIN LICENSE BLOCK *****
;; Roadsend PHP Compiler
;;
;; Copyright (c) 2008 Shannon Weyrick <weyrick@roadsend.com>
;;
;; This program is free software; you can redistribute it and/or
;; modify it under the terms of the GNU General Public License
;; as published by the Free Software Foundation; either version 2
;; of the License, or (at your option) any later version.
;;
;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with this program; if not, write to the Free Software
;; Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
   ***** END LICENSE BLOCK *****
*/

#include <llvm/Module.h>

#include "pModule.h"
#include "pASTVisitors.h"
#include "pGenerator.h"
#include "pGenSupport.h"
#include "pParser.h"
#include "pCompileTarget.h"

namespace rphp {

pModule::pModule(pFilenameString name, bool dUnicode):
    filename_(name),
    llvmModule_(NULL),
    llvmModuleOwner_(true),
    defaultUnicode_(dUnicode),
    currentLineNum_(0),
    lastNewline_(),
    lastToken_()
{

    parser::parseSourceFile(filename_, this);

}

pModule::~pModule() {
    // free up statements
    for(astType::iterator s = ast_.begin(); s != ast_.end(); ++s) {
        delete *s;
    }
    // only if codegen was performed, and we are still the owner
    // we aren't the owner if the llvmModule was executed in the JIT, for example
    if (llvmModuleOwner_)
        delete llvmModule_;
}

void pModule::applyVisitor(AST::baseVisitor* v) {
    for(astType::iterator s = ast_.begin(); s != ast_.end(); ++s) {
        v->visit(*s);
    }
}

void pModule::dumpAST() {

    AST::dumpVisitor v;
    applyVisitor(&v);

}

void pModule::dumpIR() {

    pCompileTarget* target = new pCompileTarget(filename_, "/");
    if (lowerToIR(target))
        llvmModule_->dump();
    delete target;

}


bool pModule::lowerToIR(pCompileTarget* target) {

    assert(target != NULL);
    assert(llvmModule_ == NULL);

    llvmModule_ = new llvm::Module(filename_);
    pGenerator codeGen(llvmModule_, target);
    applyVisitor(&codeGen);
    codeGen.finalize();

    //bool broken = verifyModule(llvmModule_, ReturnStatusAction);
    return true;

}

bool pModule::writeBitcode(pFilenameString filename) {

    return pGenSupport::writeBitcode(llvmModule_, filename);

}

std::string pModule::getEntryFunctionName() {
    return pGenSupport::mangleModuleName(filename_);
}

} // namespace
