#ifndef __output_table_h_
#define __output_table_h_
#include <vector>
#include <string>

template<typename T>
struct outPutTableRow{

    static const int size;
    T operator[] (int i);
    operator T*();
    operator const T*();
private:
    T data[];
};

template<typename T>
class outPutTable{
public:
    outPutTable();
    ~outPutTable();


private:
    std::vector<std::string> header;
    std::vector<outPutTableRow<T> *> rows;
};



#endif
