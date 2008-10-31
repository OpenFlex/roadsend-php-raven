/* ***** BEGIN LICENSE BLOCK *****
 * Roadsend PHP Compiler Runtime Libraries
 *
 * Copyright (c) 2008 Thomas Moenicke <tm@php-qt.org>
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

#include "pVar.h"
#include "pHash.h"
#include "pObject.h"

#include <boost/foreach.hpp>

namespace rphp
{
    
    class pHash;

    pClass::pClass()
    {
    }

    pHash pClass::properties()
    {
	pHash result;
/*
  BOOST_FOREACH( pVar property, _properties )
    {
	result.append( property );
    }
*/
	return result;
    }

    const pUString& pClass::name() const
    {
	return _name;
    }

    void pClass::setName( const pUString& name )
    {
	_name = name;
    }
    
}
