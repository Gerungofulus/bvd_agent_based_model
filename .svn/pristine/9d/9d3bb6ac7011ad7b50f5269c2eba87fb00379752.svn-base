#include "FileHandler.h"
#include "projectImports/inih/cpp/INIReader.h"
FileHandler::FileHandler(INIReader& reader){
		this->overwrite = reader.GetBoolean("output", "overwrite", false);
		this->fileprefix = reader.Get("output", "fileprefix", "output_");
		this->path = reader.Get("output", "path", "./");
		this->setPath();
	}
FileHandler::~FileHandler(){} 

void FileHandler::setPath(){
	this->fullFilePath = this->path + this->fileprefix + this->fileExtension;
}