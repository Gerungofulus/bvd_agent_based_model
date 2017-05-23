#ifndef __SQLiteHandler_h_
#define __SQLiteHandler_h_
#include "FileHandler.h"
#include <sstream>
#include <sqlite3.h>
#include <sys/stat.h>
#include <fstream>

class Event;
class Cow;
class Farm;

class SQLiteHandler: public FileHandler{
	public:
	SQLiteHandler();
	~SQLiteHandler();

	//void saveCow(const Cow* c);
	void logFarms(const double time,const std::vector< Farm* >*farms);
	void logBirth(const Cow* c);
	void logEvent(const Event *e);
	//void logDyingCow(const Event* event,const Cow* cow)
	void write_to_file(const double time=0.0);
	void logResultingEventOfInfection(const Event* e);
	private:
		void runSQLQuery(const std::ostringstream& sqlstream);
		static const std::string eventTableName;
		static const std::string cowTableName;
		static const std::string templateDBPath;
		int rc;                   /* Function return code */
		//sqlite3 *pFile;           /* Database connection opened on zFilename */

		sqlite3 *pMemory;          /* Database to copy to (pFile or pInMemory) */
		sqlite3 *pTemplate;           /* Database to copy from (pFile or pInMemory) */
		int loadOrSaveDb(sqlite3 *pInMemory, const char *zFilename, int isSave);
};
#endif
