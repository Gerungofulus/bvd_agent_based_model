#include "FileHandler.h"
#include "projectImports/inih/cpp/INIReader.h"
#include "BVDSettings.h"
FileHandler::FileHandler(){
	this->overwrite = BVDSettings::sharedInstance()->outputSettings.overwrite;
    this->fileprefix = BVDSettings::sharedInstance()->outputSettings.fileprefix;
    this->path = BVDSettings::sharedInstance()->outputSettings.path;

    this->fullFilePath = BVDSettings::sharedInstance()->outputSettings.fullFilePath;
	this->setPath();
}
FileHandler::~FileHandler(){}

void FileHandler::setPath(){
	this->fullFilePath = this->path + this->fileprefix + this->fileExtension;
}
