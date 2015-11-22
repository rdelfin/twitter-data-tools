//
// Created by rdelfin on 11/22/15.
//

#ifndef TWITTER_DATA_TOOLS_CSVREADER_H
#define TWITTER_DATA_TOOLS_CSVREADER_H

#include <string>


namespace tagger
{
    class CsvRecord;

    class CsvReader {
    public:
        CsvReader();
        void open(std::string file);

        CsvRecord next();

    private:

    };
}


#endif //TWITTER_DATA_TOOLS_CSVREADER_H
