#ifndef __csv_file_handler_h_
#define __csv_file_handler_h_
#include "TableBasedOutput.h"

class CSVFileHandler: public TableBasedOutput{
    CSVFileHandler();
    ~CSVFileHandler();



private:
    void writeLivingPIsToFile(const std::string& fileName);
    void writeFarmData(const std::string& fileName);
    void writeCowData(const std::string& fileName);
    void writeTestData(const std::string& fileName);
    void writeInfectionResultData(const std::string& fileName);
    void writeTradeData(const std::string& fileName);


    void write_to_file(const double time);

    template<typename T, typename returnType>
    void createWritableData(std::vector<T>* save, returnType** data);

    template<typename T>
    void writeSaveToFile(const std::vector<T>* save,const std::string& fileName);
    template<typename T>
    void writeDataPointToFile(const T& point, const std::ofstream& filestream);

};


#endif
