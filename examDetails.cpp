

#include "examDetails.h"
using std::cout;
using std::endl;
//using mtm::ExamDetails;


namespace mtm    ///////////////inside a namespae ? ?  ?
{

    bool ExamDetails::checkIfHourIsValid(double exam_time)
    {
        int int_time = (int)exam_time;
        double substraction=exam_time-int_time;
        if(substraction == 0.0 || substraction == HALF_HOUR)
        {
            return true;
        }
        return false;
    }

    bool ExamDetails::checkIfDateValid(int day, int month) 
    {
        if(day<MIN_DAY || day>MAX_DAY || month<MIN_MONTH || month>MAX_MONTH)
        {
            return false;
        }
        return true;
    }

    ExamDetails::ExamDetails(int course_num,int month,int day,double exam_time,int length,string exam_link):
            course_num(course_num),month(month),day(day),exam_time(exam_time),length(length),exam_link(exam_link)
    {   

        if(checkIfDateValid(day,month)==false)
        {
            throw InvalidDateException();  
        }

        if(checkIfHourIsValid(exam_time)==false)
        {
            throw InvalidTimeException();
        }
    }

    string ExamDetails::getLink()const
    {
        return this->exam_link;
    }


    void ExamDetails::setLink(const string new_link)
    {
        this->exam_link = new_link;
        return;
    }

    int ExamDetails::operator-(const ExamDetails& exam) const   ////////12 and 1 or 1 and 12  ? ? ?12 and 2 , 2 and 12 ??
    {                                                                    //same year?
        int day_difference = this->day - exam.day;
        int month_difference = this->month - exam.month;
        int difference = day_difference + (month_difference*NUM_DAYS);
        return difference;
    }

    bool ExamDetails::operator<(const ExamDetails& exam)const
    {
        int day_difference = this->operator-(exam);
        if(day_difference<0)
        {
            return true;
        }
        if (day_difference > 0)
        {
            return false;
        }
        if (day_difference == 0)
        {
            if (this->exam_time < exam.exam_time)  //somthing to do with 10^-6???
            {
                return true;
            } 
        }
        return false;
    }


    std::ostream& operator<<(std::ostream& os, const ExamDetails& exam)
    {
        os << "Course Number: " << exam.course_num << endl;
        int integer_part_of_exam_time=(int)exam.exam_time;
        if (exam.exam_time - integer_part_of_exam_time)
        {
            os << "Time: "<< exam.day<<"."<<exam.month <<" at " <<integer_part_of_exam_time<<":30"<<endl; //need const for 30 ??
        }
        else  
        {
            os << "Time: "<< exam.day<<"."<<exam.month <<" at " <<integer_part_of_exam_time<<":00"<<endl;
        }
        os << "Duration: "<<exam.length << ":00"<< endl;   
        os <<"Zoom Link: "<<exam.exam_link<<endl;
        return os;
    }

};