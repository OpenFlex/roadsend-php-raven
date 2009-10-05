/* ***** BEGIN LICENSE BLOCK *****
 * Roadsend PHP Compiler Runtime Libraries
 *
 * Copyright (c) 2008-2009 Shannon Weyrick <weyrick@roadsend.com>
 *                         Thomas Moenicke <tm@php-qt.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 * ***** END LICENSE BLOCK ***** */

#include <iostream>
#include <unicode/ustream.h>

#include "c-runtime.h"

using namespace rphp;

extern "C" {

    // create a new runtime engine
    pRuntimeEngine* rphp_newRuntimeEngine() {
        pRuntimeEngine* rt = new pRuntimeEngine();
        return rt;
    }

    // destroy runtime engine
    void rphp_deleteRuntimeEngine(pRuntimeEngine* e) {
        delete e;
    }

    // print a c string to the current output buffer in the given runtime
    void rphp_print_cstr(pRuntimeEngine* e, const char* str) {
        e->output << str;
    }

    // print a pVar, coercing to string
    void rphp_print_pVar(pRuntimeEngine* e, pVar v) {
        e->output << v;
    }

    // create a new pVar for a NULL
    pVar rphp_make_pVar_pNull() {
        return pVar(pNull);
    }

    // create a new binary string
    pVar rphp_make_pVar_pBString(const char* str) {
        return pVar(pBString(str));
    }

    // create a new unicode string
    pVar rphp_make_pVar_pUString(const char* str, size_t len) {
        // our code generator always generates UTF-16BE
        return pVar(pUStringP(new UnicodeString(str, len, "UTF-16BE")));
    }

    // create a new pVar from a pInt
    pVar rphp_make_pVar_pInt(pInt v) {
        return pVar(v);
    }

    // create a new pVar from a pFloat
    pVar rphp_make_pVar_pFloat(pFloat v) {
        return pVar(v);
    }

    // create a new bool pVar
    pVar rphp_make_pVar_pBool(int v) {
        return (v) ? pVar(pTrue) : pVar(pFalse);
    }

    pVar rphp_make_pVar_pObject(const char *className) {
        return pObjectP( new pObject(className) );
    }

    pVar rphp_make_pVar_pHash() {
        return pHashP(new pHash());
    }

    int rphp_pVar_evalAsBool(pVar arg) {
    	return arg.evalAsBool();
    }

    void rphp_pHash_insertNext(pVar h, pVar v) {
        h.getHash()->insertNext(v);
    }

    void rphp_pHash_insert(pVar h, pVar k, pVar v) {
        h.getHash()->insert(k, v);
    }

    void rphp_registerUserFun0(pRuntimeEngine* r, const char* name, pFunPointer0 p) {
        r->functionManager->registerUser(name, p, 0);
    }

    void rphp_registerUserFun1(pRuntimeEngine* r, const char* name, pFunPointer1 p) {
        r->functionManager->registerUser(name, p, 1);
    }

    void rphp_registerUserFun2(pRuntimeEngine* r, const char* name, pFunPointer2 p) {
        r->functionManager->registerUser(name, p, 2);
    }

    void rphp_registerUserFun3(pRuntimeEngine* r, const char* name, pFunPointer3 p) {
        r->functionManager->registerUser(name, p, 3);
    }

    void rphp_registerUserFun4(pRuntimeEngine* r, const char* name, pFunPointer4 p) {
        r->functionManager->registerUser(name, p, 4);
    }

    void rphp_registerUserFun5(pRuntimeEngine* r, const char* name, pFunPointer5 p) {
        r->functionManager->registerUser(name, p, 5);
    }

    pVar rphp_funCall0(pRuntimeEngine* r, const char* name) {
        return r->functionManager->invoke(name);
    }

    pVar rphp_funCall1(pRuntimeEngine* r, const char* name, pVar arg1) {
        return r->functionManager->invoke(name, arg1);
    }

    pVar rphp_funCall2(pRuntimeEngine* r, const char* name, pVar arg1, pVar arg2) {
        return r->functionManager->invoke(name, arg1, arg2);
    }

    pVar rphp_funCall3(pRuntimeEngine* r, const char* name, pVar arg1, pVar arg2, pVar arg3) {
        return r->functionManager->invoke(name, arg1, arg2, arg3);
    }

    pVar rphp_funCall4(pRuntimeEngine* r, const char* name, pVar arg1, pVar arg2, pVar arg3, pVar arg4) {
        return r->functionManager->invoke(name, arg1, arg2, arg3, arg4);
    }

    pVar rphp_funCall5(pRuntimeEngine* r, const char* name, pVar arg1, pVar arg2, pVar arg3, pVar arg4, pVar arg5) {
        return r->functionManager->invoke(name, arg1, arg2, arg3, arg4, arg5);
    }

    pVar rphp_newCall(pRuntimeEngine* r, const char* className, pVar arg1) {
      pVar result = rphp_make_pVar_pObject( className );
      // invoke method call "__construct" on result
      return result;
    }

    void rphp_setSourceLocation(rphp::pRuntimeEngine* r, const char* file, rphp::pInt line) {
       r->errorManager->setSourceLocation(file, line);
    }

    void _make_pVar(void) {
      pVar p;
      p = 5;
    }

    void _assign_pVar(void) {
      pVar l;
      pVar r;
      l = r;
    }

    int _runtimeError(void) {
        pVar l;
        try {
            l = 0;
        }
        catch (pRuntimeError& e) {
            return l.copyAsInt();
        }
        catch (...) {
            return l.copyAsInt();
        }
    }

}

