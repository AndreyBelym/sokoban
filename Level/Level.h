#ifndef LEVEL_H
#define LEVEL_H
#include <iostream>
#include "../Core/DataStructures.h"
#include "LevelObject.h"
#include "Field.h"
#include "Board.h"
//! Класс "Игровой уровень"
class Level{
  protected:
    int rows,//!<число строк
        cols;//!<число столбцов
    Board fields;//!<игровая доска(набор игровых полей)
  public:
    /*!Конструктор, задающий размер уровня.
     * \param rows количество строк
     * \param cols количество столбцов
     */
    Level(int rows=0,int cols=0);
    
    /*!Виртуальный деструктор.
     */
    virtual ~Level();

    /*!Отключение от уровня объекта, 
     * находящегося в указанных строке и столбце.
     * \param row строка, в которой находится объект
     * \param col столбец, в котором находится объект
     * \return указатель на отключенный объект
     */
    virtual LevelObject* detachObject(int row,int col);
    
    /*!Отключение от уровня объекта, заданного указателем на него.
     * \param obj
     * \return 
     */
    LevelObject* detachObject(LevelObject *obj);
    
    /*!Добавление на уровень существующего объекта,
     * заданного указателем на него, и размещение его
     * в заданных строке и столбце.
     * \param obj указатель на добавляемый объект
     * \param row строка, куда добавляется объект
     * \param col столбец, куда возвращается объект
     * \return true, если операция выполнена успешно, иначе false. 
     */ 
    virtual bool attachObject(LevelObject *obj,int row, int col);

    /*!Создание и добавление на уровень нового объекта,
     * и размещение его
     * в заданных строке и столбце.
     * \param type_name имя класса нового объекта
     * \param row строка, куда добавляется объект
     * \param col столбец, куда возвращается объект
     * \return true, если операция выполнена успешно, иначе false. 
     */ 
    bool addObject(const std::string& type_name,int row,int col);

    /*!Получение объекта,находящегося в заданных строке и столбце.
     * \param row  строка, в которой находится объект
     * \param col  столбец, в котором находится объект
     * \return указатель на запрошенный объект
     */
    LevelObject* getObject(int row,int col);      

    /*!Удаление объекта, 
     * находящегося в указанных строке и столбце.
     * \param row строка, в которой находится объект
     * \param col столбец, в котором находится объект
     */
    void deleteObject(int row, int col);

    /*!Удаление объекта, заданного указателем на него. 
     * \param obj указатель на удаляемый объект
     */
    void deleteObject(LevelObject* obj);

    /*!Очистка уровня: удаление всех объектов и обнуление размера уровня.
     */
    virtual void clear();
    
    /*!Установка размера уровня.
     * \param rows количество строк
     * \param cols количество столбцов
     */
    void setSize(int rows,int cols);
    
    /*!Замена объекта, находящегося в заданных строке и столбце,
     * на объект, заданный указателем, с возможностью отключения или удаления
     * старого объекта.
     * \param obj указатель на новый объект
     * \param row строка, в которой находится старый объект
     * \param col столбец, в котором находится старый объект
     * \param destroy флаг удаления старого объекта
     * \return указатель на старый объект.
     */
    virtual LevelObject* replaceObject(LevelObject *obj,int row, int col,bool destroy=true);

    /*!Замена объекта, находящегося в заданных строке и столбце,
     * на новый создаваемый по имени заданного типа объект, 
     * с возможностью отключения или удаления старого объекта.
     * \param type_name имя класса нового объекта
     * \param row строка, в которой находится старый объект
     * \param col столбец, в котором находится старый объект
     * \param destroy флаг удаления старого объекта
     * \return указатель на старый объект.
     */
    LevelObject* replaceObject(const std::string& type_name,int row, int col,bool destroy=true);
    
    /*!Перемещение объекта, находящегося в заданных строке и столбце,
     * в новое положение, также задаваемое строкой и столбцом.
     * \param row0 строка, в которой находится объект
     * \param col0 столбец, в котором находится объект
     * \param row строка, в которую перемещается объект
     * \param col столбец, в который перемещается объект
     * \return true, если операция выполнена успешно, иначе false. 
     */
    bool moveObject(int row0,int col0,int row,int col);
    
    /*!Проверка меченых полей: проверка присутствия на каждом меченом поле
     * объекта указанного типа.
     * \param type_name имя класса объектов, стоящих на меченых полях
     * \return true, если объекты заданного класса находятся на всех меченых полях, иначе false.
     */
    bool check(const std::string& type_name);
    
    /*!Установка или снятие метки с указанного поля.
     * \param row строка, в которой находится поле
     * \param col столбец, в котором находится поле
     * \param val флаг метки поля
     * \return true, если операция выполнена успешно, иначе false. 
     */
    virtual bool setMarked(int row,int col,bool val=true);
    
    /*!Проверка, является ли указанное поле меченым.
     * \param row строка, в которой находится поле
     * \param col столбец, в котором находится поле
     * \return флаг метки поля.
     */
    bool isMarked(int row,int col);
    
    /*!Получение размера уровня.
     * \param r текущее количество строк
     * \param c текущее количество столбцов
     */
    void getSize(int &r,int& c);
    
    /*!Получение объекта, относящегося к заданному типу.
     * Возвращается первый найденный объект.
     * \param type_name имя класса искомого объекта
     * \return указатель на найденный объект.
     */
    LevelObject* getObject(const std::string& type_name);

    /*!Сохранение уровня: вывод уровня в поток.
     * \param os поток вывода
     * \return измененный поток вывода
     */      
    virtual std::ostream& save(std::ostream& os);
    
    /*!Загрузка уровня: ввод уровня из потока.
     * \param is поток ввода
     * \return измененный поток ввода
     */
    virtual std::istream& load(std::istream& is);
    
    /*!Оператор вывода уровня в поток.
     * \param os поток вывода
     * \param lvl выводимый уровень
     * \return измененный поток вывода
     */
    friend std::ostream& operator<<(std::ostream& os,Level& lvl);
    
    /*!Оператор ввода уровня из потока.
     * \param is поток ввода
     * \param lvl загружаемый уровень
     * \return измененный поток ввода
     */
    friend std::istream& operator>>(std::istream& is,Level& lvl);
    
    /*!Загрузка уровня из указанного файла.
     * \param filename имя файла, из которого загружается уровень
     */
    void loadLevel(const char* filename);
    
    /*!Сохранение уровня в указанный файл.
     * \param filename имя файла, в который сохраняется уровень
     */
    void saveLevel(const char* filename);
    
    /*!Проверка допустимости координаты, задаваемой строком и столбцом.
     * \param row номер строки
     * \param col номер столбца
     * \return true, если данная координата допустима, иначе false.
     */
    bool isValid(int row,int col);
    
    /*!Проверка целостности уровня.
     * \return true, если уровень находится в допустимом сотоянии, иначе false.
     */
    virtual bool validate();
};
#endif //LEVEL_H
