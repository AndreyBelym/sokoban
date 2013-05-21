#pragma once
#include "LevelObjectFactory.h"

//!Вспомогательный класс регистрации на фабрике. 
template <LevelObjectFactory::TypeNameFuncPtr type_name,
          LevelObjectFactory::CreatorFuncPtr creator>
class NestedRegistrator{
  public:  
    /*!Конструктор
     */
    NestedRegistrator(){
        registered=LevelObjectFactory::registerType(type_name(),creator);
        count=0;
    }
    bool registered;//!<флаг состояния регистрации класса.
    unsigned count;//!<количество объектов класса
};

//!Класс регистрации на фабрике.
template <LevelObjectFactory::TypeNameFuncPtr type_name,
         LevelObjectFactory::CreatorFuncPtr creator>
class Registrator{
  public:
      //!Конструктор по умолчанию.
      Registrator(){
          reg.count++;
      }
      /*!Конструктор копирования.
       * \param other игнорируется
       */
      Registrator(const Registrator &other){
          reg.count++;
      }
      //!Деструктор
      ~Registrator(){
          reg.count--;
      }
      /*!Получение количества зарегистрированных объектов.
       * \return количество объектов данного класса
       */
      unsigned registeredCount(){return reg.count;}
  private:
    //!Статический вспомогательный объект регистрации на фабрике.
    static NestedRegistrator<type_name,creator> reg;
};    

template <LevelObjectFactory::TypeNameFuncPtr type_name,
         LevelObjectFactory::CreatorFuncPtr creator>
NestedRegistrator<type_name,creator>
       Registrator<type_name,creator>::reg; 
