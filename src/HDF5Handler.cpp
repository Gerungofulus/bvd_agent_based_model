#include "HDF5Handler.h"
#include "System.h"
#include "Utilities.h"
#include "Cow.h"
#include "Farm.h"
#include "Herd.h"

#pragma mark -
#pragma mark Writing the file

void HDF5FileHandler::writeLivingPIsToFile(const hid_t& file){

    const std::string tablePrefix = "PIs_LIVING_t";
	for(int i=0; i < piStorage->size(); i++){
		CowDataSave * currentSave = (*piStorage)[i];

		double time = (*farmDataTimes)[i];
		std::string tableName = tablePrefix + std::to_string((int)(time));

		this->writeSaveToFile(file, currentSave,tableName);

	}
}
void HDF5FileHandler::writeFarmData(const hid_t& file){

	if(this->farmData->size() <= 0 || this->farmDataTimes->size() <= 0){
		return;
	}
	hsize_t t_dims[1] = {this->farmDataTimes->size()};
	const double *timeData = &((*this->farmDataTimes)[0]);
	int success = H5LTmake_dataset_double( file ,
				     "/BVD_Farm_Times",
				     1,
				     t_dims,
				      timeData);
	if(success < 0){
			std::cerr << "Failed to create farm time dataset" << std::endl;
			Utilities::printStackTrace(15);
			exit(14);
	}



	const int rank = 2;//FarmDataPoint::size;

    const std::string tablePrefix = "Farms_t";


	for(int i=0; i < farmData->size(); i++){
		FarmDataSave * currentSave = (*farmData)[i];
		static hsize_t dims[rank] = {currentSave->size(), (hsize_t) FarmDataPoint::size};
		double time = (*farmDataTimes)[i];


		std::string tableName = tablePrefix + std::to_string((int)(time));
		int * data ;
		this->createWritableData(currentSave, &data);


		int success = H5LTmake_dataset_int( file ,
						  tableName.c_str(),
						  rank,
						  dims,
						  data);
		if(success < 0){
			std::cerr << "Failed to create farm dataset for time " << time << std::endl;

			exit(13);
		}
		delete[] data;
	}



}

void HDF5FileHandler::writeCowData(const hid_t& file_id){

	if( this->intermediateCalvingTimes->size() > 0){
		double *calvingTimeData;// = &((*this->intermediateCalvingTimes)[0]);
		this->createWritableData(this->intermediateCalvingTimes, &calvingTimeData);
		const int rank = 2;
		hsize_t calvingTime_dims[rank] = {(hsize_t) this->intermediateCalvingTimes->size(), (hsize_t)intermediateCalvingTimePoint::size};
		int success = H5LTmake_dataset_double( file_id ,
						 HDF5FileHandler::intermediateCalvingTimeTableName.c_str(),
						 rank,
						 calvingTime_dims,
						  calvingTimeData);
		if(success < 0){
				std::cerr << "Failed to create intermediate calving times dataset" << std::endl;
				Utilities::printStackTrace(15);
				exit(14);
		}
		delete[] calvingTimeData;
	}
	this->writeSaveToFile(file_id,this->CowData, "BVD_Dead_Cows");
	this->writeSaveToFile(file_id,this->InfectionData, "BVD_Cows_Infections");
	this->writeSaveToFile(file_id,this->PIDeathSave, "BVD_Dead_PIs");
	this->writeLivingPIsToFile(file_id);
}




void HDF5FileHandler::writeTestData(const hid_t& file_id){


	if(this->testStorage->size() > 0){
		const int rank = 2;
		hsize_t dims[rank] = { static_cast<hsize_t>(this->testStorage->size()), static_cast<hsize_t>(TestDataPoint::size) };


		double * data = NULL;
		this->createWritableData(this->testStorage, &data);
		int success = H5LTmake_dataset_double( file_id ,
						  HDF5FileHandler::testsTableName.c_str(),
						  rank,
						  dims,
						  data);
		if(success < 0){
			std::cerr << "Failed to create test dataset" << std::endl;
			exit(12);
		}
		delete[] data;
	}

}

void HDF5FileHandler::writeInfectionResultData(const hid_t& file){
	if(this->infectionResultSave->size() <= 0) return;
	const int rank = 2;
	hsize_t dims[rank] = { static_cast<hsize_t>(this->infectionResultSave->size()), static_cast<hsize_t>(InfectionResultDataPoint::size) };


	int * data = NULL;
	this->createWritableData(this->infectionResultSave, &data);
	int success = H5LTmake_dataset_int( file ,
					  HDF5FileHandler::infectionResultTabelName.c_str(),
					  rank,
					  dims,
					  data);

	delete[] data;
	if(success < 0){
		std::cerr << "Failed to create infection result dataset" << std::endl;
		exit(12);
	}

}

void HDF5FileHandler::writeTradeData(const hid_t& file_id){
	const int rank = 2;
	hsize_t dims[rank] = { this->trades->size(), (hsize_t) TradeDataPoint::size};
	double * data;

	if(trades->size() > 0){

		data = new double[this->trades->size()*TradeDataPoint::size];
		int *tradeMatrix;
		std::vector<int*> *tradeMatrices = new std::vector<int*>();
		std::vector<double> *tradingTimes = new std::vector<double>();



		double tTemp = -1.0;

		for(auto it = this->trades->begin(); it != this->trades->end(); it++){
			double tRead = (*it).date;
				if((*it).srcFarmID == -1) continue;

				if((int) tRead != (int) tTemp ){//if there is a new timestep

					tTemp = tRead;
					tradingTimes->push_back(tRead);
					tradeMatrix = new int[this->farmNum * this->farmNum];
					std::fill_n(tradeMatrix, this->farmNum*this->farmNum, 0);
					tradeMatrices->push_back(tradeMatrix);
				}
			double* tradeDP = ((double *) (*it));
//			std::cout << "aha " << std::endl;

			int tradeIndex = (int) ((*it).srcFarmID * this->farmNum + (*it).destFarmID);
			tradeMatrix[tradeIndex]++;
			for(int i=0; i < TradeDataPoint::size; i++){

				int index = (int) (it - this->trades->begin()) * TradeDataPoint::size + i;

				data[index] = tradeDP[i];
			}
			 delete[] tradeDP;
			 tradeDP = nullptr;
			//std::cout << std::endl;
		}
		int success = H5LTmake_dataset_double( file_id ,
						  "/BVD_Trades",
						  rank,
						  dims,
						  data);
		if(success < 0){
			std::cerr << "Failed to create trade dataset" << std::endl;
			exit(12);
		}
		delete[] data;
		const int tradeMatRank = 2;
		const std::string tablePrefix = "Trades_t";

		for(int i = 0; i < tradeMatrices->size();i++){
			const int * mat = (*tradeMatrices)[i];
			hsize_t num =  static_cast<hsize_t>(this->farmNum );


			hsize_t tradeDims[rank] = {num, num};

			double time = (*tradingTimes)[i];
			std::string tableName = tablePrefix + std::to_string((int)(time));
			//std::cout << i << " " <<   tableName << " " << time << std::endl;
			int tradeSuccess = H5LTmake_dataset_int( file_id ,
						  tableName.c_str(),
						  tradeMatRank,
						  tradeDims,
						  mat);
			if(tradeSuccess < 0){
				std::cout << "failed to create trade matrices table with table name " << tableName << std::endl;
				exit(16);
			}
		}
		//std::cout << "wrote all trade matrices" << std::endl;
		hsize_t tradeTimeDim[1] = {tradingTimes->size()};
		const double* tradeTimeData = &((*tradingTimes)[0]);
		int tradeTimeSuccess = H5LTmake_dataset_double( file_id ,
						  "/BVD_Trade_Times",
						  1,
						  tradeTimeDim,
						  tradeTimeData);
		if(tradeTimeSuccess < 0){
			std::cerr << "Failed to create trade time dataset" << std::endl;
			exit(12);
		}

		for(auto mat : *tradeMatrices){delete[] mat;}
		delete tradeMatrices;
		delete tradingTimes;



	}

}

template<typename T>
void HDF5FileHandler::writeTemplateSaveToFile(const hid_t& file, std::vector<T>* save,const std::string tableName){}

#pragma mark -
#pragma mark - Basic File Management
hid_t HDF5FileHandler::open_file( std::string filename , bool overwrite){

  hid_t file_id = H5Fcreate( filename.c_str() ,
					  overwrite ? H5F_ACC_TRUNC : H5F_ACC_EXCL ,
					  H5P_DEFAULT,
					  H5P_DEFAULT);
  if (file_id < 0 )
    {
      std::cerr << "Error while setting up output file with name " << filename << " . . Possible reason: File already exists." << std::endl;
      exit(1);
    }
  return file_id;
}
void HDF5FileHandler::write_to_file(const double time){

//typedef std::vector<TradeDataPoint*> TradeDataSave;


	if(this->intermediateCalvingTimes->size() == 0 && this->farmDataTimes->size() == 0 && this->CowData->size() == 0 && this->trades->size() == 0) return;

	std::string filename, listfilename;
	hid_t file;
	bool flush = false;
	std::ofstream outfile;
	switch(this->mode){
		case single_file:

			filename = this->fullFilePath;

			this->overwrite = true; //after writing for the first time, we will always be writing to the same file
			break;
		case multi_file:
			flush = true;
			filename = this->path + this->fileprefix + "_time_" + std::to_string((int) time) + this->fileExtension;
			listfilename = this->path + this->fileprefix + "_list.txt";
			if(this->deleteList){
				std::remove(listfilename.c_str());
				this->deleteList = false;
			}

  			outfile.open(listfilename.c_str(), std::ios_base::app);
 			outfile << this->fileprefix + "_time_" + std::to_string((int) time) + this->fileExtension << std::endl;
 			outfile.close();
//			std::cerr << "Multifile output is not yet supported. Exiting" << std::endl;
//			exit(5);
			break;

	}
	file = this->open_file(filename, this->overwrite);
//		Utilities::printStackTrace(15);
	this->writeTradeData(file);
	this->writeFarmData(file);
	this->writeCowData(file);
	this->writeTestData(file);
	this->writeInfectionResultData(file);
	H5Fclose( file );
    std::system((BVDSettings::sharedInstance()->outputSettings.postFileWriteCall + " " + filename).c_str());
	if(flush)
		this->flushStorages();
}

void HDF5FileHandler::writeSaveToFile(const hid_t& file, CowDataSave* save, const std::string tableName){

	if(save->size() <= 0 ) return;

	const int rank = 2;//CowDataPoint::size;

	hsize_t dims[rank] = { save->size(), (hsize_t) CowDataPoint::size };

	double * data = nullptr;// = new double[save->size()*CowDataPoint::size];
	this->createWritableData(save, &data);

	int success = H5LTmake_dataset_double( file,
					  tableName.c_str(),
					  rank,
					  dims,
					  data);
	if(success < 0){
		std::cerr << "Failed to create trade dataset" << std::endl;
		exit(12);
	}

	if(data != NULL)
		delete[] data;
	else
		std::cout << "data should not be NULL, it has a size of " << save->size() << std::endl;
}
template<typename T, typename returnType>
void HDF5FileHandler::createWritableData(std::vector<T>* save, returnType** data){
	*data = new returnType[save->size()*T::size];
	for(auto it = save->begin(); it != save->end(); it++){

		returnType* cowDP = ((returnType *) (*it));

		for(int i=0; i < T::size; i++){

			int index = (int) (it - save->begin()) * T::size + i;

			(*data)[index] = cowDP[i];
		}
		delete[] cowDP;
		cowDP = nullptr;
	//std::cout << std::endl;
	}
}




HDF5FileHandler::HDF5FileHandler():TableBasedOutput(){
	this->fileExtension = ".h5";
	this->deleteList = this->overwrite;

}

HDF5FileHandler::~HDF5FileHandler(){

}
