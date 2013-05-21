#ifndef KEEPER_H
#define KEEPER_H
#include "LevelObjectFactory.h"
#include "Registrator.h"

//!Класс "Кладовщик" (англ. Warehouse keeper, яп. Sokoban).
class Keeper:public LevelObject{
    /*!Перемещение от текущего положения на указанное количество строк и столбцов.
     * \param dx смещение по столбцам
     * \param dy смещение по строкам
     */
    void move(int dx,int dy);
  public:

    /*!Конструктор по умолчанию.
     */
    Keeper(){
        std::cout<<creator.registeredCount()<<std::endl;
    }

    /*!Деструктор.
     */
    ~Keeper(){
        std::cout<<"destructor"<<std::endl;
    }

    /*!Создание нового объекта данного класса.
     * \return указатель на созданный объект
     */
    static LevelObject* instance(){return new Keeper;}      
    
    /*!Получение имени данного класса.
     * \return имя класса данного объекта("Keeper").
     */
    std::string type_name()const{return static_typename();}
    
    /*!Статическая функция получения имени класса.
     * \return имя класса данного объекта("Keeper").
     */
    static std::string static_typename(){return "Keeper";}
    
    /*!Перемещение влево.
     */
    void moveLeft(){move(-1,0);}
    
    /*!Перемещение врпаво.
     */
    void moveRight(){move(1,0);}
    
    /*!Перемещение вверх.
     */
    void moveUp(){move(0,-1);}
    
    /*!Перемещение вниз.
     */
    void moveDown(){move(0,1);}
    
  private:
    /*!Объект, регистрирующий класс на фабрике.
     */
    Registrator<static_typename,instance> creator;
}; 


#endif //KEEPER_H
