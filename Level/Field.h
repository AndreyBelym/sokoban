#if !defined(LEVEL_H)&&!defined(DOXYGEN)
#include "Level.h"
#else
#pragma once

//!Класс "Игровое поле"(клетка игровой доски).
class Field{
  protected:
    mutable LevelObject *obj;//!<объект, находящийся на данном поле
    bool marked_;//!<метка поля
    int row_;//!<номер строка, в которой находится поле
    int col_;//!<номер, в котором находится поле

    /*!Установка номера строки, в которой находится поле.
     * \param row номер строки
     */
    void setRow(int row);
    
    /*!Установка номера столбца, в которой находится поле.
     * \param col номер столбца
     */
    void setCol(int col);
    
    /*!Установка метки поля.
     * \param m флаг метки поля
     */
    void setMarked(bool m);
    
    /*!Отключение и удаление объекта, находящегося на поле.
     */
    void deleteObject()const;

    /*!Отключение объекта, находящегося на поле, от данного поля.
     * \return указатель на отключенный объект.
     */
    LevelObject* detachObject()const;
    
    /*!Замена объекта, находящегося на поле,
     * на объект, заданный указателем, с возможностью отключения или удаления
     * старого объекта
     * \param new_obj указатель на новый объект
     * \param destroy флаг удаления старого объекта
     * \return указатель на старый объект.
     */
    LevelObject* replaceObject(LevelObject *new_obj,bool destroy=true);
    
    /*!Замена объекта, находящегося на поле,
     * на новый создаваемый по имени заданного типа объект, 
     * с возможностью отключения или удаления старого объекта.
     * \param type_name имя класса нового объекта
     * \param destroy флаг удаления старого объекта
     * \return указатель на старый объект.
     */
    LevelObject* replaceObject(const std::string& type_name,bool destroy=true);
    
    /*!Добавление на поле существующего объекта,
     * заданного указателем на него.
     * \param new_obj указатель на добавляемый объект
     * \return true, если операция выполнена успешно, иначе false.
     */
    bool attachObject(LevelObject* new_obj)const;
    
    /*!Создание и добавление на поле нового объекта,
     * заданного именем типа.
     * \param type_name имя класса нового объекта
     * \return true, если операция выполнена успешно, иначе false. 
     */
    bool addObject(const std::string& type_name)const;
  public:
    friend class Board;//!<класс "Игровая доска"
    friend class Level;//!<класс "Игровой уровень"
    
    /*!Конструктор по умолчанию.
     */
    Field();
    
    /*!Конструктор копирования.
     * \param other копируемое значение
     */
    Field(const Field& other);
    
    /*!Копирующий оператор присваивания.
     * \param other копируемое значение
     */
    void operator=(const Field& other);
    
    /*!Деструктор.
     */
    ~Field();

    /*!Сохранение поля: оператор вывода в поток.
     * \param os поток вывода
     * \param f выводимое поле
     * \return измененный поток вывода
     */
    friend std::ostream& operator<<(std::ostream &os,const Field& f);
    
    /*!Загрузка поля: оператор ввода из потока.
     * \param is поток ввода
     * \param f загружаемое поле
     * \return измененный поток ввода
     */
    friend std::istream& operator>>(std::istream& is,Field &f);
    
    /*!Получение объекта, находящегося на поле.
     * \return указатель на связанный объект.
     */
    LevelObject* object();
    
    /*!Получение метки поля.
     * \return флаг метки поля.
     */
    bool marked()const;
    
    /*!Получение номера строки, в которой находится поле.
     * \return номер строки поля.
     */
    int row()const;
    
    /*!Получение номера столбца, в котором находится поле.
     * \return номер столбца поля.
     */
    int col()const;
};
#endif
