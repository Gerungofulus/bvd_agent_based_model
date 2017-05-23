#include "CSVFileHandler.h"

template<typename T>
void CSVFileHandler::writeSaveToFile(const std::vector<T>* save,const std::string& fileName){
    for( T point : *save){
        this->writeDataPointToFile(point, fileName);
    }
}
template<typename T>
void CSVFileHandler::writeDataPointToFile(const T& point, const std::ofstream& filestream){
    for(int i=0; i < T::size-1; i++){
        filestream << point[i] << ";\t";
    }
    filestream << point[T::size - 1] << std::endl;
}

void CSVFileHandler::write_to_file(const double time){

}



CSVFileHandler::CSVFileHandler():TableBasedOutput(){

}

CSVFileHandler::~CSVFileHandler(){}
