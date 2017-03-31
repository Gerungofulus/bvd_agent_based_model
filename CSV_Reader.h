#ifndef __csvreader_h_
#define __csvreader_h_
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <array>
#include <iostream>
//because this is a class using templates, everything is implemented within the header file

template <typename T>

class CSVCol{
	public:
	CSVCol(){}
	CSVCol(const T* dat, int rowCount):data(dat),rowNum(rowCount){}
	~CSVCol(){
		delete[] data;
		data = NULL;
	}
	
	T& operator[](const int i){return data[i];}
	T* data;
	operator T*(){return data;}
	int rowNum;
};

template <typename T>
class CSVTable{
	public:
		CSVTable(std::istream&  fileContent, const bool& head, const char& delimiter){
			_doesContainHeader = head;
			std::string line;
			bool firstLine = true;
			
			std::string item;
			std::vector<std::vector<T>> lines;
			std::vector<T> linevalues;
			
			while(std::getline(fileContent, line)){
				std::istringstream ss(line);
				linevalues.clear();
				if(firstLine && head){
					while (getline(ss, item, delimiter))
						header.push_back(item);
					firstLine = false;
				}else{
					firstLine = false;
					while (getline(ss, item, delimiter)){
						linevalues.push_back(static_cast<T>(atof(item.c_str())));//converting the string to a double before casting it to another type
							
					}
					lines.push_back(std::vector<T>(linevalues));//does this need to be done?
				}		
				
			} 
			
			numRows = lines.size();
			numCols = linevalues.size();
			data = new CSVCol<T>[numCols]();
			for(int i=0; i < numCols; i++){
				data[i].data = new T[numRows]();
				data[i].rowNum = numRows;
			}
			for(int i=0; i < numRows; i++){
				
				for(int j = 0; j < numCols; j++){
					//std::cout << lines[i][j] << " " ;
					data[j].data[i] = lines[i][j];
				}
//				std::cout << std::endl;
			}
				 
		}
		~CSVTable(){
			
			delete[] data;
			data = NULL;
		}
		bool doesContainHeader(){return _doesContainHeader;}
		int getNumRows(){return numRows;}
		int getNumCols(){return numCols;}
		std::string& getHeader(const int i){ return header[i];}
		CSVCol<T>& operator[](const int i){return data[i];}
	
	private:
		bool _doesContainHeader;
		int numRows;
		int numCols;
		std::vector<std::string> header;
		CSVCol<T>* data;
	
	};
	
template <typename T>
class CSVReader{
	public:
	static CSVTable<T> readCSVFile(const std::string& filename, bool head = true, char delimiter = ','){
		std::ifstream file(filename);
		return CSVTable<T>(file,head,delimiter);
	}
		
};

#endif