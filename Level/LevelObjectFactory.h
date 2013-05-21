#pragma once
#include "LevelObject.h"
#include <map>
#include <string>
//!Класс "Фабрика объектов уровня".
class LevelObjectFactory{
  public:
    /*!Тип указателя на функцию создания объекта.
     */
    typedef LevelObject* (*CreatorFuncPtr)();
    
    /*!Тип указателя на функцию получения имени класса.
     */
    typedef std::string (*TypeNameFuncPtr)();
    
    /*!Создание объекта указанного класса.
     * \param type_name имя класса создаваемого объекта
     * \return указатель на созданный объект.
     */
    static LevelObject* create(const std::string& type_name);

    /*!Регистрация класса на фабрике.
     * \param type_name имя регистрируемого класса 
     * \param create функция создания объектов класса
     * \return true, если операция выполнена успешно, иначе false.
     */
    static bool registerType(const std::string& type_name,CreatorFuncPtr create);
  private:

    /*!Тип отображения имени класса на производящую функцию.
     */
    typedef std::map<std::string,CreatorFuncPtr> TypeInfo;
    
    /*!Получение отображения "имя класса"->"производящая функция".
     * \return ссылку на отображение.
     */
    static TypeInfo& types(){
        static TypeInfo types_;
        return types_;
    }
};
/*!Оператор считывания из потока объекта через указатель на базовый класс.
 * \param is поток ввода
 * \param new_obj указатель на создаваемый и загружаемый объект
 * \return измененный поток ввода
 */
std::istream& operator>>(std::istream& is,LevelObject* &new_obj);

