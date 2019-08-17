////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Definition of some methods for class Subject
/// \author    Sergey Shershakov
/// \version   0.2.0
/// \date      30.01.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
///
////////////////////////////////////////////////////////////////////////////////


#include "subject.h"



namespace xi {

    /** \brief Дружественная оператор-функция вывода объекта в поток вывода.
         *
         *  Конструкция расширяет семантику объекта типа Subject, позволяя его использовать
         *  в потоковых операциях, например со стандартным потоком вывода: \verbatim
            Subject s...
            cout << s;   \endverbatim
         *  \param[in,out] str Поток вывода.
         *  \param[in] subj Константный объект-предмет, для вывода его текстового представления.
         *  \return Функция возвращает тот же поток \c str, чтобы ее можно было использовать ...
         *  <span style='color:orange'>подумать, зачем это нужно.</span>
         */
    std::ostream& operator<<(std::ostream& outs, const Subject& subj)
    {
        outs << subj.name << ": " << subj.title << "\n";

        int index = 0;
        int maxSubj = subj.description.getCapacity();               // добавочка по наводке Данила Кашина

        while (index < maxSubj && subj.description[index] != "")
            outs << subj.description[index++] << "\n";

        return outs;
    }

    /// \brief Дружественная оператор-функция для ввода объекта из потока.
    /// \see Subject::operator<<
    std::istream& operator>>(std::istream& ins, Subject& subj)
    {
        int k = 0; // for strings in safearray
        std::string tmp; // tmp string

        std::getline(ins, subj.name); // reading name
        std::getline(ins, subj.title);  // reading title

        while (std::getline(ins, tmp)){ // reading strings while empty string
            if (tmp.empty())
                return ins;
            subj.description[k++] = tmp;
        }

        return ins;
    }

} // namespace xi

