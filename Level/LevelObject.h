#if !defined(LEVEL_H)&&!defined(DOXYGEN)
#include "Level.h"
#else
#pragma once
#include <iostream>
#include <string>

class Level;
class Field;
//!Класс "Объект игрового уровня".
class LevelObject{
  public:
    /*!Получение имени класса данного экземпляра.
     * \return имя класса данного объекта.
     */
    virtual std::string type_name()const=0; 

    /*!Установка игрового уровня,которому принадлежит объект.
     * \param level уровень, на который добавляется объект
     */
    virtual void setLevel(Level *level);
    
    /*!Установка игрового поля, на котором находится объект.
     * \param field поле, на которое добавлется объект
     */
    virtual void setField(const Field *field);
    
    /*!Виртуальный деструктор.
     */
    virtual ~LevelObject();
    
    /*!Сохранение объекта: вывод его в поток.
     * \param os поток вывода
     * \return измененный поток вывода
     */
    std::ostream& printTo(std::ostream& os)const ;

    /*!Оператор вывода в поток.
     * \param os поток вывода
     * \param obj выводимый объект
     * \return измененный поток вывода
     */
    friend std::ostream& operator<<(std::ostream& os,const LevelObject& obj);
    
    /*!Получение поля, на котором находится объект.
     * \return указатель на связанное поле
     */
    const Field* field()const;
    
    /*!Получение уровня, которому принадлежит объект.
     * \return указатель на связанный уровень
     */
    Level* level()const;
  protected:
    Level *level_;//!<<уровень, которому принадлежит объект 
    const Field *field_;//!<поле, на котором находится объект

    /*!Сохранение специфических свойств объектов-наследников в поток.
     * \param os поток вывода
     * \return измененный поток вывода
     */
    virtual std::ostream& overridedPrintTo(std::ostream& os)const;
    
    /*!Загрузка специфических свойств объектов-наследников из потока.
     * \param is поток ввода
     * \return измененный поток ввода
     */
    virtual std::istream& overridedInputFrom(std::istream& is);
};  
#endif
