#pragma once
#include "LevelObjectFactory.h"
#include "Registrator.h"

//!Класс "Ящик".
class Box:public LevelObject{
  public:

    /*!Конструктор по умолчанию.
     */
    Box(){
        std::cout<<creator.registeredCount()<<std::endl;
    }

    /*!Получение имени данного класса.
     * \return имя класса данного объекта("Box").
     */
    std::string type_name()const {
        return static_typename();
    }

    /*!Статическая функция получения имени класса.
     * \return имя класса данного объекта("Box").
     */
    static std::string static_typename(){
        return "Box";
    }

    /*!Создание нового объекта данного класса.
     * \return указатель на созданный объект.
     */
    static LevelObject* instance(){
        return new Box;
    }
  private:
    /*!Объект, регистрирующий класс на фабрике.
     */
    Registrator<static_typename,instance> creator;
};

//!Класс "Стена".
class Wall:public LevelObject{
  public:

    /*!Конструктор по умолчанию.
     */
    Wall(){
        std::cout<<creator.registeredCount()<<std::endl;        
    }

    /*!Получение имени данного класса.
     * \return имя класса данного объекта("Wall").
     */
    std::string type_name()const{
        return static_typename();
    }

    /*!Статическая функция получения имени класса.
     * \return имя класса данного объекта("Wall").
     */
    static std::string static_typename(){
        return "Wall";
    }
    
    /*!Создание нового объекта данного класса.
     * \return указатель на созданный объект.
     */
    static LevelObject* instance(){
        return new Wall;
    }

    /*!Объект, регистрирующий класс на фабрике.
     */
    Registrator<static_typename,instance> creator;
};

#include "Keeper.h" 
