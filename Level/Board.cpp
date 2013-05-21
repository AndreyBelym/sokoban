#include "Board.h"
void Board::setRows(size_t rows){
    int dr=rows-rows_;
    cout<<"Board::setRows(int)!"<<endl;        
    Table::setRows(rows);
    for(int i=rows_-dr;i<rows_;++i)
        for(int j=0;j<cols_;++j){
            at(i,j).setRow(i);
            at(i,j).setCol(j);
        }
    cout<<"Board::setRows(int)!"<<endl;        
}
void Board::setCols(size_t cols){
    int dc=cols-cols_;
    cout<<"Board::setCols(int)!"<<endl;        
    Table::setCols(cols);
    for(int i=0;i<rows_;++i)
        for(int j=cols_-dc;j<cols_;++j){
            at(i,j).setRow(i);
            at(i,j).setCol(j);
        }
    cout<<"Board::setCols(int)!"<<endl;        
}
void Board::setSize(size_t rows,size_t cols){
    setRows(rows);
    setCols(cols);
    cout<<"Board::setSize(int,int)!"<<endl;        
    
}
