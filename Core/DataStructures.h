#pragma once
#include <vector>
using namespace std;
//!Класс "Таблица".
template <typename T>
class Table{
  protected:
    size_t rows_,//!<количество строк
           cols_;//!<количество столбцов
    #ifdef DOXYGEN
    T* data;//!<данные
    #else
    vector<vector <T> > data;//!<данные
    #endif 
  public:
    /*!Конструктор по умолчанию.
     */
    Table():rows_(0),cols_(0){};
    
    /*!Конструктор, задающий размер таблицы.
     * \param rows количество строк
     * \param cols количество столбцов
     */
    Table(size_t rows,size_t cols){
        setSize(rows,cols);
    }

    /*!Получение количества строк.
     * \return количество строк
     */
    size_t rows(){return rows_;}
    
    /*!Получение количества столбцов.
     * \return количество столбцов
     */
    size_t cols(){return cols_;}
    
    /*!Установка количества строк.
     * \param rows количество строк
     */
    void setRows(size_t rows){
        data.resize(rows);
        rows_=rows;
    }

    /*!Установка количества столбцов.
     * \param cols количество столбцов
     */
    void setCols(size_t cols){
        for(int i=0;i<rows_;++i){
            data.at(i).resize(cols);
        }
        cols_=cols;
    }

    /*!Установка размера таблицы.
     * \param rows количество строк
     * \param cols количество строк
     */
    void setSize(size_t rows,size_t cols){
        setCols(cols);
        setRows(rows);
    }

    /*!Получение элемента по номерам строки и столбца.
     * \param row строка, в которой находится элемент
     * \param col столбец, в котором находится элемент
     * \return запрошенный элемент
     */
    T& at(size_t row,size_t col){
        return data.at(row).at(col);
    }

    /*!Оператор получения элемента по номерам строки и столбца.
     * \param row строка, в которой находится элемент
     * \param col столбец, в котором находится элемент
     * \return запрошенный элемент
     */
    T& operator()(size_t row,size_t col){
        return at(row,col);
    }

    /*!Очистка таблицы, установка размеров в ноль.
     */
    void clear(){
        for(int i=0;i<rows_;++i){
            data.at(i).clear();
        }
        data.clear();
        rows_=0;cols_=0;
        
        setSize(0,0);
    }
};
