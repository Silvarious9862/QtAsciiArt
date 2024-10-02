#ifndef MYMATRIX_H
#define MYMATRIX_H

#include <vector>
#include <string>
#include <iostream>

template<typename T>
class Matrix
{
public:
    struct iterator
    {
    public:
        iterator(Matrix& matrix, int quality) :
            beginX(0), beginY(0), it_matrix(&matrix),
            step(11 - quality) {}

        iterator& operator++(int)
        {
            beginX += step;
            if (beginX >= it_matrix->getCols()) {
                beginX = 0;
                beginY += step;
                rowDone = true;
            }
            if (beginY >= it_matrix->getRows()) {
                beginX = 0;
                beginY = 0;
                fullDone = true;
            }
            return *this;
        }


        int getBeginX() const {return beginX; }
        int getBeginY() const {return beginY; }
        int getStep() const { return step; }
        Matrix* getMatrix() const {return it_matrix; }

        void setStep(int step) { this->step = step; }

        bool checkRowDone() const { return rowDone; }
        bool checkFullDone() const { return fullDone; }

        void unsetRowDone() { rowDone = false; }

    private:
        Matrix* it_matrix;
        int beginX{};
        int beginY{};
        int step{};
        bool rowDone = false;
        bool fullDone = false;
    };

    Matrix(unsigned rows = 0, unsigned cols = 1)  {
        m_rowSize = rows;
        m_colSize = cols;
        m_matrix.resize(m_rowSize);
        for(auto& elem : m_matrix)
            elem.resize(m_colSize);
    }
    ~Matrix()
    {
        for(auto& elem : m_matrix)
            elem.clear();
        m_matrix.clear();
    }
    T& operator()(const unsigned& row, const unsigned& col)
    {
        return this->m_matrix[row][col];
    }

    void print()
    {
        std::cout << "Matrix:\n" << this->toString();
    }

    std::string toString()
    {
        std::string output = "";
        for (unsigned i = 0; i < m_rowSize; i++) {
            for (unsigned j = 0; j < m_colSize; j++) {
                output += this->m_matrix[i][j];
            }
            output+='\n';
        }
        return output;
    }
    unsigned getRows()
    {
        return this->m_rowSize;
    }

    unsigned getCols()
    {
        return this->m_colSize;
    }

    double countAvg(iterator& it)
    {
        if (it.getStep() == -4) it.setStep(15);
        double avg = 0;
        int count = 0;
        int y = 0;
        int x = 0;
        for (y = it.getBeginY(); (y < it.getBeginY() + it.getStep()) && (y < it.getMatrix()->getRows()); y++) {     // for rows
            for (x = it.getBeginX(); (x < it.getBeginX() + it.getStep()) && x < it.getMatrix()->getCols(); x++) {	// for elems
                avg += (*it.getMatrix())(y, x);
                count++;
            }
        }
        return avg / count;
    }

    void push(unsigned row, unsigned col, T value)
    {
        while(this->m_matrix.size() <= row) {
            this->m_matrix.emplace_back(1);
            this->m_rowSize++;
        }
        while(this->m_matrix.at(row).size() <= col) {
            this->m_matrix.at(row).emplace_back(1);
            if(this->m_matrix.size() == 1) this->m_colSize++; }
        m_matrix.at(row).at(col) = value;

    }

private:
    unsigned m_rowSize;
    unsigned m_colSize;
    std::vector<std::vector<T> > m_matrix;
};
#endif // MYMATRIX_H
