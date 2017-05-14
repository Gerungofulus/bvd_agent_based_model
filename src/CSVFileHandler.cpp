#include "CSVFileHandler.h"

void CSVFileHandler::writeSaveToFile(const std::vector<T>* save,const std::string fileName){
    for( T point : *save){
        this->writeDataPointToFile(point, fileName);
    }
}

void CSVFileHandler::writeDataPointToFile(const T point, const std::string fileName){

}

CSVFileHandler::CSVFileHandler():TableBasedOutput(){

}

CSVFileHandler::~CSVFileHandler(){}
