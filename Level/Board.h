#if !defined(LEVEL_H)&&!defined(DOXYGEN)
#include "Level.h"
#else 
#pragma once
//!Класс "Игровая доска"(набор игровых полей).
class Board:public Table<Field>{
  public:
    /*!Установка количества строк.
     * \param rows количество строк
     */
    void setRows(size_t rows);
    
    /*!Установка количества столбцов.
     * \param cols количество столбцов
     */
    void setCols(size_t cols);
    
    /*!Установка размера: установка количества строк и столбцов.
     * \param rows количество строк
     * \param cols количество столбцов
     */
    void setSize(size_t rows,size_t cols);
};
#endif
