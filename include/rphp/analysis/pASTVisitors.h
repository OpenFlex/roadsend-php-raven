/* ***** BEGIN LICENSE BLOCK *****
;; Roadsend PHP Compiler
;;
;; Copyright (c) 2008-2009 Shannon Weyrick <weyrick@roadsend.com>
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

#ifndef RPHP_PASTVISITORS_H_
#define RPHP_PASTVISITORS_H_

#include "rphp/analysis/pAST.h"

namespace rphp { namespace AST {

class baseVisitor {
private:
    typedef void (baseVisitor::*dispatchFunction)(stmt *);
    static dispatchFunction preDispatchTable_[];
    static dispatchFunction postDispatchTable_[];

public:
    virtual ~baseVisitor(void) { }

    // root dispatch
    void visit(stmt*);

    virtual void visit_pre_stmt(stmt* ) { }
    virtual void visit_post_stmt(stmt* ) { }

    virtual void visit_pre_decl(decl* ) { }
    virtual void visit_post_decl(decl* ) { }

    virtual void visit_pre_expr(expr* ) { }
    virtual void visit_post_expr(expr* ) { }

    // PRE
#define STMT(CLASS, PARENT) virtual void visit_pre_##CLASS(CLASS *) { }
#include "rphp/analysis/astNodes.def"

    // POST
#define STMT(CLASS, PARENT) virtual void visit_post_##CLASS(CLASS *) { }
#include "rphp/analysis/astNodes.def"

};


class dumpVisitor: public baseVisitor {
    int indentLevel_;
    void showindent();
public:
    dumpVisitor(void): indentLevel_(0) { }

    void visit_pre_stmt(stmt*);
    void visit_post_stmt(stmt*);

    void visit_pre_expr(expr*);
    void visit_post_expr(expr*);

    void visit_pre_functionDecl(functionDecl*);
    void visit_pre_ifStmt(ifStmt*);
    void visit_pre_echoStmt(echoStmt*);
    void visit_pre_inlineHtml(inlineHtml*);
    void visit_pre_literalString(literalString* n);
    void visit_pre_literalInt(literalInt*);
    void visit_pre_literalFloat(literalFloat*);
    void visit_pre_literalBool(literalBool*);
    void visit_pre_literalArray(literalArray*);
    void visit_pre_literalNull(literalNull*);
    void visit_pre_logicalNot(logicalNot*);
    void visit_pre_assignment(assignment*);
    void visit_pre_var(var*);
    void visit_pre_functionInvoke(functionInvoke*);
    void visit_pre_constructorInvoke(constructorInvoke*);
    void visit_pre_unaryArithmeticOp(unaryArithmeticOp*);

};

} } // namespace

#endif /* RPHP_PASTVISITORS_H_ */
