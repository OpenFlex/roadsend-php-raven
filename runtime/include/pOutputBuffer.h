/* ***** BEGIN LICENSE BLOCK *****
 * Roadsend PHP Compiler Runtime Libraries
 *
 * Copyright (c) 2008 Shannon Weyrick <weyrick@roadsend.com>
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

#ifndef RPHP_POUTPUTBUFFER_H_
#define RPHP_POUTPUTBUFFER_H_

#include "pTypes.h"

namespace rphp {

    class pOutputBuffer {

    public:

        typedef enum { bufTypeBinary, bufTypeUnicode } bufTypeT;

            // constructors

            // specify type
            pOutputBuffer(bufTypeT t) : bBuffer(0), uBuffer(0), bType(t) {
                switch (t) {
                    case bufTypeBinary:
                        bBuffer = new pBString();
                        break;
                    case bufTypeUnicode:
                        uBuffer = new pUString();
                        break;
                }
            }

            // destructor
            ~pOutputBuffer() {
                if (uBuffer)
                    delete uBuffer;
                if (bBuffer)
                    delete bBuffer;
            }

            const char* getRawBuffer() {
                switch (bType) {
                    case bufTypeBinary:
                        return bBuffer->c_str();
                    case bufTypeUnicode:
                        return (const char*)uBuffer->getTerminatedBuffer();
                }
            }

            void operator<< (const pBString& str) {
                switch (bType) {
                    case bufTypeBinary:
                        bBuffer->append(str);
                        break;
                    case bufTypeUnicode:
                        // TODO: this doesn't seem so efficient. but how often will it be used?
                        uBuffer->append(pUString(str.c_str(),str.length(), US_INV));
                        break;
                }
            }

            void operator<< (const pUString& str) {
                if (bType == bufTypeBinary) {
                    // convert to unicode buffer
                    uBuffer = new pUString(bBuffer->c_str(), bBuffer->length(), US_INV);
                    delete bBuffer;
                }
                uBuffer->append(str);
            }

    private:

            pUString *uBuffer;
            pBString *bBuffer;
            bufTypeT bType;

    };

}

#endif /* RPHP_POUTPUTBUFFER_H_ */
