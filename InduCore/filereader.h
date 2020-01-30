#ifndef FILEREADER_H
#define FILEREADER_H

#include "InduCore_global.h"
#include "datafile.h"

#include <memory>
#include <QString>


class INDUCORE_EXPORT FileReader
{
public:
    FileReader(Datafile &dfile);
    std::shared_ptr<Datafile> readFile();
private:
    Datafile dfile_;
};

#endif // FILEREADER_H
