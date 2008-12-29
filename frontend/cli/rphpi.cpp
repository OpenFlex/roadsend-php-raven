
#include <exception>
#include <iostream>
#include <vector>
#include <string>
#include <llvm/Support/CommandLine.h>
#include <llvm/System/Path.h>

#include "rphp/JIT/pInterpretTarget.h"

using namespace llvm;
using namespace rphp;

void rphpVersion(void) {
    // TODO get version info from runtime
    std::cout << "Roadsend PHP JIT" << std::endl;
}

int main( int argc, char* argv[] )
{

    // command line options
    cl::opt<std::string> inputFile(cl::Positional, cl::desc("<input file>"), cl::Required);
    cl::opt<bool> iSF ("f", cl::desc("Execute source file immediately"));
    cl::opt<int> verbosity ("v", cl::desc("Verbosity level (0=Silent/1=Info/2=Full/3+=Debug)"));
    cl::opt<std::string> encoding ("encoding",cl::desc("Character encoding of the source file"));

    cl::SetVersionPrinter(&rphpVersion);
    cl::ParseCommandLineOptions(argc, argv, "Roadsend PHP");

    // default encoding
    if (encoding.empty())
        encoding = "ASCII";

    assert(!inputFile.empty() && "empty input file");
    
    pSourceFileDesc inFile = boost::make_tuple(inputFile, encoding);

    pTarget* target = NULL;
    target = new pInterpretTarget(inFile, "/");

    try {
        if (verbosity >= 0)
            target->setVerbosity(verbosity);
        target->execute();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        delete target;
        return 1;
    }

    // success
    delete target;
    return 0;

}
