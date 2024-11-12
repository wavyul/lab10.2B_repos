#include "pch.h"
#include "CppUnitTest.h"
#include "../LB10.2_B/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(StudentAverageEvaluationTest)
        {
            Students student;

            student.speciality = KN;
            student.grade_math = 4;
            student.grade_physics = 3;
            student.grade_program = 5;

            double resultKN = student_avarage_evaluation(&student, 0);
            Assert::AreEqual(4.0, resultKN, L"KN specialization average evaluation is incorrect");

            student.speciality = ITIS;
            student.grade_nm = 2;

            double resultITIS = student_avarage_evaluation(&student, 0);
            Assert::AreEqual(3.0, resultITIS, L"ITIS specialization average evaluation is incorrect");

            student.speciality = TN;
            student.grade_ped = 4;

            double resultOther = student_avarage_evaluation(&student, 0);
            Assert::AreEqual(3.66667, resultOther, 0.00001, L"Other specialization average evaluation is incorrect");
        }

    };
}
