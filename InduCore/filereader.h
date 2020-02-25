#ifndef FILEREADER_H
#define FILEREADER_H

#include "InduCore_global.h"

#include <memory>

//Internal Classes
#include "datafile.h"




class INDUCORE_EXPORT FileReader
{
public:
    FileReader(Datafile &dfile);
    std::shared_ptr<Datafile> readFile();
private:
    Datafile dfile_;

};

#endif // FILEREADER_H
